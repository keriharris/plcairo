/*  This file is part of PLcairo.

    Copyright (C) 2015 Keri Harris <keri@gentoo.org>

    PLcairo is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 2.1
    of the License, or (at your option) any later version.

    PLcairo is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PLcairo.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "plcairo.h"


/* cairo_path_t */
static atom_t ATOM_cairo_path_data_type_move_to = 0;
static atom_t ATOM_cairo_path_data_type_line_to = 0;
static atom_t ATOM_cairo_path_data_type_curve_to = 0;
static atom_t ATOM_cairo_path_data_type_close_path = 0;

cairo_bool_t
cairo_term_to_path_data_point(term_t t_point, cairo_path_data_t *data)
{
  term_t t_x = PL_new_term_ref();
  term_t t_y = PL_new_term_ref();
  double x, y;
  atom_t a;
  int arity;

  atom_t ATOM_comma = PL_new_atom(",");

  if ( !( PL_get_name_arity(t_point, &a, &arity) &&
          (a == ATOM_comma) && (arity == 2) ) )
  { return PL_type_error("CairoPoint", t_point);
  }

  _PL_get_arg(1, t_point, t_x);
  _PL_get_arg(2, t_point, t_y);
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;

  data->point.x = x;
  data->point.y = y;

  return TRUE;
}

cairo_bool_t
cairo_path_data_point_to_term(cairo_path_data_t *data, term_t t)
{
  term_t t_point = PL_new_term_ref();
  term_t t_x = PL_new_term_ref();
  term_t t_y = PL_new_term_ref();
  functor_t f_comma = PL_new_functor(PL_new_atom(","), 2);

  if ( !plcairo_double_to_term(data->point.x, t_x) ) return FALSE;
  if ( !plcairo_double_to_term(data->point.y, t_y) ) return FALSE;
  if ( !PL_cons_functor(t_point, f_comma, t_x, t_y) ) return FALSE;

  return PL_unify(t, t_point);
}

cairo_bool_t
plcairo_term_to_path(term_t         t,
                     cairo_path_t **path)
{
  term_t list = PL_copy_term_ref(t);
  term_t head = PL_new_term_ref();
  cairo_path_t *path0;
  cairo_path_data_t *path_data;
  size_t num_data;
  int i = 0;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_path_t: %p", t, *path);

  if ( PL_skip_list(list, 0, &num_data) != PL_LIST )
  { return PL_type_error("list", t);
  }

  if ( !ATOM_cairo_path_data_type_move_to )
  {
    ATOM_cairo_path_data_type_move_to = PL_new_atom("CAIRO_PATH_MOVE_TO");
    ATOM_cairo_path_data_type_line_to = PL_new_atom("CAIRO_PATH_LINE_TO");
    ATOM_cairo_path_data_type_curve_to = PL_new_atom("CAIRO_PATH_CURVE_TO");
    ATOM_cairo_path_data_type_close_path = PL_new_atom("CAIRO_PATH_CLOSE_PATH");
  }

  path0 = g_malloc0(sizeof(cairo_path_t));
  path_data = g_malloc0_n(num_data, sizeof(cairo_path_data_t));

  path0->status = CAIRO_STATUS_SUCCESS;
  path0->data = path_data;
  path0->num_data = num_data;

  while ( PL_get_list(list, head, list) )
  {
    cairo_path_data_t *data = path_data + i++;
    cairo_path_data_type_t type = data->header.type;

    if ( !plcairo_term_to_path_data_type(head, &type) ) goto error;
    data->header.type = type;

    if ( type == CAIRO_PATH_MOVE_TO )
    {
      data->header.length = 2;

      if ( !PL_get_list(list, head, list) )
      { plgi_raise_error("Missing CairoPoint in CairoPath after CAIRO_PATH_MOVE_TO");
        goto error;
      }
      if ( !cairo_term_to_path_data_point(head, data + 1) ) goto error;
    }

    else if ( type == CAIRO_PATH_LINE_TO )
    {
      data->header.length = 2;

      if ( !PL_get_list(list, head, list) )
      { plgi_raise_error("Missing CairoPoint in CairoPath after CAIRO_PATH_LINE_TO");
        goto error;
      }
      if ( !cairo_term_to_path_data_point(head, data + 1) ) goto error;
    }

    else if ( type == CAIRO_PATH_CURVE_TO )
    {
      data->header.length = 4;

      if ( !PL_get_list(list, head, list) )
      { plgi_raise_error("Missing 1st CairoPoint in CairoPath after CAIRO_PATH_CURVE_TO");
        goto error;
      }
      if ( !cairo_term_to_path_data_point(head, data + 1) ) goto error;

      if ( !PL_get_list(list, head, list) )
      { plgi_raise_error("Missing 2nd CairoPoint in CairoPath after CAIRO_PATH_CURVE_TO");
        goto error;
      }
      if ( !cairo_term_to_path_data_point(head, data + 2) ) goto error;

      if ( !PL_get_list(list, head, list) )
      { plgi_raise_error("Missing 3rd CairoPoint in CairoPath after CAIRO_PATH_CURVE_TO");
        goto error;
      }
      if ( !cairo_term_to_path_data_point(head, data + 3) ) goto error;
    }

    else if ( type == CAIRO_PATH_CLOSE_PATH )
    {
      data->header.length = 1;
    }

    else
    { return PL_domain_error("CairoPathHeader", head);
    }
  }

  *path = path0;

  return TRUE;

error:

  g_free(path0);
  g_free(path_data);

  return FALSE;
}

cairo_bool_t
plcairo_path_to_term(cairo_path_t *path,
                     term_t         t)
{
  term_t t0 = PL_new_term_ref();
  term_t list = PL_copy_term_ref(t0);
  term_t head = PL_new_term_ref();
  int i;

  PLCAIRO_debug("    cairo_path_t: %p  --->  term: 0x%lx", path, t);

  if ( path->status != CAIRO_STATUS_SUCCESS )
  { return plcairo_raise_error_status(path->status);
  }

  for ( i = 0; i < path->num_data; i += path->data[i].header.length )
  {
    cairo_path_data_t *data = path->data + i;
    cairo_path_data_type_t type = data->header.type;
    term_t t_header = PL_new_term_ref();

    if ( !plcairo_path_data_type_to_term(type, t_header) ) return FALSE;
    if ( !(PL_unify_list(list, head, list) &&
           PL_unify(head, t_header)) )
    { return FALSE;
    }

    if ( type == CAIRO_PATH_MOVE_TO )
    { term_t t_point = PL_new_term_ref();

      if ( !cairo_path_data_point_to_term(data + 1, t_point) ) return FALSE;
      if ( !(PL_unify_list(list, head, list) &&
             PL_unify(head, t_point)) )
      { return FALSE;
      }
    }

    else if ( type == CAIRO_PATH_LINE_TO )
    { term_t t_point = PL_new_term_ref();

      if ( !cairo_path_data_point_to_term(data + 1, t_point) ) return FALSE;
      if ( !(PL_unify_list(list, head, list) &&
             PL_unify(head, t_point)) )
      { return FALSE;
      }
    }

    else if ( type == CAIRO_PATH_CURVE_TO )
    { term_t t_point = PL_new_term_ref();

      if ( !cairo_path_data_point_to_term(data + 1, t_point) ) return FALSE;
      if ( !(PL_unify_list(list, head, list) &&
             PL_unify(head, t_point)) )
      { return FALSE;
      }

      if ( !cairo_path_data_point_to_term(data + 2, t_point) ) return FALSE;
      if ( !(PL_unify_list(list, head, list) &&
             PL_unify(head, t_point)) )
      { return FALSE;
      }

      if ( !cairo_path_data_point_to_term(data + 3, t_point) ) return FALSE;
      if ( !(PL_unify_list(list, head, list) &&
             PL_unify(head, t_point)) )
      { return FALSE;
      }
    }

    else if ( type == CAIRO_PATH_CLOSE_PATH )
    {
    }

    else
    { g_assert_not_reached();
    }
  }

  if ( !PL_unify_nil(list) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}


/* cairo_path_data_type_t */
static atom_t ATOM_cairo_path_move_to = 0;
static atom_t ATOM_cairo_path_line_to = 0;
static atom_t ATOM_cairo_path_curve_to = 0;
static atom_t ATOM_cairo_path_close_path = 0;

cairo_bool_t
plcairo_term_to_path_data_type(term_t                  t,
                               cairo_path_data_type_t *type)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_path_data_type_t: %p", t, type);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoPathDataType", t);
  }

  if ( !ATOM_cairo_path_move_to )
  {
    ATOM_cairo_path_move_to = PL_new_atom("CAIRO_PATH_MOVE_TO");
    ATOM_cairo_path_line_to = PL_new_atom("CAIRO_PATH_LINE_TO");
    ATOM_cairo_path_curve_to = PL_new_atom("CAIRO_PATH_CURVE_TO");
    ATOM_cairo_path_close_path = PL_new_atom("CAIRO_PATH_CLOSE_PATH");
  }

  if ( a == ATOM_cairo_path_move_to )
  { *type = CAIRO_PATH_MOVE_TO;
  }
  else if ( a == ATOM_cairo_path_line_to )
  { *type = CAIRO_PATH_LINE_TO;
  }
  else if ( a == ATOM_cairo_path_curve_to )
  { *type = CAIRO_PATH_CURVE_TO;
  }
  else if ( a == ATOM_cairo_path_close_path )
  { *type = CAIRO_PATH_CLOSE_PATH;
  }
  else
  { return PL_domain_error("CairoPathDataType", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_path_data_type_to_term(cairo_path_data_type_t type,
                               term_t                 t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_path_data_type_t: %d  --->  term: 0x%lx", type, t);

  if ( !ATOM_cairo_path_move_to )
  {
    ATOM_cairo_path_move_to = PL_new_atom("CAIRO_PATH_MOVE_TO");
    ATOM_cairo_path_line_to = PL_new_atom("CAIRO_PATH_LINE_TO");
    ATOM_cairo_path_curve_to = PL_new_atom("CAIRO_PATH_CURVE_TO");
    ATOM_cairo_path_close_path = PL_new_atom("CAIRO_PATH_CLOSE_PATH");
  }

  if ( type == CAIRO_PATH_MOVE_TO )
  { PL_put_atom(t0, ATOM_cairo_path_move_to);
  }
  else if ( type == CAIRO_PATH_LINE_TO )
  { PL_put_atom(t0, ATOM_cairo_path_line_to);
  }
  else if ( type == CAIRO_PATH_CURVE_TO )
  { PL_put_atom(t0, ATOM_cairo_path_curve_to);
  }
  else if ( type == CAIRO_PATH_CLOSE_PATH )
  { PL_put_atom(t0, ATOM_cairo_path_close_path);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLGI_PRED_IMPL(plcairo_append_path)
{
  term_t t_cr = FA0;
  term_t t_path = FA1;

  cairo_t *cr;
  cairo_path_t *path;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_path(t_path, &path) ) return FALSE;

  cairo_append_path(cr, path);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}

PLGI_PRED_IMPL(plcairo_arc)
{
  term_t t_cr = FA0;
  term_t t_xc = FA1;
  term_t t_yc = FA2;
  term_t t_radius = FA3;
  term_t t_angle1 = FA4;
  term_t t_angle2 = FA5;

  cairo_t *cr;
  double xc, yc, radius, angle1, angle2;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_xc, &xc) ) return FALSE;
  if ( !plcairo_term_to_double(t_yc, &yc) ) return FALSE;
  if ( !plcairo_term_to_double(t_radius, &radius) ) return FALSE;
  if ( !plcairo_term_to_double(t_angle1, &angle1) ) return FALSE;
  if ( !plcairo_term_to_double(t_angle2, &angle2) ) return FALSE;

  cairo_arc(cr, xc, yc, radius, angle1, angle2);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_arc_negative)
{
  term_t t_cr = FA0;
  term_t t_xc = FA1;
  term_t t_yc = FA2;
  term_t t_radius = FA3;
  term_t t_angle1 = FA4;
  term_t t_angle2 = FA5;

  cairo_t *cr;
  double xc, yc, radius, angle1, angle2;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_xc, &xc) ) return FALSE;
  if ( !plcairo_term_to_double(t_yc, &yc) ) return FALSE;
  if ( !plcairo_term_to_double(t_radius, &radius) ) return FALSE;
  if ( !plcairo_term_to_double(t_angle1, &angle1) ) return FALSE;
  if ( !plcairo_term_to_double(t_angle2, &angle2) ) return FALSE;

  cairo_arc_negative(cr, xc, yc, radius, angle1, angle2);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_close_path)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_close_path(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_copy_path)
{
  term_t t_cr = FA0;
  term_t t_path = FA1;

  cairo_t *cr;
  cairo_path_t *path;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  path = cairo_copy_path(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_path_to_term(path, t_path) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_copy_path_flat)
{
  term_t t_cr = FA0;
  term_t t_path = FA1;

  cairo_t *cr;
  cairo_path_t *path;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  path = cairo_copy_path_flat(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_path_to_term(path, t_path) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_curve_to)
{
  term_t t_cr = FA0;
  term_t t_x1 = FA1;
  term_t t_y1 = FA2;
  term_t t_x2 = FA3;
  term_t t_y2 = FA4;
  term_t t_x3 = FA5;
  term_t t_y3 = FA6;

  cairo_t *cr;
  double x1, y1, x2, y2, x3, y3;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_x1, &x1) ) return FALSE;
  if ( !plcairo_term_to_double(t_y1, &y1) ) return FALSE;
  if ( !plcairo_term_to_double(t_x2, &x2) ) return FALSE;
  if ( !plcairo_term_to_double(t_y2, &y2) ) return FALSE;
  if ( !plcairo_term_to_double(t_x3, &x3) ) return FALSE;
  if ( !plcairo_term_to_double(t_y3, &y3) ) return FALSE;

  cairo_curve_to(cr, x1, y1, x2, y2, x3, y3);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_get_current_point)
{
  term_t t_cr = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;

  cairo_t *cr;
  double x, y;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_get_current_point(cr, &x, &y);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_double_to_term(x, t_x) ) return FALSE;
  if ( !plcairo_double_to_term(y, t_y) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_glyph_path)
{
  term_t t_cr = FA0;
  term_t t_glyphs = FA1;

  cairo_t *cr;
  cairo_glyph_t *glyphs;
  int num_glyphs;
  size_t len;
  int i = 0;
  term_t list = PL_copy_term_ref(t_glyphs);
  term_t head = PL_new_term_ref();

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  if ( PL_skip_list(t_glyphs, 0, &len) != PL_LIST )
  { return PL_type_error("list", t_glyphs);
  }

  num_glyphs = len;
  glyphs = g_malloc0_n(num_glyphs, sizeof(cairo_glyph_t));

  while ( PL_get_list(list, head, list) )
  { cairo_glyph_t *glyph = glyphs + i++;
    if ( !plcairo_term_to_glyph(head, &glyph) )
    { g_free(glyphs);
      return FALSE;
    }
  }

  cairo_glyph_path(cr, glyphs, num_glyphs);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_has_current_point)
{
  term_t t_cr = FA0;

  cairo_t *cr;
  cairo_bool_t ret;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  ret = cairo_has_current_point(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return (ret != 0);
}


PLGI_PRED_IMPL(plcairo_line_to)
{
  term_t t_cr = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;

  cairo_t *cr;
  double x, y;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;

  cairo_line_to(cr, x, y);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_move_to)
{
  term_t t_cr = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;

  cairo_t *cr;
  double x, y;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;

  cairo_move_to(cr, x, y);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_new_path)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_new_path(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_new_sub_path)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_new_sub_path(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_path_extents)
{
  term_t t_cr = FA0;
  term_t t_x1 = FA1;
  term_t t_y1 = FA2;
  term_t t_x2 = FA3;
  term_t t_y2 = FA4;

  cairo_t *cr;
  double x1, y1, x2, y2;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_path_extents(cr, &x1, &y1, &x2, &y2);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_double_to_term(x1, t_x1) ) return FALSE;
  if ( !plcairo_double_to_term(y1, t_y1) ) return FALSE;
  if ( !plcairo_double_to_term(x2, t_x2) ) return FALSE;
  if ( !plcairo_double_to_term(y2, t_y2) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_rectangle)
{
  term_t t_cr = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;
  term_t t_width = FA3;
  term_t t_height = FA4;

  cairo_t *cr;
  double x, y, width, height;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;
  if ( !plcairo_term_to_double(t_width, &width) ) return FALSE;
  if ( !plcairo_term_to_double(t_height, &height) ) return FALSE;

  cairo_rectangle(cr, x, y, width, height);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_rel_curve_to)
{
  term_t t_cr = FA0;
  term_t t_dx1 = FA1;
  term_t t_dy1 = FA2;
  term_t t_dx2 = FA3;
  term_t t_dy2 = FA4;
  term_t t_dx3 = FA5;
  term_t t_dy3 = FA6;

  cairo_t *cr;
  double dx1, dy1, dx2, dy2, dx3, dy3;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_dx1, &dx1) ) return FALSE;
  if ( !plcairo_term_to_double(t_dy1, &dy1) ) return FALSE;
  if ( !plcairo_term_to_double(t_dx2, &dx2) ) return FALSE;
  if ( !plcairo_term_to_double(t_dy2, &dy2) ) return FALSE;
  if ( !plcairo_term_to_double(t_dx3, &dx3) ) return FALSE;
  if ( !plcairo_term_to_double(t_dy3, &dy3) ) return FALSE;

  cairo_rel_curve_to(cr, dx1, dy1, dx2, dy2, dx3, dy3);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_rel_line_to)
{
  term_t t_cr = FA0;
  term_t t_dx = FA1;
  term_t t_dy = FA2;

  cairo_t *cr;
  double dx, dy;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_dx, &dx) ) return FALSE;
  if ( !plcairo_term_to_double(t_dy, &dy) ) return FALSE;

  cairo_rel_line_to(cr, dx, dy);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_rel_move_to)
{
  term_t t_cr = FA0;
  term_t t_dx = FA1;
  term_t t_dy = FA2;

  cairo_t *cr;
  double dx, dy;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_dx, &dx) ) return FALSE;
  if ( !plcairo_term_to_double(t_dy, &dy) ) return FALSE;

  cairo_rel_move_to(cr, dx, dy);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_text_path)
{
  term_t t_cr = FA0;
  term_t t_text = FA1;

  cairo_t *cr;
  char *text;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_string(t_text, &text) ) return FALSE;

  cairo_text_path(cr, text);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}
