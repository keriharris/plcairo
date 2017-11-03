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

#ifdef CAIRO_HAS_PNG_FUNCTIONS


                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLCAIRO_PRED_IMPL(plcairo_image_surface_create_from_png)
{
  term_t t_filename = FA0;
  term_t t_surface = FA1;

  char *filename;
  cairo_surface_t *surface;

  if ( !plcairo_term_to_string(t_filename, &filename) ) return FALSE;

  surface = cairo_image_surface_create_from_png(filename);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_image_surface_create_from_png_stream)
{
  term_t t_stream = FA0;
  term_t t_surface = FA1;

  void *closure;
  cairo_surface_t *surface;

  if ( !plcairo_term_to_closure(t_stream, &closure) ) return FALSE;

  surface = cairo_image_surface_create_from_png_stream(&plcairo_read_func, closure);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_surface_write_to_png)
{
  term_t t_surface = FA0;
  term_t t_filename = FA1;

  cairo_surface_t *surface;
  char *filename;
  cairo_status_t status;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_string(t_filename, &filename) ) return FALSE;

  status = cairo_surface_write_to_png(surface, filename);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( status != CAIRO_STATUS_SUCCESS )
  { return plcairo_raise_error_status(status);
  }

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_surface_write_to_png_stream)
{
  term_t t_surface = FA0;
  term_t t_stream = FA1;

  cairo_surface_t *surface;
  void *closure;
  cairo_status_t status;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_closure(t_stream, &closure) ) return FALSE;

  status = cairo_surface_write_to_png_stream(surface, &plcairo_write_func, closure);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( status != CAIRO_STATUS_SUCCESS )
  { return plcairo_raise_error_status(status);
  }

  return TRUE;
}

#else

PLCAIRO_PRED_IMPL(plcairo_image_surface_create_from_png)
{ return plcairo_raise_error("cairo_image_surface_create_from_png/2 not supported");
}

PLCAIRO_PRED_IMPL(plcairo_image_surface_create_from_png_stream)
{ return plcairo_raise_error("cairo_image_surface_create_from_png_stream/2 not supported");
}

PLCAIRO_PRED_IMPL(plcairo_surface_write_to_png)
{ return plcairo_raise_error("cairo_surface_write_to_png/2 not supported");
}

PLCAIRO_PRED_IMPL(plcairo_surface_write_to_png_stream)
{ return plcairo_raise_error("cairo_surface_write_to_png_stream/2 not supported");
}

#endif
