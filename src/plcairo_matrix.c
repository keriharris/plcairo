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


/* cairo_matrix_t */
void plcairo_register_matrix_t(void)
{
  PLGIStructInfo *struct_info;
  PLGIFieldInfo *field_info;
  int n_fields, offset;

  PLCAIRO_debug("registering struct: CairoMatrix");

  n_fields = 6;
  offset = 0;

  struct_info = g_malloc0(sizeof(*struct_info));
  struct_info->info = NULL;
  struct_info->namespace = PL_new_atom("cairo");
  struct_info->name = PL_new_atom("CairoMatrix");
  struct_info->gtype = CAIRO_GOBJECT_TYPE_MATRIX;
  struct_info->size = sizeof(cairo_matrix_t);
  struct_info->n_fields = n_fields;
  struct_info->fields_info = g_malloc0_n(n_fields, sizeof(*struct_info->fields_info));

  plcairo_alloc_struct_double_field(0, "xx");
  plcairo_alloc_struct_double_field(1, "yx");
  plcairo_alloc_struct_double_field(2, "xy");
  plcairo_alloc_struct_double_field(3, "yy");
  plcairo_alloc_struct_double_field(4, "x0");
  plcairo_alloc_struct_double_field(5, "y0");

  plgi_cache_struct_info(struct_info);
}

cairo_bool_t
plcairo_term_to_matrix(term_t           t,
                       cairo_matrix_t **matrix)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_matrix_t: %p", t, *matrix);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoMatrix", t);
  }

  if ( blob->gtype != G_TYPE_NONE &&
       !g_type_is_a( blob->gtype, CAIRO_GOBJECT_TYPE_MATRIX ) )
  { return PL_type_error("CairoMatrix", t);
  }

  *matrix = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_matrix_to_term(cairo_matrix_t *matrix,
                       term_t          t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_matrix_t: %p  --->  term: 0x%lx", matrix, t);

  if ( !matrix )
  { return ( plgi_put_null(t0) && PL_unify(t, t0) );
  }

  data = matrix;
  blob_type = PLGI_BLOB_BOXED;

  if ( !plgi_put_blob(blob_type, CAIRO_GOBJECT_TYPE_MATRIX,
                      PL_new_atom("CairoMatrix"), TRUE, data, t0) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLGI_PRED_IMPL(plcairo_matrix_init)
{
  term_t t_matrix = FA0;
  term_t t_xx = FA1;
  term_t t_yx = FA2;
  term_t t_xy = FA3;
  term_t t_yy = FA4;
  term_t t_x0 = FA5;
  term_t t_y0 = FA6;

  cairo_matrix_t *matrix;
  double xx, yx, xy, yy, x0, y0;

  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;
  if ( !plcairo_term_to_double(t_xx, &xx) ) return FALSE;
  if ( !plcairo_term_to_double(t_yx, &yx) ) return FALSE;
  if ( !plcairo_term_to_double(t_xy, &xy) ) return FALSE;
  if ( !plcairo_term_to_double(t_yy, &yy) ) return FALSE;
  if ( !plcairo_term_to_double(t_x0, &x0) ) return FALSE;
  if ( !plcairo_term_to_double(t_y0, &y0) ) return FALSE;

  cairo_matrix_init(matrix, xx, yx, xy, yy, x0, y0);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_matrix_init_identity)
{
  term_t t_matrix = FA0;

  cairo_matrix_t *matrix;

  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;

  cairo_matrix_init_identity(matrix);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_matrix_init_rotate)
{
  term_t t_matrix = FA0;
  term_t t_radians = FA1;

  cairo_matrix_t *matrix;
  double radians;

  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;
  if ( !plcairo_term_to_double(t_radians, &radians) ) return FALSE;

  cairo_matrix_init_rotate(matrix, radians);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_matrix_init_scale)
{
  term_t t_matrix = FA0;
  term_t t_sx = FA1;
  term_t t_sy = FA2;

  cairo_matrix_t *matrix;
  double sx, sy;

  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;
  if ( !plcairo_term_to_double(t_sx, &sx) ) return FALSE;
  if ( !plcairo_term_to_double(t_sy, &sy) ) return FALSE;

  cairo_matrix_init_scale(matrix, sx, sy);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_matrix_init_translate)
{
  term_t t_matrix = FA0;
  term_t t_tx = FA1;
  term_t t_ty = FA2;

  cairo_matrix_t *matrix;
  double tx, ty;

  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;
  if ( !plcairo_term_to_double(t_tx, &tx) ) return FALSE;
  if ( !plcairo_term_to_double(t_ty, &ty) ) return FALSE;

  cairo_matrix_init_translate(matrix, tx, ty);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_matrix_invert)
{
  term_t t_matrix = FA0;

  cairo_matrix_t *matrix;
  cairo_status_t status;

  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;

  status = cairo_matrix_invert(matrix);

  if ( status != CAIRO_STATUS_SUCCESS )
  { return plcairo_raise_error_status(status);
  }

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_matrix_multiply)
{
  term_t t_matrix = FA0;
  term_t t_a = FA1;
  term_t t_b = FA2;

  cairo_matrix_t *matrix, *a, *b;

  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;
  if ( !plcairo_term_to_matrix(t_a, &a) ) return FALSE;
  if ( !plcairo_term_to_matrix(t_b, &b) ) return FALSE;

  cairo_matrix_multiply(matrix, a, b);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_matrix_rotate)
{
  term_t t_matrix = FA0;
  term_t t_radians = FA1;

  cairo_matrix_t *matrix;
  double radians;

  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;
  if ( !plcairo_term_to_double(t_radians, &radians) ) return FALSE;

  cairo_matrix_rotate(matrix, radians);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_matrix_scale)
{
  term_t t_matrix = FA0;
  term_t t_sx = FA1;
  term_t t_sy = FA2;

  cairo_matrix_t *matrix;
  double sx, sy;

  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;
  if ( !plcairo_term_to_double(t_sx, &sx) ) return FALSE;
  if ( !plcairo_term_to_double(t_sy, &sy) ) return FALSE;

  cairo_matrix_scale(matrix, sx, sy);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_matrix_transform_distance)
{
  term_t t_matrix = FA0;
  term_t t_dx_in = FA1;
  term_t t_dy_in = FA2;
  term_t t_dx_out = FA3;
  term_t t_dy_out = FA4;

  cairo_matrix_t *matrix;
  double dx, dy;

  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;
  if ( !plcairo_term_to_double(t_dx_in, &dx) ) return FALSE;
  if ( !plcairo_term_to_double(t_dy_in, &dy) ) return FALSE;

  cairo_matrix_transform_distance(matrix, &dx, &dy);

  if ( !plcairo_double_to_term(dx, t_dx_out) ) return FALSE;
  if ( !plcairo_double_to_term(dy, t_dy_out) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_matrix_transform_point)
{
  term_t t_matrix = FA0;
  term_t t_x_in = FA1;
  term_t t_y_in = FA2;
  term_t t_x_out = FA3;
  term_t t_y_out = FA4;

  cairo_matrix_t *matrix;
  double x, y;

  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;
  if ( !plcairo_term_to_double(t_x_in, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y_in, &y) ) return FALSE;

  cairo_matrix_transform_point(matrix, &x, &y);

  if ( !plcairo_double_to_term(x, t_x_out) ) return FALSE;
  if ( !plcairo_double_to_term(y, t_y_out) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_matrix_translate)
{
  term_t t_matrix = FA0;
  term_t t_tx = FA1;
  term_t t_ty = FA2;

  cairo_matrix_t *matrix;
  double tx, ty;

  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;
  if ( !plcairo_term_to_double(t_tx, &tx) ) return FALSE;
  if ( !plcairo_term_to_double(t_ty, &ty) ) return FALSE;

  cairo_matrix_translate(matrix, tx, ty);

  return TRUE;
}
