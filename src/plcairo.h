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

#include <SWI-Stream.h>
#include <SWI-Prolog.h>
#include <cairo.h>
#include <cairo-gobject.h>
#include <plgi.h>



                /*******************************
                 *    Cairo Integral Types     *
                 *******************************/

#define plcairo_term_to_bool(t, v) plgi_term_to_gboolean(t, v)
#define plcairo_bool_to_term(v, t) plgi_gboolean_to_term(v, t)

#define plcairo_term_to_char(t, v) plgi_term_to_gint8(t, v)
#define plcairo_char_to_term(v, t) plgi_gint8_to_term(v, t)

#define plcairo_term_to_int(t, v) plgi_term_to_gint(t, v)
#define plcairo_int_to_term(v, t) plgi_gint_to_term(v, t)

#define plcairo_term_to_unsigned_int(t, v) plgi_term_to_guint(t, v)
#define plcairo_unsigned_int_to_term(v, t) plgi_guint_to_term(v, t)

#define plcairo_term_to_long(t, v) plgi_term_to_glong(t, v)
#define plcairo_long_to_term(v, t) plgi_glong_to_term(v, t)

#define plcairo_term_to_unsigned_long(t, v) plgi_term_to_gulong(t, v)
#define plcairo_unsigned_long_to_term(v, t) plgi_gulong_to_term(v, t)

#define plcairo_term_to_double(t, v) plgi_term_to_gdouble(t, v)
#define plcairo_double_to_term(v, t) plgi_gdouble_to_term(v, t)

#define plcairo_term_to_string(t, v) plgi_term_to_utf8(t, v)
#define plcairo_string_to_term(v, t) plgi_utf8_to_term(v, t)



                /*******************************
                 *     Cairo Struct Fields     *
                 *******************************/

#define plcairo_alloc_struct_double_field(i, n) \
	{ PLGIArgInfo *arg_info = g_malloc(sizeof(*arg_info)); \
	  arg_info->type_tag = GI_TYPE_TAG_DOUBLE; \
	  field_info = struct_info->fields_info + i; \
	  field_info->name = PL_new_atom(n); \
	  field_info->size = sizeof(double); \
	  field_info->offset = offset; offset += sizeof(double); \
	  field_info->flags = GI_FIELD_IS_READABLE | GI_FIELD_IS_WRITABLE; \
	  field_info->arg_info = arg_info; \
	}

#define plcairo_alloc_struct_int_field(i, n) \
	{ PLGIArgInfo *arg_info = g_malloc(sizeof(*arg_info)); \
	  arg_info->type_tag = GI_TYPE_TAG_INT32; \
	  field_info = struct_info->fields_info + i; \
	  field_info->name = PL_new_atom(n); \
	  field_info->size = sizeof(int); \
	  field_info->offset = offset; offset += sizeof(int); \
	  field_info->flags = GI_FIELD_IS_READABLE | GI_FIELD_IS_WRITABLE; \
	  field_info->arg_info = arg_info; \
	}

#define plcairo_alloc_struct_uint32_field(i, n) \
	{ PLGIArgInfo *arg_info = g_malloc(sizeof(*arg_info)); \
	  arg_info->type_tag = GI_TYPE_TAG_UINT32; \
	  field_info = struct_info->fields_info + i; \
	  field_info->name = PL_new_atom(n); \
	  field_info->size = sizeof(guint32); \
	  field_info->offset = offset; offset += sizeof(guint32); \
	  field_info->flags = GI_FIELD_IS_READABLE | GI_FIELD_IS_WRITABLE; \
	  field_info->arg_info = arg_info; \
	}

#define plcairo_alloc_struct_uint64_field(i, n) \
	{ PLGIArgInfo *arg_info = g_malloc(sizeof(*arg_info)); \
	  arg_info->type_tag = GI_TYPE_TAG_UINT64; \
	  field_info = struct_info->fields_info + i; \
	  field_info->name = PL_new_atom(n); \
	  field_info->size = sizeof(guint64); \
	  field_info->offset = offset; offset += sizeof(guint64); \
	  field_info->flags = GI_FIELD_IS_READABLE | GI_FIELD_IS_WRITABLE; \
	  field_info->arg_info = arg_info; \
	}

#if SIZEOF_LONG == 8
#define plcairo_alloc_struct_ulong_field plcairo_alloc_struct_uint64_field
#else
#define plcairo_alloc_struct_ulong_field plcairo_alloc_struct_uint32_field
#endif



                /*******************************
                 *        Cairo Context        *
                 *******************************/

#define PLCAIRO_CHECK_CONTEXT(c) \
          { cairo_status_t status = cairo_status(c); \
            if ( status != CAIRO_STATUS_SUCCESS ) \
            { return plcairo_raise_error_status(status); \
            } \
          }

cairo_bool_t plcairo_term_to_context(term_t t,
                                     cairo_t **cr) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_context_to_term(cairo_t *cr,
                                     term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_antialias(term_t t,
                                       cairo_antialias_t *antialias) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_antialias_to_term(cairo_antialias_t antialias,
                                       term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_fill_rule(term_t t,
                                       cairo_fill_rule_t *fill_rule) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_fill_rule_to_term(cairo_fill_rule_t fill_rule,
                                       term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_line_cap(term_t t,
                                      cairo_line_cap_t *line_cap) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_line_cap_to_term(cairo_line_cap_t line_cap,
                                      term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_line_join(term_t t,
                                       cairo_line_join_t *line_join) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_line_join_to_term(cairo_line_join_t line_join,
                                       term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_operator(term_t t,
                                      cairo_operator_t *op) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_operator_to_term(cairo_operator_t op,
                                      term_t t) PLGI_WARN_UNUSED;

void plcairo_register_rectangle_t(void);

cairo_bool_t plcairo_term_to_rectangle(term_t t,
                                       cairo_rectangle_t **rectangle) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_rectangle_to_term(cairo_rectangle_t *rectangle,
                                       term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_rectangle_list(term_t t,
                                            cairo_rectangle_list_t **rectangle) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_rectangle_list_to_term(cairo_rectangle_list_t *rectangle_list,
                                            term_t t) PLGI_WARN_UNUSED;

PLGI_PRED_DEF(plcairo_clip);
PLGI_PRED_DEF(plcairo_clip_extents);
PLGI_PRED_DEF(plcairo_clip_preserve);
PLGI_PRED_DEF(plcairo_copy_clip_rectangle_list);
PLGI_PRED_DEF(plcairo_copy_page);
PLGI_PRED_DEF(plcairo_create);
PLGI_PRED_DEF(plcairo_fill);
PLGI_PRED_DEF(plcairo_fill_extents);
PLGI_PRED_DEF(plcairo_fill_preserve);
PLGI_PRED_DEF(plcairo_get_antialias);
PLGI_PRED_DEF(plcairo_get_dash);
PLGI_PRED_DEF(plcairo_get_dash_count);
PLGI_PRED_DEF(plcairo_get_fill_rule);
PLGI_PRED_DEF(plcairo_get_group_target);
PLGI_PRED_DEF(plcairo_get_line_cap);
PLGI_PRED_DEF(plcairo_get_line_join);
PLGI_PRED_DEF(plcairo_get_line_width);
PLGI_PRED_DEF(plcairo_get_miter_limit);
PLGI_PRED_DEF(plcairo_get_operator);
PLGI_PRED_DEF(plcairo_get_source);
PLGI_PRED_DEF(plcairo_get_target);
PLGI_PRED_DEF(plcairo_get_tolerance);
PLGI_PRED_DEF(plcairo_in_clip);
PLGI_PRED_DEF(plcairo_in_fill);
PLGI_PRED_DEF(plcairo_in_stroke);
PLGI_PRED_DEF(plcairo_mask);
PLGI_PRED_DEF(plcairo_mask_surface);
PLGI_PRED_DEF(plcairo_paint);
PLGI_PRED_DEF(plcairo_paint_with_alpha);
PLGI_PRED_DEF(plcairo_pop_group);
PLGI_PRED_DEF(plcairo_pop_group_to_source);
PLGI_PRED_DEF(plcairo_push_group);
PLGI_PRED_DEF(plcairo_push_group_with_content);
PLGI_PRED_DEF(plcairo_reset_clip);
PLGI_PRED_DEF(plcairo_restore);
PLGI_PRED_DEF(plcairo_save);
PLGI_PRED_DEF(plcairo_set_antialias);
PLGI_PRED_DEF(plcairo_set_dash);
PLGI_PRED_DEF(plcairo_set_fill_rule);
PLGI_PRED_DEF(plcairo_set_line_cap);
PLGI_PRED_DEF(plcairo_set_line_join);
PLGI_PRED_DEF(plcairo_set_line_width);
PLGI_PRED_DEF(plcairo_set_miter_limit);
PLGI_PRED_DEF(plcairo_set_operator);
PLGI_PRED_DEF(plcairo_set_source);
PLGI_PRED_DEF(plcairo_set_source_rgb);
PLGI_PRED_DEF(plcairo_set_source_rgba);
PLGI_PRED_DEF(plcairo_set_source_surface);
PLGI_PRED_DEF(plcairo_set_tolerance);
PLGI_PRED_DEF(plcairo_show_page);
PLGI_PRED_DEF(plcairo_stroke);
PLGI_PRED_DEF(plcairo_stroke_extents);
PLGI_PRED_DEF(plcairo_stroke_preserve);
PLGI_PRED_DEF(plcairo_set_source_surface);



                /*******************************
                 *         Cairo Paths         *
                 *******************************/

cairo_bool_t plcairo_term_to_path(term_t t,
                                  cairo_path_t **type) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_path_to_term(cairo_path_t *type,
                                  term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_path_data_type(term_t t,
                                            cairo_path_data_type_t *type) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_path_data_type_to_term(cairo_path_data_type_t type,
                                            term_t t) PLGI_WARN_UNUSED;

PLGI_PRED_DEF(plcairo_append_path);
PLGI_PRED_DEF(plcairo_arc);
PLGI_PRED_DEF(plcairo_arc_negative);
PLGI_PRED_DEF(plcairo_close_path);
PLGI_PRED_DEF(plcairo_copy_path);
PLGI_PRED_DEF(plcairo_copy_path_flat);
PLGI_PRED_DEF(plcairo_curve_to);
PLGI_PRED_DEF(plcairo_get_current_point);
PLGI_PRED_DEF(plcairo_glyph_path);
PLGI_PRED_DEF(plcairo_has_current_point);
PLGI_PRED_DEF(plcairo_line_to);
PLGI_PRED_DEF(plcairo_move_to);
PLGI_PRED_DEF(plcairo_new_path);
PLGI_PRED_DEF(plcairo_new_sub_path);
PLGI_PRED_DEF(plcairo_path_extents);
PLGI_PRED_DEF(plcairo_rectangle);
PLGI_PRED_DEF(plcairo_rel_curve_to);
PLGI_PRED_DEF(plcairo_rel_line_to);
PLGI_PRED_DEF(plcairo_rel_move_to);
PLGI_PRED_DEF(plcairo_text_path);



                /*******************************
                 *        Cairo Pattern        *
                 *******************************/

#define PLCAIRO_CHECK_PATTERN(c) \
          { cairo_status_t status = cairo_pattern_status(c); \
            if ( status != CAIRO_STATUS_SUCCESS ) \
            { return plcairo_raise_error_status(status); \
            } \
          }

cairo_bool_t plcairo_term_to_pattern(term_t t,
                                     cairo_pattern_t **pattern) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_pattern_to_term(cairo_pattern_t *pattern,
                                     term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_extend(term_t t,
                                    cairo_extend_t *extend) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_extend_to_term(cairo_extend_t extend,
                                    term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_filter(term_t t,
                                    cairo_filter_t *filter) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_filter_to_term(cairo_filter_t filter,
                                    term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_pattern_type(term_t t,
                                          cairo_pattern_type_t *type) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_pattern_type_to_term(cairo_pattern_type_t type,
                                          term_t t) PLGI_WARN_UNUSED;

PLGI_PRED_DEF(plcairo_pattern_add_color_stop_rgb);
PLGI_PRED_DEF(plcairo_pattern_add_color_stop_rgba);
PLGI_PRED_DEF(plcairo_pattern_create_for_surface);
PLGI_PRED_DEF(plcairo_pattern_create_linear);
PLGI_PRED_DEF(plcairo_pattern_create_mesh);
PLGI_PRED_DEF(plcairo_pattern_create_radial);
PLGI_PRED_DEF(plcairo_pattern_create_rgb);
PLGI_PRED_DEF(plcairo_pattern_create_rgba);
PLGI_PRED_DEF(plcairo_pattern_get_color_stop_count);
PLGI_PRED_DEF(plcairo_pattern_get_color_stop_rgba);
PLGI_PRED_DEF(plcairo_pattern_get_extend);
PLGI_PRED_DEF(plcairo_pattern_get_filter);
PLGI_PRED_DEF(plcairo_pattern_get_linear_points);
PLGI_PRED_DEF(plcairo_pattern_get_matrix);
PLGI_PRED_DEF(plcairo_pattern_get_radial_circles);
PLGI_PRED_DEF(plcairo_pattern_get_rgba);
PLGI_PRED_DEF(plcairo_pattern_get_surface);
PLGI_PRED_DEF(plcairo_pattern_get_type);
PLGI_PRED_DEF(plcairo_mesh_pattern_begin_patch);
PLGI_PRED_DEF(plcairo_mesh_pattern_curve_to);
PLGI_PRED_DEF(plcairo_mesh_pattern_end_patch);
PLGI_PRED_DEF(plcairo_mesh_pattern_get_control_point);
PLGI_PRED_DEF(plcairo_mesh_pattern_get_corner_color_rgba);
PLGI_PRED_DEF(plcairo_mesh_pattern_get_patch_count);
PLGI_PRED_DEF(plcairo_mesh_pattern_get_path);
PLGI_PRED_DEF(plcairo_mesh_pattern_line_to);
PLGI_PRED_DEF(plcairo_mesh_pattern_move_to);
PLGI_PRED_DEF(plcairo_mesh_pattern_set_control_point);
PLGI_PRED_DEF(plcairo_mesh_pattern_set_corner_color_rgb);
PLGI_PRED_DEF(plcairo_mesh_pattern_set_corner_color_rgba);
PLGI_PRED_DEF(plcairo_pattern_set_extend);
PLGI_PRED_DEF(plcairo_pattern_set_filter);
PLGI_PRED_DEF(plcairo_pattern_set_matrix);



                /*******************************
                 *        Cairo Region         *
                 *******************************/

#define PLCAIRO_CHECK_REGION(c) \
          { cairo_status_t status = cairo_region_status(c); \
            if ( status != CAIRO_STATUS_SUCCESS ) \
            { return plcairo_raise_error_status(status); \
            } \
          }

cairo_bool_t plcairo_term_to_region(term_t t,
                                    cairo_region_t **region) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_region_to_term(cairo_region_t *region,
                                    term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_region_overlap(term_t t,
                                            cairo_region_overlap_t *overlap) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_region_overlap_to_term(cairo_region_overlap_t overlap,
                                            term_t t) PLGI_WARN_UNUSED;

PLGI_PRED_DEF(plcairo_region_contains_point);
PLGI_PRED_DEF(plcairo_region_contains_rectangle);
PLGI_PRED_DEF(plcairo_region_create);
PLGI_PRED_DEF(plcairo_region_create_rectangle);
PLGI_PRED_DEF(plcairo_region_create_rectangles);
PLGI_PRED_DEF(plcairo_region_equal);
PLGI_PRED_DEF(plcairo_region_get_extents);
PLGI_PRED_DEF(plcairo_region_get_rectangle);
PLGI_PRED_DEF(plcairo_region_intersect);
PLGI_PRED_DEF(plcairo_region_intersect_rectangle);
PLGI_PRED_DEF(plcairo_region_is_empty);
PLGI_PRED_DEF(plcairo_region_num_rectangles);
PLGI_PRED_DEF(plcairo_region_subtract);
PLGI_PRED_DEF(plcairo_region_subtract_rectangle);
PLGI_PRED_DEF(plcairo_region_translate);
PLGI_PRED_DEF(plcairo_region_union);
PLGI_PRED_DEF(plcairo_region_union_rectangle);
PLGI_PRED_DEF(plcairo_region_xor);
PLGI_PRED_DEF(plcairo_region_xor_rectangle);



                /*******************************
                 *    Cairo Transformation     *
                 *******************************/

PLGI_PRED_DEF(plcairo_device_to_user);
PLGI_PRED_DEF(plcairo_device_to_user_distance);
PLGI_PRED_DEF(plcairo_get_matrix);
PLGI_PRED_DEF(plcairo_identity_matrix);
PLGI_PRED_DEF(plcairo_rotate);
PLGI_PRED_DEF(plcairo_scale);
PLGI_PRED_DEF(plcairo_set_matrix);
PLGI_PRED_DEF(plcairo_transform);
PLGI_PRED_DEF(plcairo_translate);
PLGI_PRED_DEF(plcairo_user_to_device);
PLGI_PRED_DEF(plcairo_user_to_device_distance);



                /*******************************
                 *         Cairo Text          *
                 *******************************/

cairo_bool_t plcairo_term_to_font_slant(term_t t,
                                        cairo_font_slant_t *slant) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_font_slant_to_term(cairo_font_slant_t slant,
                                        term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_font_weight(term_t t,
                                         cairo_font_weight_t *weight) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_font_weight_to_term(cairo_font_weight_t weight,
                                         term_t t) PLGI_WARN_UNUSED;

void plcairo_register_glyph_t(void);

cairo_bool_t plcairo_term_to_glyph(term_t t,
                                   cairo_glyph_t **glyph) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_glyph_to_term(cairo_glyph_t *glyph,
                                   term_t t) PLGI_WARN_UNUSED;

void plcairo_register_text_cluster_t(void);

cairo_bool_t plcairo_term_to_text_cluster(term_t t,
                                          cairo_text_cluster_t **text_cluster) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_text_cluster_to_term(cairo_text_cluster_t *text_cluster,
                                          term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_text_cluster_flags(term_t t,
                                                cairo_text_cluster_flags_t *flags) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_text_cluster_flags_to_term(cairo_text_cluster_flags_t flags,
                                                term_t t) PLGI_WARN_UNUSED;

PLGI_PRED_DEF(plcairo_font_extents);
PLGI_PRED_DEF(plcairo_get_font_face);
PLGI_PRED_DEF(plcairo_get_font_matrix);
PLGI_PRED_DEF(plcairo_get_font_options);
PLGI_PRED_DEF(plcairo_get_scaled_font);
PLGI_PRED_DEF(plcairo_glyph_extents);
PLGI_PRED_DEF(plcairo_select_font_face);
PLGI_PRED_DEF(plcairo_set_font_face);
PLGI_PRED_DEF(plcairo_set_font_matrix);
PLGI_PRED_DEF(plcairo_set_font_options);
PLGI_PRED_DEF(plcairo_set_font_size);
PLGI_PRED_DEF(plcairo_set_scaled_font);
PLGI_PRED_DEF(plcairo_show_glyphs);
PLGI_PRED_DEF(plcairo_show_text);
PLGI_PRED_DEF(plcairo_show_text_glyphs);
PLGI_PRED_DEF(plcairo_text_extents);
PLGI_PRED_DEF(plcairo_toy_font_face_create);
PLGI_PRED_DEF(plcairo_toy_font_face_get_family);
PLGI_PRED_DEF(plcairo_toy_font_face_get_slant);
PLGI_PRED_DEF(plcairo_toy_font_face_get_weight);



                /*******************************
                 *     Cairo Raster Source     *
                 *******************************/

PLGI_PRED_DEF(plcairo_pattern_create_raster_source);



                /*******************************
                 *       Cairo Font Face       *
                 *******************************/

#define PLCAIRO_CHECK_FONT_FACE(c) \
          { cairo_status_t status = cairo_font_face_status(c); \
            if ( status != CAIRO_STATUS_SUCCESS ) \
            { return plcairo_raise_error_status(status); \
            } \
          }

cairo_bool_t plcairo_term_to_font_face(term_t t,
                                       cairo_font_face_t **font_face) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_font_face_to_term(cairo_font_face_t *font_face,
                                       term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_font_type(term_t t,
                                       cairo_font_type_t *font_type) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_font_type_to_term(cairo_font_type_t font_type,
                                       term_t t) PLGI_WARN_UNUSED;

PLGI_PRED_DEF(plcairo_font_face_get_type);



                /*******************************
                 *      Cairo Scaled Font      *
                 *******************************/

#define PLCAIRO_CHECK_SCALED_FONT(c) \
          { cairo_status_t status = cairo_scaled_font_status(c); \
            if ( status != CAIRO_STATUS_SUCCESS ) \
            { return plcairo_raise_error_status(status); \
            } \
          }

cairo_bool_t plcairo_term_to_scaled_font(term_t t,
                                         cairo_scaled_font_t **scaled_font) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_scaled_font_to_term(cairo_scaled_font_t *scaled_font,
                                         term_t t) PLGI_WARN_UNUSED;

void plcairo_register_font_extents_t(void);

cairo_bool_t plcairo_term_to_font_extents(term_t t,
                                          cairo_font_extents_t **extents) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_font_extents_to_term(cairo_font_extents_t *extents,
                                          term_t t) PLGI_WARN_UNUSED;

void plcairo_register_text_extents_t(void);

cairo_bool_t plcairo_term_to_text_extents(term_t t,
                                          cairo_text_extents_t **extents) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_text_extents_to_term(cairo_text_extents_t *extents,
                                          term_t t) PLGI_WARN_UNUSED;

PLGI_PRED_DEF(plcairo_scaled_font_create);
PLGI_PRED_DEF(plcairo_scaled_font_extents);
PLGI_PRED_DEF(plcairo_scaled_font_get_ctm);
PLGI_PRED_DEF(plcairo_scaled_font_get_font_face);
PLGI_PRED_DEF(plcairo_scaled_font_get_font_matrix);
PLGI_PRED_DEF(plcairo_scaled_font_get_font_options);
PLGI_PRED_DEF(plcairo_scaled_font_get_scale_matrix);
PLGI_PRED_DEF(plcairo_scaled_font_get_type);
PLGI_PRED_DEF(plcairo_scaled_font_glyph_extents);
PLGI_PRED_DEF(plcairo_scaled_font_text_extents);
PLGI_PRED_DEF(plcairo_scaled_font_text_to_glyphs);



                /*******************************
                 *     Cairo Font Options      *
                 *******************************/

#define PLCAIRO_CHECK_FONT_OPTIONS(c) \
          { cairo_status_t status = cairo_font_options_status(c); \
            if ( status != CAIRO_STATUS_SUCCESS ) \
            { return plcairo_raise_error_status(status); \
            } \
          }

cairo_bool_t plcairo_term_to_font_options(term_t t,
                                          cairo_font_options_t **font_options) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_font_options_to_term(cairo_font_options_t *font_options,
                                          term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_hint_metrics(term_t t,
                                          cairo_hint_metrics_t *hint_metrics) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_hint_metrics_to_term(cairo_hint_metrics_t hint_metrics,
                                          term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_hint_style(term_t t,
                                        cairo_hint_style_t *hint_style) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_hint_style_to_term(cairo_hint_style_t hint_style,
                                        term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_subpixel_order(term_t t,
                                            cairo_subpixel_order_t *subpixel_order) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_subpixel_order_to_term(cairo_subpixel_order_t subpixel_order,
                                            term_t t) PLGI_WARN_UNUSED;

PLGI_PRED_DEF(plcairo_font_options_create);
PLGI_PRED_DEF(plcairo_font_options_equal);
PLGI_PRED_DEF(plcairo_font_options_get_antialias);
PLGI_PRED_DEF(plcairo_font_options_get_hint_metrics);
PLGI_PRED_DEF(plcairo_font_options_get_hint_style);
PLGI_PRED_DEF(plcairo_font_options_get_subpixel_order);
PLGI_PRED_DEF(plcairo_font_options_hash);
PLGI_PRED_DEF(plcairo_font_options_merge);
PLGI_PRED_DEF(plcairo_font_options_set_antialias);
PLGI_PRED_DEF(plcairo_font_options_set_hint_metrics);
PLGI_PRED_DEF(plcairo_font_options_set_hint_style);
PLGI_PRED_DEF(plcairo_font_options_set_subpixel_order);



                /*******************************
                 *        Cairo Device         *
                 *******************************/

#define PLCAIRO_CHECK_DEVICE(c) \
          { cairo_status_t status = cairo_device_status(c); \
            if ( status != CAIRO_STATUS_SUCCESS ) \
            { return plcairo_raise_error_status(status); \
            } \
          }

cairo_bool_t plcairo_term_to_device(term_t           t,
                                    cairo_device_t **device) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_device_to_term(cairo_device_t *device,
                                    term_t          t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_device_type(term_t               t,
                                         cairo_device_type_t *device_type) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_device_type_to_term(cairo_device_type_t device_type,
                                         term_t              t) PLGI_WARN_UNUSED;

PLGI_PRED_DEF(plcairo_device_acquire);
PLGI_PRED_DEF(plcairo_device_finish);
PLGI_PRED_DEF(plcairo_device_flush);
PLGI_PRED_DEF(plcairo_device_get_type);
PLGI_PRED_DEF(plcairo_device_observer_elapsed);
PLGI_PRED_DEF(plcairo_device_observer_fill_elapsed);
PLGI_PRED_DEF(plcairo_device_observer_glyphs_elapsed);
PLGI_PRED_DEF(plcairo_device_observer_mask_elapsed);
PLGI_PRED_DEF(plcairo_device_observer_paint_elapsed);
PLGI_PRED_DEF(plcairo_device_observer_print);
PLGI_PRED_DEF(plcairo_device_observer_stroke_elapsed);
PLGI_PRED_DEF(plcairo_device_release);



                /*******************************
                 *        Cairo Surface        *
                 *******************************/

#define PLCAIRO_CHECK_SURFACE(c) \
          { cairo_status_t status = cairo_surface_status(c); \
            if ( status != CAIRO_STATUS_SUCCESS ) \
            { return plcairo_raise_error_status(status); \
            } \
          }

cairo_bool_t plcairo_term_to_surface(term_t t,
                                     cairo_surface_t **surface) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_surface_to_term(cairo_surface_t *surface,
                                     term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_content(term_t t,
                                     cairo_content_t *content) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_content_to_term(cairo_content_t content,
                                     term_t t) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_term_to_surface_type(term_t                t,
                                          cairo_surface_type_t *surface_type) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_surface_type_to_term(cairo_surface_type_t surface_type,
                                          term_t               t) PLGI_WARN_UNUSED;

PLGI_PRED_DEF(plcairo_surface_copy_page);
PLGI_PRED_DEF(plcairo_surface_create_for_rectangle);
PLGI_PRED_DEF(plcairo_surface_create_similar);
PLGI_PRED_DEF(plcairo_surface_create_similar_image);
PLGI_PRED_DEF(plcairo_surface_finish);
PLGI_PRED_DEF(plcairo_surface_flush);
PLGI_PRED_DEF(plcairo_surface_get_content);
PLGI_PRED_DEF(plcairo_surface_get_device);
PLGI_PRED_DEF(plcairo_surface_get_device_offset);
PLGI_PRED_DEF(plcairo_surface_get_device_scale);
PLGI_PRED_DEF(plcairo_surface_get_fallback_resolution);
PLGI_PRED_DEF(plcairo_surface_get_font_options);
PLGI_PRED_DEF(plcairo_surface_get_type);
PLGI_PRED_DEF(plcairo_surface_has_show_text_glyphs);
PLGI_PRED_DEF(plcairo_surface_map_to_image);
PLGI_PRED_DEF(plcairo_surface_mark_dirty);
PLGI_PRED_DEF(plcairo_surface_mark_dirty_rectangle);
PLGI_PRED_DEF(plcairo_surface_set_device_offset);
PLGI_PRED_DEF(plcairo_surface_set_device_scale);
PLGI_PRED_DEF(plcairo_surface_set_fallback_resolution);
PLGI_PRED_DEF(plcairo_surface_show_page);
PLGI_PRED_DEF(plcairo_surface_supports_mime_type);
PLGI_PRED_DEF(plcairo_surface_unmap_image);



                /*******************************
                 *     Cairo Image Surface     *
                 *******************************/

cairo_bool_t plcairo_term_to_format(term_t          t,
                                    cairo_format_t *format) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_format_to_term(cairo_format_t format,
                                    term_t         t) PLGI_WARN_UNUSED;

PLGI_PRED_DEF(plcairo_image_surface_create);
PLGI_PRED_DEF(plcairo_image_surface_get_format);
PLGI_PRED_DEF(plcairo_image_surface_get_height);
PLGI_PRED_DEF(plcairo_image_surface_get_stride);
PLGI_PRED_DEF(plcairo_image_surface_get_width);



                /*******************************
                 *      Cairo PDF Surface      *
                 *******************************/

PLGI_PRED_DEF(plcairo_pdf_get_versions);
PLGI_PRED_DEF(plcairo_pdf_surface_create);
PLGI_PRED_DEF(plcairo_pdf_surface_create_for_stream);
PLGI_PRED_DEF(plcairo_pdf_surface_restrict_to_version);
PLGI_PRED_DEF(plcairo_pdf_surface_set_size);
PLGI_PRED_DEF(plcairo_pdf_version_to_string);



                /*******************************
                 *      Cairo PNG Surface      *
                 *******************************/

PLGI_PRED_DEF(plcairo_image_surface_create_from_png);
PLGI_PRED_DEF(plcairo_image_surface_create_from_png_stream);
PLGI_PRED_DEF(plcairo_surface_write_to_png);
PLGI_PRED_DEF(plcairo_surface_write_to_png_stream);



                /*******************************
                 *  Cairo PostScript Surface   *
                 *******************************/

PLGI_PRED_DEF(plcairo_ps_get_levels);
PLGI_PRED_DEF(plcairo_ps_level_to_string);
PLGI_PRED_DEF(plcairo_ps_surface_create);
PLGI_PRED_DEF(plcairo_ps_surface_create_for_stream);
PLGI_PRED_DEF(plcairo_ps_surface_dsc_begin_page_setup);
PLGI_PRED_DEF(plcairo_ps_surface_dsc_begin_setup);
PLGI_PRED_DEF(plcairo_ps_surface_dsc_comment);
PLGI_PRED_DEF(plcairo_ps_surface_get_eps);
PLGI_PRED_DEF(plcairo_ps_surface_restrict_to_level);
PLGI_PRED_DEF(plcairo_ps_surface_set_eps);
PLGI_PRED_DEF(plcairo_ps_surface_set_size);



                /*******************************
                 *   Cairo Recording Surface   *
                 *******************************/

PLGI_PRED_DEF(plcairo_recording_surface_create);
PLGI_PRED_DEF(plcairo_recording_surface_get_extents);
PLGI_PRED_DEF(plcairo_recording_surface_ink_extents);



                /*******************************
                 *      Cairo SVG Surface      *
                 *******************************/

PLGI_PRED_DEF(plcairo_svg_get_versions);
PLGI_PRED_DEF(plcairo_svg_surface_create);
PLGI_PRED_DEF(plcairo_svg_surface_create_for_stream);
PLGI_PRED_DEF(plcairo_svg_surface_restrict_to_version);
PLGI_PRED_DEF(plcairo_svg_version_to_string);



                /*******************************
                 *    Cairo Script Surface     *
                 *******************************/

PLGI_PRED_DEF(plcairo_script_create);
PLGI_PRED_DEF(plcairo_script_create_for_stream);
PLGI_PRED_DEF(plcairo_script_from_recording_surface);
PLGI_PRED_DEF(plcairo_script_get_mode);
PLGI_PRED_DEF(plcairo_script_set_mode);
PLGI_PRED_DEF(plcairo_script_surface_create);
PLGI_PRED_DEF(plcairo_script_surface_create_for_target);
PLGI_PRED_DEF(plcairo_script_write_comment);



                /*******************************
                 *        Cairo Matrix         *
                 *******************************/

void plcairo_register_matrix_t(void);

cairo_bool_t plcairo_term_to_matrix(term_t t,
                                    cairo_matrix_t **matrix) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_matrix_to_term(cairo_matrix_t *matrix,
                                    term_t t) PLGI_WARN_UNUSED;

PLGI_PRED_DEF(plcairo_matrix_init);
PLGI_PRED_DEF(plcairo_matrix_init_identity);
PLGI_PRED_DEF(plcairo_matrix_init_rotate);
PLGI_PRED_DEF(plcairo_matrix_init_scale);
PLGI_PRED_DEF(plcairo_matrix_init_translate);
PLGI_PRED_DEF(plcairo_matrix_invert);
PLGI_PRED_DEF(plcairo_matrix_multiply);
PLGI_PRED_DEF(plcairo_matrix_rotate);
PLGI_PRED_DEF(plcairo_matrix_scale);
PLGI_PRED_DEF(plcairo_matrix_transform_distance);
PLGI_PRED_DEF(plcairo_matrix_transform_point);
PLGI_PRED_DEF(plcairo_matrix_translate);


                /*******************************
                 *       Cairo Rectangle       *
                 *******************************/

void plcairo_register_rectangle_int_t(void);

cairo_bool_t plcairo_term_to_rectangle_int(term_t                  t,
                                           cairo_rectangle_int_t **rectangle) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_rectangle_int_to_term(cairo_rectangle_int_t *rectangle,
                                           term_t                 t) PLGI_WARN_UNUSED;



                 /*******************************
                 *          Callbacks           *
                 *******************************/

cairo_bool_t plcairo_term_to_closure(term_t   t_closure,
                                     void   **closure) PLGI_WARN_UNUSED;

cairo_status_t plcairo_write_func(void *closure,
                                  const unsigned char *data,
                                  unsigned int length);

cairo_status_t plcairo_read_func(void *closure,
                                 unsigned char *data,
                                 unsigned int length);



                 /*******************************
                 *            Errors            *
                 *******************************/

cairo_bool_t plcairo_raise_error(char *message);
cairo_bool_t plcairo_raise_error__va(char *fmt, ...);
cairo_bool_t plcairo_raise_error_status(int status);
