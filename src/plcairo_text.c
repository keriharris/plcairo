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


/* cairo_font_slant_t */
static atom_t ATOM_cairo_font_slant_normal = 0;
static atom_t ATOM_cairo_font_slant_italic = 0;
static atom_t ATOM_cairo_font_slant_oblique = 0;

cairo_bool_t
plcairo_term_to_font_slant(term_t              t,
                           cairo_font_slant_t *slant)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_font_slant_t: %p", t, slant);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("cairo_font_slant_t", t);
  }

  if ( !ATOM_cairo_font_slant_normal )
  {
    ATOM_cairo_font_slant_normal = PL_new_atom("CAIRO_FONT_SLANT_NORMAL");
    ATOM_cairo_font_slant_italic = PL_new_atom("CAIRO_FONT_SLANT_ITALIC");
    ATOM_cairo_font_slant_oblique = PL_new_atom("CAIRO_FONT_SLANT_OBLIQUE");
  }

  if ( a == ATOM_cairo_font_slant_normal )
  { *slant = CAIRO_FONT_SLANT_NORMAL;
  }
  else if ( a == ATOM_cairo_font_slant_italic )
  { *slant = CAIRO_FONT_SLANT_ITALIC;
  }
  else if ( a == ATOM_cairo_font_slant_oblique )
  { *slant = CAIRO_FONT_SLANT_OBLIQUE;
  }
  else
  { return PL_domain_error("cairo_font_slant_t", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_font_slant_to_term(cairo_font_slant_t slant,
                           term_t             t)
{
  atom_t a;

  PLCAIRO_debug("    cairo_font_slant_t: %d  --->  term: 0x%lx", slant, t);

  if ( !ATOM_cairo_font_slant_normal )
  {
    ATOM_cairo_font_slant_normal = PL_new_atom("CAIRO_FONT_SLANT_NORMAL");
    ATOM_cairo_font_slant_italic = PL_new_atom("CAIRO_FONT_SLANT_ITALIC");
    ATOM_cairo_font_slant_oblique = PL_new_atom("CAIRO_FONT_SLANT_OBLIQUE");
  }

  if ( slant == CAIRO_FONT_SLANT_NORMAL )
  { a = ATOM_cairo_font_slant_normal;
  }
  else if ( slant == CAIRO_FONT_SLANT_ITALIC )
  { a = ATOM_cairo_font_slant_italic;
  }
  else if ( slant == CAIRO_FONT_SLANT_OBLIQUE )
  { a = ATOM_cairo_font_slant_oblique;
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify_atom(t, a);
}


/* cairo_font_weight_t */
static atom_t ATOM_cairo_font_weight_normal = 0;
static atom_t ATOM_cairo_font_weight_bold = 0;

cairo_bool_t
plcairo_term_to_font_weight(term_t               t,
                            cairo_font_weight_t *weight)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_font_weight_t: %p", t, weight);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("cairo_font_weight_t", t);
  }

  if ( !ATOM_cairo_font_weight_normal )
  {
    ATOM_cairo_font_weight_normal = PL_new_atom("CAIRO_FONT_WEIGHT_NORMAL");
    ATOM_cairo_font_weight_bold = PL_new_atom("CAIRO_FONT_WEIGHT_BOLD");
  }

  if ( a == ATOM_cairo_font_weight_normal )
  { *weight = CAIRO_FONT_WEIGHT_NORMAL;
  }
  else if ( a == ATOM_cairo_font_weight_bold )
  { *weight = CAIRO_FONT_WEIGHT_BOLD;
  }
  else
  { return PL_domain_error("cairo_font_weight_t", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_font_weight_to_term(cairo_font_weight_t weight,
                            term_t              t)
{
  atom_t a;

  PLCAIRO_debug("    cairo_font_weight_t: %d  --->  term: 0x%lx", weight, t);

  if ( !ATOM_cairo_font_weight_normal )
  {
    ATOM_cairo_font_weight_normal = PL_new_atom("CAIRO_FONT_WEIGHT_NORMAL");
    ATOM_cairo_font_weight_bold = PL_new_atom("CAIRO_FONT_WEIGHT_BOLD");
  }

  if ( weight == CAIRO_FONT_WEIGHT_NORMAL )
  { a = ATOM_cairo_font_weight_normal;
  }
  else if ( weight == CAIRO_FONT_WEIGHT_BOLD )
  { a = ATOM_cairo_font_weight_bold;
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify_atom(t, a);
}


/* cairo_glyph_t */
void plcairo_register_glyph_t(void)
{
  PLGIStructInfo *struct_info;
  PLGIFieldInfo *field_info;
  int n_fields, offset;

  PLCAIRO_debug("registering struct: CairoGlyph");

  n_fields = 3;
  offset = 0;

  struct_info = g_malloc0(sizeof(*struct_info));
  struct_info->info = NULL;
  struct_info->namespace = PL_new_atom("cairo");
  struct_info->name = PL_new_atom("CairoGlyph");
  struct_info->gtype = G_TYPE_NONE;
  struct_info->size = sizeof(cairo_glyph_t);
  struct_info->n_fields = n_fields;
  struct_info->fields_info = g_malloc0_n(n_fields, sizeof(*struct_info->fields_info));

  plcairo_alloc_struct_ulong_field(0, "index");
  plcairo_alloc_struct_double_field(1, "x");
  plcairo_alloc_struct_double_field(2, "y");

  plgi_cache_struct_info(struct_info);
}


cairo_bool_t
plcairo_term_to_glyph(term_t          t,
                      cairo_glyph_t **glyph)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_glyph_t: %p", t, *glyph);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoGlyph", t);
  }

  if ( blob->name != PL_new_atom("CairoGlyph") )
  { return PL_type_error("CairoGlyph", t);
  }

  *glyph = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_glyph_to_term(cairo_glyph_t *glyph,
                      term_t         t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_glyph_t: %p  --->  term: 0x%lx", glyph, t);

  if ( !glyph )
  { return ( plcairo_put_null(t0) && PL_unify(t, t0) );
  }

  data = g_memdup(glyph, sizeof(*glyph));
  blob_type = PLGI_BLOB_SIMPLE;

  if ( !plgi_put_blob(blob_type, G_TYPE_NONE,
                      PL_new_atom("CairoGlyph"), data, t0, NULL) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}


/* cairo_text_cluster_t */
void plcairo_register_text_cluster_t(void)
{
  PLGIStructInfo *struct_info;
  PLGIFieldInfo *field_info;
  int n_fields, offset;

  PLCAIRO_debug("registering struct: CairoTextCluster");

  n_fields = 3;
  offset = 0;

  struct_info = g_malloc0(sizeof(*struct_info));
  struct_info->info = NULL;
  struct_info->namespace = PL_new_atom("cairo");
  struct_info->name = PL_new_atom("CairoTextCluster");
  struct_info->gtype = G_TYPE_NONE;
  struct_info->size = sizeof(cairo_text_cluster_t);
  struct_info->n_fields = n_fields;
  struct_info->fields_info = g_malloc0_n(n_fields, sizeof(*struct_info->fields_info));

  plcairo_alloc_struct_int_field(0, "num_bytes");
  plcairo_alloc_struct_int_field(1, "num_glyphs");

  plgi_cache_struct_info(struct_info);
}


cairo_bool_t
plcairo_term_to_text_cluster(term_t                 t,
                             cairo_text_cluster_t **text_cluster)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_text_cluster_t: %p", t, *text_cluster);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoGlyph", t);
  }

  if ( blob->name != PL_new_atom("CairoGlyph") )
  { return PL_type_error("CairoGlyph", t);
  }

  *text_cluster = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_text_cluster_to_term(cairo_text_cluster_t *text_cluster,
                             term_t                t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_text_cluster_t: %p  --->  term: 0x%lx", text_cluster, t);

  if ( !text_cluster )
  { return ( plcairo_put_null(t0) && PL_unify(t, t0) );
  }

  data = g_memdup(text_cluster, sizeof(*text_cluster));
  blob_type = PLGI_BLOB_SIMPLE;

  if ( !plgi_put_blob(blob_type, G_TYPE_NONE,
                      PL_new_atom("CairoTextCluster"), data, t0, NULL) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}


/* cairo_text_cluster_flags_t */
static atom_t ATOM_cairo_text_cluster_flag_backward = 0;

cairo_bool_t
plcairo_term_to_text_cluster_flags(term_t                      t,
                                   cairo_text_cluster_flags_t *flags)
{
  term_t list = PL_copy_term_ref(t);
  term_t head = PL_new_term_ref();
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_text_cluster_flags_t: %p", t, flags);

  if ( !ATOM_cairo_text_cluster_flag_backward )
  {
    ATOM_cairo_text_cluster_flag_backward = PL_new_atom("CAIRO_TEXT_CLUSTER_FLAG_BACKWARD");
  }

  if ( PL_skip_list(list, 0, NULL) != PL_LIST )
  { return PL_type_error("list", t);
  }

  *flags = 0;
  while ( PL_get_list(list, head, list) )
  {
    if ( !PL_get_atom(head, &a) )
    { return PL_type_error("CairoTextClusterFlags", head);
    }

    if ( a == ATOM_cairo_text_cluster_flag_backward )
    { *flags |= CAIRO_TEXT_CLUSTER_FLAG_BACKWARD;
    }
    else
    { return PL_domain_error("CairoTextClusterFlags", t);
    }
  }

  return TRUE;
}

cairo_bool_t
plcairo_text_cluster_flags_to_term(cairo_text_cluster_flags_t flags,
                                   term_t                     t)
{
  PLCAIRO_debug("    cairo_text_cluster_flags_t: %d  --->  term: 0x%lx", flags, t);

  if ( !ATOM_cairo_text_cluster_flag_backward )
  {
    ATOM_cairo_text_cluster_flag_backward = PL_new_atom("CAIRO_TEXT_CLUSTER_FLAG_BACKWARD");
  }

  if ( flags == CAIRO_TEXT_CLUSTER_FLAG_BACKWARD )
  { term_t a = PL_new_term_ref();
    PL_put_atom(a, ATOM_cairo_text_cluster_flag_backward);
    PL_put_nil(t);
    if ( !PL_cons_list(t, a, t) ) return FALSE;
    return TRUE;
  }
  else if ( !flags )
  { if ( !PL_unify_nil(t) ) return FALSE;
  }
  else
  { g_assert_not_reached();
  }

  return TRUE;
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLCAIRO_PRED_IMPL(plcairo_font_extents)
{
  term_t t_cr = FA0;
  term_t t_extents = FA1;

  cairo_t *cr;
  cairo_font_extents_t extents;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_font_extents(cr, &extents);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_font_extents_to_term(&extents, t_extents) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_font_face)
{
  term_t t_cr = FA0;
  term_t t_font_face = FA1;

  cairo_t *cr;
  cairo_font_face_t *font_face;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  font_face = cairo_get_font_face(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_font_face_to_term(font_face, t_font_face) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_font_matrix)
{
  term_t t_cr = FA0;
  term_t t_matrix = FA1;

  cairo_t *cr;
  cairo_matrix_t matrix;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  cairo_get_font_matrix(cr, &matrix);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_matrix_to_term(&matrix, t_matrix) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_font_options)
{
  term_t t_cr = FA0;
  term_t t_options = FA1;

  cairo_t *cr;
  cairo_font_options_t *options;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;

  cairo_get_font_options(cr, options);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_get_scaled_font)
{
  term_t t_cr = FA0;
  term_t t_scaled_font = FA1;

  cairo_t *cr;
  cairo_scaled_font_t *scaled_font;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  scaled_font = cairo_get_scaled_font(cr);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_scaled_font_to_term(scaled_font, t_scaled_font) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_glyph_extents)
{
  term_t t_cr = FA0;
  term_t t_glyphs = FA1;
  term_t t_extents = FA2;

  cairo_t *cr;
  cairo_glyph_t *glyphs;
  int num_glyphs;
  size_t len;
  cairo_text_extents_t extents;
  term_t list = PL_copy_term_ref(t_glyphs);
  term_t head = PL_new_term_ref();
  int i = 0;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  if ( PL_skip_list(list, 0, &len) != PL_LIST )
  { return PL_type_error("list", t_glyphs);
  }

  num_glyphs = len;
  glyphs = g_malloc0_n(num_glyphs, sizeof(cairo_glyph_t));

  while ( PL_get_list(list, head, list) )
  { cairo_glyph_t *glyph = glyphs + i++;

    if ( !plcairo_term_to_glyph(head, &glyph) )
    { g_free(glyphs);
      return PL_type_error("CairoGlyph", head);
    }
  }

  cairo_glyph_extents(cr, glyphs, num_glyphs, &extents);
  g_free(glyphs);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_text_extents_to_term(&extents, t_extents) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_select_font_face)
{
  term_t t_cr = FA0;
  term_t t_family = FA1;
  term_t t_slant = FA2;
  term_t t_weight = FA3;

  cairo_t *cr;
  cairo_font_slant_t slant;
  cairo_font_weight_t weight;
  char *family;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_string(t_family, &family) ) return FALSE;
  if ( !plcairo_term_to_font_slant(t_slant, &slant) ) return FALSE;
  if ( !plcairo_term_to_font_weight(t_weight, &weight) ) return FALSE;

  cairo_select_font_face(cr, family, slant, weight);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_font_face)
{
  term_t t_cr = FA0;
  term_t t_font_face = FA1;

  cairo_t *cr;
  cairo_font_face_t *font_face;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_font_face(t_font_face, &font_face) ) return FALSE;

  cairo_set_font_face(cr, font_face);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_font_matrix)
{
  term_t t_cr = FA0;
  term_t t_matrix = FA1;

  cairo_t *cr;
  cairo_matrix_t *matrix;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_matrix(t_matrix, &matrix) ) return FALSE;

  cairo_set_font_matrix(cr, matrix);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_font_options)
{
  term_t t_cr = FA0;
  term_t t_options = FA1;

  cairo_t *cr;
  cairo_font_options_t *options;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;

  cairo_set_font_options(cr, options);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_font_size)
{
  term_t t_cr = FA0;
  term_t t_size = FA1;

  cairo_t *cr;
  double size;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_double(t_size, &size) ) return FALSE;

  cairo_set_font_size(cr, size);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_set_scaled_font)
{
  term_t t_cr = FA0;
  term_t t_scaled_font = FA1;

  cairo_t *cr;
  cairo_scaled_font_t *scaled_font;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_scaled_font(t_scaled_font, &scaled_font) ) return FALSE;

  cairo_set_scaled_font(cr, scaled_font);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_show_glyphs)
{
  term_t t_cr = FA0;
  term_t t_glyphs = FA1;

  cairo_t *cr;
  cairo_glyph_t *glyphs;
  int num_glyphs;
  size_t len;
  term_t list = PL_copy_term_ref(t_glyphs);
  term_t head = PL_new_term_ref();
  int i = 0;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;

  if ( PL_skip_list(list, 0, &len) != PL_LIST )
  { return PL_type_error("list", t_glyphs);
  }

  num_glyphs = len;
  glyphs = g_malloc0_n(num_glyphs, sizeof(cairo_glyph_t));

  while ( PL_get_list(list, head, list) )
  { cairo_glyph_t *glyph = glyphs + i++;

    if ( !plcairo_term_to_glyph(head, &glyph) )
    { g_free(glyphs);
      return PL_type_error("CairoGlyph", head);
    }
  }

  cairo_show_glyphs(cr, glyphs, num_glyphs);
  g_free(glyphs);
  PLCAIRO_CHECK_CONTEXT(cr);
      
  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_show_text)
{
  term_t t_cr = FA0;
  term_t t_text = FA1;

  cairo_t *cr;
  char *text;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_string(t_text, &text) ) return FALSE;

  cairo_show_text(cr, text);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_show_text_glyphs)
{
  term_t t_cr = FA0;
  term_t t_text = FA1;
  term_t t_glyphs = FA2;
  term_t t_clusters = FA3;
  term_t t_cluster_flags = FA4;

  cairo_t *cr;
  char *text;
  cairo_glyph_t *glyphs;
  int num_glyphs;
  cairo_text_cluster_t *clusters;
  int num_clusters;
  cairo_text_cluster_flags_t cluster_flags;
  size_t len;
  term_t glist = PL_copy_term_ref(t_glyphs);
  term_t ghead = PL_new_term_ref();
  term_t clist = PL_copy_term_ref(t_glyphs);
  term_t chead = PL_new_term_ref();
  int i = 0;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_string(t_text, &text) ) return FALSE;
  if ( !plcairo_term_to_text_cluster_flags(t_cluster_flags, &cluster_flags) ) return FALSE;

  if ( PL_skip_list(glist, 0, &len) != PL_LIST )
  { return PL_type_error("list", t_glyphs);
  }
  num_glyphs = len;
  glyphs = g_malloc0_n(num_glyphs, sizeof(cairo_glyph_t));

  if ( PL_skip_list(clist, 0, &len) != PL_LIST )
  { return PL_type_error("list", t_clusters);
  }
  num_clusters = len;
  clusters = g_malloc0_n(num_clusters, sizeof(cairo_text_cluster_t));

  while ( PL_get_list(glist, ghead, glist) )
  { cairo_glyph_t *glyph = glyphs + i++;

    if ( !plcairo_term_to_glyph(ghead, &glyph) )
    { g_free(glyphs);
      g_free(clusters);
      return PL_type_error("CairoGlyph", ghead);
    }
  }

  while ( PL_get_list(clist, chead, clist) )
  { cairo_text_cluster_t *cluster = clusters + i++;

    if ( !plcairo_term_to_text_cluster(chead, &cluster) )
    { g_free(glyphs);
      g_free(clusters);
      return PL_type_error("CairoTextCluster", chead);
    }
  }

  cairo_show_text_glyphs(cr, text, -1, glyphs, num_glyphs, clusters, num_clusters, cluster_flags);
  g_free(glyphs);
  g_free(clusters);
  PLCAIRO_CHECK_CONTEXT(cr);
      
  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_text_extents)
{
  term_t t_cr = FA0;
  term_t t_text = FA1;
  term_t t_extents = FA2;

  cairo_t *cr;
  char *text;
  cairo_text_extents_t extents;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_string(t_text, &text) ) return FALSE;

  cairo_text_extents(cr, text, &extents);
  PLCAIRO_CHECK_CONTEXT(cr);

  if ( !plcairo_text_extents_to_term(&extents, t_extents) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_toy_font_face_create)
{
  term_t t_family = FA0;
  term_t t_slant = FA1;
  term_t t_weight = FA2;
  term_t t_font_face = FA3;

  char *family;
  cairo_font_slant_t slant;
  cairo_font_weight_t weight;
  cairo_font_face_t *font_face;

  if ( !plcairo_term_to_string(t_family, &family) ) return FALSE;
  if ( !plcairo_term_to_font_slant(t_slant, &slant) ) return FALSE;
  if ( !plcairo_term_to_font_weight(t_weight, &weight) ) return FALSE;

  font_face = cairo_toy_font_face_create(family, slant, weight);
  PLCAIRO_CHECK_FONT_FACE(font_face);

  if ( !plcairo_font_face_to_term(font_face, t_font_face) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_toy_font_face_get_family)
{
  term_t t_font_face = FA0;
  term_t t_family = FA1;

  cairo_font_face_t *font_face;
  char *family;

  if ( !plcairo_term_to_font_face(t_font_face, &font_face) ) return FALSE;

  family = (char*)cairo_toy_font_face_get_family(font_face);
  PLCAIRO_CHECK_FONT_FACE(font_face);

  if ( !plcairo_string_to_term(family, t_family) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_toy_font_face_get_slant)
{
  term_t t_font_face = FA0;
  term_t t_slant = FA1;

  cairo_font_face_t *font_face;
  cairo_font_slant_t slant;

  if ( !plcairo_term_to_font_face(t_font_face, &font_face) ) return FALSE;

  slant = cairo_toy_font_face_get_slant(font_face);
  PLCAIRO_CHECK_FONT_FACE(font_face);

  if ( !plcairo_font_slant_to_term(slant, t_slant) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_toy_font_face_get_weight)
{
  term_t t_font_face = FA0;
  term_t t_weight = FA1;

  cairo_font_face_t *font_face;
  cairo_font_weight_t weight;

  if ( !plcairo_term_to_font_face(t_font_face, &font_face) ) return FALSE;

  weight = cairo_toy_font_face_get_weight(font_face);
  PLCAIRO_CHECK_FONT_FACE(font_face);

  if ( !plcairo_font_slant_to_term(weight, t_weight) ) return FALSE;

  return TRUE;
}
