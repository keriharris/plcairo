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

:- module(plcairo, [
                     /* Cairo Context */
                     cairo_clip/1,
                     cairo_clip_extents/5,
                     cairo_clip_preserve/1,
                     cairo_copy_clip_rectangle_list/2,
                     cairo_copy_page/1,
                     cairo_create/2,
                     cairo_fill/1,
                     cairo_fill_extents/5,
                     cairo_fill_preserve/1,
                     cairo_get_antialias/2,
                     cairo_get_dash/3,
                     cairo_get_dash_count/2,
                     cairo_get_fill_rule/2,
                     cairo_get_group_target/2,
                     cairo_get_line_cap/2,
                     cairo_get_line_join/2,
                     cairo_get_line_width/2,
                     cairo_get_miter_limit/2,
                     cairo_get_operator/2,
                     cairo_get_source/2,
                     cairo_get_target/2,
                     cairo_get_tolerance/2,
                     cairo_in_clip/3,
                     cairo_in_fill/3,
                     cairo_in_stroke/3,
                     cairo_mask/2,
                     cairo_mask_surface/4,
                     cairo_paint/1,
                     cairo_paint_with_alpha/2,
                     cairo_pop_group/2,
                     cairo_pop_group_to_source/1,
                     cairo_push_group/1,
                     cairo_push_group_with_content/2,
                     cairo_reset_clip/1,
                     cairo_restore/1,
                     cairo_save/1,
                     cairo_set_antialias/2,
                     cairo_set_dash/3,
                     cairo_set_fill_rule/2,
                     cairo_set_line_cap/2,
                     cairo_set_line_join/2,
                     cairo_set_line_width/2,
                     cairo_set_miter_limit/2,
                     cairo_set_operator/2,
                     cairo_set_source/2,
                     cairo_set_source_rgb/4,
                     cairo_set_source_rgba/5,
                     cairo_set_source_surface/4,
                     cairo_set_tolerance/2,
                     cairo_show_page/1,
                     cairo_stroke/1,
                     cairo_stroke_extents/5,
                     cairo_stroke_preserve/1,

                     /* Cairo Paths */
                     cairo_append_path/2,
                     cairo_arc/6,
                     cairo_arc_negative/6,
                     cairo_close_path/1,
                     cairo_copy_path/2,
                     cairo_copy_path_flat/2,
                     cairo_curve_to/7,
                     cairo_get_current_point/3,
                     cairo_glyph_path/2,
                     cairo_has_current_point/2,
                     cairo_line_to/3,
                     cairo_move_to/3,
                     cairo_new_path/1,
                     cairo_new_sub_path/1,
                     cairo_path_extents/5,
                     cairo_rectangle/5,
                     cairo_rel_curve_to/7,
                     cairo_rel_line_to/3,
                     cairo_rel_move_to/3,
                     cairo_text_path/2,

                     /* Cairo Pattern */
                     cairo_pattern_add_color_stop_rgb/5,
                     cairo_pattern_add_color_stop_rgba/6,
                     cairo_pattern_create_for_surface/2,
                     cairo_pattern_create_linear/5,
                     cairo_pattern_create_mesh/1,
                     cairo_pattern_create_radial/7,
                     cairo_pattern_create_rgb/4,
                     cairo_pattern_create_rgba/5,
                     cairo_pattern_get_color_stop_count/2,
                     cairo_pattern_get_color_stop_rgba/7,
                     cairo_pattern_get_extend/2,
                     cairo_pattern_get_filter/2,
                     cairo_pattern_get_linear_points/5,
                     cairo_pattern_get_matrix/2,
                     cairo_pattern_get_radial_circles/7,
                     cairo_pattern_get_rgba/5,
                     cairo_pattern_get_surface/2,
                     cairo_pattern_get_type/2,
                     cairo_mesh_pattern_begin_patch/1,
                     cairo_mesh_pattern_curve_to/7,
                     cairo_mesh_pattern_end_patch/1,
                     cairo_mesh_pattern_get_control_point/5,
                     cairo_mesh_pattern_get_corner_color_rgba/7,
                     cairo_mesh_pattern_get_patch_count/2,
                     cairo_mesh_pattern_get_path/3,
                     cairo_mesh_pattern_line_to/3,
                     cairo_mesh_pattern_move_to/3,
                     cairo_mesh_pattern_set_control_point/4,
                     cairo_mesh_pattern_set_corner_color_rgb/5,
                     cairo_mesh_pattern_set_corner_color_rgba/6,
                     cairo_pattern_set_extend/2,
                     cairo_pattern_set_filter/2,
                     cairo_pattern_set_matrix/2,

                     /* Cairo Region */
                     cairo_region_contains_point/3,
                     cairo_region_contains_rectangle/3,
                     cairo_region_create/1,
                     cairo_region_create_rectangle/2,
                     cairo_region_create_rectangles/2,
                     cairo_region_equal/2,
                     cairo_region_get_extents/2,
                     cairo_region_get_rectangle/3,
                     cairo_region_intersect/2,
                     cairo_region_intersect_rectangle/2,
                     cairo_region_is_empty/1,
                     cairo_region_num_rectangles/2,
                     cairo_region_subtract/2,
                     cairo_region_subtract_rectangle/2,
                     cairo_region_translate/3,
                     cairo_region_union/2,
                     cairo_region_union_rectangle/2,
                     cairo_region_xor/2,
                     cairo_region_xor_rectangle/2,

                     /* Cairo Transformation */
                     cairo_device_to_user/5,
                     cairo_device_to_user_distance/5,
                     cairo_get_matrix/2,
                     cairo_identity_matrix/1,
                     cairo_rotate/2,
                     cairo_scale/3,
                     cairo_set_matrix/2,
                     cairo_transform/2,
                     cairo_translate/3,
                     cairo_user_to_device/5,
                     cairo_user_to_device_distance/5,

                     /* Cairo Text */
                     cairo_font_extents/2,
                     cairo_get_font_face/2,
                     cairo_get_font_matrix/2,
                     cairo_get_font_options/2,
                     cairo_get_scaled_font/2,
                     cairo_glyph_extents/3,
                     cairo_select_font_face/4,
                     cairo_set_font_face/2,
                     cairo_set_font_matrix/2,
                     cairo_set_font_options/2,
                     cairo_set_font_size/2,
                     cairo_set_scaled_font/2,
                     cairo_show_glyphs/2,
                     cairo_show_text/2,
                     cairo_show_text_glyphs/5,
                     cairo_text_extents/3,
                     cairo_toy_font_face_create/4,
                     cairo_toy_font_face_get_family/2,
                     cairo_toy_font_face_get_slant/2,
                     cairo_toy_font_face_get_weight/2,

                     /* Cairo Raster Source */
                     cairo_pattern_create_raster_source/4,

                     /* Cairo Tag */
                     cairo_tag_begin/3,
                     cairo_tag_end/2,

                     /* Cairo Font Face */
                     cairo_font_face_get_type/2,

                     /* Cairo Scaled Font */
                     cairo_scaled_font_create/5,
                     cairo_scaled_font_extents/2,
                     cairo_scaled_font_get_ctm/2,
                     cairo_scaled_font_get_font_face/2,
                     cairo_scaled_font_get_font_matrix/2,
                     cairo_scaled_font_get_font_options/2,
                     cairo_scaled_font_get_scale_matrix/2,
                     cairo_scaled_font_get_type/2,
                     cairo_scaled_font_glyph_extents/3,
                     cairo_scaled_font_text_extents/3,
                     cairo_scaled_font_text_to_glyphs/7,

                     /* Cairo Font Options */
                     cairo_font_options_create/1,
                     cairo_font_options_equal/3,
                     cairo_font_options_get_antialias/2,
                     cairo_font_options_get_hint_metrics/2,
                     cairo_font_options_get_hint_style/2,
                     cairo_font_options_get_subpixel_order/2,
                     cairo_font_options_get_variations/2,
                     cairo_font_options_hash/2,
                     cairo_font_options_merge/2,
                     cairo_font_options_set_antialias/2,
                     cairo_font_options_set_hint_metrics/2,
                     cairo_font_options_set_hint_style/2,
                     cairo_font_options_set_subpixel_order/2,
                     cairo_font_options_set_variations/2,

/* FIXME: add cairo freetype fonts */
/* FIXME: add cairo win32 fonts */
/* FIXME: add cairo quartz fonts */
/* FIXME: add cairo user fonts */

                     /* Cairo Device */
                     cairo_device_acquire/1,
                     cairo_device_finish/1,
                     cairo_device_flush/1,
                     cairo_device_get_type/2,
                     cairo_device_observer_elapsed/2,
                     cairo_device_observer_fill_elapsed/2,
                     cairo_device_observer_glyphs_elapsed/2,
                     cairo_device_observer_mask_elapsed/2,
                     cairo_device_observer_paint_elapsed/2,
                     cairo_device_observer_print/3,
                     cairo_device_observer_stroke_elapsed/2,
                     cairo_device_release/1,

                     /* Cairo Surface */
                     cairo_surface_copy_page/1,
                     cairo_surface_create_for_rectangle/6,
                     cairo_surface_create_similar/5,
                     cairo_surface_create_similar_image/5,
                     cairo_surface_finish/1,
                     cairo_surface_flush/1,
                     cairo_surface_get_content/2,
                     cairo_surface_get_device/2,
                     cairo_surface_get_device_offset/3,
                     cairo_surface_get_device_scale/3,
                     cairo_surface_get_fallback_resolution/3,
                     cairo_surface_get_font_options/2,
                     cairo_surface_get_type/2,
                     cairo_surface_has_show_text_glyphs/1,
                     cairo_surface_map_to_image/3,
                     cairo_surface_mark_dirty/1,
                     cairo_surface_mark_dirty_rectangle/5,
                     cairo_surface_set_device_offset/3,
                     cairo_surface_set_device_scale/3,
                     cairo_surface_set_fallback_resolution/3,
                     cairo_surface_show_page/1,
                     cairo_surface_supports_mime_type/2,
                     cairo_surface_unmap_image/2,
 
                     /* Cairo Image Surface */
                     cairo_image_surface_create/4,
                     cairo_image_surface_get_format/2,
                     cairo_image_surface_get_height/2,
                     cairo_image_surface_get_stride/2,
                     cairo_image_surface_get_width/2,

                     /* Cairo PDF Surface */
                     cairo_pdf_get_versions/1,
                     cairo_pdf_surface_add_outline/6,
                     cairo_pdf_surface_create/4,
                     cairo_pdf_surface_create_for_stream/4,
                     cairo_pdf_surface_restrict_to_version/2,
                     cairo_pdf_surface_set_metadata/3,
                     cairo_pdf_surface_set_page_label/2,
                     cairo_pdf_surface_set_size/3,
                     cairo_pdf_surface_set_thumbnail_size/3,
                     cairo_pdf_version_to_string/2,

                     /* Cairo PNG Surface */
                     cairo_image_surface_create_from_png/2,
                     cairo_image_surface_create_from_png_stream/2,
                     cairo_surface_write_to_png/2,
                     cairo_surface_write_to_png_stream/2,

                     /* Cairo PostScript surface */
                     cairo_ps_get_levels/1,
                     cairo_ps_level_to_string/2,
                     cairo_ps_surface_create/4,
                     cairo_ps_surface_create_for_stream/4,
                     cairo_ps_surface_dsc_begin_page_setup/1,
                     cairo_ps_surface_dsc_begin_setup/1,
                     cairo_ps_surface_dsc_comment/2,
                     cairo_ps_surface_get_eps/2,
                     cairo_ps_surface_restrict_to_level/2,
                     cairo_ps_surface_set_eps/2,
                     cairo_ps_surface_set_size/3,

                     /* Cairo Recording Surface */
                     cairo_recording_surface_create/3,
                     cairo_recording_surface_get_extents/2,
                     cairo_recording_surface_ink_extents/5,

                     /* Cairo SVG Surface */
                     cairo_svg_get_versions/1,
                     cairo_svg_surface_create/4,
                     cairo_svg_surface_create_for_stream/4,
                     cairo_svg_surface_get_document_unit/2,
                     cairo_svg_surface_restrict_to_version/2,
                     cairo_svg_surface_set_document_unit/2,
                     cairo_svg_version_to_string/2,

                     /* Cairo Script Surface */
                     cairo_script_create/2,
                     cairo_script_create_for_stream/2,
                     cairo_script_from_recording_surface/3,
                     cairo_script_get_mode/2,
                     cairo_script_set_mode/2,
                     cairo_script_surface_create/5,
                     cairo_script_surface_create_for_target/3,
                     cairo_script_write_comment/2,

                     /* Cairo Matrix */
                     cairo_matrix_init/7,
                     cairo_matrix_init_identity/1,
                     cairo_matrix_init_rotate/2,
                     cairo_matrix_init_scale/3,
                     cairo_matrix_init_translate/3,
                     cairo_matrix_invert/1,
                     cairo_matrix_multiply/3,
                     cairo_matrix_rotate/2,
                     cairo_matrix_scale/3,
                     cairo_matrix_transform_distance/5,
                     cairo_matrix_transform_point/5,
                     cairo_matrix_translate/3,

                     /* PLcairo Specific */
                     plcairo_debug/1,
                     plcairo_version/1
                   ]).


:- use_module(library(plgi)).
:- use_foreign_library(foreign(plcairo), install_plcairo).

:- multifile
	prolog:message/3.

prolog:error_message(plcairo_error(Message)) -->
	[ 'PLcairo Error: ~w'-[Message] ].

prolog:error_message(cairo_error(Code, Message)) -->
	[ 'cairo Error: [~w] ~w'-[Code, Message] ].
