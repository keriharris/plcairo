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

#ifdef CAIRO_HAS_SCRIPT_SURFACE
#include <cairo-script.h>


/* cairo_script_mode_t */
static atom_t ATOM_cairo_script_mode_ascii = 0;
static atom_t ATOM_cairo_script_mode_binary = 0;

cairo_bool_t
plcairo_term_to_script_mode(term_t               t,
                            cairo_script_mode_t *mode)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_script_mode_t: %p", t, mode);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoScriptMode", t);
  }

  if ( !ATOM_cairo_script_mode_ascii )
  {
    ATOM_cairo_script_mode_ascii = PL_new_atom("CAIRO_SCRIPT_MODE_ASCII");
    ATOM_cairo_script_mode_binary = PL_new_atom("CAIRO_SCRIPT_MODE_BINARY");
  }

  if ( a == ATOM_cairo_script_mode_ascii )
  { *mode = CAIRO_SCRIPT_MODE_ASCII;
  }
  else if ( a == ATOM_cairo_script_mode_binary )
  { *mode = CAIRO_SCRIPT_MODE_BINARY;
  }
  else
  { return PL_domain_error("CairoScriptMode", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_script_mode_to_term(cairo_script_mode_t mode,
                            term_t              t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_script_mode_t: %d  --->  term: 0x%lx", mode, t);

  if ( !ATOM_cairo_script_mode_ascii )
  {
    ATOM_cairo_script_mode_ascii = PL_new_atom("CAIRO_SCRIPT_MODE_ASCII");
    ATOM_cairo_script_mode_binary = PL_new_atom("CAIRO_SCRIPT_MODE_BINARY");
  }

  if ( mode == CAIRO_SCRIPT_MODE_ASCII )
  { PL_put_atom(t0, ATOM_cairo_script_mode_ascii);
  }
  else if ( mode == CAIRO_SCRIPT_MODE_BINARY )
  { PL_put_atom(t0, ATOM_cairo_script_mode_binary);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLGI_PRED_IMPL(plcairo_script_create)
{
  term_t t_filename = FA0;
  term_t t_device = FA1;

  char *filename;
  cairo_device_t *device;

  if ( !plcairo_term_to_string(t_filename, &filename) ) return FALSE;

  device = cairo_script_create(filename);
  PLCAIRO_CHECK_DEVICE(device);

  if ( !plcairo_device_to_term(device, t_device) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_script_create_for_stream)
{
  term_t t_stream = FA0;
  term_t t_device = FA1;

  void *closure;
  cairo_device_t *device;

  if ( !plcairo_term_to_closure(t_stream, &closure) ) return FALSE;

  device = cairo_script_create_for_stream(&plcairo_write_func, closure);
  PLCAIRO_CHECK_DEVICE(device);

  if ( !plcairo_device_to_term(device, t_device) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_script_from_recording_surface)
{
  term_t t_script = FA0;
  term_t t_recording_surface = FA1;

  cairo_device_t *script;
  cairo_surface_t *recording_surface;
  cairo_status_t status;

  if ( !plcairo_term_to_device(t_script, &script) ) return FALSE;
  if ( !plcairo_term_to_surface(t_recording_surface, &recording_surface) ) return FALSE;

  status = cairo_script_from_recording_surface(script, recording_surface);
  PLCAIRO_CHECK_DEVICE(script);

  if ( status != CAIRO_STATUS_SUCCESS )
  { return plcairo_raise_error_status(status);
  }

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_script_get_mode)
{
  term_t t_script = FA0;
  term_t t_mode = FA1;

  cairo_device_t *script;
  cairo_script_mode_t mode;

  if ( !plcairo_term_to_device(t_script, &script) ) return FALSE;

  mode = cairo_script_get_mode(script);
  PLCAIRO_CHECK_DEVICE(script);

  if ( !plcairo_script_mode_to_term(mode, t_mode) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_script_set_mode)
{
  term_t t_script = FA0;
  term_t t_mode = FA1;

  cairo_device_t *script;
  cairo_script_mode_t mode;

  if ( !plcairo_term_to_device(t_script, &script) ) return FALSE;
  if ( !plcairo_term_to_script_mode(t_mode, &mode) ) return FALSE;

  cairo_script_set_mode(script, mode);
  PLCAIRO_CHECK_DEVICE(script);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_script_surface_create)
{
  term_t t_script = FA0;
  term_t t_content = FA1;
  term_t t_width = FA2;
  term_t t_height = FA3;
  term_t t_surface = FA4;

  cairo_device_t *script;
  cairo_content_t content;
  double width, height;
  cairo_surface_t *surface;

  if ( !plcairo_term_to_device(t_script, &script) ) return FALSE;
  if ( !plcairo_term_to_content(t_content, &content) ) return FALSE;
  if ( !plcairo_term_to_double(t_width, &width) ) return FALSE;
  if ( !plcairo_term_to_double(t_height, &height) ) return FALSE;

  surface = cairo_script_surface_create(script, content, width, height);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_script_surface_create_for_target)
{
  term_t t_script = FA0;
  term_t t_target = FA1;
  term_t t_surface = FA2;

  cairo_device_t *script;
  cairo_surface_t *target;
  cairo_surface_t *surface;

  if ( !plcairo_term_to_device(t_script, &script) ) return FALSE;
  if ( !plcairo_term_to_surface(t_target, &target) ) return FALSE;

  surface = cairo_script_surface_create_for_target(script, target);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_script_write_comment)
{
  term_t t_script = FA0;
  term_t t_comment = FA1;

  cairo_device_t *script;
  char *comment;

  if ( !plcairo_term_to_device(t_script, &script) ) return FALSE;
  if ( !plcairo_term_to_string(t_comment, &comment) ) return FALSE;

  cairo_script_write_comment(script, comment, -1);
  PLCAIRO_CHECK_DEVICE(script);

  return TRUE;
}

#else

PLGI_PRED_IMPL(plcairo_script_create)
{ return plgi_raise_error("cairo_script_create/2 not supported");
}

PLGI_PRED_IMPL(plcairo_script_create_for_stream)
{ return plgi_raise_error("cairo_script_create_for_stream/2 not supported");
}

PLGI_PRED_IMPL(plcairo_script_from_recording_surface)
{ return plgi_raise_error("cairo_script_from_recording_surface/2 not supported");
}

PLGI_PRED_IMPL(plcairo_script_get_mode)
{ return plgi_raise_error("cairo_script_get_mode/2 not supported");
}

PLGI_PRED_IMPL(plcairo_script_set_mode)
{ return plgi_raise_error("cairo_script_set_mode/2 not supported");
}

PLGI_PRED_IMPL(plcairo_script_surface_create)
{ return plgi_raise_error("cairo_script_surface_create/5 not supported");
}

PLGI_PRED_IMPL(plcairo_script_surface_create_for_target)
{ return plgi_raise_error("cairo_script_surface_create_for_target/3 not supported");
}

PLGI_PRED_IMPL(plcairo_script_write_comment)
{ return plgi_raise_error("cairo_script_write_comment/2 not supported");
}

#endif
