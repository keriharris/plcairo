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


/* cairo_font_options_t */
cairo_bool_t
plcairo_term_to_font_options(term_t                 t,
                             cairo_font_options_t **font_options)
{
  PLGIBlob *blob;

  PLGI_debug("    term: 0x%lx  --->  cairo_font_options_t: %p", t, *font_options);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoFontOptions", t);
  }

  if ( blob->gtype != G_TYPE_NONE &&
       !g_type_is_a( blob->gtype, CAIRO_GOBJECT_TYPE_FONT_OPTIONS ) )
  { return PL_type_error("CairoFontOptions", t);
  }

  *font_options = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_font_options_to_term(cairo_font_options_t *font_options,
                             term_t                t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLGI_debug("    cairo_font_options_t: %p  --->  term: 0x%lx", font_options, t);

  if ( !font_options )
  { return ( plgi_put_null(t0) && PL_unify(t, t0) );
  }

  data = font_options;
  blob_type = PLGI_BLOB_BOXED;

  if ( !plgi_put_blob(blob_type, CAIRO_GOBJECT_TYPE_FONT_OPTIONS,
                      PL_new_atom("CairoFontOptions"), TRUE, data, t0) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}


/* cairo_hint_metrics_t */
static atom_t ATOM_cairo_hint_metrics_default = 0;
static atom_t ATOM_cairo_hint_metrics_off = 0;
static atom_t ATOM_cairo_hint_metrics_on = 0;

cairo_bool_t
plcairo_term_to_hint_metrics(term_t                t,
                             cairo_hint_metrics_t *hint_metrics)
{
  atom_t a;

  PLGI_debug("    term: 0x%lx  --->  cairo_hint_metrics_t: %p", t, hint_metrics);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoHintMetrics", t);
  }

  if ( !ATOM_cairo_hint_metrics_default )
  {
    ATOM_cairo_hint_metrics_default = PL_new_atom("CAIRO_HINT_METRICS_DEFAULT");
    ATOM_cairo_hint_metrics_off = PL_new_atom("CAIRO_HINT_METRICS_OFF");
    ATOM_cairo_hint_metrics_on = PL_new_atom("CAIRO_HINT_METRICS_ON");
  }

  if ( a == ATOM_cairo_hint_metrics_default )
  { *hint_metrics = CAIRO_HINT_METRICS_DEFAULT;
  }
  else if ( a == ATOM_cairo_hint_metrics_off )
  { *hint_metrics = CAIRO_HINT_METRICS_OFF;
  }
  else if ( a == ATOM_cairo_hint_metrics_on )
  { *hint_metrics = CAIRO_HINT_METRICS_ON;
  }
  else
  { return PL_domain_error("CairoHintMetrics", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_hint_metrics_to_term(cairo_hint_metrics_t hint_metrics,
                             term_t               t)
{
  term_t t0 = PL_new_term_ref();

  PLGI_debug("    cairo_hint_metrics_t: %d  --->  term: 0x%lx", hint_metrics, t);

  if ( !ATOM_cairo_hint_metrics_default )
  {
    ATOM_cairo_hint_metrics_default = PL_new_atom("CAIRO_HINT_METRICS_DEFAULT");
    ATOM_cairo_hint_metrics_off = PL_new_atom("CAIRO_HINT_METRICS_OFF");
    ATOM_cairo_hint_metrics_on = PL_new_atom("CAIRO_HINT_METRICS_ON");
  }

  if ( hint_metrics == CAIRO_HINT_METRICS_DEFAULT )
  { PL_put_atom(t0, ATOM_cairo_hint_metrics_default);
  }
  else if ( hint_metrics == CAIRO_HINT_METRICS_OFF )
  { PL_put_atom(t0, ATOM_cairo_hint_metrics_off);
  }
  else if ( hint_metrics == CAIRO_HINT_METRICS_ON )
  { PL_put_atom(t0, ATOM_cairo_hint_metrics_on);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}


/* cairo_hint_style_t */
static atom_t ATOM_cairo_hint_style_default = 0;
static atom_t ATOM_cairo_hint_style_none = 0;
static atom_t ATOM_cairo_hint_style_slight = 0;
static atom_t ATOM_cairo_hint_style_medium = 0;
static atom_t ATOM_cairo_hint_style_full = 0;

cairo_bool_t
plcairo_term_to_hint_style(term_t              t,
                           cairo_hint_style_t *hint_style)
{
  atom_t a;

  PLGI_debug("    term: 0x%lx  --->  cairo_hint_style_t: %p", t, hint_style);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoHintStyle", t);
  }

  if ( !ATOM_cairo_hint_style_default )
  {
    ATOM_cairo_hint_style_default = PL_new_atom("CAIRO_HINT_STYLE_DEFAULT");
    ATOM_cairo_hint_style_none = PL_new_atom("CAIRO_HINT_STYLE_NONE");
    ATOM_cairo_hint_style_slight = PL_new_atom("CAIRO_HINT_STYLE_SLIGHT");
    ATOM_cairo_hint_style_medium = PL_new_atom("CAIRO_HINT_STYLE_MEDIUM");
    ATOM_cairo_hint_style_full = PL_new_atom("CAIRO_HINT_STYLE_FULL");
  }

  if ( a == ATOM_cairo_hint_style_default )
  { *hint_style = CAIRO_HINT_STYLE_DEFAULT;
  }
  else if ( a == ATOM_cairo_hint_style_none )
  { *hint_style = CAIRO_HINT_STYLE_NONE;
  }
  else if ( a == ATOM_cairo_hint_style_slight )
  { *hint_style = CAIRO_HINT_STYLE_SLIGHT;
  }
  else if ( a == ATOM_cairo_hint_style_medium )
  { *hint_style = CAIRO_HINT_STYLE_MEDIUM;
  }
  else if ( a == ATOM_cairo_hint_style_full )
  { *hint_style = CAIRO_HINT_STYLE_FULL;
  }
  else
  { return PL_domain_error("CairoHintStyle", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_hint_style_to_term(cairo_hint_style_t hint_style,
                           term_t             t)
{
  term_t t0 = PL_new_term_ref();

  PLGI_debug("    cairo_hint_style_t: %d  --->  term: 0x%lx", hint_style, t);

  if ( !ATOM_cairo_hint_style_default )
  {
    ATOM_cairo_hint_style_default = PL_new_atom("CAIRO_HINT_STYLE_DEFAULT");
    ATOM_cairo_hint_style_none = PL_new_atom("CAIRO_HINT_STYLE_NONE");
    ATOM_cairo_hint_style_slight = PL_new_atom("CAIRO_HINT_STYLE_SLIGHT");
    ATOM_cairo_hint_style_medium = PL_new_atom("CAIRO_HINT_STYLE_MEDIUM");
    ATOM_cairo_hint_style_full = PL_new_atom("CAIRO_HINT_STYLE_FULL");
  }

  if ( hint_style == CAIRO_HINT_STYLE_DEFAULT )
  { PL_put_atom(t0, ATOM_cairo_hint_style_default);
  }
  else if ( hint_style == CAIRO_HINT_STYLE_NONE )
  { PL_put_atom(t0, ATOM_cairo_hint_style_none);
  }
  else if ( hint_style == CAIRO_HINT_STYLE_SLIGHT )
  { PL_put_atom(t0, ATOM_cairo_hint_style_slight);
  }
  else if ( hint_style == CAIRO_HINT_STYLE_MEDIUM )
  { PL_put_atom(t0, ATOM_cairo_hint_style_medium);
  }
  else if ( hint_style == CAIRO_HINT_STYLE_FULL )
  { PL_put_atom(t0, ATOM_cairo_hint_style_full);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}


/* cairo_subpixel_order_t */
static atom_t ATOM_cairo_subpixel_order_default = 0;
static atom_t ATOM_cairo_subpixel_order_rgb = 0;
static atom_t ATOM_cairo_subpixel_order_bgr = 0;
static atom_t ATOM_cairo_subpixel_order_vrgb = 0;
static atom_t ATOM_cairo_subpixel_order_vbgr = 0;

cairo_bool_t
plcairo_term_to_subpixel_order(term_t             t,
                               cairo_subpixel_order_t *subpixel_order)
{
  atom_t a;

  PLGI_debug("    term: 0x%lx  --->  cairo_subpixel_order_t: %p", t, subpixel_order);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoSubpixelOrder", t);
  }

  if ( !ATOM_cairo_subpixel_order_default )
  {
    ATOM_cairo_subpixel_order_default = PL_new_atom("CAIRO_SUBPIXEL_ORDER_DEFAULT");
    ATOM_cairo_subpixel_order_rgb = PL_new_atom("CAIRO_SUBPIXEL_ORDER_RGB");
    ATOM_cairo_subpixel_order_bgr = PL_new_atom("CAIRO_SUBPIXEL_ORDER_BGR");
    ATOM_cairo_subpixel_order_vrgb = PL_new_atom("CAIRO_SUBPIXEL_ORDER_VRGB");
    ATOM_cairo_subpixel_order_vbgr = PL_new_atom("CAIRO_SUBPIXEL_ORDER_VBGR");
  }

  if ( a == ATOM_cairo_subpixel_order_default )
  { *subpixel_order = CAIRO_SUBPIXEL_ORDER_DEFAULT;
  }
  else if ( a == ATOM_cairo_subpixel_order_rgb )
  { *subpixel_order = CAIRO_SUBPIXEL_ORDER_RGB;
  }
  else if ( a == ATOM_cairo_subpixel_order_bgr )
  { *subpixel_order = CAIRO_SUBPIXEL_ORDER_BGR;
  }
  else if ( a == ATOM_cairo_subpixel_order_vrgb )
  { *subpixel_order = CAIRO_SUBPIXEL_ORDER_VRGB;
  }
  else if ( a == ATOM_cairo_subpixel_order_vbgr )
  { *subpixel_order = CAIRO_SUBPIXEL_ORDER_VBGR;
  }
  else
  { return PL_domain_error("CairoSubpixelOrder", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_subpixel_order_to_term(cairo_subpixel_order_t subpixel_order,
                               term_t                 t)
{
  term_t t0 = PL_new_term_ref();

  PLGI_debug("    cairo_subpixel_order_t: %d  --->  term: 0x%lx", subpixel_order, t);

  if ( !ATOM_cairo_subpixel_order_default )
  {
    ATOM_cairo_subpixel_order_default = PL_new_atom("CAIRO_SUBPIXEL_ORDER_DEFAULT");
    ATOM_cairo_subpixel_order_rgb = PL_new_atom("CAIRO_SUBPIXEL_ORDER_RGB");
    ATOM_cairo_subpixel_order_bgr = PL_new_atom("CAIRO_SUBPIXEL_ORDER_BGR");
    ATOM_cairo_subpixel_order_vrgb = PL_new_atom("CAIRO_SUBPIXEL_ORDER_VRGB");
    ATOM_cairo_subpixel_order_vbgr = PL_new_atom("CAIRO_SUBPIXEL_ORDER_VBGR");
  }

  if ( subpixel_order == CAIRO_SUBPIXEL_ORDER_DEFAULT )
  { PL_put_atom(t0, ATOM_cairo_subpixel_order_default);
  }
  else if ( subpixel_order == CAIRO_SUBPIXEL_ORDER_RGB )
  { PL_put_atom(t0, ATOM_cairo_subpixel_order_rgb);
  }
  else if ( subpixel_order == CAIRO_SUBPIXEL_ORDER_BGR )
  { PL_put_atom(t0, ATOM_cairo_subpixel_order_bgr);
  }
  else if ( subpixel_order == CAIRO_SUBPIXEL_ORDER_VRGB )
  { PL_put_atom(t0, ATOM_cairo_subpixel_order_vrgb);
  }
  else if ( subpixel_order == CAIRO_SUBPIXEL_ORDER_VBGR )
  { PL_put_atom(t0, ATOM_cairo_subpixel_order_vbgr);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLGI_PRED_IMPL(plcairo_font_options_create)
{
  term_t t_options = FA0;

  cairo_font_options_t *options;

  options = cairo_font_options_create();
  PLCAIRO_CHECK_FONT_OPTIONS(options);

  if ( !plcairo_font_options_to_term(options, t_options) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_font_options_equal)
{
  term_t t_options = FA0;
  term_t t_other = FA1;
  term_t t_is_equal = FA2;

  cairo_font_options_t *options;
  cairo_font_options_t *other;
  cairo_bool_t is_equal;

  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;
  if ( !plcairo_term_to_font_options(t_other, &other) ) return FALSE;

  is_equal = cairo_font_options_equal(options, other);
  PLCAIRO_CHECK_FONT_OPTIONS(options);

  if ( !plcairo_bool_to_term(is_equal, t_is_equal) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_font_options_get_antialias)
{
  term_t t_options = FA0;
  term_t t_antialias = FA1;

  cairo_font_options_t *options;
  cairo_antialias_t antialias;

  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;

  antialias = cairo_font_options_get_antialias(options);
  PLCAIRO_CHECK_FONT_OPTIONS(options);

  if ( !plcairo_antialias_to_term(antialias, t_antialias) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_font_options_get_hint_metrics)
{
  term_t t_options = FA0;
  term_t t_hint_metrics = FA1;

  cairo_font_options_t *options;
  cairo_hint_metrics_t hint_metrics;

  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;

  hint_metrics = cairo_font_options_get_hint_metrics(options);
  PLCAIRO_CHECK_FONT_OPTIONS(options);

  if ( !plcairo_hint_metrics_to_term(hint_metrics, t_hint_metrics) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_font_options_get_hint_style)
{
  term_t t_options = FA0;
  term_t t_hint_style = FA1;

  cairo_font_options_t *options;
  cairo_hint_style_t hint_style;

  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;

  hint_style = cairo_font_options_get_hint_style(options);
  PLCAIRO_CHECK_FONT_OPTIONS(options);

  if ( !plcairo_hint_style_to_term(hint_style, t_hint_style) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_font_options_get_subpixel_order)
{
  term_t t_options = FA0;
  term_t t_subpixel_order = FA1;

  cairo_font_options_t *options;
  cairo_subpixel_order_t subpixel_order;

  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;

  subpixel_order = cairo_font_options_get_subpixel_order(options);
  PLCAIRO_CHECK_FONT_OPTIONS(options);

  if ( !plcairo_subpixel_order_to_term(subpixel_order, t_subpixel_order) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_font_options_hash)
{
  term_t t_options = FA0;
  term_t t_hash = FA1;

  cairo_font_options_t *options;
  unsigned long hash;

  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;

  hash = cairo_font_options_hash(options);
  PLCAIRO_CHECK_FONT_OPTIONS(options);

  if ( !plcairo_unsigned_long_to_term(hash, t_hash) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_font_options_merge)
{
  term_t t_options = FA0;
  term_t t_other = FA1;

  cairo_font_options_t *options;
  cairo_font_options_t *other;

  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;
  if ( !plcairo_term_to_font_options(t_other, &other) ) return FALSE;

  cairo_font_options_merge(options, other);
  PLCAIRO_CHECK_FONT_OPTIONS(options);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_font_options_set_antialias)
{
  term_t t_options = FA0;
  term_t t_antialias = FA1;

  cairo_font_options_t *options;
  cairo_antialias_t antialias;

  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;
  if ( !plcairo_term_to_antialias(t_antialias, &antialias) ) return FALSE;

  cairo_font_options_set_antialias(options, antialias);
  PLCAIRO_CHECK_FONT_OPTIONS(options);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_font_options_set_hint_metrics)
{
  term_t t_options = FA0;
  term_t t_hint_metrics = FA1;

  cairo_font_options_t *options;
  cairo_hint_metrics_t hint_metrics;

  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;
  if ( !plcairo_term_to_hint_metrics(t_hint_metrics, &hint_metrics) ) return FALSE;

  cairo_font_options_set_hint_metrics(options, hint_metrics);
  PLCAIRO_CHECK_FONT_OPTIONS(options);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_font_options_set_hint_style)
{
  term_t t_options = FA0;
  term_t t_hint_style = FA1;

  cairo_font_options_t *options;
  cairo_hint_style_t hint_style;

  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;
  if ( !plcairo_term_to_hint_style(t_hint_style, &hint_style) ) return FALSE;

  cairo_font_options_set_hint_style(options, hint_style);
  PLCAIRO_CHECK_FONT_OPTIONS(options);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_font_options_set_subpixel_order)
{
  term_t t_options = FA0;
  term_t t_subpixel_order = FA1;

  cairo_font_options_t *options;
  cairo_subpixel_order_t subpixel_order;

  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;
  if ( !plcairo_term_to_subpixel_order(t_subpixel_order, &subpixel_order) ) return FALSE;

  cairo_font_options_set_subpixel_order(options, subpixel_order);
  PLCAIRO_CHECK_FONT_OPTIONS(options);

  return TRUE;
}
