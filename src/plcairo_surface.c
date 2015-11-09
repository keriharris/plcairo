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


/* cairo_surface_t */
cairo_bool_t
plcairo_term_to_surface(term_t            t,
                        cairo_surface_t **surface)
{
  PLGIBlob *blob;

  PLGI_debug("    term: 0x%lx  --->  cairo_surface_t: %p", t, *surface);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoSurface", t);
  }

  if ( blob->gtype != G_TYPE_NONE &&
       !g_type_is_a( blob->gtype, CAIRO_GOBJECT_TYPE_SURFACE ) )
  { return PL_type_error("CairoSurface", t);
  }

  *surface = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_surface_to_term(cairo_surface_t *surface,
                        term_t           t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLGI_debug("    cairo_surface_t: %p  --->  term: 0x%lx", surface, t);

  if ( !surface )
  { return ( plgi_put_null(t0) && PL_unify(t, t0) );
  }

  PLCAIRO_CHECK_SURFACE(surface);

  data = surface;
  blob_type = PLGI_BLOB_BOXED;

  if ( !plgi_put_blob(blob_type, CAIRO_GOBJECT_TYPE_SURFACE,
                      PL_new_atom("CairoSurface"), TRUE, data, t0) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}


/* cairo_content_t */
static atom_t ATOM_cairo_content_color = 0;
static atom_t ATOM_cairo_content_alpha = 0;
static atom_t ATOM_cairo_content_color_alpha = 0;

cairo_bool_t
plcairo_term_to_content(term_t           t,
                        cairo_content_t *content)
{
  atom_t a;

  PLGI_debug("    term: 0x%lx  --->  cairo_content_t: %p", t, content);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoContent", t);
  }

  if ( !ATOM_cairo_content_color )
  {
    ATOM_cairo_content_color = PL_new_atom("CAIRO_CONTENT_COLOR");
    ATOM_cairo_content_alpha = PL_new_atom("CAIRO_CONTENT_ALPHA");
    ATOM_cairo_content_color_alpha = PL_new_atom("CAIRO_CONTENT_COLOR_ALPHA");
  }

  if ( a == ATOM_cairo_content_color )
  { *content = CAIRO_CONTENT_COLOR;
  }
  else if ( a == ATOM_cairo_content_alpha )
  { *content = CAIRO_CONTENT_ALPHA;
  }
  else if ( a == ATOM_cairo_content_color_alpha )
  { *content = CAIRO_CONTENT_COLOR_ALPHA;
  }
  else
  { return PL_domain_error("CairoContent", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_content_to_term(cairo_content_t content,
                        term_t          t)
{
  term_t t0 = PL_new_term_ref();

  PLGI_debug("    cairo_content_t: %d  --->  term: 0x%lx", content, t);

  if ( !ATOM_cairo_content_color )
  {
    ATOM_cairo_content_color = PL_new_atom("CAIRO_CONTENT_COLOR");
    ATOM_cairo_content_alpha = PL_new_atom("CAIRO_CONTENT_ALPHA");
    ATOM_cairo_content_color_alpha = PL_new_atom("CAIRO_CONTENT_COLOR_ALPHA");
  }

  if ( content == CAIRO_CONTENT_COLOR )
  { PL_put_atom(t0, ATOM_cairo_content_color);
  }
  else if ( content == CAIRO_CONTENT_ALPHA )
  { PL_put_atom(t0, ATOM_cairo_content_alpha);
  }
  else if ( content == CAIRO_CONTENT_COLOR_ALPHA )
  { PL_put_atom(t0, ATOM_cairo_content_color_alpha);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}


/* cairo_surface_type_t */
static atom_t ATOM_cairo_surface_type_image = 0;
static atom_t ATOM_cairo_surface_type_pdf = 0;
static atom_t ATOM_cairo_surface_type_ps = 0;
static atom_t ATOM_cairo_surface_type_xlib = 0;
static atom_t ATOM_cairo_surface_type_xcb = 0;
static atom_t ATOM_cairo_surface_type_glitz = 0;
static atom_t ATOM_cairo_surface_type_quartz = 0;
static atom_t ATOM_cairo_surface_type_win32 = 0;
static atom_t ATOM_cairo_surface_type_beos = 0;
static atom_t ATOM_cairo_surface_type_directfb = 0;
static atom_t ATOM_cairo_surface_type_svg = 0;
static atom_t ATOM_cairo_surface_type_os2 = 0;
static atom_t ATOM_cairo_surface_type_win32_printing = 0;
static atom_t ATOM_cairo_surface_type_quartz_image = 0;
static atom_t ATOM_cairo_surface_type_script = 0;
static atom_t ATOM_cairo_surface_type_qt = 0;
static atom_t ATOM_cairo_surface_type_recording = 0;
static atom_t ATOM_cairo_surface_type_vg = 0;
static atom_t ATOM_cairo_surface_type_gl = 0;
static atom_t ATOM_cairo_surface_type_drm = 0;
static atom_t ATOM_cairo_surface_type_tee = 0;
static atom_t ATOM_cairo_surface_type_xml = 0;
static atom_t ATOM_cairo_surface_type_skia = 0;
static atom_t ATOM_cairo_surface_type_subsurface = 0;
static atom_t ATOM_cairo_surface_type_cogl = 0;

cairo_bool_t
plcairo_term_to_surface_type(term_t                t,
                             cairo_surface_type_t *surface_type)
{
  atom_t a;

  PLGI_debug("    term: 0x%lx  --->  cairo_surface_type_t: %p", t, surface_type);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoSurfaceType", t);
  }

  if ( !ATOM_cairo_surface_type_image )
  {
    ATOM_cairo_surface_type_image = PL_new_atom("CAIRO_SURFACE_TYPE_IMAGE");
    ATOM_cairo_surface_type_pdf = PL_new_atom("CAIRO_SURFACE_TYPE_PDF");
    ATOM_cairo_surface_type_ps = PL_new_atom("CAIRO_SURFACE_TYPE_PS");
    ATOM_cairo_surface_type_xlib = PL_new_atom("CAIRO_SURFACE_TYPE_XLIB");
    ATOM_cairo_surface_type_xcb = PL_new_atom("CAIRO_SURFACE_TYPE_XCB");
    ATOM_cairo_surface_type_glitz = PL_new_atom("CAIRO_SURFACE_TYPE_GLITZ");
    ATOM_cairo_surface_type_quartz = PL_new_atom("CAIRO_SURFACE_TYPE_QUARTZ");
    ATOM_cairo_surface_type_win32 = PL_new_atom("CAIRO_SURFACE_TYPE_WIN32");
    ATOM_cairo_surface_type_beos = PL_new_atom("CAIRO_SURFACE_TYPE_BEOS");
    ATOM_cairo_surface_type_directfb = PL_new_atom("CAIRO_SURFACE_TYPE_DIRECTFB");
    ATOM_cairo_surface_type_svg = PL_new_atom("CAIRO_SURFACE_TYPE_SVG");
    ATOM_cairo_surface_type_os2 = PL_new_atom("CAIRO_SURFACE_TYPE_OS2");
    ATOM_cairo_surface_type_win32_printing = PL_new_atom("CAIRO_SURFACE_TYPE_WIN32_PRINTING");
    ATOM_cairo_surface_type_quartz_image = PL_new_atom("CAIRO_SURFACE_TYPE_QUARTZ_IMAGE");
    ATOM_cairo_surface_type_script = PL_new_atom("CAIRO_SURFACE_TYPE_SCRIPT");
    ATOM_cairo_surface_type_qt = PL_new_atom("CAIRO_SURFACE_TYPE_QT");
    ATOM_cairo_surface_type_recording = PL_new_atom("CAIRO_SURFACE_TYPE_RECORDING");
    ATOM_cairo_surface_type_vg = PL_new_atom("CAIRO_SURFACE_TYPE_VG");
    ATOM_cairo_surface_type_gl = PL_new_atom("CAIRO_SURFACE_TYPE_GL");
    ATOM_cairo_surface_type_drm = PL_new_atom("CAIRO_SURFACE_TYPE_DRM");
    ATOM_cairo_surface_type_tee = PL_new_atom("CAIRO_SURFACE_TYPE_TEE");
    ATOM_cairo_surface_type_xml = PL_new_atom("CAIRO_SURFACE_TYPE_XML");
    ATOM_cairo_surface_type_skia = PL_new_atom("CAIRO_SURFACE_TYPE_SKIA");
    ATOM_cairo_surface_type_subsurface = PL_new_atom("CAIRO_SURFACE_TYPE_SUBSURFACE");
    ATOM_cairo_surface_type_cogl = PL_new_atom("CAIRO_SURFACE_TYPE_COGL");
  }

  if ( a == ATOM_cairo_surface_type_image )
  { *surface_type = CAIRO_SURFACE_TYPE_IMAGE;
  }
  else if ( a == ATOM_cairo_surface_type_pdf )
  { *surface_type = CAIRO_SURFACE_TYPE_PDF;
  }
  else if ( a == ATOM_cairo_surface_type_ps )
  { *surface_type = CAIRO_SURFACE_TYPE_PS;
  }
  else if ( a == ATOM_cairo_surface_type_xlib )
  { *surface_type = CAIRO_SURFACE_TYPE_XLIB;
  }
  else if ( a == ATOM_cairo_surface_type_xcb )
  { *surface_type = CAIRO_SURFACE_TYPE_XCB;
  }
  else if ( a == ATOM_cairo_surface_type_glitz )
  { *surface_type = CAIRO_SURFACE_TYPE_GLITZ;
  }
  else if ( a == ATOM_cairo_surface_type_quartz )
  { *surface_type = CAIRO_SURFACE_TYPE_QUARTZ;
  }
  else if ( a == ATOM_cairo_surface_type_win32 )
  { *surface_type = CAIRO_SURFACE_TYPE_WIN32;
  }
  else if ( a == ATOM_cairo_surface_type_beos )
  { *surface_type = CAIRO_SURFACE_TYPE_BEOS;
  }
  else if ( a == ATOM_cairo_surface_type_directfb )
  { *surface_type = CAIRO_SURFACE_TYPE_DIRECTFB;
  }
  else if ( a == ATOM_cairo_surface_type_svg )
  { *surface_type = CAIRO_SURFACE_TYPE_SVG;
  }
  else if ( a == ATOM_cairo_surface_type_os2 )
  { *surface_type = CAIRO_SURFACE_TYPE_OS2;
  }
  else if ( a == ATOM_cairo_surface_type_win32_printing )
  { *surface_type = CAIRO_SURFACE_TYPE_WIN32_PRINTING;
  }
  else if ( a == ATOM_cairo_surface_type_quartz_image )
  { *surface_type = CAIRO_SURFACE_TYPE_QUARTZ_IMAGE;
  }
  else if ( a == ATOM_cairo_surface_type_script )
  { *surface_type = CAIRO_SURFACE_TYPE_SCRIPT;
  }
  else if ( a == ATOM_cairo_surface_type_qt )
  { *surface_type = CAIRO_SURFACE_TYPE_QT;
  }
  else if ( a == ATOM_cairo_surface_type_recording )
  { *surface_type = CAIRO_SURFACE_TYPE_RECORDING;
  }
  else if ( a == ATOM_cairo_surface_type_vg )
  { *surface_type = CAIRO_SURFACE_TYPE_VG;
  }
  else if ( a == ATOM_cairo_surface_type_gl )
  { *surface_type = CAIRO_SURFACE_TYPE_GL;
  }
  else if ( a == ATOM_cairo_surface_type_drm )
  { *surface_type = CAIRO_SURFACE_TYPE_DRM;
  }
  else if ( a == ATOM_cairo_surface_type_tee )
  { *surface_type = CAIRO_SURFACE_TYPE_TEE;
  }
  else if ( a == ATOM_cairo_surface_type_xml )
  { *surface_type = CAIRO_SURFACE_TYPE_XML;
  }
  else if ( a == ATOM_cairo_surface_type_skia )
  { *surface_type = CAIRO_SURFACE_TYPE_SKIA;
  }
  else if ( a == ATOM_cairo_surface_type_subsurface )
  { *surface_type = CAIRO_SURFACE_TYPE_SUBSURFACE;
  }
  else if ( a == ATOM_cairo_surface_type_cogl )
  { *surface_type = CAIRO_SURFACE_TYPE_COGL;
  }
  else
  { return PL_domain_error("CairoSurfaceType", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_surface_type_to_term(cairo_surface_type_t surface_type,
                             term_t               t)
{
  term_t t0 = PL_new_term_ref();

  PLGI_debug("    cairo_surface_type_t: %d  --->  term: 0x%lx", surface_type, t);

  if ( !ATOM_cairo_surface_type_image )
  {
    ATOM_cairo_surface_type_image = PL_new_atom("CAIRO_SURFACE_TYPE_IMAGE");
    ATOM_cairo_surface_type_pdf = PL_new_atom("CAIRO_SURFACE_TYPE_PDF");
    ATOM_cairo_surface_type_ps = PL_new_atom("CAIRO_SURFACE_TYPE_PS");
    ATOM_cairo_surface_type_xlib = PL_new_atom("CAIRO_SURFACE_TYPE_XLIB");
    ATOM_cairo_surface_type_xcb = PL_new_atom("CAIRO_SURFACE_TYPE_XCB");
    ATOM_cairo_surface_type_glitz = PL_new_atom("CAIRO_SURFACE_TYPE_GLITZ");
    ATOM_cairo_surface_type_quartz = PL_new_atom("CAIRO_SURFACE_TYPE_QUARTZ");
    ATOM_cairo_surface_type_win32 = PL_new_atom("CAIRO_SURFACE_TYPE_WIN32");
    ATOM_cairo_surface_type_beos = PL_new_atom("CAIRO_SURFACE_TYPE_BEOS");
    ATOM_cairo_surface_type_directfb = PL_new_atom("CAIRO_SURFACE_TYPE_DIRECTFB");
    ATOM_cairo_surface_type_svg = PL_new_atom("CAIRO_SURFACE_TYPE_SVG");
    ATOM_cairo_surface_type_os2 = PL_new_atom("CAIRO_SURFACE_TYPE_OS2");
    ATOM_cairo_surface_type_win32_printing = PL_new_atom("CAIRO_SURFACE_TYPE_WIN32_PRINTING");
    ATOM_cairo_surface_type_quartz_image = PL_new_atom("CAIRO_SURFACE_TYPE_QUARTZ_IMAGE");
    ATOM_cairo_surface_type_script = PL_new_atom("CAIRO_SURFACE_TYPE_SCRIPT");
    ATOM_cairo_surface_type_qt = PL_new_atom("CAIRO_SURFACE_TYPE_QT");
    ATOM_cairo_surface_type_recording = PL_new_atom("CAIRO_SURFACE_TYPE_RECORDING");
    ATOM_cairo_surface_type_vg = PL_new_atom("CAIRO_SURFACE_TYPE_VG");
    ATOM_cairo_surface_type_gl = PL_new_atom("CAIRO_SURFACE_TYPE_GL");
    ATOM_cairo_surface_type_drm = PL_new_atom("CAIRO_SURFACE_TYPE_DRM");
    ATOM_cairo_surface_type_tee = PL_new_atom("CAIRO_SURFACE_TYPE_TEE");
    ATOM_cairo_surface_type_xml = PL_new_atom("CAIRO_SURFACE_TYPE_XML");
    ATOM_cairo_surface_type_skia = PL_new_atom("CAIRO_SURFACE_TYPE_SKIA");
    ATOM_cairo_surface_type_subsurface = PL_new_atom("CAIRO_SURFACE_TYPE_SUBSURFACE");
    ATOM_cairo_surface_type_cogl = PL_new_atom("CAIRO_SURFACE_TYPE_COGL");
  }

  if ( surface_type == CAIRO_SURFACE_TYPE_IMAGE )
  { PL_put_atom(t0, ATOM_cairo_surface_type_image);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_PDF )
  { PL_put_atom(t0, ATOM_cairo_surface_type_pdf);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_PS )
  { PL_put_atom(t0, ATOM_cairo_surface_type_ps);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_XLIB )
  { PL_put_atom(t0, ATOM_cairo_surface_type_xlib);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_XCB )
  { PL_put_atom(t0, ATOM_cairo_surface_type_xcb);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_GLITZ )
  { PL_put_atom(t0, ATOM_cairo_surface_type_glitz);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_QUARTZ )
  { PL_put_atom(t0, ATOM_cairo_surface_type_quartz);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_WIN32 )
  { PL_put_atom(t0, ATOM_cairo_surface_type_win32);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_BEOS )
  { PL_put_atom(t0, ATOM_cairo_surface_type_beos);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_DIRECTFB )
  { PL_put_atom(t0, ATOM_cairo_surface_type_directfb);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_SVG )
  { PL_put_atom(t0, ATOM_cairo_surface_type_svg);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_OS2 )
  { PL_put_atom(t0, ATOM_cairo_surface_type_os2);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_WIN32_PRINTING )
  { PL_put_atom(t0, ATOM_cairo_surface_type_win32_printing);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_QUARTZ_IMAGE )
  { PL_put_atom(t0, ATOM_cairo_surface_type_quartz_image);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_SCRIPT )
  { PL_put_atom(t0, ATOM_cairo_surface_type_script);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_QT )
  { PL_put_atom(t0, ATOM_cairo_surface_type_qt);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_RECORDING )
  { PL_put_atom(t0, ATOM_cairo_surface_type_recording);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_VG )
  { PL_put_atom(t0, ATOM_cairo_surface_type_vg);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_GL )
  { PL_put_atom(t0, ATOM_cairo_surface_type_gl);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_DRM )
  { PL_put_atom(t0, ATOM_cairo_surface_type_drm);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_TEE )
  { PL_put_atom(t0, ATOM_cairo_surface_type_tee);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_XML )
  { PL_put_atom(t0, ATOM_cairo_surface_type_xml);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_SKIA )
  { PL_put_atom(t0, ATOM_cairo_surface_type_skia);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_SUBSURFACE )
  { PL_put_atom(t0, ATOM_cairo_surface_type_subsurface);
  }
  else if ( surface_type == CAIRO_SURFACE_TYPE_COGL )
  { PL_put_atom(t0, ATOM_cairo_surface_type_cogl);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLGI_PRED_IMPL(plcairo_surface_copy_page)
{
  term_t t_surface = FA0;

  cairo_surface_t *surface;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  cairo_surface_copy_page(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_create_for_rectangle)
{
  term_t t_target = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;
  term_t t_width = FA3;
  term_t t_height = FA4;
  term_t t_surface = FA5;

  cairo_surface_t *target;
  double x, y, width, height;
  cairo_surface_t *surface;

  if ( !plcairo_term_to_surface(t_target, &target) ) return FALSE;
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;
  if ( !plcairo_term_to_double(t_width, &width) ) return FALSE;
  if ( !plcairo_term_to_double(t_height, &height) ) return FALSE;

  surface = cairo_surface_create_for_rectangle(target, x, y, width, height);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}

PLGI_PRED_IMPL(plcairo_surface_create_similar)
{
  term_t t_other = FA0;
  term_t t_content = FA1;
  term_t t_width = FA2;
  term_t t_height = FA3;
  term_t t_surface = FA4;

  cairo_surface_t *other;
  cairo_content_t content;
  int width, height;
  cairo_surface_t *surface;

  if ( !plcairo_term_to_surface(t_other, &other) ) return FALSE;
  if ( !plcairo_term_to_content(t_content, &content) ) return FALSE;
  if ( !plcairo_term_to_int(t_width, &width) ) return FALSE;
  if ( !plcairo_term_to_int(t_height, &height) ) return FALSE;

  surface = cairo_surface_create_similar(other, content, width, height);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}

PLGI_PRED_IMPL(plcairo_surface_create_similar_image)
{
  term_t t_other = FA0;
  term_t t_format = FA1;
  term_t t_width = FA2;
  term_t t_height = FA3;
  term_t t_surface = FA4;

  cairo_surface_t *other;
  cairo_format_t format;
  int width, height;
  cairo_surface_t *surface;

  if ( !plcairo_term_to_surface(t_other, &other) ) return FALSE;
  if ( !plcairo_term_to_format(t_format, &format) ) return FALSE;
  if ( !plcairo_term_to_int(t_width, &width) ) return FALSE;
  if ( !plcairo_term_to_int(t_height, &height) ) return FALSE;

  surface = cairo_surface_create_similar_image(other, format, width, height);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}

PLGI_PRED_IMPL(plcairo_surface_finish)
{
  term_t t_surface = FA0;

  cairo_surface_t *surface;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  cairo_surface_finish(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_flush)
{
  term_t t_surface = FA0;

  cairo_surface_t *surface;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  cairo_surface_flush(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_get_content)
{
  term_t t_surface = FA0;
  term_t t_content = FA1;

  cairo_surface_t *surface;
  cairo_content_t content;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  content = cairo_surface_get_content(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_content_to_term(content, t_content) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_get_device)
{
  term_t t_surface = FA0;
  term_t t_device = FA1;

  cairo_surface_t *surface;
  cairo_device_t *device;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  device = cairo_surface_get_device(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_device_to_term(device, t_device) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_get_device_offset)
{
  term_t t_surface = FA0;
  term_t t_x_offset = FA1;
  term_t t_y_offset = FA2;

  cairo_surface_t *surface;
  double x_offset, y_offset;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  cairo_surface_get_device_offset(surface, &x_offset, &y_offset);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_double_to_term(x_offset, t_x_offset) ) return FALSE;
  if ( !plcairo_double_to_term(y_offset, t_y_offset) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_get_device_scale)
{
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 14, 0)
  term_t t_surface = FA0;
  term_t t_x_scale = FA1;
  term_t t_y_scale = FA2;

  cairo_surface_t *surface;
  double x_scale, y_scale;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  cairo_surface_get_device_scale(surface, &x_scale, &y_scale);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_double_to_term(x_scale, t_x_scale) ) return FALSE;
  if ( !plcairo_double_to_term(y_scale, t_y_scale) ) return FALSE;

  return TRUE;
#else
  return plcairo_raise_error("cairo_surface_get_device_scale/3 requires Cairo >= v1.14");
#endif
}


PLGI_PRED_IMPL(plcairo_surface_get_fallback_resolution)
{
  term_t t_surface = FA0;
  term_t t_x_pixels_per_inch = FA1;
  term_t t_y_pixels_per_inch = FA2;

  cairo_surface_t *surface;
  double x_pixels_per_inch, y_pixels_per_inch;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  cairo_surface_get_fallback_resolution(surface, &x_pixels_per_inch, &y_pixels_per_inch);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_double_to_term(x_pixels_per_inch, t_x_pixels_per_inch) ) return FALSE;
  if ( !plcairo_double_to_term(y_pixels_per_inch, t_y_pixels_per_inch) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_get_font_options)
{
  term_t t_surface = FA0;
  term_t t_options = FA1;

  cairo_surface_t *surface;
  cairo_font_options_t *options;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  options = cairo_font_options_create();
  cairo_surface_get_font_options(surface, options);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_font_options_to_term(options, t_options) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_get_type)
{
  term_t t_surface = FA0;
  term_t t_surface_type = FA1;

  cairo_surface_t *surface;
  cairo_surface_type_t surface_type;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  surface_type = cairo_surface_get_type(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_type_to_term(surface_type, t_surface_type) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_has_show_text_glyphs)
{
  term_t t_surface = FA0;

  cairo_surface_t *surface;
  cairo_bool_t ret;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  ret = cairo_surface_has_show_text_glyphs(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  return (ret != 0);
}


PLGI_PRED_IMPL(plcairo_surface_map_to_image)
{
  term_t t_surface = FA0;
  term_t t_extents = FA1;
  term_t t_image = FA2;

  cairo_surface_t *surface;
  cairo_rectangle_int_t *extents;
  cairo_surface_t *image;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_rectangle_int(t_extents, &extents) ) return FALSE;

  image = cairo_surface_map_to_image(surface, extents);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(image, t_image) ) return FALSE;

  return TRUE;
}

PLGI_PRED_IMPL(plcairo_surface_mark_dirty)
{
  term_t t_surface = FA0;

  cairo_surface_t *surface;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  cairo_surface_mark_dirty(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_mark_dirty_rectangle)
{
  term_t t_surface = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;
  term_t t_width = FA3;
  term_t t_height = FA4;

  cairo_surface_t *surface;
  double x, y, width, height;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;
  if ( !plcairo_term_to_double(t_width, &width) ) return FALSE;
  if ( !plcairo_term_to_double(t_height, &height) ) return FALSE;

  cairo_surface_mark_dirty_rectangle(surface, x, y, width, height);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_set_device_offset)
{
  term_t t_surface = FA0;
  term_t t_x_offset = FA1;
  term_t t_y_offset = FA2;

  cairo_surface_t *surface;
  double x_offset, y_offset;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_double(t_x_offset, &x_offset) ) return FALSE;
  if ( !plcairo_term_to_double(t_y_offset, &y_offset) ) return FALSE;

  cairo_surface_set_device_offset(surface, x_offset, y_offset);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_set_device_scale)
{
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 14, 0)
  term_t t_surface = FA0;
  term_t t_x_scale = FA1;
  term_t t_y_scale = FA2;

  cairo_surface_t *surface;
  double x_scale, y_scale;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_double(t_x_scale, &x_scale) ) return FALSE;
  if ( !plcairo_term_to_double(t_y_scale, &y_scale) ) return FALSE;

  cairo_surface_set_device_scale(surface, x_scale, y_scale);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
#else
  return plcairo_raise_error("cairo_surface_set_device_scale/3 requires Cairo >= v1.14");
#endif
}


PLGI_PRED_IMPL(plcairo_surface_set_fallback_resolution)
{
  term_t t_surface = FA0;
  term_t t_x_pixels_per_inch = FA1;
  term_t t_y_pixels_per_inch = FA2;

  cairo_surface_t *surface;
  double x_pixels_per_inch, y_pixels_per_inch;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_double(t_x_pixels_per_inch, &x_pixels_per_inch) ) return FALSE;
  if ( !plcairo_term_to_double(t_y_pixels_per_inch, &y_pixels_per_inch) ) return FALSE;

  cairo_surface_set_fallback_resolution(surface, x_pixels_per_inch, y_pixels_per_inch);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_show_page)
{
  term_t t_surface = FA0;

  cairo_surface_t *surface;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  cairo_surface_show_page(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_surface_supports_mime_type)
{
  term_t t_surface = FA0;
  term_t t_mime_type = FA1;

  cairo_surface_t *surface;
  char *mime_type;
  cairo_bool_t ret;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_string(t_mime_type, &mime_type) ) return FALSE;

  ret = cairo_surface_supports_mime_type(surface, mime_type);
  PLCAIRO_CHECK_SURFACE(surface);

  return (ret != 0);
}


PLGI_PRED_IMPL(plcairo_surface_unmap_image)
{
  term_t t_surface = FA0;
  term_t t_image = FA1;

  cairo_surface_t *surface;
  cairo_surface_t *image;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_surface(t_image, &image) ) return FALSE;

  cairo_surface_unmap_image(surface, image);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}
