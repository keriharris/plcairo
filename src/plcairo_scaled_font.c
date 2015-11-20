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


/* cairo_scaled_font_t */
cairo_bool_t
plcairo_term_to_scaled_font(term_t                t,
                            cairo_scaled_font_t **scaled_font)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_scaled_font_t: %p", t, *scaled_font);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoScaledFont", t);
  }

  if ( blob->gtype != G_TYPE_NONE &&
       !g_type_is_a( blob->gtype, CAIRO_GOBJECT_TYPE_SCALED_FONT ) )
  { return PL_type_error("CairoScaledFont", t);
  }

  *scaled_font = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_scaled_font_to_term(cairo_scaled_font_t *scaled_font,
                            term_t               t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_scaled_font_t: %p  --->  term: 0x%lx", scaled_font, t);

  if ( !scaled_font )
  { return ( plgi_put_null(t0) && PL_unify(t, t0) );
  }

  data = scaled_font;
  blob_type = PLGI_BLOB_BOXED;

  if ( !plgi_put_blob(blob_type, CAIRO_GOBJECT_TYPE_SCALED_FONT,
                      PL_new_atom("CairoScaledFont"), TRUE, data, t0) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}


/* cairo_font_extents_t */
void plcairo_register_font_extents_t(void)
{
  PLGIStructInfo *struct_info;
  PLGIFieldInfo *field_info;
  int n_fields, offset;

  PLCAIRO_debug("registering struct: CairoFontExtents");

  n_fields = 5;
  offset = 0;

  struct_info = g_malloc0(sizeof(*struct_info));
  struct_info->info = NULL;
  struct_info->namespace = PL_new_atom("cairo");
  struct_info->name = PL_new_atom("CairoFontExtents");
  struct_info->gtype = G_TYPE_NONE;
  struct_info->size = sizeof(cairo_font_extents_t);
  struct_info->n_fields = n_fields;
  struct_info->fields_info = g_malloc0_n(n_fields, sizeof(*struct_info->fields_info));

  plcairo_alloc_struct_double_field(0, "ascent");
  plcairo_alloc_struct_double_field(1, "descent");
  plcairo_alloc_struct_double_field(2, "height");
  plcairo_alloc_struct_double_field(3, "x_advance");
  plcairo_alloc_struct_double_field(4, "y_advance");

  plgi_cache_struct_info(struct_info);
}


cairo_bool_t
plcairo_term_to_font_extents(term_t                 t,
                             cairo_font_extents_t **extents)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_font_extents_t: %p", t, *extents);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoFontExtents", t);
  }

  if ( blob->name != PL_new_atom("CairoFontExtents") )
  { return PL_type_error("CairoFontExtents", t);
  }

  *extents = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_font_extents_to_term(cairo_font_extents_t *extents,
                             term_t                t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_font_extents_t: %p  --->  term: 0x%lx", extents, t);

  if ( !extents )
  { return ( plgi_put_null(t0) && PL_unify(t, t0) );
  }

  data = g_memdup(extents, sizeof(*extents));
  blob_type = PLGI_BLOB_SIMPLE;

  if ( !plgi_put_blob(blob_type, G_TYPE_NONE,
                      PL_new_atom("CairoFontExtents"), TRUE, data, t0) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}


/* cairo_text_extents_t */
void plcairo_register_text_extents_t(void)
{
  PLGIStructInfo *struct_info;
  PLGIFieldInfo *field_info;
  int n_fields, offset;

  PLCAIRO_debug("registering struct: CairoTextExtents");

  n_fields = 6;
  offset = 0;

  struct_info = g_malloc0(sizeof(*struct_info));
  struct_info->info = NULL;
  struct_info->namespace = PL_new_atom("cairo");
  struct_info->name = PL_new_atom("CairoTextExtents");
  struct_info->gtype = G_TYPE_NONE;
  struct_info->size = sizeof(cairo_text_extents_t);
  struct_info->n_fields = n_fields;
  struct_info->fields_info = g_malloc0_n(n_fields, sizeof(*struct_info->fields_info));

  plcairo_alloc_struct_double_field(0, "x_bearing");
  plcairo_alloc_struct_double_field(1, "y_bearing");
  plcairo_alloc_struct_double_field(2, "width");
  plcairo_alloc_struct_double_field(3, "height");
  plcairo_alloc_struct_double_field(4, "x_advance");
  plcairo_alloc_struct_double_field(5, "y_advance");

  plgi_cache_struct_info(struct_info);
}


cairo_bool_t
plcairo_term_to_text_extents(term_t                 t,
                             cairo_text_extents_t **extents)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_text_extents_t: %p", t, *extents);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoTextExtents", t);
  }

  if ( blob->name != PL_new_atom("CairoTextExtents") )
  { return PL_type_error("CairoTextExtents", t);
  }

  *extents = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_text_extents_to_term(cairo_text_extents_t *extents,
                             term_t                t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_text_extents_t: %p  --->  term: 0x%lx", extents, t);

  if ( !extents )
  { return ( plgi_put_null(t0) && PL_unify(t, t0) );
  }

  data = g_memdup(extents, sizeof(*extents));
  blob_type = PLGI_BLOB_SIMPLE;

  if ( !plgi_put_blob(blob_type, G_TYPE_NONE,
                      PL_new_atom("CairoTextExtents"), TRUE, data, t0) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLCAIRO_PRED_IMPL(plcairo_scaled_font_create)
{
  term_t t_font_face = FA0;
  term_t t_font_matrix = FA1;
  term_t t_ctm = FA2;
  term_t t_options = FA3;
  term_t t_scaled_font = FA4;

  cairo_font_face_t *font_face;
  cairo_matrix_t *font_matrix;
  cairo_matrix_t *ctm;
  cairo_font_options_t *options;
  cairo_scaled_font_t *scaled_font;

  if ( !plcairo_term_to_font_face(t_font_face, &font_face) ) return FALSE;
  if ( !plcairo_term_to_matrix(t_font_matrix, &font_matrix) ) return FALSE;
  if ( !plcairo_term_to_matrix(t_ctm, &ctm) ) return FALSE;
  if ( !plcairo_term_to_font_options(t_options, &options) ) return FALSE;

  scaled_font = cairo_scaled_font_create(font_face, font_matrix, ctm, options);
  PLCAIRO_CHECK_SCALED_FONT(scaled_font);

  if ( !plcairo_scaled_font_to_term(scaled_font, t_scaled_font) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_scaled_font_extents)
{
  term_t t_scaled_font = FA0;
  term_t t_extents = FA1;

  cairo_scaled_font_t *scaled_font;
  cairo_font_extents_t extents;

  if ( !plcairo_term_to_scaled_font(t_scaled_font, &scaled_font) ) return FALSE;

  cairo_scaled_font_extents(scaled_font, &extents);
  PLCAIRO_CHECK_SCALED_FONT(scaled_font);

  if ( !plcairo_font_extents_to_term(&extents, t_extents) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_scaled_font_get_ctm)
{
  term_t t_scaled_font = FA0;
  term_t t_ctm = FA1;

  cairo_scaled_font_t *scaled_font;
  cairo_matrix_t ctm;

  if ( !plcairo_term_to_scaled_font(t_scaled_font, &scaled_font) ) return FALSE;

  cairo_scaled_font_get_ctm(scaled_font, &ctm);
  PLCAIRO_CHECK_SCALED_FONT(scaled_font);

  if ( !plcairo_matrix_to_term(&ctm, t_ctm) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_scaled_font_get_font_face)
{
  term_t t_scaled_font = FA0;
  term_t t_font_face = FA1;

  cairo_scaled_font_t *scaled_font;
  cairo_font_face_t *font_face;

  if ( !plcairo_term_to_scaled_font(t_scaled_font, &scaled_font) ) return FALSE;

  font_face = cairo_scaled_font_get_font_face(scaled_font);
  PLCAIRO_CHECK_SCALED_FONT(scaled_font);

  if ( !plcairo_font_face_to_term(font_face, t_font_face) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_scaled_font_get_font_matrix)
{
  term_t t_scaled_font = FA0;
  term_t t_font_matrix = FA1;

  cairo_scaled_font_t *scaled_font;
  cairo_matrix_t font_matrix;

  if ( !plcairo_term_to_scaled_font(t_scaled_font, &scaled_font) ) return FALSE;

  cairo_scaled_font_get_font_matrix(scaled_font, &font_matrix);
  PLCAIRO_CHECK_SCALED_FONT(scaled_font);

  if ( !plcairo_matrix_to_term(&font_matrix, t_font_matrix) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_scaled_font_get_font_options)
{
  term_t t_scaled_font = FA0;
  term_t t_font_options = FA1;

  cairo_scaled_font_t *scaled_font;
  cairo_font_options_t *font_options;

  if ( !plcairo_term_to_scaled_font(t_scaled_font, &scaled_font) ) return FALSE;

  font_options = cairo_font_options_create();
  cairo_scaled_font_get_font_options(scaled_font, font_options);
  PLCAIRO_CHECK_SCALED_FONT(scaled_font);

  if ( !plcairo_font_options_to_term(font_options, t_font_options) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_scaled_font_get_scale_matrix)
{
  term_t t_scaled_font = FA0;
  term_t t_scale_matrix = FA1;

  cairo_scaled_font_t *scaled_font;
  cairo_matrix_t scale_matrix;

  if ( !plcairo_term_to_scaled_font(t_scaled_font, &scaled_font) ) return FALSE;

  cairo_scaled_font_get_scale_matrix(scaled_font, &scale_matrix);
  PLCAIRO_CHECK_SCALED_FONT(scaled_font);

  if ( !plcairo_matrix_to_term(&scale_matrix, t_scale_matrix) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_scaled_font_get_type)
{
  term_t t_scaled_font = FA0;
  term_t t_font_type = FA1;

  cairo_scaled_font_t *scaled_font;
  cairo_font_type_t font_type;

  if ( !plcairo_term_to_scaled_font(t_scaled_font, &scaled_font) ) return FALSE;

  font_type = cairo_scaled_font_get_type(scaled_font);
  PLCAIRO_CHECK_SCALED_FONT(scaled_font);

  if ( !plcairo_font_type_to_term(font_type, t_font_type) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_scaled_font_glyph_extents)
{
  term_t t_scaled_font = FA0;
  term_t t_glyphs = FA1;
  term_t t_extents = FA2;

  cairo_scaled_font_t *scaled_font;
  cairo_glyph_t *glyphs;
  int num_glyphs;
  size_t len;
  cairo_text_extents_t extents;
  term_t list = PL_copy_term_ref(t_glyphs);
  term_t head = PL_new_term_ref();
  int i = 0;

  if ( !plcairo_term_to_scaled_font(t_scaled_font, &scaled_font) ) return FALSE;
  if ( PL_skip_list(list, 0, &len) != PL_LIST )
  { return PL_type_error("list", t_glyphs);
  }
  num_glyphs = len;
  glyphs = cairo_glyph_allocate(num_glyphs);
  while ( PL_get_list(list, head, list) )
  { if ( !plcairo_term_to_glyph(head, &glyphs + i) )
    { cairo_glyph_free(glyphs);
      return FALSE;
    }
    i++;
  }

  cairo_scaled_font_glyph_extents(scaled_font, glyphs, num_glyphs, &extents);
  PLCAIRO_CHECK_SCALED_FONT(scaled_font);

  if ( !plcairo_text_extents_to_term(&extents, t_extents) )
  { cairo_glyph_free(glyphs);
    return FALSE;
  }
  cairo_glyph_free(glyphs);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_scaled_font_text_extents)
{
  term_t t_scaled_font = FA0;
  term_t t_text = FA1;
  term_t t_extents = FA2;

  cairo_scaled_font_t *scaled_font;
  char *text;
  cairo_text_extents_t extents;

  if ( !plcairo_term_to_scaled_font(t_scaled_font, &scaled_font) ) return FALSE;
  if ( !plcairo_term_to_string(t_text, &text) ) return FALSE;

  cairo_scaled_font_text_extents(scaled_font, text, &extents);
  PLCAIRO_CHECK_SCALED_FONT(scaled_font);

  if ( !plcairo_text_extents_to_term(&extents, t_extents) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_scaled_font_text_to_glyphs)
{
  term_t t_scaled_font = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;
  term_t t_text = FA3;
  term_t t_glyphs = FA4;
  term_t t_clusters = FA5;
  term_t t_cluster_flags = FA6;

  cairo_scaled_font_t *scaled_font;
  int x;
  int y;
  char *text;
  int text_len = -1;
  cairo_glyph_t *glyphs = NULL;
  int num_glyphs;
  cairo_text_cluster_t *clusters = NULL;
  int num_clusters;
  cairo_text_cluster_flags_t cluster_flags;
  cairo_status_t status;
  int ret, i;
  term_t t, list, head;

  if ( !plcairo_term_to_scaled_font(t_scaled_font, &scaled_font) ) return FALSE;
  if ( !plcairo_term_to_int(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_int(t_y, &y) ) return FALSE;
  if ( !plcairo_term_to_string(t_text, &text) ) return FALSE;

  status = cairo_scaled_font_text_to_glyphs(scaled_font, x, y, text, text_len, &glyphs, &num_glyphs, &clusters, &num_clusters, &cluster_flags);
  PLCAIRO_CHECK_SCALED_FONT(scaled_font);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  t = PL_new_term_ref();
  list = PL_copy_term_ref(t);
  head = PL_new_term_ref();
  for ( i = 0; i < num_glyphs; i++ )
  { term_t a = PL_new_term_ref();
    if ( !plcairo_glyph_to_term(glyphs + i, a) )
    { ret = FALSE;
      goto cleanup;
    }
    if ( !(PL_unify_list(list, head, list) &&
           PL_unify(head, a)) )
    { ret = FALSE;
      goto cleanup;
    }
  }
  if ( !PL_unify(t, t_glyphs) )
  { ret = FALSE;
    goto cleanup;
  }

  t = PL_new_term_ref();
  list = PL_copy_term_ref(t);
  head = PL_new_term_ref();
  for ( i = 0; i < num_clusters; i++ )
  { term_t a = PL_new_term_ref();
    if ( !plcairo_text_cluster_to_term(clusters + i, a) )
    { ret = FALSE;
      goto cleanup;
    }
    if ( !(PL_unify_list(list, head, list) &&
           PL_unify(head, a)) )
    { ret = FALSE;
      goto cleanup;
    }
  }
  if ( !PL_unify(t, t_clusters) )
  { ret = FALSE;
    goto cleanup;
  }

  if ( !plcairo_text_cluster_flags_to_term(cluster_flags, t_cluster_flags) )
  { ret = FALSE;
    goto cleanup;
  }

  ret = TRUE;

cleanup:

  if ( glyphs )
  { cairo_glyph_free(glyphs);
  }
  if ( clusters )
  { cairo_text_cluster_free(clusters);
  }

  return ret;
}
