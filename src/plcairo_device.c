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


/* cairo_device_t */
cairo_bool_t
plcairo_term_to_device(term_t    t,
                       cairo_device_t **device)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_device_t: %p", t, *device);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoDevice", t);
  }

  if ( blob->gtype != G_TYPE_NONE &&
       !g_type_is_a( blob->gtype, CAIRO_GOBJECT_TYPE_DEVICE ) )
  { return PL_type_error("CairoDevice", t);
  }

  *device = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_device_to_term(cairo_device_t *device,
                       term_t   t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_device_t: %p  --->  term: 0x%lx", device, t);

  if ( !device )
  { return ( plcairo_put_null(t0) && PL_unify(t, t0) );
  }

  data = device;
  blob_type = PLGI_BLOB_BOXED;

  if ( !plgi_put_blob(blob_type, CAIRO_GOBJECT_TYPE_DEVICE,
                      PL_new_atom("CairoDevice"), TRUE, data, t0) )
  { return FALSE;
  }

  return PL_unify(t, t0);;
}


/* cairo_device_type_t */
static atom_t ATOM_cairo_device_type_drm = 0;
static atom_t ATOM_cairo_device_type_gl = 0;
static atom_t ATOM_cairo_device_type_script = 0;
static atom_t ATOM_cairo_device_type_xcb = 0;
static atom_t ATOM_cairo_device_type_xlib = 0;
static atom_t ATOM_cairo_device_type_xml = 0;
static atom_t ATOM_cairo_device_type_cogl = 0;
static atom_t ATOM_cairo_device_type_win32 = 0;
static atom_t ATOM_cairo_device_type_invalid = 0;

cairo_bool_t
plcairo_term_to_device_type(term_t               t,
                            cairo_device_type_t *device_type)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_device_type_t: %p", t, device_type);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoDeviceType", t);
  }

  if ( !ATOM_cairo_device_type_drm )
  {
    ATOM_cairo_device_type_drm = PL_new_atom("CAIRO_DEVICE_TYPE_DRM");
    ATOM_cairo_device_type_gl = PL_new_atom("CAIRO_DEVICE_TYPE_GL");
    ATOM_cairo_device_type_script = PL_new_atom("CAIRO_DEVICE_TYPE_SCRIPT");
    ATOM_cairo_device_type_xcb = PL_new_atom("CAIRO_DEVICE_TYPE_XCB");
    ATOM_cairo_device_type_xlib = PL_new_atom("CAIRO_DEVICE_TYPE_XLIB");
    ATOM_cairo_device_type_xml = PL_new_atom("CAIRO_DEVICE_TYPE_XML");
    ATOM_cairo_device_type_cogl = PL_new_atom("CAIRO_DEVICE_TYPE_COGL");
    ATOM_cairo_device_type_win32 = PL_new_atom("CAIRO_DEVICE_TYPE_WIN32");
    ATOM_cairo_device_type_invalid = PL_new_atom("CAIRO_DEVICE_TYPE_INVALID");
  }

  if ( a == ATOM_cairo_device_type_drm )
  { *device_type = CAIRO_DEVICE_TYPE_DRM;
  }
  else if ( a == ATOM_cairo_device_type_gl )
  { *device_type = CAIRO_DEVICE_TYPE_GL;
  }
  else if ( a == ATOM_cairo_device_type_script )
  { *device_type = CAIRO_DEVICE_TYPE_SCRIPT;
  }
  else if ( a == ATOM_cairo_device_type_xcb )
  { *device_type = CAIRO_DEVICE_TYPE_XCB;
  }
  else if ( a == ATOM_cairo_device_type_xlib )
  { *device_type = CAIRO_DEVICE_TYPE_XLIB;
  }
  else if ( a == ATOM_cairo_device_type_xml )
  { *device_type = CAIRO_DEVICE_TYPE_XML;
  }
  else if ( a == ATOM_cairo_device_type_cogl )
  { *device_type = CAIRO_DEVICE_TYPE_COGL;
  }
  else if ( a == ATOM_cairo_device_type_win32 )
  { *device_type = CAIRO_DEVICE_TYPE_WIN32;
  }
  else if ( a == ATOM_cairo_device_type_invalid )
  { *device_type = CAIRO_DEVICE_TYPE_INVALID;
  }
  else
  { return PL_domain_error("CairoDeviceType", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_device_type_to_term(cairo_device_type_t device_type,
                            term_t              t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_device_type_t: %d  --->  term: 0x%lx", device_type, t);

  if ( !ATOM_cairo_device_type_drm )
  {
    ATOM_cairo_device_type_drm = PL_new_atom("CAIRO_DEVICE_TYPE_DRM");
    ATOM_cairo_device_type_gl = PL_new_atom("CAIRO_DEVICE_TYPE_GL");
    ATOM_cairo_device_type_script = PL_new_atom("CAIRO_DEVICE_TYPE_SCRIPT");
    ATOM_cairo_device_type_xcb = PL_new_atom("CAIRO_DEVICE_TYPE_XCB");
    ATOM_cairo_device_type_xlib = PL_new_atom("CAIRO_DEVICE_TYPE_XLIB");
    ATOM_cairo_device_type_xml = PL_new_atom("CAIRO_DEVICE_TYPE_XML");
    ATOM_cairo_device_type_cogl = PL_new_atom("CAIRO_DEVICE_TYPE_COGL");
    ATOM_cairo_device_type_win32 = PL_new_atom("CAIRO_DEVICE_TYPE_WIN32");
    ATOM_cairo_device_type_invalid = PL_new_atom("CAIRO_DEVICE_TYPE_INVALID");
  }

  if ( device_type == CAIRO_DEVICE_TYPE_DRM )
  { PL_put_atom(t0, ATOM_cairo_device_type_drm);
  }
  else if ( device_type == CAIRO_DEVICE_TYPE_GL )
  { PL_put_atom(t0, ATOM_cairo_device_type_gl);
  }
  else if ( device_type == CAIRO_DEVICE_TYPE_SCRIPT )
  { PL_put_atom(t0, ATOM_cairo_device_type_script);
  }
  else if ( device_type == CAIRO_DEVICE_TYPE_XCB )
  { PL_put_atom(t0, ATOM_cairo_device_type_xcb);
  }
  else if ( device_type == CAIRO_DEVICE_TYPE_XLIB )
  { PL_put_atom(t0, ATOM_cairo_device_type_xlib);
  }
  else if ( device_type == CAIRO_DEVICE_TYPE_XML )
  { PL_put_atom(t0, ATOM_cairo_device_type_xml);
  }
  else if ( device_type == CAIRO_DEVICE_TYPE_COGL )
  { PL_put_atom(t0, ATOM_cairo_device_type_cogl);
  }
  else if ( device_type == CAIRO_DEVICE_TYPE_WIN32 )
  { PL_put_atom(t0, ATOM_cairo_device_type_win32);
  }
  else if ( device_type == CAIRO_DEVICE_TYPE_INVALID )
  { PL_put_atom(t0, ATOM_cairo_device_type_invalid);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLCAIRO_PRED_IMPL(plcairo_device_acquire)
{
  term_t t_device = FA0;

  cairo_device_t *device;
  cairo_status_t status;

  if ( !plcairo_term_to_device(t_device, &device) ) return FALSE;

  status = cairo_device_acquire(device);
  PLCAIRO_CHECK_DEVICE(device);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_device_finish)
{
  term_t t_device = FA0;

  cairo_device_t *device;

  if ( !plcairo_term_to_device(t_device, &device) ) return FALSE;

  cairo_device_finish(device);
  PLCAIRO_CHECK_DEVICE(device);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_device_flush)
{
  term_t t_device = FA0;

  cairo_device_t *device;

  if ( !plcairo_term_to_device(t_device, &device) ) return FALSE;

  cairo_device_flush(device);
  PLCAIRO_CHECK_DEVICE(device);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_device_get_type)
{
  term_t t_device = FA0;
  term_t t_device_type = FA1;

  cairo_device_t *device;
  cairo_device_type_t device_type;

  if ( !plcairo_term_to_device(t_device, &device) ) return FALSE;

  device_type = cairo_device_get_type(device);
  PLCAIRO_CHECK_DEVICE(device);

  if ( !plcairo_device_type_to_term(device_type, t_device_type) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_device_observer_elapsed)
{
  term_t t_device = FA0;
  term_t t_elapsed = FA1;

  cairo_device_t *device;
  double elapsed;

  if ( !plcairo_term_to_device(t_device, &device) ) return FALSE;

  elapsed = cairo_device_observer_elapsed(device);
  PLCAIRO_CHECK_DEVICE(device);

  if ( !plcairo_double_to_term(elapsed, t_elapsed) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_device_observer_fill_elapsed)
{
  term_t t_device = FA0;
  term_t t_fill_elapsed = FA1;

  cairo_device_t *device;
  double fill_elapsed;

  if ( !plcairo_term_to_device(t_device, &device) ) return FALSE;

  fill_elapsed = cairo_device_observer_fill_elapsed(device);
  PLCAIRO_CHECK_DEVICE(device);

  if ( !plcairo_double_to_term(fill_elapsed, t_fill_elapsed) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_device_observer_glyphs_elapsed)
{
  term_t t_device = FA0;
  term_t t_glyphs_elapsed = FA1;

  cairo_device_t *device;
  double glyphs_elapsed;

  if ( !plcairo_term_to_device(t_device, &device) ) return FALSE;

  glyphs_elapsed = cairo_device_observer_glyphs_elapsed(device);
  PLCAIRO_CHECK_DEVICE(device);

  if ( !plcairo_double_to_term(glyphs_elapsed, t_glyphs_elapsed) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_device_observer_mask_elapsed)
{
  term_t t_device = FA0;
  term_t t_mask_elapsed = FA1;

  cairo_device_t *device;
  double mask_elapsed;

  if ( !plcairo_term_to_device(t_device, &device) ) return FALSE;

  mask_elapsed = cairo_device_observer_mask_elapsed(device);
  PLCAIRO_CHECK_DEVICE(device);

  if ( !plcairo_double_to_term(mask_elapsed, t_mask_elapsed) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_device_observer_paint_elapsed)
{
  term_t t_device = FA0;
  term_t t_paint_elapsed = FA1;

  cairo_device_t *device;
  double paint_elapsed;

  if ( !plcairo_term_to_device(t_device, &device) ) return FALSE;

  paint_elapsed = cairo_device_observer_paint_elapsed(device);
  PLCAIRO_CHECK_DEVICE(device);

  if ( !plcairo_double_to_term(paint_elapsed, t_paint_elapsed) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_device_observer_print)
{
  term_t t_device = FA0;
  term_t t_stream = FA1;

  cairo_device_t *device;
  void *closure;

  if ( !plcairo_term_to_device(t_device, &device) ) return FALSE;
  if ( !plcairo_term_to_closure(t_stream, &closure) ) return FALSE;

  cairo_device_observer_print(device, &plcairo_write_func, closure);
  PLCAIRO_CHECK_DEVICE(device);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_device_observer_stroke_elapsed)
{
  term_t t_device = FA0;
  term_t t_stroke_elapsed = FA1;

  cairo_device_t *device;
  double stroke_elapsed;

  if ( !plcairo_term_to_device(t_device, &device) ) return FALSE;

  stroke_elapsed = cairo_device_observer_stroke_elapsed(device);
  PLCAIRO_CHECK_DEVICE(device);

  if ( !plcairo_double_to_term(stroke_elapsed, t_stroke_elapsed) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_device_release)
{
  term_t t_device = FA0;

  cairo_device_t *device;

  if ( !plcairo_term_to_device(t_device, &device) ) return FALSE;

  cairo_device_release(device);
  PLCAIRO_CHECK_DEVICE(device);

  return TRUE;
}
