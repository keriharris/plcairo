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

#ifdef CAIRO_HAS_SVG_SURFACE


                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLGI_PRED_IMPL(plcairo_recording_surface_create)
{
  term_t t_content = FA0;
  term_t t_extents = FA1;
  term_t t_surface = FA2;

  cairo_content_t content;
  cairo_rectangle_t *extents;
  cairo_surface_t *surface;

  if ( !plcairo_term_to_content(t_content, &content) ) return FALSE;
  if ( !plcairo_term_to_rectangle(t_extents, &extents) ) return FALSE;

  surface = cairo_recording_surface_create(content, extents);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_recording_surface_get_extents)
{
  term_t t_surface = FA0;
  term_t t_extents = FA1;

  cairo_surface_t *surface;
  cairo_rectangle_t extents;
  cairo_bool_t ret;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  ret = cairo_recording_surface_get_extents(surface, &extents);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_rectangle_to_term(&extents, t_extents) ) return FALSE;

  return (ret != 0);
}


PLGI_PRED_IMPL(plcairo_recording_surface_ink_extents)
{
  term_t t_surface = FA0;
  term_t t_x0 = FA1;
  term_t t_y0 = FA2;
  term_t t_width = FA3;
  term_t t_height = FA4;

  cairo_surface_t *surface;
  double x0, y0, width, height;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_double(t_x0, &x0) ) return FALSE;
  if ( !plcairo_term_to_double(t_y0, &y0) ) return FALSE;
  if ( !plcairo_term_to_double(t_width, &width) ) return FALSE;
  if ( !plcairo_term_to_double(t_height, &height) ) return FALSE;

  cairo_recording_surface_ink_extents(surface, &x0, &y0, &width, &height);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}

#else

PLGI_PRED_IMPL(plcairo_recording_surface_create)
{ return plgi_raise_error("cairo_recording_surface_create/3 not supported");
}

PLGI_PRED_IMPL(plcairo_recording_surface_get_extents)
{ return plgi_raise_error("cairo_recording_surface_get_extents/2 not supported");
}

PLGI_PRED_IMPL(plcairo_recording_surface_ink_extents)
{ return plgi_raise_error("cairo_recording_surface_ink_extents/5 not supported");
}

#endif
