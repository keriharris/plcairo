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


/* cairo_pattern_t */
cairo_bool_t
plcairo_term_to_pattern(term_t            t,
                        cairo_pattern_t **pattern)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_pattern_t: %p", t, *pattern);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoPattern", t);
  }

  if ( blob->gtype != G_TYPE_NONE &&
       !g_type_is_a( blob->gtype, CAIRO_GOBJECT_TYPE_PATTERN ) )
  { return PL_type_error("CairoPattern", t);
  }

  *pattern = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_pattern_to_term(cairo_pattern_t *pattern,
                        term_t           t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_pattern_t: %p  --->  term: 0x%lx", pattern, t);

  if ( !pattern )
  { return ( plgi_put_null(t0) && PL_unify(t, t0) );
  }

  data = pattern;
  blob_type = PLGI_BLOB_BOXED;

  if ( !plgi_put_blob(blob_type, CAIRO_GOBJECT_TYPE_PATTERN,
                      PL_new_atom("CairoPattern"), TRUE, data, t0) )
  { return FALSE;
  }

  return PL_unify(t, t0);;
}


/* cairo_extend_t */
static atom_t ATOM_cairo_extend_none = 0;
static atom_t ATOM_cairo_extend_repeat = 0;
static atom_t ATOM_cairo_extend_reflect = 0;
static atom_t ATOM_cairo_extend_pad = 0;

cairo_bool_t
plcairo_term_to_extend(term_t          t,
                       cairo_extend_t *extend)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_extend_t: %p", t, extend);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoExtend", t);
  }

  if ( !ATOM_cairo_extend_none )
  {
    ATOM_cairo_extend_none = PL_new_atom("CAIRO_EXTEND_NONE");
    ATOM_cairo_extend_repeat = PL_new_atom("CAIRO_EXTEND_REPEAT");
    ATOM_cairo_extend_reflect = PL_new_atom("CAIRO_EXTEND_REFLECT");
    ATOM_cairo_extend_pad = PL_new_atom("CAIRO_EXTEND_PAD");
  }

  if ( a == ATOM_cairo_extend_none )
  { *extend = CAIRO_EXTEND_NONE;
  }
  else if ( a == ATOM_cairo_extend_repeat )
  { *extend = CAIRO_EXTEND_REPEAT;
  }
  else if ( a == ATOM_cairo_extend_reflect )
  { *extend = CAIRO_EXTEND_REFLECT;
  }
  else if ( a == ATOM_cairo_extend_pad )
  { *extend = CAIRO_EXTEND_PAD;
  }
  else
  { return PL_domain_error("CairoExtend", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_extend_to_term(cairo_extend_t extend,
                       term_t         t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_extend_t: %d  --->  term: 0x%lx", extend, t);

  if ( !ATOM_cairo_extend_none )
  {
    ATOM_cairo_extend_none = PL_new_atom("CAIRO_EXTEND_NONE");
    ATOM_cairo_extend_repeat = PL_new_atom("CAIRO_EXTEND_REPEAT");
    ATOM_cairo_extend_reflect = PL_new_atom("CAIRO_EXTEND_REFLECT");
    ATOM_cairo_extend_pad = PL_new_atom("CAIRO_EXTEND_PAD");
  }

  if ( extend == CAIRO_EXTEND_NONE )
  { PL_put_atom(t0, ATOM_cairo_extend_none);
  }
  else if ( extend == CAIRO_EXTEND_REPEAT )
  { PL_put_atom(t0, ATOM_cairo_extend_repeat);
  }
  else if ( extend == CAIRO_EXTEND_REFLECT )
  { PL_put_atom(t0, ATOM_cairo_extend_reflect);
  }
  else if ( extend == CAIRO_EXTEND_PAD )
  { PL_put_atom(t0, ATOM_cairo_extend_pad);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}


/* cairo_filter_t */
static atom_t ATOM_cairo_filter_fast = 0;
static atom_t ATOM_cairo_filter_good = 0;
static atom_t ATOM_cairo_filter_best = 0;
static atom_t ATOM_cairo_filter_nearest = 0;
static atom_t ATOM_cairo_filter_bilinear = 0;
static atom_t ATOM_cairo_filter_gaussian = 0;

cairo_bool_t
plcairo_term_to_filter(term_t          t,
                       cairo_filter_t *filter)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_filter_t: %p", t, filter);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoFilter", t);
  }

  if ( !ATOM_cairo_filter_fast )
  {
    ATOM_cairo_filter_fast = PL_new_atom("CAIRO_FILTER_FAST");
    ATOM_cairo_filter_good = PL_new_atom("CAIRO_FILTER_GOOD");
    ATOM_cairo_filter_best = PL_new_atom("CAIRO_FILTER_BEST");
    ATOM_cairo_filter_nearest = PL_new_atom("CAIRO_FILTER_NEAREST");
    ATOM_cairo_filter_bilinear = PL_new_atom("CAIRO_FILTER_BILINEAR");
    ATOM_cairo_filter_gaussian = PL_new_atom("CAIRO_FILTER_GAUSSIAN");
  }

  if ( a == ATOM_cairo_filter_fast )
  { *filter = CAIRO_FILTER_FAST;
  }
  else if ( a == ATOM_cairo_filter_good )
  { *filter = CAIRO_FILTER_GOOD;
  }
  else if ( a == ATOM_cairo_filter_best )
  { *filter = CAIRO_FILTER_BEST;
  }
  else if ( a == ATOM_cairo_filter_nearest )
  { *filter = CAIRO_FILTER_NEAREST;
  }
  else if ( a == ATOM_cairo_filter_bilinear )
  { *filter = CAIRO_FILTER_BILINEAR;
  }
  else if ( a == ATOM_cairo_filter_gaussian )
  { *filter = CAIRO_FILTER_GAUSSIAN;
  }
  else
  { return PL_domain_error("CairoFilter", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_filter_to_term(cairo_filter_t filter,
                       term_t         t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_filter_t: %d  --->  term: 0x%lx", filter, t);

  if ( !ATOM_cairo_filter_fast )
  {
    ATOM_cairo_filter_fast = PL_new_atom("CAIRO_FILTER_FAST");
    ATOM_cairo_filter_good = PL_new_atom("CAIRO_FILTER_GOOD");
    ATOM_cairo_filter_best = PL_new_atom("CAIRO_FILTER_BEST");
    ATOM_cairo_filter_nearest = PL_new_atom("CAIRO_FILTER_NEAREST");
    ATOM_cairo_filter_bilinear = PL_new_atom("CAIRO_FILTER_BILINEAR");
    ATOM_cairo_filter_gaussian = PL_new_atom("CAIRO_FILTER_GAUSSIAN");
  }

  if ( filter == CAIRO_FILTER_FAST )
  { PL_put_atom(t0, ATOM_cairo_filter_fast);
  }
  else if ( filter == CAIRO_FILTER_GOOD )
  { PL_put_atom(t0, ATOM_cairo_filter_good);
  }
  else if ( filter == CAIRO_FILTER_BEST )
  { PL_put_atom(t0, ATOM_cairo_filter_best);
  }
  else if ( filter == CAIRO_FILTER_NEAREST )
  { PL_put_atom(t0, ATOM_cairo_filter_nearest);
  }
  else if ( filter == CAIRO_FILTER_BILINEAR )
  { PL_put_atom(t0, ATOM_cairo_filter_bilinear);
  }
  else if ( filter == CAIRO_FILTER_GAUSSIAN )
  { PL_put_atom(t0, ATOM_cairo_filter_gaussian);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}


/* cairo_pattern_type_t */
static atom_t ATOM_cairo_pattern_type_solid = 0;
static atom_t ATOM_cairo_pattern_type_surface = 0;
static atom_t ATOM_cairo_pattern_type_linear = 0;
static atom_t ATOM_cairo_pattern_type_radial = 0;
static atom_t ATOM_cairo_pattern_type_mesh = 0;
static atom_t ATOM_cairo_pattern_type_raster_source = 0;

cairo_bool_t
plcairo_term_to_pattern_type(term_t                t,
                             cairo_pattern_type_t *pattern_type)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_pattern_type_t: %p", t, pattern_type);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoPatternType", t);
  }

  if ( !ATOM_cairo_pattern_type_solid )
  {
    ATOM_cairo_pattern_type_solid = PL_new_atom("CAIRO_PATTERN_TYPE_SOLID");
    ATOM_cairo_pattern_type_surface = PL_new_atom("CAIRO_PATTERN_TYPE_SURFACE");
    ATOM_cairo_pattern_type_linear = PL_new_atom("CAIRO_PATTERN_TYPE_LINEAR");
    ATOM_cairo_pattern_type_radial = PL_new_atom("CAIRO_PATTERN_TYPE_RADIAL");
    ATOM_cairo_pattern_type_mesh = PL_new_atom("CAIRO_PATTERN_TYPE_MESH");
    ATOM_cairo_pattern_type_raster_source = PL_new_atom("CAIRO_PATTERN_TYPE_RASTER_SOURCE");
  }

  if ( a == ATOM_cairo_pattern_type_solid )
  { *pattern_type = CAIRO_PATTERN_TYPE_SOLID;
  }
  else if ( a == ATOM_cairo_pattern_type_surface )
  { *pattern_type = CAIRO_PATTERN_TYPE_SURFACE;
  }
  else if ( a == ATOM_cairo_pattern_type_linear )
  { *pattern_type = CAIRO_PATTERN_TYPE_LINEAR;
  }
  else if ( a == ATOM_cairo_pattern_type_radial )
  { *pattern_type = CAIRO_PATTERN_TYPE_RADIAL;
  }
  else if ( a == ATOM_cairo_pattern_type_mesh )
  { *pattern_type = CAIRO_PATTERN_TYPE_MESH;
  }
  else if ( a == ATOM_cairo_pattern_type_raster_source )
  { *pattern_type = CAIRO_PATTERN_TYPE_RASTER_SOURCE;
  }
  else
  { return PL_domain_error("CairoPatternType", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_pattern_type_to_term(cairo_pattern_type_t pattern_type,
                             term_t               t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_pattern_type_t: %d  --->  term: 0x%lx", pattern_type, t);

  if ( !ATOM_cairo_pattern_type_solid )
  {
    ATOM_cairo_pattern_type_solid = PL_new_atom("CAIRO_PATTERN_TYPE_SOLID");
    ATOM_cairo_pattern_type_surface = PL_new_atom("CAIRO_PATTERN_TYPE_SURFACE");
    ATOM_cairo_pattern_type_linear = PL_new_atom("CAIRO_PATTERN_TYPE_LINEAR");
    ATOM_cairo_pattern_type_radial = PL_new_atom("CAIRO_PATTERN_TYPE_RADIAL");
    ATOM_cairo_pattern_type_mesh = PL_new_atom("CAIRO_PATTERN_TYPE_MESH");
    ATOM_cairo_pattern_type_raster_source = PL_new_atom("CAIRO_PATTERN_TYPE_RASTER_SOURCE");
  }

  if ( pattern_type == CAIRO_PATTERN_TYPE_SOLID )
  { PL_put_atom(t0, ATOM_cairo_pattern_type_solid);
  }
  else if ( pattern_type == CAIRO_PATTERN_TYPE_SURFACE )
  { PL_put_atom(t0, ATOM_cairo_pattern_type_surface);
  }
  else if ( pattern_type == CAIRO_PATTERN_TYPE_LINEAR )
  { PL_put_atom(t0, ATOM_cairo_pattern_type_linear);
  }
  else if ( pattern_type == CAIRO_PATTERN_TYPE_RADIAL )
  { PL_put_atom(t0, ATOM_cairo_pattern_type_radial);
  }
  else if ( pattern_type == CAIRO_PATTERN_TYPE_MESH )
  { PL_put_atom(t0, ATOM_cairo_pattern_type_mesh);
  }
  else if ( pattern_type == CAIRO_PATTERN_TYPE_RASTER_SOURCE )
  { PL_put_atom(t0, ATOM_cairo_pattern_type_raster_source);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLGI_PRED_IMPL(plcairo_pattern_add_color_stop_rgb)
{
  term_t t_pattern = FA0;
  term_t t_offset = FA1;
  term_t t_red = FA2;
  term_t t_green = FA3;
  term_t t_blue = FA4;

  cairo_pattern_t *pattern;
  double offset, red, green, blue;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_double(t_offset, &offset) ) return FALSE;
  if ( !plcairo_term_to_double(t_red, &red) ) return FALSE;
  if ( !plcairo_term_to_double(t_green, &green) ) return FALSE;
  if ( !plcairo_term_to_double(t_blue, &blue) ) return FALSE;

  cairo_pattern_add_color_stop_rgb(pattern, offset, red, green, blue);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_add_color_stop_rgba)
{
  term_t t_pattern = FA0;
  term_t t_offset = FA1;
  term_t t_red = FA2;
  term_t t_green = FA3;
  term_t t_blue = FA4;
  term_t t_alpha = FA5;

  cairo_pattern_t *pattern;
  double offset, red, green, blue, alpha;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_double(t_offset, &offset) ) return FALSE;
  if ( !plcairo_term_to_double(t_red, &red) ) return FALSE;
  if ( !plcairo_term_to_double(t_green, &green) ) return FALSE;
  if ( !plcairo_term_to_double(t_blue, &blue) ) return FALSE;
  if ( !plcairo_term_to_double(t_alpha, &alpha) ) return FALSE;

  cairo_pattern_add_color_stop_rgba(pattern, offset, red, green, blue, alpha);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_create_for_surface)
{
  term_t t_surface = FA0;
  term_t t_pattern = FA1;

  cairo_surface_t *surface;
  cairo_pattern_t *pattern;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  pattern = cairo_pattern_create_for_surface(surface);
  PLCAIRO_CHECK_PATTERN(pattern);

  if ( !plcairo_pattern_to_term(pattern, t_pattern) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_create_linear)
{
  term_t t_x0 = FA0;
  term_t t_y0 = FA1;
  term_t t_x1 = FA2;
  term_t t_y1 = FA3;
  term_t t_pattern = FA4;

  cairo_pattern_t *pattern;
  double x0, y0, x1, y1;

  if ( !plcairo_term_to_double(t_x0, &x0) ) return FALSE;
  if ( !plcairo_term_to_double(t_y0, &y0) ) return FALSE;
  if ( !plcairo_term_to_double(t_x1, &x1) ) return FALSE;
  if ( !plcairo_term_to_double(t_y1, &y1) ) return FALSE;

  pattern = cairo_pattern_create_linear(x0, y0, x1, y1);
  PLCAIRO_CHECK_PATTERN(pattern);

  if ( !plcairo_pattern_to_term(pattern, t_pattern) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_create_mesh)
{
  term_t t_pattern = FA0;

  cairo_pattern_t *pattern;

  pattern = cairo_pattern_create_mesh();
  PLCAIRO_CHECK_PATTERN(pattern);

  if ( !plcairo_pattern_to_term(pattern, t_pattern) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_create_radial)
{
  term_t t_cx0 = FA0;
  term_t t_cy0 = FA1;
  term_t t_radius0 = FA2;
  term_t t_cx1 = FA3;
  term_t t_cy1 = FA4;
  term_t t_radius1 = FA5;
  term_t t_pattern = FA6;

  cairo_pattern_t *pattern;
  double cx0, cy0, radius0, cx1, cy1, radius1;

  if ( !plcairo_term_to_double(t_cx0, &cx0) ) return FALSE;
  if ( !plcairo_term_to_double(t_cy0, &cy0) ) return FALSE;
  if ( !plcairo_term_to_double(t_radius0, &radius0) ) return FALSE;
  if ( !plcairo_term_to_double(t_cx1, &cx1) ) return FALSE;
  if ( !plcairo_term_to_double(t_cy1, &cy1) ) return FALSE;
  if ( !plcairo_term_to_double(t_radius1, &radius1) ) return FALSE;

  pattern = cairo_pattern_create_radial(cx0, cy0, radius0, cx1, cy1, radius1);
  PLCAIRO_CHECK_PATTERN(pattern);

  if ( !plcairo_pattern_to_term(pattern, t_pattern) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_create_rgb)
{
  term_t t_red = FA0;
  term_t t_green = FA1;
  term_t t_blue = FA2;
  term_t t_pattern = FA3;

  cairo_pattern_t *pattern;
  double red, green, blue;

  if ( !plcairo_term_to_double(t_red, &red) ) return FALSE;
  if ( !plcairo_term_to_double(t_green, &green) ) return FALSE;
  if ( !plcairo_term_to_double(t_blue, &blue) ) return FALSE;

  pattern = cairo_pattern_create_rgb(red, green, blue);
  PLCAIRO_CHECK_PATTERN(pattern);

  if ( !plcairo_pattern_to_term(pattern, t_pattern) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_create_rgba)
{
  term_t t_red = FA0;
  term_t t_green = FA1;
  term_t t_blue = FA2;
  term_t t_alpha = FA2;
  term_t t_pattern = FA4;

  cairo_pattern_t *pattern;
  double red, green, blue, alpha;

  if ( !plcairo_term_to_double(t_red, &red) ) return FALSE;
  if ( !plcairo_term_to_double(t_green, &green) ) return FALSE;
  if ( !plcairo_term_to_double(t_blue, &blue) ) return FALSE;
  if ( !plcairo_term_to_double(t_alpha, &alpha) ) return FALSE;

  pattern = cairo_pattern_create_rgba(red, green, blue, alpha);
  PLCAIRO_CHECK_PATTERN(pattern);

  if ( !plcairo_pattern_to_term(pattern, t_pattern) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_get_color_stop_count)
{
  term_t t_pattern = FA0;
  term_t t_count = FA1;

  cairo_pattern_t *pattern;
  int count;
  cairo_status_t status;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  status = cairo_pattern_get_color_stop_count(pattern, &count);
  PLCAIRO_CHECK_PATTERN(pattern);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  if ( !plcairo_int_to_term(count, t_count) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_get_color_stop_rgba)
{
  term_t t_pattern = FA0;
  term_t t_index = FA1;
  term_t t_offset = FA2;
  term_t t_red = FA3;
  term_t t_green = FA4;
  term_t t_blue = FA5;
  term_t t_alpha = FA6;

  cairo_pattern_t *pattern;
  int index;
  double offset, red, green, blue, alpha;
  cairo_status_t status;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_int(t_index, &index) ) return FALSE;

  status = cairo_pattern_get_color_stop_rgba(pattern, index, &offset, &red, &green, &blue, &alpha);
  PLCAIRO_CHECK_PATTERN(pattern);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  if ( !plcairo_int_to_term(offset, t_offset) ) return FALSE;
  if ( !plcairo_int_to_term(red, t_red) ) return FALSE;
  if ( !plcairo_int_to_term(green, t_green) ) return FALSE;
  if ( !plcairo_int_to_term(blue, t_blue) ) return FALSE;
  if ( !plcairo_int_to_term(alpha, t_alpha) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_get_extend)
{
  term_t t_pattern = FA0;
  term_t t_extend = FA1;

  cairo_pattern_t *pattern;
  cairo_extend_t extend;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  extend = cairo_pattern_get_extend(pattern);
  PLCAIRO_CHECK_PATTERN(pattern);

  if ( !plcairo_extend_to_term(extend, t_extend) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_get_filter)
{
  term_t t_pattern = FA0;
  term_t t_filter = FA1;

  cairo_pattern_t *pattern;
  cairo_filter_t filter;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  filter = cairo_pattern_get_filter(pattern);
  PLCAIRO_CHECK_PATTERN(pattern);

  if ( !plcairo_filter_to_term(filter, t_filter) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_get_linear_points)
{
  term_t t_pattern = FA0;
  term_t t_x0 = FA1;
  term_t t_y0 = FA2;
  term_t t_x1 = FA3;
  term_t t_y1 = FA4;

  cairo_pattern_t *pattern;
  double x0, y0, x1, y1;
  cairo_status_t status;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  status = cairo_pattern_get_linear_points(pattern, &x0, &y0, &x1, &y1);
  PLCAIRO_CHECK_PATTERN(pattern);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  if ( !plcairo_int_to_term(x0, t_x0) ) return FALSE;
  if ( !plcairo_int_to_term(y0, t_y0) ) return FALSE;
  if ( !plcairo_int_to_term(x1, t_x1) ) return FALSE;
  if ( !plcairo_int_to_term(y1, t_y1) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_get_matrix)
{
  term_t t_pattern = FA0;
  term_t t_matrix = FA1;

  cairo_pattern_t *pattern;
  cairo_matrix_t matrix;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  cairo_pattern_get_matrix(pattern, &matrix);
  PLCAIRO_CHECK_PATTERN(pattern);

  if ( !plcairo_matrix_to_term(&matrix, t_matrix) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_get_radial_circles)
{
  term_t t_pattern = FA0;
  term_t t_x0 = FA1;
  term_t t_y0 = FA2;
  term_t t_r0 = FA3;
  term_t t_x1 = FA4;
  term_t t_y1 = FA5;
  term_t t_r1 = FA6;

  cairo_pattern_t *pattern;
  double x0, y0, r0, x1, y1, r1;
  cairo_status_t status;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  status = cairo_pattern_get_radial_circles(pattern, &x0, &y0, &r0, &x1, &y1, &r1);
  PLCAIRO_CHECK_PATTERN(pattern);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  if ( !plcairo_int_to_term(x0, t_x0) ) return FALSE;
  if ( !plcairo_int_to_term(y0, t_y0) ) return FALSE;
  if ( !plcairo_int_to_term(r0, t_r0) ) return FALSE;
  if ( !plcairo_int_to_term(x1, t_x1) ) return FALSE;
  if ( !plcairo_int_to_term(y1, t_y1) ) return FALSE;
  if ( !plcairo_int_to_term(r1, t_r1) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_get_rgba)
{
  term_t t_pattern = FA0;
  term_t t_red = FA1;
  term_t t_green = FA2;
  term_t t_blue = FA3;
  term_t t_alpha = FA4;

  cairo_pattern_t *pattern;
  double red, green, blue, alpha;
  cairo_status_t status;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  status = cairo_pattern_get_rgba(pattern, &red, &green, &blue, &alpha);
  PLCAIRO_CHECK_PATTERN(pattern);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  if ( !plcairo_int_to_term(red, t_red) ) return FALSE;
  if ( !plcairo_int_to_term(green, t_green) ) return FALSE;
  if ( !plcairo_int_to_term(blue, t_blue) ) return FALSE;
  if ( !plcairo_int_to_term(alpha, t_alpha) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_get_surface)
{
  term_t t_pattern = FA0;
  term_t t_surface = FA1;

  cairo_pattern_t *pattern;
  cairo_surface_t *surface;
  cairo_status_t status;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  status = cairo_pattern_get_surface(pattern, &surface);
  PLCAIRO_CHECK_PATTERN(pattern);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_get_type)
{
  term_t t_pattern = FA0;
  term_t t_type = FA1;

  cairo_pattern_t *pattern;
  cairo_pattern_type_t type;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  type = cairo_pattern_get_type(pattern);
  PLCAIRO_CHECK_PATTERN(pattern);

  if ( !plcairo_filter_to_term(type, t_type) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_mesh_pattern_begin_patch)
{
  term_t t_pattern = FA0;

  cairo_pattern_t *pattern;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  cairo_mesh_pattern_begin_patch(pattern);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_mesh_pattern_curve_to)
{
  term_t t_pattern = FA0;
  term_t t_x1 = FA1;
  term_t t_y1 = FA2;
  term_t t_x2 = FA3;
  term_t t_y2 = FA4;
  term_t t_x3 = FA5;
  term_t t_y3 = FA6;

  cairo_pattern_t *pattern;
  double x1, y1, x2, y2, x3, y3;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_double(t_x1, &x1) ) return FALSE;
  if ( !plcairo_term_to_double(t_y1, &y1) ) return FALSE;
  if ( !plcairo_term_to_double(t_x2, &x2) ) return FALSE;
  if ( !plcairo_term_to_double(t_y2, &y2) ) return FALSE;
  if ( !plcairo_term_to_double(t_x3, &x3) ) return FALSE;
  if ( !plcairo_term_to_double(t_y3, &y3) ) return FALSE;

  cairo_mesh_pattern_curve_to(pattern, x1, y1, x2, y2, x3, y3);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_mesh_pattern_end_patch)
{
  term_t t_pattern = FA0;

  cairo_pattern_t *pattern;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  cairo_mesh_pattern_end_patch(pattern);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_mesh_pattern_get_control_point)
{
  term_t t_pattern = FA0;
  term_t t_patch_num = FA1;
  term_t t_point_num = FA2;
  term_t t_x = FA3;
  term_t t_y = FA4;

  cairo_pattern_t *pattern;
  unsigned int patch_num, point_num;
  double x, y;
  cairo_status_t status;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_unsigned_int(t_patch_num, &patch_num) ) return FALSE;
  if ( !plcairo_term_to_unsigned_int(t_point_num, &point_num) ) return FALSE;

  status = cairo_mesh_pattern_get_control_point(pattern, patch_num, point_num, &x, &y);
  PLCAIRO_CHECK_PATTERN(pattern);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  if ( !plcairo_double_to_term(x, t_x) ) return FALSE;
  if ( !plcairo_double_to_term(y, t_y) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_mesh_pattern_get_corner_color_rgba)
{
  term_t t_pattern = FA0;
  term_t t_patch_num = FA1;
  term_t t_corner_num = FA2;
  term_t t_red = FA3;
  term_t t_green = FA4;
  term_t t_blue = FA5;
  term_t t_alpha = FA6;

  cairo_pattern_t *pattern;
  unsigned int patch_num, corner_num;
  double red, green, blue, alpha;
  cairo_status_t status;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_unsigned_int(t_patch_num, &patch_num) ) return FALSE;
  if ( !plcairo_term_to_unsigned_int(t_corner_num, &corner_num) ) return FALSE;

  status = cairo_mesh_pattern_get_corner_color_rgba(pattern, patch_num, corner_num, &red, &green, &blue, &alpha);
  PLCAIRO_CHECK_PATTERN(pattern);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  if ( !plcairo_double_to_term(red, t_red) ) return FALSE;
  if ( !plcairo_double_to_term(green, t_green) ) return FALSE;
  if ( !plcairo_double_to_term(blue, t_blue) ) return FALSE;
  if ( !plcairo_double_to_term(alpha, t_alpha) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_mesh_pattern_get_patch_count)
{
  term_t t_pattern = FA0;
  term_t t_count = FA1;

  cairo_pattern_t *pattern;
  unsigned int count;
  cairo_status_t status;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  status = cairo_mesh_pattern_get_patch_count(pattern, &count);
  PLCAIRO_CHECK_PATTERN(pattern);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  if ( !plcairo_unsigned_int_to_term(count, t_count) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_mesh_pattern_get_path)
{
  term_t t_pattern = FA0;
  term_t t_patch_num = FA1;
  term_t t_path = FA2;

  cairo_pattern_t *pattern;
  unsigned int patch_num;
  cairo_path_t *path;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_unsigned_int(t_patch_num, &patch_num) ) return FALSE;

  path = cairo_mesh_pattern_get_path(pattern, patch_num);
  PLCAIRO_CHECK_PATTERN(pattern);

  if ( !plcairo_path_to_term(path, t_path) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_mesh_pattern_line_to)
{
  term_t t_pattern = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;

  cairo_pattern_t *pattern;
  double x, y;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;

  cairo_mesh_pattern_line_to(pattern, x, y);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_mesh_pattern_move_to)
{
  term_t t_pattern = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;

  cairo_pattern_t *pattern;
  double x, y;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;

  cairo_mesh_pattern_move_to(pattern, x, y);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_mesh_pattern_set_control_point)
{
  term_t t_pattern = FA0;
  term_t t_point_num = FA1;
  term_t t_x = FA2;
  term_t t_y = FA3;

  cairo_pattern_t *pattern;
  unsigned int point_num;
  double x, y;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_unsigned_int(t_point_num, &point_num) ) return FALSE;
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;

  cairo_mesh_pattern_set_control_point(pattern, point_num, x, y);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_mesh_pattern_set_corner_color_rgb)
{
  term_t t_pattern = FA0;
  term_t t_corner_num = FA1;
  term_t t_red = FA2;
  term_t t_green = FA3;
  term_t t_blue = FA4;

  cairo_pattern_t *pattern;
  unsigned int corner_num;
  double red, green, blue;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_unsigned_int(t_corner_num, &corner_num) ) return FALSE;
  if ( !plcairo_term_to_double(t_red, &red) ) return FALSE;
  if ( !plcairo_term_to_double(t_green, &green) ) return FALSE;
  if ( !plcairo_term_to_double(t_blue, &blue) ) return FALSE;

  cairo_mesh_pattern_set_corner_color_rgb(pattern, corner_num, red, green, blue);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_mesh_pattern_set_corner_color_rgba)
{
  term_t t_pattern = FA0;
  term_t t_corner_num = FA1;
  term_t t_red = FA2;
  term_t t_green = FA3;
  term_t t_blue = FA4;
  term_t t_alpha = FA5;

  cairo_pattern_t *pattern;
  unsigned int corner_num;
  double red, green, blue, alpha;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_unsigned_int(t_corner_num, &corner_num) ) return FALSE;
  if ( !plcairo_term_to_double(t_red, &red) ) return FALSE;
  if ( !plcairo_term_to_double(t_green, &green) ) return FALSE;
  if ( !plcairo_term_to_double(t_blue, &blue) ) return FALSE;
  if ( !plcairo_term_to_double(t_alpha, &alpha) ) return FALSE;

  cairo_mesh_pattern_set_corner_color_rgba(pattern, corner_num, red, green, blue, alpha);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_set_extend)
{
  term_t t_pattern = FA0;
  term_t t_extend = FA1;

  cairo_pattern_t *pattern;
  cairo_extend_t extend;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_extend(t_extend, &extend) ) return FALSE;

  cairo_pattern_set_extend(pattern, extend);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_set_filter)
{
  term_t t_pattern = FA0;
  term_t t_filter = FA1;

  cairo_pattern_t *pattern;
  cairo_filter_t filter;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_filter(t_filter, &filter) ) return FALSE;

  cairo_pattern_set_extend(pattern, filter);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_pattern_set_matrix)
{
  term_t t_pattern = FA0;
  term_t t_matrix = FA1;

  cairo_pattern_t *pattern;
  cairo_matrix_t *matrix;

  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;
  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;

  cairo_pattern_set_matrix(pattern, matrix);
  PLCAIRO_CHECK_PATTERN(pattern);

  return TRUE;
}
