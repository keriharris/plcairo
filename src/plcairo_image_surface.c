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


/* cairo_format_t */
static atom_t ATOM_cairo_format_invalid = 0;
static atom_t ATOM_cairo_format_argb32 = 0;
static atom_t ATOM_cairo_format_rgb24 = 0;
static atom_t ATOM_cairo_format_a8 = 0;
static atom_t ATOM_cairo_format_a1 = 0;
static atom_t ATOM_cairo_format_rgb16_565 = 0;
static atom_t ATOM_cairo_format_rgb30 = 0;

cairo_bool_t
plcairo_term_to_format(term_t          t,
                       cairo_format_t *format)
{
  atom_t a;

  PLGI_debug("    term: 0x%lx  --->  cairo_format_t: %p", t, format);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("cairo_format_t", t);
  }

  if ( !ATOM_cairo_format_invalid )
  {
    ATOM_cairo_format_invalid = PL_new_atom("CAIRO_FORMAT_INVALID");
    ATOM_cairo_format_argb32 = PL_new_atom("CAIRO_FORMAT_ARGB32");
    ATOM_cairo_format_rgb24 = PL_new_atom("CAIRO_FORMAT_RGB24");
    ATOM_cairo_format_a8 = PL_new_atom("CAIRO_FORMAT_A8");
    ATOM_cairo_format_a1 = PL_new_atom("CAIRO_FORMAT_A1");
    ATOM_cairo_format_rgb16_565 = PL_new_atom("CAIRO_FORMAT_RGB16_565");
    ATOM_cairo_format_rgb30 = PL_new_atom("CAIRO_FORMAT_RGB30");
  }

  if ( a == ATOM_cairo_format_invalid )
  { *format = CAIRO_FORMAT_INVALID;
  }
  else if ( a == ATOM_cairo_format_argb32 )
  { *format = CAIRO_FORMAT_ARGB32;
  }
  else if ( a == ATOM_cairo_format_rgb24 )
  { *format = CAIRO_FORMAT_RGB24;
  }
  else if ( a == ATOM_cairo_format_a8 )
  { *format = CAIRO_FORMAT_A8;
  }
  else if ( a == ATOM_cairo_format_a1 )
  { *format = CAIRO_FORMAT_A1;
  }
  else if ( a == ATOM_cairo_format_rgb16_565 )
  { *format = CAIRO_FORMAT_RGB16_565;
  }
  else if ( a == ATOM_cairo_format_rgb30 )
  { *format = CAIRO_FORMAT_RGB30;
  }
  else
  { return PL_domain_error("cairo_format_t", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_format_to_term(cairo_format_t format,
                       term_t         t)
{
  term_t t0 = PL_new_term_ref();

  PLGI_debug("    cairo_format_t: %d  --->  term: 0x%lx", format, t);

  if ( !ATOM_cairo_format_invalid )
  {
    ATOM_cairo_format_invalid = PL_new_atom("CAIRO_FORMAT_INVALID");
    ATOM_cairo_format_argb32 = PL_new_atom("CAIRO_FORMAT_ARGB32");
    ATOM_cairo_format_rgb24 = PL_new_atom("CAIRO_FORMAT_RGB24");
    ATOM_cairo_format_a8 = PL_new_atom("CAIRO_FORMAT_A8");
    ATOM_cairo_format_a1 = PL_new_atom("CAIRO_FORMAT_A1");
    ATOM_cairo_format_rgb16_565 = PL_new_atom("CAIRO_FORMAT_RGB16_565");
    ATOM_cairo_format_rgb30 = PL_new_atom("CAIRO_FORMAT_RGB30");
  }

  if ( format == CAIRO_FORMAT_INVALID )
  { PL_put_atom(t0, ATOM_cairo_format_invalid);
  }
  else if ( format == CAIRO_FORMAT_ARGB32 )
  { PL_put_atom(t0, ATOM_cairo_format_argb32);
  }
  else if ( format == CAIRO_FORMAT_RGB24 )
  { PL_put_atom(t0, ATOM_cairo_format_rgb24);
  }
  else if ( format == CAIRO_FORMAT_A8 )
  { PL_put_atom(t0, ATOM_cairo_format_a8);
  }
  else if ( format == CAIRO_FORMAT_A1 )
  { PL_put_atom(t0, ATOM_cairo_format_a1);
  }
  else if ( format == CAIRO_FORMAT_RGB16_565 )
  { PL_put_atom(t0, ATOM_cairo_format_rgb16_565);
  }
  else if ( format == CAIRO_FORMAT_RGB30 )
  { PL_put_atom(t0, ATOM_cairo_format_rgb30);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLGI_PRED_IMPL(plcairo_image_surface_create)
{
  term_t t_format = FA0;
  term_t t_width = FA1;
  term_t t_height = FA2;
  term_t t_surface = FA3;

  cairo_surface_t *surface;
  cairo_format_t format;
  int width, height;
  term_t t_surface0 = PL_new_term_ref();

  if ( !plcairo_term_to_format(t_format, &format) ) return FALSE;
  if ( !plcairo_term_to_int(t_width, &width) ) return FALSE;
  if ( !plcairo_term_to_int(t_height, &height) ) return FALSE;

  surface = cairo_image_surface_create(format, width, height);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface0) )
  { return FALSE;
  }

  return PL_unify(t_surface, t_surface0);
}


PLGI_PRED_IMPL(plcairo_image_surface_get_format)
{
  term_t t_surface = FA0;
  term_t t_format = FA1;

  cairo_surface_t *surface;
  cairo_format_t format;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  format = cairo_image_surface_get_height(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_int_to_term(format, t_format) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_image_surface_get_height)
{
  term_t t_surface = FA0;
  term_t t_height = FA1;

  cairo_surface_t *surface;
  int height;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  height = cairo_image_surface_get_height(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_int_to_term(height, t_height) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_image_surface_get_stride)
{
  term_t t_surface = FA0;
  term_t t_stride = FA1;

  cairo_surface_t *surface;
  int stride;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  stride = cairo_image_surface_get_stride(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_int_to_term(stride, t_stride) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_image_surface_get_width)
{
  term_t t_surface = FA0;
  term_t t_width = FA1;

  cairo_surface_t *surface;
  int width;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  width = cairo_image_surface_get_width(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_int_to_term(width, t_width) ) return FALSE;

  return TRUE;
}
