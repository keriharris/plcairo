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


/* cairo_t */
cairo_bool_t
plcairo_term_to_context(term_t    t,
                        cairo_t **cr)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_t: %p", t, *cr);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoContext", t);
  }

  if ( blob->gtype != G_TYPE_NONE &&
       !g_type_is_a( blob->gtype, CAIRO_GOBJECT_TYPE_CONTEXT ) )
  { return PL_type_error("CairoContext", t);
  }

  *cr = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_context_to_term(cairo_t *cr,
                        term_t   t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_t: %p  --->  term: 0x%lx", cr, t);

  if ( !cr )
  { return ( plcairo_put_null(t0) && PL_unify(t, t0) );
  }

  data = cr;
  blob_type = PLGI_BLOB_BOXED;

  if ( !plgi_put_blob(blob_type, CAIRO_GOBJECT_TYPE_CONTEXT,
                      PL_new_atom("CairoContext"), data, t0, NULL) )
  { return FALSE;
  }

  return PL_unify(t, t0);;
}


/* cairo_antialias_t */
static atom_t ATOM_cairo_antialias_default = 0;
static atom_t ATOM_cairo_antialias_none = 0;
static atom_t ATOM_cairo_antialias_gray = 0;
static atom_t ATOM_cairo_antialias_subpixel = 0;
static atom_t ATOM_cairo_antialias_fast = 0;
static atom_t ATOM_cairo_antialias_good = 0;
static atom_t ATOM_cairo_antialias_best = 0;

cairo_bool_t
plcairo_term_to_antialias(term_t             t,
                          cairo_antialias_t *antialias)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_antialias_t: %p", t, antialias);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoAntialias", t);
  }

  if ( !ATOM_cairo_antialias_default )
  {
    ATOM_cairo_antialias_default = PL_new_atom("CAIRO_ANTIALIAS_DEFAULT");
    ATOM_cairo_antialias_none = PL_new_atom("CAIRO_ANTIALIAS_NONE");
    ATOM_cairo_antialias_gray = PL_new_atom("CAIRO_ANTIALIAS_GRAY");
    ATOM_cairo_antialias_subpixel = PL_new_atom("CAIRO_ANTIALIAS_SUBPIXEL");
    ATOM_cairo_antialias_fast = PL_new_atom("CAIRO_ANTIALIAS_FAST");
    ATOM_cairo_antialias_good = PL_new_atom("CAIRO_ANTIALIAS_GOOD");
    ATOM_cairo_antialias_best = PL_new_atom("CAIRO_ANTIALIAS_BEST");
  }

  if ( a == ATOM_cairo_antialias_default )
  { *antialias = CAIRO_ANTIALIAS_DEFAULT;
  }
  else if ( a == ATOM_cairo_antialias_none )
  { *antialias = CAIRO_ANTIALIAS_NONE;
  }
  else if ( a == ATOM_cairo_antialias_gray )
  { *antialias = CAIRO_ANTIALIAS_GRAY;
  }
  else if ( a == ATOM_cairo_antialias_subpixel )
  { *antialias = CAIRO_ANTIALIAS_SUBPIXEL;
  }
  else if ( a == ATOM_cairo_antialias_fast )
  { *antialias = CAIRO_ANTIALIAS_FAST;
  }
  else if ( a == ATOM_cairo_antialias_good )
  { *antialias = CAIRO_ANTIALIAS_GOOD;
  }
  else if ( a == ATOM_cairo_antialias_best )
  { *antialias = CAIRO_ANTIALIAS_BEST;
  }
  else
  { return PL_domain_error("CairoAntialias", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_antialias_to_term(cairo_antialias_t antialias,
                          term_t            t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_antialias_t: %d  --->  term: 0x%lx", antialias, t);

  if ( !ATOM_cairo_antialias_default )
  {
    ATOM_cairo_antialias_default = PL_new_atom("CAIRO_ANTIALIAS_DEFAULT");
    ATOM_cairo_antialias_none = PL_new_atom("CAIRO_ANTIALIAS_NONE");
    ATOM_cairo_antialias_gray = PL_new_atom("CAIRO_ANTIALIAS_GRAY");
    ATOM_cairo_antialias_subpixel = PL_new_atom("CAIRO_ANTIALIAS_SUBPIXEL");
    ATOM_cairo_antialias_fast = PL_new_atom("CAIRO_ANTIALIAS_FAST");
    ATOM_cairo_antialias_good = PL_new_atom("CAIRO_ANTIALIAS_GOOD");
    ATOM_cairo_antialias_best = PL_new_atom("CAIRO_ANTIALIAS_BEST");
  }

  if ( antialias == CAIRO_ANTIALIAS_DEFAULT )
  { PL_put_atom(t0, ATOM_cairo_antialias_default);
  }
  else if ( antialias == CAIRO_ANTIALIAS_NONE )
  { PL_put_atom(t0, ATOM_cairo_antialias_none);
  }
  else if ( antialias == CAIRO_ANTIALIAS_GRAY )
  { PL_put_atom(t0, ATOM_cairo_antialias_gray);
  }
  else if ( antialias == CAIRO_ANTIALIAS_SUBPIXEL )
  { PL_put_atom(t0, ATOM_cairo_antialias_subpixel);
  }
  else if ( antialias == CAIRO_ANTIALIAS_FAST )
  { PL_put_atom(t0, ATOM_cairo_antialias_fast);
  }
  else if ( antialias == CAIRO_ANTIALIAS_GOOD )
  { PL_put_atom(t0, ATOM_cairo_antialias_good);
  }
  else if ( antialias == CAIRO_ANTIALIAS_BEST )
  { PL_put_atom(t0, ATOM_cairo_antialias_best);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}


/* cairo_fill_rule_t */
static atom_t ATOM_cairo_fill_rule_winding = 0;
static atom_t ATOM_cairo_fill_rule_even_odd = 0;

cairo_bool_t
plcairo_term_to_fill_rule(term_t             t,
                          cairo_fill_rule_t *fill_rule)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_fill_rule_t: %p", t, fill_rule);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoFillRule", t);
  }

  if ( !ATOM_cairo_fill_rule_winding )
  {
    ATOM_cairo_fill_rule_winding = PL_new_atom("CAIRO_FILL_RULE_WINDING");
    ATOM_cairo_fill_rule_even_odd = PL_new_atom("CAIRO_FILL_RULE_EVEN_ODD");
  }

  if ( a == ATOM_cairo_fill_rule_winding )
  { *fill_rule = CAIRO_FILL_RULE_WINDING;
  }
  else if ( a == ATOM_cairo_fill_rule_even_odd )
  { *fill_rule = CAIRO_FILL_RULE_EVEN_ODD;
  }
  else
  { return PL_domain_error("CairoFillRule", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_fill_rule_to_term(cairo_fill_rule_t fill_rule,
                          term_t            t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_fill_rule_t: %d  --->  term: 0x%lx", fill_rule, t);

  if ( !ATOM_cairo_fill_rule_winding )
  {
    ATOM_cairo_fill_rule_winding = PL_new_atom("CAIRO_FILL_RULE_WINDING");
    ATOM_cairo_fill_rule_even_odd = PL_new_atom("CAIRO_FILL_RULE_EVEN_ODD");
  }

  if ( fill_rule == CAIRO_FILL_RULE_WINDING )
  { PL_put_atom(t0, ATOM_cairo_fill_rule_winding);
  }
  else if ( fill_rule == CAIRO_FILL_RULE_EVEN_ODD )
  { PL_put_atom(t0, ATOM_cairo_fill_rule_even_odd);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}


/* cairo_line_cap_t */
static atom_t ATOM_cairo_line_cap_butt = 0;
static atom_t ATOM_cairo_line_cap_round = 0;
static atom_t ATOM_cairo_line_cap_square = 0;

cairo_bool_t
plcairo_term_to_line_cap(term_t            t,
                         cairo_line_cap_t *line_cap)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_line_cap_t: %p", t, line_cap);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoLineCap", t);
  }

  if ( !ATOM_cairo_line_cap_butt )
  {
    ATOM_cairo_line_cap_butt = PL_new_atom("CAIRO_LINE_CAP_BUTT");
    ATOM_cairo_line_cap_round = PL_new_atom("CAIRO_LINE_CAP_ROUND");
    ATOM_cairo_line_cap_square = PL_new_atom("CAIRO_LINE_CAP_SQUARE");
  }

  if ( a == ATOM_cairo_line_cap_butt )
  { *line_cap = CAIRO_LINE_CAP_BUTT;
  }
  else if ( a == ATOM_cairo_line_cap_round )
  { *line_cap = CAIRO_LINE_CAP_ROUND;
  }
  else if ( a == ATOM_cairo_line_cap_square )
  { *line_cap = CAIRO_LINE_CAP_SQUARE;
  }
  else
  { return PL_domain_error("CairoLineCap", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_line_cap_to_term(cairo_line_cap_t line_cap,
                         term_t           t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_line_cap_t: %d  --->  term: 0x%lx", line_cap, t);

  if ( !ATOM_cairo_line_cap_butt )
  {
    ATOM_cairo_line_cap_butt = PL_new_atom("CAIRO_LINE_CAP_BUTT");
    ATOM_cairo_line_cap_round = PL_new_atom("CAIRO_LINE_CAP_ROUND");
    ATOM_cairo_line_cap_square = PL_new_atom("CAIRO_LINE_CAP_SQUARE");
  }

  if ( line_cap == CAIRO_LINE_CAP_BUTT )
  { PL_put_atom(t0, ATOM_cairo_line_cap_butt);
  }
  else if ( line_cap == CAIRO_LINE_CAP_ROUND )
  { PL_put_atom(t0, ATOM_cairo_line_cap_round);
  }
  else if ( line_cap == CAIRO_LINE_CAP_SQUARE )
  { PL_put_atom(t0, ATOM_cairo_line_cap_square);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}


/* cairo_line_join_t */
static atom_t ATOM_cairo_line_join_miter = 0;
static atom_t ATOM_cairo_line_join_round = 0;
static atom_t ATOM_cairo_line_join_bevel = 0;

cairo_bool_t
plcairo_term_to_line_join(term_t             t,
                          cairo_line_join_t *line_join)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_line_join_t: %p", t, line_join);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoLineJoin", t);
  }

  if ( !ATOM_cairo_line_join_miter )
  {
    ATOM_cairo_line_join_miter = PL_new_atom("CAIRO_LINE_JOIN_MITER");
    ATOM_cairo_line_join_round = PL_new_atom("CAIRO_LINE_JOIN_ROUND");
    ATOM_cairo_line_join_bevel = PL_new_atom("CAIRO_LINE_JOIN_BEVEL");
  }

  if ( a == ATOM_cairo_line_join_miter )
  { *line_join = CAIRO_LINE_JOIN_MITER;
  }
  else if ( a == ATOM_cairo_line_join_round )
  { *line_join = CAIRO_LINE_JOIN_ROUND;
  }
  else if ( a == ATOM_cairo_line_join_bevel )
  { *line_join = CAIRO_LINE_JOIN_BEVEL;
  }
  else
  { return PL_domain_error("CairoLineJoin", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_line_join_to_term(cairo_line_join_t line_join,
                          term_t            t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_line_join_t: %d  --->  term: 0x%lx", line_join, t);

  if ( !ATOM_cairo_line_join_miter )
  {
    ATOM_cairo_line_join_miter = PL_new_atom("CAIRO_LINE_JOIN_MITER");
    ATOM_cairo_line_join_round = PL_new_atom("CAIRO_LINE_JOIN_ROUND");
    ATOM_cairo_line_join_bevel = PL_new_atom("CAIRO_LINE_JOIN_BEVEL");
  }

  if ( line_join == CAIRO_LINE_JOIN_MITER )
  { PL_put_atom(t0, ATOM_cairo_line_join_miter);
  }
  else if ( line_join == CAIRO_LINE_JOIN_ROUND )
  { PL_put_atom(t0, ATOM_cairo_line_join_round);
  }
  else if ( line_join == CAIRO_LINE_JOIN_BEVEL )
  { PL_put_atom(t0, ATOM_cairo_line_join_bevel);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}


/* cairo_operator_t */
static atom_t ATOM_cairo_operator_clear = 0;
static atom_t ATOM_cairo_operator_source = 0;
static atom_t ATOM_cairo_operator_over = 0;
static atom_t ATOM_cairo_operator_in = 0;
static atom_t ATOM_cairo_operator_out = 0;
static atom_t ATOM_cairo_operator_atop = 0;
static atom_t ATOM_cairo_operator_dest = 0;
static atom_t ATOM_cairo_operator_dest_over = 0;
static atom_t ATOM_cairo_operator_dest_in = 0;
static atom_t ATOM_cairo_operator_dest_out = 0;
static atom_t ATOM_cairo_operator_dest_atop = 0;
static atom_t ATOM_cairo_operator_xor = 0;
static atom_t ATOM_cairo_operator_add = 0;
static atom_t ATOM_cairo_operator_saturate = 0;
static atom_t ATOM_cairo_operator_multiply = 0;
static atom_t ATOM_cairo_operator_screen = 0;
static atom_t ATOM_cairo_operator_overlay = 0;
static atom_t ATOM_cairo_operator_darken = 0;
static atom_t ATOM_cairo_operator_lighten = 0;
static atom_t ATOM_cairo_operator_color_dodge = 0;
static atom_t ATOM_cairo_operator_color_burn = 0;
static atom_t ATOM_cairo_operator_hard_light = 0;
static atom_t ATOM_cairo_operator_soft_light = 0;
static atom_t ATOM_cairo_operator_difference = 0;
static atom_t ATOM_cairo_operator_exclusion = 0;
static atom_t ATOM_cairo_operator_hsl_hue = 0;
static atom_t ATOM_cairo_operator_hsl_saturation = 0;
static atom_t ATOM_cairo_operator_hsl_color = 0;
static atom_t ATOM_cairo_operator_hsl_luminosity = 0;

cairo_bool_t
plcairo_term_to_operator(term_t            t,
                         cairo_operator_t *operator)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_operator_t: %p", t, operator);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoOperator", t);
  }

  if ( !ATOM_cairo_operator_clear )
  {
    ATOM_cairo_operator_clear = PL_new_atom("CAIRO_OPERATOR_CLEAR");
    ATOM_cairo_operator_source = PL_new_atom("CAIRO_OPERATOR_SOURCE");
    ATOM_cairo_operator_over = PL_new_atom("CAIRO_OPERATOR_OVER");
    ATOM_cairo_operator_in = PL_new_atom("CAIRO_OPERATOR_IN");
    ATOM_cairo_operator_out = PL_new_atom("CAIRO_OPERATOR_OUT");
    ATOM_cairo_operator_atop = PL_new_atom("CAIRO_OPERATOR_ATOP");
    ATOM_cairo_operator_dest = PL_new_atom("CAIRO_OPERATOR_DEST");
    ATOM_cairo_operator_dest_over = PL_new_atom("CAIRO_OPERATOR_DEST_OVER");
    ATOM_cairo_operator_dest_in = PL_new_atom("CAIRO_OPERATOR_DEST_IN");
    ATOM_cairo_operator_dest_out = PL_new_atom("CAIRO_OPERATOR_DEST_OUT");
    ATOM_cairo_operator_dest_atop = PL_new_atom("CAIRO_OPERATOR_DEST_ATOP");
    ATOM_cairo_operator_xor = PL_new_atom("CAIRO_OPERATOR_XOR");
    ATOM_cairo_operator_add = PL_new_atom("CAIRO_OPERATOR_ADD");
    ATOM_cairo_operator_saturate = PL_new_atom("CAIRO_OPERATOR_SATURATE");
    ATOM_cairo_operator_multiply = PL_new_atom("CAIRO_OPERATOR_MULTIPLY");
    ATOM_cairo_operator_screen = PL_new_atom("CAIRO_OPERATOR_SCREEN");
    ATOM_cairo_operator_overlay = PL_new_atom("CAIRO_OPERATOR_OVERLAY");
    ATOM_cairo_operator_darken = PL_new_atom("CAIRO_OPERATOR_DARKEN");
    ATOM_cairo_operator_lighten = PL_new_atom("CAIRO_OPERATOR_LIGHTEN");
    ATOM_cairo_operator_color_dodge = PL_new_atom("CAIRO_OPERATOR_COLOR_DODGE");
    ATOM_cairo_operator_color_burn = PL_new_atom("CAIRO_OPERATOR_COLOR_BURN");
    ATOM_cairo_operator_hard_light = PL_new_atom("CAIRO_OPERATOR_HARD_LIGHT");
    ATOM_cairo_operator_soft_light = PL_new_atom("CAIRO_OPERATOR_SOFT_LIGHT");
    ATOM_cairo_operator_difference = PL_new_atom("CAIRO_OPERATOR_DIFFERENCE");
    ATOM_cairo_operator_exclusion = PL_new_atom("CAIRO_OPERATOR_EXCLUSION");
    ATOM_cairo_operator_hsl_hue = PL_new_atom("CAIRO_OPERATOR_HSL_HUE");
    ATOM_cairo_operator_hsl_saturation = PL_new_atom("CAIRO_OPERATOR_HSL_SATURATION");
    ATOM_cairo_operator_hsl_color = PL_new_atom("CAIRO_OPERATOR_HSL_COLOR");
    ATOM_cairo_operator_hsl_luminosity = PL_new_atom("CAIRO_OPERATOR_HSL_LUMINOSITY");
  }

  if ( a == ATOM_cairo_operator_clear )
  { *operator = CAIRO_OPERATOR_CLEAR;
  }
  else if ( a == ATOM_cairo_operator_source )
  { *operator = CAIRO_OPERATOR_SOURCE;
  }
  else if ( a == ATOM_cairo_operator_over )
  { *operator = CAIRO_OPERATOR_OVER;
  }
  else if ( a == ATOM_cairo_operator_in )
  { *operator = CAIRO_OPERATOR_IN;
  }
  else if ( a == ATOM_cairo_operator_out )
  { *operator = CAIRO_OPERATOR_OUT;
  }
  else if ( a == ATOM_cairo_operator_atop )
  { *operator = CAIRO_OPERATOR_ATOP;
  }
  else if ( a == ATOM_cairo_operator_dest )
  { *operator = CAIRO_OPERATOR_DEST;
  }
  else if ( a == ATOM_cairo_operator_dest_over )
  { *operator = CAIRO_OPERATOR_DEST_OVER;
  }
  else if ( a == ATOM_cairo_operator_dest_in )
  { *operator = CAIRO_OPERATOR_DEST_IN;
  }
  else if ( a == ATOM_cairo_operator_dest_out )
  { *operator = CAIRO_OPERATOR_DEST_OUT;
  }
  else if ( a == ATOM_cairo_operator_dest_atop )
  { *operator = CAIRO_OPERATOR_DEST_ATOP;
  }
  else if ( a == ATOM_cairo_operator_xor )
  { *operator = CAIRO_OPERATOR_XOR;
  }
  else if ( a == ATOM_cairo_operator_add )
  { *operator = CAIRO_OPERATOR_ADD;
  }
  else if ( a == ATOM_cairo_operator_saturate )
  { *operator = CAIRO_OPERATOR_SATURATE;
  }
  else if ( a == ATOM_cairo_operator_multiply )
  { *operator = CAIRO_OPERATOR_MULTIPLY;
  }
  else if ( a == ATOM_cairo_operator_screen )
  { *operator = CAIRO_OPERATOR_SCREEN;
  }
  else if ( a == ATOM_cairo_operator_overlay )
  { *operator = CAIRO_OPERATOR_OVERLAY;
  }
  else if ( a == ATOM_cairo_operator_darken )
  { *operator = CAIRO_OPERATOR_DARKEN;
  }
  else if ( a == ATOM_cairo_operator_lighten )
  { *operator = CAIRO_OPERATOR_LIGHTEN;
  }
  else if ( a == ATOM_cairo_operator_color_dodge )
  { *operator = CAIRO_OPERATOR_COLOR_DODGE;
  }
  else if ( a == ATOM_cairo_operator_color_burn )
  { *operator = CAIRO_OPERATOR_COLOR_BURN;
  }
  else if ( a == ATOM_cairo_operator_hard_light )
  { *operator = CAIRO_OPERATOR_HARD_LIGHT;
  }
  else if ( a == ATOM_cairo_operator_soft_light )
  { *operator = CAIRO_OPERATOR_SOFT_LIGHT;
  }
  else if ( a == ATOM_cairo_operator_difference )
  { *operator = CAIRO_OPERATOR_DIFFERENCE;
  }
  else if ( a == ATOM_cairo_operator_exclusion )
  { *operator = CAIRO_OPERATOR_EXCLUSION;
  }
  else if ( a == ATOM_cairo_operator_hsl_hue )
  { *operator = CAIRO_OPERATOR_HSL_HUE;
  }
  else if ( a == ATOM_cairo_operator_hsl_saturation )
  { *operator = CAIRO_OPERATOR_HSL_SATURATION;
  }
  else if ( a == ATOM_cairo_operator_hsl_color )
  { *operator = CAIRO_OPERATOR_HSL_COLOR;
  }
  else if ( a == ATOM_cairo_operator_hsl_luminosity )
  { *operator = CAIRO_OPERATOR_HSL_LUMINOSITY;
  }
  else
  { return PL_domain_error("CairoOperator", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_operator_to_term(cairo_operator_t operator,
                         term_t            t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_operator_t: %d  --->  term: 0x%lx", operator, t);

  if ( !ATOM_cairo_operator_clear )
  {
    ATOM_cairo_operator_clear = PL_new_atom("CAIRO_OPERATOR_CLEAR");
    ATOM_cairo_operator_source = PL_new_atom("CAIRO_OPERATOR_SOURCE");
    ATOM_cairo_operator_over = PL_new_atom("CAIRO_OPERATOR_OVER");
    ATOM_cairo_operator_in = PL_new_atom("CAIRO_OPERATOR_IN");
    ATOM_cairo_operator_out = PL_new_atom("CAIRO_OPERATOR_OUT");
    ATOM_cairo_operator_atop = PL_new_atom("CAIRO_OPERATOR_ATOP");
    ATOM_cairo_operator_dest = PL_new_atom("CAIRO_OPERATOR_DEST");
    ATOM_cairo_operator_dest_over = PL_new_atom("CAIRO_OPERATOR_DEST_OVER");
    ATOM_cairo_operator_dest_in = PL_new_atom("CAIRO_OPERATOR_DEST_IN");
    ATOM_cairo_operator_dest_out = PL_new_atom("CAIRO_OPERATOR_DEST_OUT");
    ATOM_cairo_operator_dest_atop = PL_new_atom("CAIRO_OPERATOR_DEST_ATOP");
    ATOM_cairo_operator_xor = PL_new_atom("CAIRO_OPERATOR_XOR");
    ATOM_cairo_operator_add = PL_new_atom("CAIRO_OPERATOR_ADD");
    ATOM_cairo_operator_saturate = PL_new_atom("CAIRO_OPERATOR_SATURATE");
    ATOM_cairo_operator_multiply = PL_new_atom("CAIRO_OPERATOR_MULTIPLY");
    ATOM_cairo_operator_screen = PL_new_atom("CAIRO_OPERATOR_SCREEN");
    ATOM_cairo_operator_overlay = PL_new_atom("CAIRO_OPERATOR_OVERLAY");
    ATOM_cairo_operator_darken = PL_new_atom("CAIRO_OPERATOR_DARKEN");
    ATOM_cairo_operator_lighten = PL_new_atom("CAIRO_OPERATOR_LIGHTEN");
    ATOM_cairo_operator_color_dodge = PL_new_atom("CAIRO_OPERATOR_COLOR_DODGE");
    ATOM_cairo_operator_color_burn = PL_new_atom("CAIRO_OPERATOR_COLOR_BURN");
    ATOM_cairo_operator_hard_light = PL_new_atom("CAIRO_OPERATOR_HARD_LIGHT");
    ATOM_cairo_operator_soft_light = PL_new_atom("CAIRO_OPERATOR_SOFT_LIGHT");
    ATOM_cairo_operator_difference = PL_new_atom("CAIRO_OPERATOR_DIFFERENCE");
    ATOM_cairo_operator_exclusion = PL_new_atom("CAIRO_OPERATOR_EXCLUSION");
    ATOM_cairo_operator_hsl_hue = PL_new_atom("CAIRO_OPERATOR_HSL_HUE");
    ATOM_cairo_operator_hsl_saturation = PL_new_atom("CAIRO_OPERATOR_HSL_SATURATION");
    ATOM_cairo_operator_hsl_color = PL_new_atom("CAIRO_OPERATOR_HSL_COLOR");
    ATOM_cairo_operator_hsl_luminosity = PL_new_atom("CAIRO_OPERATOR_HSL_LUMINOSITY");
  }

  if ( operator == CAIRO_OPERATOR_CLEAR )
  { PL_put_atom(t0, ATOM_cairo_operator_clear);
  }
  else if ( operator == CAIRO_OPERATOR_SOURCE )
  { PL_put_atom(t0, ATOM_cairo_operator_source);
  }
  else if ( operator == CAIRO_OPERATOR_OVER )
  { PL_put_atom(t0, ATOM_cairo_operator_over);
  }
  else if ( operator == CAIRO_OPERATOR_IN )
  { PL_put_atom(t0, ATOM_cairo_operator_in);
  }
  else if ( operator == CAIRO_OPERATOR_OUT )
  { PL_put_atom(t0, ATOM_cairo_operator_out);
  }
  else if ( operator == CAIRO_OPERATOR_ATOP )
  { PL_put_atom(t0, ATOM_cairo_operator_atop);
  }
  else if ( operator == CAIRO_OPERATOR_DEST )
  { PL_put_atom(t0, ATOM_cairo_operator_dest);
  }
  else if ( operator == CAIRO_OPERATOR_DEST_OVER )
  { PL_put_atom(t0, ATOM_cairo_operator_dest_over);
  }
  else if ( operator == CAIRO_OPERATOR_DEST_IN )
  { PL_put_atom(t0, ATOM_cairo_operator_dest_in);
  }
  else if ( operator == CAIRO_OPERATOR_DEST_OUT )
  { PL_put_atom(t0, ATOM_cairo_operator_dest_out);
  }
  else if ( operator == CAIRO_OPERATOR_DEST_ATOP )
  { PL_put_atom(t0, ATOM_cairo_operator_dest_atop);
  }
  else if ( operator == CAIRO_OPERATOR_XOR )
  { PL_put_atom(t0, ATOM_cairo_operator_xor);
  }
  else if ( operator == CAIRO_OPERATOR_ADD )
  { PL_put_atom(t0, ATOM_cairo_operator_add);
  }
  else if ( operator == CAIRO_OPERATOR_SATURATE )
  { PL_put_atom(t0, ATOM_cairo_operator_saturate);
  }
  else if ( operator == CAIRO_OPERATOR_MULTIPLY )
  { PL_put_atom(t0, ATOM_cairo_operator_multiply);
  }
  else if ( operator == CAIRO_OPERATOR_SCREEN )
  { PL_put_atom(t0, ATOM_cairo_operator_screen);
  }
  else if ( operator == CAIRO_OPERATOR_OVERLAY )
  { PL_put_atom(t0, ATOM_cairo_operator_overlay);
  }
  else if ( operator == CAIRO_OPERATOR_DARKEN )
  { PL_put_atom(t0, ATOM_cairo_operator_darken);
  }
  else if ( operator == CAIRO_OPERATOR_LIGHTEN )
  { PL_put_atom(t0, ATOM_cairo_operator_lighten);
  }
  else if ( operator == CAIRO_OPERATOR_COLOR_DODGE )
  { PL_put_atom(t0, ATOM_cairo_operator_color_dodge);
  }
  else if ( operator == CAIRO_OPERATOR_COLOR_BURN )
  { PL_put_atom(t0, ATOM_cairo_operator_color_burn);
  }
  else if ( operator == CAIRO_OPERATOR_HARD_LIGHT )
  { PL_put_atom(t0, ATOM_cairo_operator_hard_light);
  }
  else if ( operator == CAIRO_OPERATOR_SOFT_LIGHT )
  { PL_put_atom(t0, ATOM_cairo_operator_soft_light);
  }
  else if ( operator == CAIRO_OPERATOR_DIFFERENCE )
  { PL_put_atom(t0, ATOM_cairo_operator_difference);
  }
  else if ( operator == CAIRO_OPERATOR_EXCLUSION )
  { PL_put_atom(t0, ATOM_cairo_operator_exclusion);
  }
  else if ( operator == CAIRO_OPERATOR_HSL_HUE )
  { PL_put_atom(t0, ATOM_cairo_operator_hsl_hue);
  }
  else if ( operator == CAIRO_OPERATOR_HSL_SATURATION )
  { PL_put_atom(t0, ATOM_cairo_operator_hsl_saturation);
  }
  else if ( operator == CAIRO_OPERATOR_HSL_COLOR )
  { PL_put_atom(t0, ATOM_cairo_operator_hsl_color);
  }
  else if ( operator == CAIRO_OPERATOR_HSL_LUMINOSITY )
  { PL_put_atom(t0, ATOM_cairo_operator_hsl_luminosity);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}


/* cairo_rectangle_t */
void plcairo_register_rectangle_t(void)
{
  PLGIStructInfo *struct_info;
  PLGIFieldInfo *field_info;
  int n_fields, offset;

  PLCAIRO_debug("registering struct: CairoRectangle");

  n_fields = 4;
  offset = 0;

  struct_info = g_malloc0(sizeof(*struct_info));
  struct_info->info = NULL;
  struct_info->namespace = PL_new_atom("cairo");
  struct_info->name = PL_new_atom("CairoRectangle");
  struct_info->gtype = CAIRO_GOBJECT_TYPE_RECTANGLE;
  struct_info->size = sizeof(cairo_rectangle_t);
  struct_info->n_fields = n_fields;
  struct_info->fields_info = g_malloc0_n(n_fields, sizeof(*struct_info->fields_info));

  plcairo_alloc_struct_double_field(0, "x");
  plcairo_alloc_struct_double_field(1, "y");
  plcairo_alloc_struct_double_field(2, "width");
  plcairo_alloc_struct_double_field(3, "height");

  plgi_cache_struct_info(struct_info);
}

cairo_bool_t
plcairo_term_to_rectangle(term_t              t,
                          cairo_rectangle_t **rectangle)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_rectangle_t: %p", t, *rectangle);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoRectangle", t);
  }

  if ( blob->gtype != G_TYPE_NONE &&
       !g_type_is_a( blob->gtype, CAIRO_GOBJECT_TYPE_RECTANGLE ) )
  { return PL_type_error("CairoRectangle", t);
  }

  *rectangle = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_rectangle_to_term(cairo_rectangle_t *rectangle,
                          term_t             t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_rectangle_t: %p  --->  term: 0x%lx", rectangle, t);

  if ( !rectangle )
  { return ( plcairo_put_null(t0) && PL_unify(t, t0) );
  }

  data = rectangle;
  blob_type = PLGI_BLOB_BOXED;

  if ( !plgi_put_blob(blob_type, CAIRO_GOBJECT_TYPE_RECTANGLE,
                      PL_new_atom("CairoRectangle"), data, t0, NULL) )
  { return FALSE;
  }

  return PL_unify(t, t0);;
}


/* cairo_rectangle_list_t */
cairo_bool_t
plcairo_term_to_rectangle_list(term_t                   t,
                               cairo_rectangle_list_t **rectangle_list)
{
  term_t list = PL_copy_term_ref(t);
  term_t head = PL_new_term_ref();
  cairo_rectangle_list_t *rectangle_list0;
  cairo_rectangle_t *rectangles;
  size_t num_rectangles;
  int i = 0;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_rectangle_list_t: %p", t, *rectangle_list);

  if ( PL_skip_list(list, 0, &num_rectangles) != PL_LIST )
  { return PL_type_error("list", t);
  }

  rectangle_list0 = g_malloc0(sizeof(cairo_rectangle_list_t));
  rectangles = g_malloc0_n(num_rectangles, sizeof(cairo_rectangle_t));

  rectangle_list0->status = CAIRO_STATUS_SUCCESS;
  rectangle_list0->rectangles = rectangles;
  rectangle_list0->num_rectangles = num_rectangles;

  while ( PL_get_list(list, head, list) )
  { cairo_rectangle_t *rectangle = rectangles + i++;

    if ( !plcairo_term_to_rectangle(head, &rectangle) )
    { return PL_type_error("CairoRectangle", head);
    }
  }

  *rectangle_list = rectangle_list0;

  return TRUE;
}

cairo_bool_t
plcairo_rectangle_list_to_term(cairo_rectangle_list_t *rectangle_list,
                               term_t                  t)
{
  term_t t0 = PL_new_term_ref();
  term_t list = PL_copy_term_ref(t0);
  term_t head = PL_new_term_ref();
  int i;

  PLCAIRO_debug("    cairo_rectangle_list_t: %p  --->  term: 0x%lx", rectangle_list, t);

  if ( rectangle_list->status != CAIRO_STATUS_SUCCESS )
  { return plcairo_raise_error_status(rectangle_list->status);
  }

  for ( i = 0; i < rectangle_list->num_rectangles; i++ )
  {
    cairo_rectangle_t *rectangle = rectangle_list->rectangles + i;
    term_t a = PL_new_term_ref();

    if ( !plcairo_rectangle_to_term(rectangle, a) ) return FALSE;
    if ( !(PL_unify_list(list, head, list) &&
           PL_unify(head, a)) )
    { return FALSE;
    }
  }

  if ( !PL_unify_nil(list) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLCAIRO_PRED_IMPL(plcairo_clip)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_clip(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_clip_extents)
{
  term_t t_cr = FA0;
  term_t t_x1 = FA1;
  term_t t_y1 = FA2;
  term_t t_x2 = FA3;
  term_t t_y2 = FA4;

  cairo_t *cr;
  double x1, y1, x2, y2;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_clip_extents(cr, &x1, &y1, &x2, &y2);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_double_to_term(x1, t_x1) ) return FALSE;
  if ( !plcairo_double_to_term(y1, t_y1) ) return FALSE;
  if ( !plcairo_double_to_term(x2, t_x2) ) return FALSE;
  if ( !plcairo_double_to_term(y2, t_y2) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_clip_preserve)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_clip_preserve(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_copy_clip_rectangle_list)
{
  term_t t_cr = FA0;
  term_t t_rectangle_list = FA1;

  cairo_t *cr;
  cairo_rectangle_list_t *rectangle_list;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  rectangle_list = cairo_copy_clip_rectangle_list(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_rectangle_list_to_term(rectangle_list, t_rectangle_list) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_copy_page)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_copy_page(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_create)
{
  term_t t_target = FA0;
  term_t t_cr = FA1;

  cairo_surface_t *target;
  cairo_t *cr;

  if ( !plcairo_term_to_surface(t_target, &target) ) return FALSE;

  cr = cairo_create(target);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_context_to_term(cr, t_cr) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_fill)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_fill(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_fill_extents)
{
  term_t t_cr = FA0;
  term_t t_x1 = FA1;
  term_t t_y1 = FA2;
  term_t t_x2 = FA3;
  term_t t_y2 = FA4;

  cairo_t *cr;
  double x1, y1, x2, y2;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_fill_extents(cr, &x1, &y1, &x2, &y2);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_double_to_term(x1, t_x1) ) return FALSE;
  if ( !plcairo_double_to_term(y1, t_y1) ) return FALSE;
  if ( !plcairo_double_to_term(x2, t_x2) ) return FALSE;
  if ( !plcairo_double_to_term(y2, t_y2) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_fill_preserve)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_fill_preserve(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_antialias)
{
  term_t t_cr = FA0;
  term_t t_antialias = FA1;

  cairo_t *cr;
  cairo_antialias_t antialias;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  antialias = cairo_get_antialias(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_antialias_to_term(antialias, t_antialias) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_dash)
{
  term_t t_cr = FA0;
  term_t t_dashes = FA1;
  term_t t_offset = FA2;

  cairo_t *cr;
  int dash_count;
  double *dashes;
  double offset;
  term_t list = PL_copy_term_ref(t_dashes);
  term_t head = PL_new_term_ref();
  int i;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  dash_count = cairo_get_dash_count(cr);
  PLCAIRO_CHECK_CONTEXT(cr);
  dashes = g_malloc0_n(dash_count, sizeof(double));
  cairo_get_dash(cr, dashes, &offset);
  PLCAIRO_CHECK_CONTEXT(cr);

  for ( i = 0; i < dash_count; i++ )
  {
    double *dash = dashes + i;
    term_t a = PL_new_term_ref();

    if ( !plcairo_double_to_term(*dash, a) ) return FALSE;
    if ( !(PL_unify_list(list, head, list) &&
           PL_unify(head, a)) )
    { return FALSE;
    }
  }

  if ( !PL_unify_nil(list) )
  { return FALSE;
  }

  if ( !plcairo_double_to_term(offset, t_offset) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_dash_count)
{
  term_t t_cr = FA0;
  term_t t_dash_count = FA1;

  cairo_t *cr;
  int dash_count;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  dash_count = cairo_get_dash_count(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_int_to_term(dash_count, t_dash_count) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_fill_rule)
{
  term_t t_cr = FA0;
  term_t t_fill_rule = FA1;

  cairo_t *cr;
  cairo_fill_rule_t fill_rule;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  fill_rule = cairo_get_fill_rule(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_fill_rule_to_term(fill_rule, t_fill_rule) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_group_target)
{
  term_t t_cr = FA0;
  term_t t_surface = FA1;

  cairo_t *cr;
  cairo_surface_t *surface;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  surface = cairo_get_group_target(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_line_cap)
{
  term_t t_cr = FA0;
  term_t t_line_cap = FA1;

  cairo_t *cr;
  cairo_line_cap_t line_cap;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  line_cap = cairo_get_line_cap(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_line_cap_to_term(line_cap, t_line_cap) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_line_join)
{
  term_t t_cr = FA0;
  term_t t_line_join = FA1;

  cairo_t *cr;
  cairo_line_join_t line_join;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  line_join = cairo_get_line_join(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_line_cap_to_term(line_join, t_line_join) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_line_width)
{
  term_t t_cr = FA0;
  term_t t_width = FA1;

  cairo_t *cr;
  double width;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  width = cairo_get_line_width(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_double_to_term(width, t_width) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_miter_limit)
{
  term_t t_cr = FA0;
  term_t t_limit = FA1;

  cairo_t *cr;
  double limit;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  limit = cairo_get_miter_limit(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_double_to_term(limit, t_limit) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_operator)
{
  term_t t_cr = FA0;
  term_t t_op = FA1;

  cairo_t *cr;
  cairo_operator_t op;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  op = cairo_get_operator(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_operator_to_term(op, t_op) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_source)
{
  term_t t_cr = FA0;
  term_t t_pattern = FA1;

  cairo_t *cr;
  cairo_pattern_t *pattern;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  pattern = cairo_get_source(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_pattern_to_term(pattern, t_pattern) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_target)
{
  term_t t_cr = FA0;
  term_t t_surface = FA1;

  cairo_t *cr;
  cairo_surface_t *surface;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  surface = cairo_get_target(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_tolerance)
{
  term_t t_cr = FA0;
  term_t t_tolerance = FA1;

  cairo_t *cr;
  double tolerance;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  tolerance = cairo_get_tolerance(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_double_to_term(tolerance, t_tolerance) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_in_clip)
{
  term_t t_cr = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;

  cairo_t *cr;
  double x, y;
  cairo_bool_t ret;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;

  ret = cairo_in_clip(cr, x, y);
  PLCAIRO_CHECK_CONTEXT(cr);

  return (ret != 0);
}


PLCAIRO_PRED_IMPL(plcairo_in_fill)
{
  term_t t_cr = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;

  cairo_t *cr;
  double x, y;
  cairo_bool_t ret;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;

  ret = cairo_in_fill(cr, x, y);
  PLCAIRO_CHECK_CONTEXT(cr);

  return (ret != 0);
}


PLCAIRO_PRED_IMPL(plcairo_in_stroke)
{
  term_t t_cr = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;

  cairo_t *cr;
  double x, y;
  cairo_bool_t ret;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;

  ret = cairo_in_stroke(cr, x, y);
  PLCAIRO_CHECK_CONTEXT(cr);

  return (ret != 0);
}


PLCAIRO_PRED_IMPL(plcairo_mask)
{
  term_t t_cr = FA0;
  term_t t_pattern = FA1;

  cairo_t *cr;
  cairo_pattern_t *pattern;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  cairo_mask(cr, pattern);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_mask_surface)
{
  term_t t_cr = FA0;
  term_t t_surface = FA1;
  term_t t_surface_x = FA2;
  term_t t_surface_y = FA3;

  cairo_t *cr;
  cairo_surface_t *surface;
  double surface_x, surface_y;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_double(t_surface_x, &surface_x) ) return FALSE;
  if ( !plcairo_term_to_double(t_surface_y, &surface_y) ) return FALSE;

  cairo_mask_surface(cr, surface, surface_x, surface_y);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_paint)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_paint(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_paint_with_alpha)
{
  term_t t_cr = FA0;
  term_t t_alpha = FA1;

  cairo_t *cr;
  double alpha;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_alpha, &alpha) ) return FALSE;

  cairo_paint_with_alpha(cr, alpha);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_pop_group)
{
  term_t t_cr = FA0;
  term_t t_pattern = FA1;

  cairo_t *cr;
  cairo_pattern_t *pattern;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  pattern = cairo_pop_group(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_pattern_to_term(pattern, t_pattern) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_pop_group_to_source)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_pop_group_to_source(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_push_group)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_push_group(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_push_group_with_content)
{
  term_t t_cr = FA0;
  term_t t_content = FA1;

  cairo_t *cr;
  cairo_content_t content;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_content(t_content, &content) ) return FALSE;

  cairo_push_group(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_reset_clip)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_reset_clip(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_restore)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_restore(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_save)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_save(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_antialias)
{
  term_t t_cr = FA0;
  term_t t_antialias = FA1;

  cairo_t *cr;
  cairo_antialias_t antialias;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_antialias(t_antialias, &antialias) ) return FALSE;

  cairo_set_antialias(cr, antialias);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_dash)
{
  term_t t_cr = FA0;
  term_t t_dashes = FA1;
  term_t t_offset = FA2;

  cairo_t *cr;
  double *dashes;
  int n_dashes;
  double offset;
  size_t len;
  int i = 0;
  term_t list = PL_copy_term_ref(t_dashes);
  term_t head = PL_new_term_ref();

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_offset, &offset) ) return FALSE;

  if ( PL_skip_list(t_dashes, 0, &len) != PL_LIST )
  { return PL_type_error("list", t_dashes);
  }

  n_dashes = len;
  dashes = g_malloc0_n(n_dashes, sizeof(double));

  while ( PL_get_list(list, head, list) )
  { double *dash = dashes + i++;
    if ( !plcairo_term_to_double(head, dash) )
    { g_free(dashes);
      return FALSE;
    }
  }

  cairo_set_dash(cr, dashes, n_dashes, offset);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_fill_rule)
{
  term_t t_cr = FA0;
  term_t t_fill_rule = FA1;

  cairo_t *cr;
  cairo_fill_rule_t fill_rule;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_fill_rule(t_fill_rule, &fill_rule) ) return FALSE;

  cairo_set_fill_rule(cr, fill_rule);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_line_cap)
{
  term_t t_cr = FA0;
  term_t t_line_cap = FA1;

  cairo_t *cr;
  cairo_line_cap_t line_cap;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_line_cap(t_line_cap, &line_cap) ) return FALSE;

  cairo_set_line_cap(cr, line_cap);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_line_join)
{
  term_t t_cr = FA0;
  term_t t_line_join = FA1;

  cairo_t *cr;
  cairo_line_join_t line_join;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_line_join(t_line_join, &line_join) ) return FALSE;

  cairo_set_line_join(cr, line_join);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_line_width)
{
  term_t t_cr = FA0;
  term_t t_width = FA1;

  cairo_t *cr;
  double width;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_width, &width) ) return FALSE;

  cairo_set_line_width(cr, width);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_miter_limit)
{
  term_t t_cr = FA0;
  term_t t_limit = FA1;

  cairo_t *cr;
  double limit;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_limit, &limit) ) return FALSE;

  cairo_set_miter_limit(cr, limit);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_operator)
{
  term_t t_cr = FA0;
  term_t t_op = FA1;

  cairo_t *cr;
  cairo_operator_t op;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_operator(t_op, &op) ) return FALSE;

  cairo_set_operator(cr, op);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_source)
{
  term_t t_cr = FA0;
  term_t t_pattern = FA1;

  cairo_t *cr;
  cairo_pattern_t *pattern;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_pattern(t_pattern, &pattern) ) return FALSE;

  cairo_set_source(cr, pattern);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_source_rgb)
{
  term_t t_cr = FA0;
  term_t t_red = FA1;
  term_t t_green = FA2;
  term_t t_blue = FA3;

  cairo_t *cr;
  double red, green, blue;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_red, &red) ) return FALSE;
  if ( !plcairo_term_to_double(t_green, &green) ) return FALSE;
  if ( !plcairo_term_to_double(t_blue, &blue) ) return FALSE;

  cairo_set_source_rgb(cr, red, green, blue);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_source_rgba)
{
  term_t t_cr = FA0;
  term_t t_red = FA1;
  term_t t_green = FA2;
  term_t t_blue = FA3;
  term_t t_alpha = FA4;

  cairo_t *cr;
  double red, green, blue, alpha;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_red, &red) ) return FALSE;
  if ( !plcairo_term_to_double(t_green, &green) ) return FALSE;
  if ( !plcairo_term_to_double(t_blue, &blue) ) return FALSE;
  if ( !plcairo_term_to_double(t_alpha, &alpha) ) return FALSE;

  cairo_set_source_rgba(cr, red, green, blue, alpha);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_source_surface)
{
  term_t t_cr = FA0;
  term_t t_surface = FA1;
  term_t t_x = FA2;
  term_t t_y = FA3;

  cairo_t *cr;
  cairo_surface_t *surface;
  double x, y;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_double(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_double(t_y, &y) ) return FALSE;

  cairo_set_source_surface(cr, surface, x, y);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_tolerance)
{
  term_t t_cr = FA0;
  term_t t_tolerance = FA1;

  cairo_t *cr;
  double tolerance;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_tolerance, &tolerance) ) return FALSE;

  cairo_set_tolerance(cr, tolerance);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_show_page)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_show_page(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_stroke)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_stroke(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_stroke_extents)
{
  term_t t_cr = FA0;
  term_t t_x1 = FA1;
  term_t t_y1 = FA2;
  term_t t_x2 = FA3;
  term_t t_y2 = FA4;

  cairo_t *cr;
  double x1, y1, x2, y2;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_stroke_extents(cr, &x1, &y1, &x2, &y2);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_double_to_term(x1, t_x1) ) return FALSE;
  if ( !plcairo_double_to_term(y1, t_y1) ) return FALSE;
  if ( !plcairo_double_to_term(x2, t_x2) ) return FALSE;
  if ( !plcairo_double_to_term(y2, t_y2) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_stroke_preserve)
{
  term_t t_cr = FA0;

  cairo_t *cr;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_stroke_preserve(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}
