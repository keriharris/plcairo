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


                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLGI_PRED_IMPL(plcairo_device_to_user)
{
  term_t t_cr = FA0;
  term_t t_x_in = FA1;
  term_t t_y_in = FA2;
  term_t t_x_out = FA3;
  term_t t_y_out = FA4;

  cairo_t *cr;
  double x, y;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_x_in, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y_in, &y) ) return FALSE;

  cairo_device_to_user(cr, &x, &y);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_double_to_term(x, t_x_out) ) return FALSE;
  if ( !plcairo_double_to_term(y, t_y_out) ) return FALSE;

  return TRUE;
}

PLGI_PRED_IMPL(plcairo_device_to_user_distance)
{
  term_t t_cr = FA0;
  term_t t_dx_in = FA1;
  term_t t_dy_in = FA2;
  term_t t_dx_out = FA3;
  term_t t_dy_out = FA4;

  cairo_t *cr;
  double dx, dy;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_dx_in, &dx) ) return FALSE;
  if ( !plcairo_term_to_double(t_dy_in, &dy) ) return FALSE;

  cairo_device_to_user_distance(cr, &dx, &dy);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_double_to_term(dx, t_dx_out) ) return FALSE;
  if ( !plcairo_double_to_term(dy, t_dy_out) ) return FALSE;

  return TRUE;
}

PLGI_PRED_IMPL(plcairo_get_matrix)
{
  term_t t_cr = FA0;
  term_t t_matrix = FA1;

  cairo_t *cr;
  cairo_matrix_t matrix;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_get_matrix(cr, &matrix);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_matrix_to_term(&matrix, t_matrix) ) return FALSE;

  return TRUE;
}

PLGI_PRED_IMPL(plcairo_identity_matrix)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_identity_matrix(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}

PLGI_PRED_IMPL(plcairo_rotate)
{
  term_t t_cr = FA0;
  term_t t_angle = FA1;

  cairo_t *cr;
  double angle;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_angle, &angle) ) return FALSE;

  cairo_rotate(cr, angle);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_scale)
{
  term_t t_cr = FA0;
  term_t t_sx = FA1;
  term_t t_sy = FA2;

  cairo_t *cr;
  double sx, sy;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_sx, &sx) ) return FALSE;
  if ( !plcairo_term_to_double(t_sy, &sy) ) return FALSE;

  cairo_scale(cr, sx, sy);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_set_matrix)
{
  term_t t_cr = FA0;
  term_t t_matrix = FA1;

  cairo_t *cr;
  cairo_matrix_t *matrix;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;

  cairo_set_matrix(cr, matrix);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_transform)
{
  term_t t_cr = FA0;
  term_t t_matrix = FA1;

  cairo_t *cr;
  cairo_matrix_t *matrix;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;

  cairo_transform(cr, matrix);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_translate)
{
  term_t t_cr = FA0;
  term_t t_tx = FA1;
  term_t t_ty = FA2;

  cairo_t *cr;
  double tx, ty;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_tx, &tx) ) return FALSE;
  if ( !plcairo_term_to_double(t_ty, &ty) ) return FALSE;

  cairo_translate(cr, tx, ty);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}

PLGI_PRED_IMPL(plcairo_user_to_device)
{
  term_t t_cr = FA0;
  term_t t_x_in = FA1;
  term_t t_y_in = FA2;
  term_t t_x_out = FA3;
  term_t t_y_out = FA4;

  cairo_t *cr;
  double x, y;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_x_in, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y_in, &y) ) return FALSE;

  cairo_user_to_device(cr, &x, &y);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_double_to_term(x, t_x_out) ) return FALSE;
  if ( !plcairo_double_to_term(y, t_y_out) ) return FALSE;

  return TRUE;
}

PLGI_PRED_IMPL(plcairo_user_to_device_distance)
{
  term_t t_cr = FA0;
  term_t t_dx_in = FA1;
  term_t t_dy_in = FA2;
  term_t t_dx_out = FA3;
  term_t t_dy_out = FA4;

  cairo_t *cr;
  double dx, dy;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_dx_in, &dx) ) return FALSE;
  if ( !plcairo_term_to_double(t_dy_in, &dy) ) return FALSE;

  cairo_user_to_device_distance(cr, &dx, &dy);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_double_to_term(dx, t_dx_out) ) return FALSE;
  if ( !plcairo_double_to_term(dy, t_dy_out) ) return FALSE;

  return TRUE;
}
