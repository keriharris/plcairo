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

#define PL_ARITY_AS_SIZE 1
#include <SWI-Stream.h>
#include <SWI-Prolog.h>
#include <cairo.h>
#include <cairo-gobject.h>
#include <plgi.h>



                /*******************************
                 *           Version           *
                 *******************************/

#define PLCAIRO_VERSION_MAJOR 0
#define PLCAIRO_VERSION_MINOR 9
#define PLCAIRO_VERSION_MICRO 0

#define PLCAIRO_VERSION_ENCODE(major, minor, micro) \
          ( (major * 10000) + (minor * 100) + (micro * 1) )

#define PLCAIRO_VERSION PLCAIRO_VERSION_ENCODE(PLCAIRO_VERSION_MAJOR, \
                                               PLCAIRO_VERSION_MINOR, \
                                               PLCAIRO_VERSION_MICRO)



                /*******************************
                 *            Debug            *
                 *******************************/

cairo_bool_t plcairo_debug_active(void);
int plcairo_exit_debug(int status, void *arg);

#define PLCAIRO_debug_helper(fmt, ...) \
        { fprintf(stderr, "[PLcairo] " fmt "%s\n", __VA_ARGS__); \
        }

#define PLCAIRO_debug(...) \
        do { if (plcairo_debug_active()) \
             { PLCAIRO_debug_helper(__VA_ARGS__, ""); \
             } \
           } while (0)

#define plcairo_debug_dashes "------------------------"
#define plcairo_debug_n_dashes \
        ( (int)( strlen(plcairo_debug_dashes) - strlen(__func__) / 2 ) )

#define PLCAIRO_debug_header \
        PLCAIRO_debug("%.*s <begin>  %s  <begin> %.*s", \
                      plcairo_debug_n_dashes, plcairo_debug_dashes, \
                      __func__, \
                      plcairo_debug_n_dashes, plcairo_debug_dashes)

#define PLCAIRO_debug_trailer \
        PLCAIRO_debug("%.*s <end>  %s  <end> %.*s", \
                      plcairo_debug_n_dashes+2, plcairo_debug_dashes, \
                      __func__, \
                      plcairo_debug_n_dashes+2, plcairo_debug_dashes)

#define PLGI_WARN_UNUSED G_GNUC_WARN_UNUSED_RESULT



                /*******************************
                 *  Foreign Predicate Wrapper  *
                 *******************************/

#define PLCAIRO_PRED_DEF(fname) \
	foreign_t fname(term_t t0, int arity, void *context)

#define PLCAIRO_PRED_IMPL(fname) \
 \
cairo_bool_t fname ## __impl(term_t t0, control_t fctxt); \
 \
foreign_t fname(term_t t0, int arity, void *fctxt) \
{ \
  int ret; \
  PLCAIRO_debug_header; \
  ret = fname ## __impl(t0, (control_t)fctxt); \
  PLCAIRO_debug("%s retval: %d", __func__, ret); \
  PLCAIRO_debug_trailer; \
  return ret; \
} \
 \
cairo_bool_t fname ## __impl(term_t t0, control_t fctxt)

#define PLCAIRO_PRED_REG(name, arity, fname) \
	PL_register_foreign(name, arity, fname, PL_FA_VARARGS)

#define FA0 t0
#define FA1 t0+1
#define FA2 t0+2
#define FA3 t0+3
#define FA4 t0+4
#define FA5 t0+5
#define FA6 t0+6
#define FA7 t0+7
#define FA8 t0+8
#define FA9 t0+9

PLCAIRO_PRED_DEF(plcairo_version);
PLCAIRO_PRED_DEF(plcairo_debug);



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

PLCAIRO_PRED_DEF(plcairo_clip);
PLCAIRO_PRED_DEF(plcairo_clip_extents);
PLCAIRO_PRED_DEF(plcairo_clip_preserve);
PLCAIRO_PRED_DEF(plcairo_copy_clip_rectangle_list);
PLCAIRO_PRED_DEF(plcairo_copy_page);
PLCAIRO_PRED_DEF(plcairo_create);
PLCAIRO_PRED_DEF(plcairo_fill);
PLCAIRO_PRED_DEF(plcairo_fill_extents);
PLCAIRO_PRED_DEF(plcairo_fill_preserve);
PLCAIRO_PRED_DEF(plcairo_get_antialias);
PLCAIRO_PRED_DEF(plcairo_get_dash);
PLCAIRO_PRED_DEF(plcairo_get_dash_count);
PLCAIRO_PRED_DEF(plcairo_get_fill_rule);
PLCAIRO_PRED_DEF(plcairo_get_group_target);
PLCAIRO_PRED_DEF(plcairo_get_line_cap);
PLCAIRO_PRED_DEF(plcairo_get_line_join);
PLCAIRO_PRED_DEF(plcairo_get_line_width);
PLCAIRO_PRED_DEF(plcairo_get_miter_limit);
PLCAIRO_PRED_DEF(plcairo_get_operator);
PLCAIRO_PRED_DEF(plcairo_get_source);
PLCAIRO_PRED_DEF(plcairo_get_target);
PLCAIRO_PRED_DEF(plcairo_get_tolerance);
PLCAIRO_PRED_DEF(plcairo_in_clip);
PLCAIRO_PRED_DEF(plcairo_in_fill);
PLCAIRO_PRED_DEF(plcairo_in_stroke);
PLCAIRO_PRED_DEF(plcairo_mask);
PLCAIRO_PRED_DEF(plcairo_mask_surface);
PLCAIRO_PRED_DEF(plcairo_paint);
PLCAIRO_PRED_DEF(plcairo_paint_with_alpha);
PLCAIRO_PRED_DEF(plcairo_pop_group);
PLCAIRO_PRED_DEF(plcairo_pop_group_to_source);
PLCAIRO_PRED_DEF(plcairo_push_group);
PLCAIRO_PRED_DEF(plcairo_push_group_with_content);
PLCAIRO_PRED_DEF(plcairo_reset_clip);
PLCAIRO_PRED_DEF(plcairo_restore);
PLCAIRO_PRED_DEF(plcairo_save);
PLCAIRO_PRED_DEF(plcairo_set_antialias);
PLCAIRO_PRED_DEF(plcairo_set_dash);
PLCAIRO_PRED_DEF(plcairo_set_fill_rule);
PLCAIRO_PRED_DEF(plcairo_set_line_cap);
PLCAIRO_PRED_DEF(plcairo_set_line_join);
PLCAIRO_PRED_DEF(plcairo_set_line_width);
PLCAIRO_PRED_DEF(plcairo_set_miter_limit);
PLCAIRO_PRED_DEF(plcairo_set_operator);
PLCAIRO_PRED_DEF(plcairo_set_source);
PLCAIRO_PRED_DEF(plcairo_set_source_rgb);
PLCAIRO_PRED_DEF(plcairo_set_source_rgba);
PLCAIRO_PRED_DEF(plcairo_set_source_surface);
PLCAIRO_PRED_DEF(plcairo_set_tolerance);
PLCAIRO_PRED_DEF(plcairo_show_page);
PLCAIRO_PRED_DEF(plcairo_stroke);
PLCAIRO_PRED_DEF(plcairo_stroke_extents);
PLCAIRO_PRED_DEF(plcairo_stroke_preserve);
PLCAIRO_PRED_DEF(plcairo_set_source_surface);



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

PLCAIRO_PRED_DEF(plcairo_append_path);
PLCAIRO_PRED_DEF(plcairo_arc);
PLCAIRO_PRED_DEF(plcairo_arc_negative);
PLCAIRO_PRED_DEF(plcairo_close_path);
PLCAIRO_PRED_DEF(plcairo_copy_path);
PLCAIRO_PRED_DEF(plcairo_copy_path_flat);
PLCAIRO_PRED_DEF(plcairo_curve_to);
PLCAIRO_PRED_DEF(plcairo_get_current_point);
PLCAIRO_PRED_DEF(plcairo_glyph_path);
PLCAIRO_PRED_DEF(plcairo_has_current_point);
PLCAIRO_PRED_DEF(plcairo_line_to);
PLCAIRO_PRED_DEF(plcairo_move_to);
PLCAIRO_PRED_DEF(plcairo_new_path);
PLCAIRO_PRED_DEF(plcairo_new_sub_path);
PLCAIRO_PRED_DEF(plcairo_path_extents);
PLCAIRO_PRED_DEF(plcairo_rectangle);
PLCAIRO_PRED_DEF(plcairo_rel_curve_to);
PLCAIRO_PRED_DEF(plcairo_rel_line_to);
PLCAIRO_PRED_DEF(plcairo_rel_move_to);
PLCAIRO_PRED_DEF(plcairo_text_path);



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

PLCAIRO_PRED_DEF(plcairo_pattern_add_color_stop_rgb);
PLCAIRO_PRED_DEF(plcairo_pattern_add_color_stop_rgba);
PLCAIRO_PRED_DEF(plcairo_pattern_create_for_surface);
PLCAIRO_PRED_DEF(plcairo_pattern_create_linear);
PLCAIRO_PRED_DEF(plcairo_pattern_create_mesh);
PLCAIRO_PRED_DEF(plcairo_pattern_create_radial);
PLCAIRO_PRED_DEF(plcairo_pattern_create_rgb);
PLCAIRO_PRED_DEF(plcairo_pattern_create_rgba);
PLCAIRO_PRED_DEF(plcairo_pattern_get_color_stop_count);
PLCAIRO_PRED_DEF(plcairo_pattern_get_color_stop_rgba);
PLCAIRO_PRED_DEF(plcairo_pattern_get_extend);
PLCAIRO_PRED_DEF(plcairo_pattern_get_filter);
PLCAIRO_PRED_DEF(plcairo_pattern_get_linear_points);
PLCAIRO_PRED_DEF(plcairo_pattern_get_matrix);
PLCAIRO_PRED_DEF(plcairo_pattern_get_radial_circles);
PLCAIRO_PRED_DEF(plcairo_pattern_get_rgba);
PLCAIRO_PRED_DEF(plcairo_pattern_get_surface);
PLCAIRO_PRED_DEF(plcairo_pattern_get_type);
PLCAIRO_PRED_DEF(plcairo_mesh_pattern_begin_patch);
PLCAIRO_PRED_DEF(plcairo_mesh_pattern_curve_to);
PLCAIRO_PRED_DEF(plcairo_mesh_pattern_end_patch);
PLCAIRO_PRED_DEF(plcairo_mesh_pattern_get_control_point);
PLCAIRO_PRED_DEF(plcairo_mesh_pattern_get_corner_color_rgba);
PLCAIRO_PRED_DEF(plcairo_mesh_pattern_get_patch_count);
PLCAIRO_PRED_DEF(plcairo_mesh_pattern_get_path);
PLCAIRO_PRED_DEF(plcairo_mesh_pattern_line_to);
PLCAIRO_PRED_DEF(plcairo_mesh_pattern_move_to);
PLCAIRO_PRED_DEF(plcairo_mesh_pattern_set_control_point);
PLCAIRO_PRED_DEF(plcairo_mesh_pattern_set_corner_color_rgb);
PLCAIRO_PRED_DEF(plcairo_mesh_pattern_set_corner_color_rgba);
PLCAIRO_PRED_DEF(plcairo_pattern_set_extend);
PLCAIRO_PRED_DEF(plcairo_pattern_set_filter);
PLCAIRO_PRED_DEF(plcairo_pattern_set_matrix);



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

PLCAIRO_PRED_DEF(plcairo_region_contains_point);
PLCAIRO_PRED_DEF(plcairo_region_contains_rectangle);
PLCAIRO_PRED_DEF(plcairo_region_create);
PLCAIRO_PRED_DEF(plcairo_region_create_rectangle);
PLCAIRO_PRED_DEF(plcairo_region_create_rectangles);
PLCAIRO_PRED_DEF(plcairo_region_equal);
PLCAIRO_PRED_DEF(plcairo_region_get_extents);
PLCAIRO_PRED_DEF(plcairo_region_get_rectangle);
PLCAIRO_PRED_DEF(plcairo_region_intersect);
PLCAIRO_PRED_DEF(plcairo_region_intersect_rectangle);
PLCAIRO_PRED_DEF(plcairo_region_is_empty);
PLCAIRO_PRED_DEF(plcairo_region_num_rectangles);
PLCAIRO_PRED_DEF(plcairo_region_subtract);
PLCAIRO_PRED_DEF(plcairo_region_subtract_rectangle);
PLCAIRO_PRED_DEF(plcairo_region_translate);
PLCAIRO_PRED_DEF(plcairo_region_union);
PLCAIRO_PRED_DEF(plcairo_region_union_rectangle);
PLCAIRO_PRED_DEF(plcairo_region_xor);
PLCAIRO_PRED_DEF(plcairo_region_xor_rectangle);



                /*******************************
                 *    Cairo Transformation     *
                 *******************************/

PLCAIRO_PRED_DEF(plcairo_device_to_user);
PLCAIRO_PRED_DEF(plcairo_device_to_user_distance);
PLCAIRO_PRED_DEF(plcairo_get_matrix);
PLCAIRO_PRED_DEF(plcairo_identity_matrix);
PLCAIRO_PRED_DEF(plcairo_rotate);
PLCAIRO_PRED_DEF(plcairo_scale);
PLCAIRO_PRED_DEF(plcairo_set_matrix);
PLCAIRO_PRED_DEF(plcairo_transform);
PLCAIRO_PRED_DEF(plcairo_translate);
PLCAIRO_PRED_DEF(plcairo_user_to_device);
PLCAIRO_PRED_DEF(plcairo_user_to_device_distance);



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

PLCAIRO_PRED_DEF(plcairo_font_extents);
PLCAIRO_PRED_DEF(plcairo_get_font_face);
PLCAIRO_PRED_DEF(plcairo_get_font_matrix);
PLCAIRO_PRED_DEF(plcairo_get_font_options);
PLCAIRO_PRED_DEF(plcairo_get_scaled_font);
PLCAIRO_PRED_DEF(plcairo_glyph_extents);
PLCAIRO_PRED_DEF(plcairo_select_font_face);
PLCAIRO_PRED_DEF(plcairo_set_font_face);
PLCAIRO_PRED_DEF(plcairo_set_font_matrix);
PLCAIRO_PRED_DEF(plcairo_set_font_options);
PLCAIRO_PRED_DEF(plcairo_set_font_size);
PLCAIRO_PRED_DEF(plcairo_set_scaled_font);
PLCAIRO_PRED_DEF(plcairo_show_glyphs);
PLCAIRO_PRED_DEF(plcairo_show_text);
PLCAIRO_PRED_DEF(plcairo_show_text_glyphs);
PLCAIRO_PRED_DEF(plcairo_text_extents);
PLCAIRO_PRED_DEF(plcairo_toy_font_face_create);
PLCAIRO_PRED_DEF(plcairo_toy_font_face_get_family);
PLCAIRO_PRED_DEF(plcairo_toy_font_face_get_slant);
PLCAIRO_PRED_DEF(plcairo_toy_font_face_get_weight);



                /*******************************
                 *     Cairo Raster Source     *
                 *******************************/

PLCAIRO_PRED_DEF(plcairo_pattern_create_raster_source);



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

PLCAIRO_PRED_DEF(plcairo_font_face_get_type);



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

PLCAIRO_PRED_DEF(plcairo_scaled_font_create);
PLCAIRO_PRED_DEF(plcairo_scaled_font_extents);
PLCAIRO_PRED_DEF(plcairo_scaled_font_get_ctm);
PLCAIRO_PRED_DEF(plcairo_scaled_font_get_font_face);
PLCAIRO_PRED_DEF(plcairo_scaled_font_get_font_matrix);
PLCAIRO_PRED_DEF(plcairo_scaled_font_get_font_options);
PLCAIRO_PRED_DEF(plcairo_scaled_font_get_scale_matrix);
PLCAIRO_PRED_DEF(plcairo_scaled_font_get_type);
PLCAIRO_PRED_DEF(plcairo_scaled_font_glyph_extents);
PLCAIRO_PRED_DEF(plcairo_scaled_font_text_extents);
PLCAIRO_PRED_DEF(plcairo_scaled_font_text_to_glyphs);



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

PLCAIRO_PRED_DEF(plcairo_font_options_create);
PLCAIRO_PRED_DEF(plcairo_font_options_equal);
PLCAIRO_PRED_DEF(plcairo_font_options_get_antialias);
PLCAIRO_PRED_DEF(plcairo_font_options_get_hint_metrics);
PLCAIRO_PRED_DEF(plcairo_font_options_get_hint_style);
PLCAIRO_PRED_DEF(plcairo_font_options_get_subpixel_order);
PLCAIRO_PRED_DEF(plcairo_font_options_hash);
PLCAIRO_PRED_DEF(plcairo_font_options_merge);
PLCAIRO_PRED_DEF(plcairo_font_options_set_antialias);
PLCAIRO_PRED_DEF(plcairo_font_options_set_hint_metrics);
PLCAIRO_PRED_DEF(plcairo_font_options_set_hint_style);
PLCAIRO_PRED_DEF(plcairo_font_options_set_subpixel_order);



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

PLCAIRO_PRED_DEF(plcairo_device_acquire);
PLCAIRO_PRED_DEF(plcairo_device_finish);
PLCAIRO_PRED_DEF(plcairo_device_flush);
PLCAIRO_PRED_DEF(plcairo_device_get_type);
PLCAIRO_PRED_DEF(plcairo_device_observer_elapsed);
PLCAIRO_PRED_DEF(plcairo_device_observer_fill_elapsed);
PLCAIRO_PRED_DEF(plcairo_device_observer_glyphs_elapsed);
PLCAIRO_PRED_DEF(plcairo_device_observer_mask_elapsed);
PLCAIRO_PRED_DEF(plcairo_device_observer_paint_elapsed);
PLCAIRO_PRED_DEF(plcairo_device_observer_print);
PLCAIRO_PRED_DEF(plcairo_device_observer_stroke_elapsed);
PLCAIRO_PRED_DEF(plcairo_device_release);



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

PLCAIRO_PRED_DEF(plcairo_surface_copy_page);
PLCAIRO_PRED_DEF(plcairo_surface_create_for_rectangle);
PLCAIRO_PRED_DEF(plcairo_surface_create_similar);
PLCAIRO_PRED_DEF(plcairo_surface_create_similar_image);
PLCAIRO_PRED_DEF(plcairo_surface_finish);
PLCAIRO_PRED_DEF(plcairo_surface_flush);
PLCAIRO_PRED_DEF(plcairo_surface_get_content);
PLCAIRO_PRED_DEF(plcairo_surface_get_device);
PLCAIRO_PRED_DEF(plcairo_surface_get_device_offset);
PLCAIRO_PRED_DEF(plcairo_surface_get_device_scale);
PLCAIRO_PRED_DEF(plcairo_surface_get_fallback_resolution);
PLCAIRO_PRED_DEF(plcairo_surface_get_font_options);
PLCAIRO_PRED_DEF(plcairo_surface_get_type);
PLCAIRO_PRED_DEF(plcairo_surface_has_show_text_glyphs);
PLCAIRO_PRED_DEF(plcairo_surface_map_to_image);
PLCAIRO_PRED_DEF(plcairo_surface_mark_dirty);
PLCAIRO_PRED_DEF(plcairo_surface_mark_dirty_rectangle);
PLCAIRO_PRED_DEF(plcairo_surface_set_device_offset);
PLCAIRO_PRED_DEF(plcairo_surface_set_device_scale);
PLCAIRO_PRED_DEF(plcairo_surface_set_fallback_resolution);
PLCAIRO_PRED_DEF(plcairo_surface_show_page);
PLCAIRO_PRED_DEF(plcairo_surface_supports_mime_type);
PLCAIRO_PRED_DEF(plcairo_surface_unmap_image);



                /*******************************
                 *     Cairo Image Surface     *
                 *******************************/

cairo_bool_t plcairo_term_to_format(term_t          t,
                                    cairo_format_t *format) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_format_to_term(cairo_format_t format,
                                    term_t         t) PLGI_WARN_UNUSED;

PLCAIRO_PRED_DEF(plcairo_image_surface_create);
PLCAIRO_PRED_DEF(plcairo_image_surface_get_format);
PLCAIRO_PRED_DEF(plcairo_image_surface_get_height);
PLCAIRO_PRED_DEF(plcairo_image_surface_get_stride);
PLCAIRO_PRED_DEF(plcairo_image_surface_get_width);



                /*******************************
                 *      Cairo PDF Surface      *
                 *******************************/

PLCAIRO_PRED_DEF(plcairo_pdf_get_versions);
PLCAIRO_PRED_DEF(plcairo_pdf_surface_create);
PLCAIRO_PRED_DEF(plcairo_pdf_surface_create_for_stream);
PLCAIRO_PRED_DEF(plcairo_pdf_surface_restrict_to_version);
PLCAIRO_PRED_DEF(plcairo_pdf_surface_set_size);
PLCAIRO_PRED_DEF(plcairo_pdf_version_to_string);



                /*******************************
                 *      Cairo PNG Surface      *
                 *******************************/

PLCAIRO_PRED_DEF(plcairo_image_surface_create_from_png);
PLCAIRO_PRED_DEF(plcairo_image_surface_create_from_png_stream);
PLCAIRO_PRED_DEF(plcairo_surface_write_to_png);
PLCAIRO_PRED_DEF(plcairo_surface_write_to_png_stream);



                /*******************************
                 *  Cairo PostScript Surface   *
                 *******************************/

PLCAIRO_PRED_DEF(plcairo_ps_get_levels);
PLCAIRO_PRED_DEF(plcairo_ps_level_to_string);
PLCAIRO_PRED_DEF(plcairo_ps_surface_create);
PLCAIRO_PRED_DEF(plcairo_ps_surface_create_for_stream);
PLCAIRO_PRED_DEF(plcairo_ps_surface_dsc_begin_page_setup);
PLCAIRO_PRED_DEF(plcairo_ps_surface_dsc_begin_setup);
PLCAIRO_PRED_DEF(plcairo_ps_surface_dsc_comment);
PLCAIRO_PRED_DEF(plcairo_ps_surface_get_eps);
PLCAIRO_PRED_DEF(plcairo_ps_surface_restrict_to_level);
PLCAIRO_PRED_DEF(plcairo_ps_surface_set_eps);
PLCAIRO_PRED_DEF(plcairo_ps_surface_set_size);



                /*******************************
                 *   Cairo Recording Surface   *
                 *******************************/

PLCAIRO_PRED_DEF(plcairo_recording_surface_create);
PLCAIRO_PRED_DEF(plcairo_recording_surface_get_extents);
PLCAIRO_PRED_DEF(plcairo_recording_surface_ink_extents);



                /*******************************
                 *      Cairo SVG Surface      *
                 *******************************/

PLCAIRO_PRED_DEF(plcairo_svg_get_versions);
PLCAIRO_PRED_DEF(plcairo_svg_surface_create);
PLCAIRO_PRED_DEF(plcairo_svg_surface_create_for_stream);
PLCAIRO_PRED_DEF(plcairo_svg_surface_restrict_to_version);
PLCAIRO_PRED_DEF(plcairo_svg_version_to_string);



                /*******************************
                 *    Cairo Script Surface     *
                 *******************************/

PLCAIRO_PRED_DEF(plcairo_script_create);
PLCAIRO_PRED_DEF(plcairo_script_create_for_stream);
PLCAIRO_PRED_DEF(plcairo_script_from_recording_surface);
PLCAIRO_PRED_DEF(plcairo_script_get_mode);
PLCAIRO_PRED_DEF(plcairo_script_set_mode);
PLCAIRO_PRED_DEF(plcairo_script_surface_create);
PLCAIRO_PRED_DEF(plcairo_script_surface_create_for_target);
PLCAIRO_PRED_DEF(plcairo_script_write_comment);



                /*******************************
                 *        Cairo Matrix         *
                 *******************************/

void plcairo_register_matrix_t(void);

cairo_bool_t plcairo_term_to_matrix(term_t t,
                                    cairo_matrix_t **matrix) PLGI_WARN_UNUSED;

cairo_bool_t plcairo_matrix_to_term(cairo_matrix_t *matrix,
                                    term_t t) PLGI_WARN_UNUSED;

PLCAIRO_PRED_DEF(plcairo_matrix_init);
PLCAIRO_PRED_DEF(plcairo_matrix_init_identity);
PLCAIRO_PRED_DEF(plcairo_matrix_init_rotate);
PLCAIRO_PRED_DEF(plcairo_matrix_init_scale);
PLCAIRO_PRED_DEF(plcairo_matrix_init_translate);
PLCAIRO_PRED_DEF(plcairo_matrix_invert);
PLCAIRO_PRED_DEF(plcairo_matrix_multiply);
PLCAIRO_PRED_DEF(plcairo_matrix_rotate);
PLCAIRO_PRED_DEF(plcairo_matrix_scale);
PLCAIRO_PRED_DEF(plcairo_matrix_transform_distance);
PLCAIRO_PRED_DEF(plcairo_matrix_transform_point);
PLCAIRO_PRED_DEF(plcairo_matrix_translate);


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
