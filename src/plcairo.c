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


install_t
install_plcairo()
{
  /* Cairo Context */
  plcairo_register_rectangle_t();
  PLGI_PRED_REG("cairo_clip", 1, plcairo_clip);
  PLGI_PRED_REG("cairo_clip_extents", 5, plcairo_clip_extents);
  PLGI_PRED_REG("cairo_clip_preserve", 1, plcairo_clip_preserve);
  PLGI_PRED_REG("cairo_copy_clip_rectangle_list", 2, plcairo_copy_clip_rectangle_list);
  PLGI_PRED_REG("cairo_copy_page", 1, plcairo_copy_page);
  PLGI_PRED_REG("cairo_create", 2, plcairo_create);
  PLGI_PRED_REG("cairo_fill", 1, plcairo_fill);
  PLGI_PRED_REG("cairo_fill_extents", 5, plcairo_fill_extents);
  PLGI_PRED_REG("cairo_fill_preserve", 1, plcairo_fill_preserve);
  PLGI_PRED_REG("cairo_get_antialias", 2, plcairo_get_antialias);
  PLGI_PRED_REG("cairo_get_dash", 3, plcairo_get_dash);
  PLGI_PRED_REG("cairo_get_dash_count", 2, plcairo_get_dash_count);
  PLGI_PRED_REG("cairo_get_fill_rule", 2, plcairo_get_fill_rule);
  PLGI_PRED_REG("cairo_get_group_target", 2, plcairo_get_group_target);
  PLGI_PRED_REG("cairo_get_line_cap", 2, plcairo_get_line_cap);
  PLGI_PRED_REG("cairo_get_line_join", 2, plcairo_get_line_join);
  PLGI_PRED_REG("cairo_get_line_width", 2, plcairo_get_line_width);
  PLGI_PRED_REG("cairo_get_miter_limit", 2, plcairo_get_miter_limit);
  PLGI_PRED_REG("cairo_get_operator", 2, plcairo_get_operator);
  PLGI_PRED_REG("cairo_get_source", 2, plcairo_get_source);
  PLGI_PRED_REG("cairo_get_target", 2, plcairo_get_target);
  PLGI_PRED_REG("cairo_get_tolerance", 2, plcairo_get_tolerance);
  PLGI_PRED_REG("cairo_in_clip", 3, plcairo_in_clip);
  PLGI_PRED_REG("cairo_in_fill", 3, plcairo_in_fill);
  PLGI_PRED_REG("cairo_in_stroke", 3, plcairo_in_stroke);
  PLGI_PRED_REG("cairo_mask", 2, plcairo_mask);
  PLGI_PRED_REG("cairo_mask_surface", 4, plcairo_mask_surface);
  PLGI_PRED_REG("cairo_paint", 1, plcairo_paint);
  PLGI_PRED_REG("cairo_paint_with_alpha", 2, plcairo_paint_with_alpha);
  PLGI_PRED_REG("cairo_pop_group", 2, plcairo_pop_group);
  PLGI_PRED_REG("cairo_pop_group_to_source", 1, plcairo_pop_group_to_source);
  PLGI_PRED_REG("cairo_push_group", 1, plcairo_push_group);
  PLGI_PRED_REG("cairo_push_group_with_content", 2, plcairo_push_group_with_content);
  PLGI_PRED_REG("cairo_reset_clip", 1, plcairo_reset_clip);
  PLGI_PRED_REG("cairo_restore", 1, plcairo_restore);
  PLGI_PRED_REG("cairo_save", 1, plcairo_save);
  PLGI_PRED_REG("cairo_set_antialias", 2, plcairo_set_antialias);
  PLGI_PRED_REG("cairo_set_dash", 3, plcairo_set_dash);
  PLGI_PRED_REG("cairo_set_fill_rule", 2, plcairo_set_fill_rule);
  PLGI_PRED_REG("cairo_set_line_cap", 2, plcairo_set_line_cap);
  PLGI_PRED_REG("cairo_set_line_join", 2, plcairo_set_line_join);
  PLGI_PRED_REG("cairo_set_line_width", 2, plcairo_set_line_width);
  PLGI_PRED_REG("cairo_set_miter_limit", 2, plcairo_set_miter_limit);
  PLGI_PRED_REG("cairo_set_operator", 2, plcairo_set_operator);
  PLGI_PRED_REG("cairo_set_source", 2, plcairo_set_source);
  PLGI_PRED_REG("cairo_set_source_rgb", 4, plcairo_set_source_rgb);
  PLGI_PRED_REG("cairo_set_source_rgba", 5, plcairo_set_source_rgba);
  PLGI_PRED_REG("cairo_set_source_surface", 4, plcairo_set_source_surface);
  PLGI_PRED_REG("cairo_set_tolerance", 2, plcairo_set_tolerance);
  PLGI_PRED_REG("cairo_show_page", 1, plcairo_show_page);
  PLGI_PRED_REG("cairo_stroke", 1, plcairo_stroke);
  PLGI_PRED_REG("cairo_stroke_extents", 5, plcairo_stroke_extents);
  PLGI_PRED_REG("cairo_stroke_preserve", 1, plcairo_stroke_preserve);

  /* Cairo Paths */
  PLGI_PRED_REG("cairo_append_path", 2, plcairo_append_path);
  PLGI_PRED_REG("cairo_arc", 6, plcairo_arc);
  PLGI_PRED_REG("cairo_arc_negative", 6, plcairo_arc_negative);
  PLGI_PRED_REG("cairo_close_path", 1, plcairo_close_path);
  PLGI_PRED_REG("cairo_copy_path", 2, plcairo_copy_path);
  PLGI_PRED_REG("cairo_copy_path_flat", 2, plcairo_copy_path_flat);
  PLGI_PRED_REG("cairo_curve_to", 7, plcairo_curve_to);
  PLGI_PRED_REG("cairo_get_current_point", 3, plcairo_get_current_point);
  PLGI_PRED_REG("cairo_glyph_path", 2, plcairo_glyph_path);
  PLGI_PRED_REG("cairo_has_current_point", 2, plcairo_has_current_point);
  PLGI_PRED_REG("cairo_line_to", 3, plcairo_line_to);
  PLGI_PRED_REG("cairo_move_to", 3, plcairo_move_to);
  PLGI_PRED_REG("cairo_new_path", 1, plcairo_new_path);
  PLGI_PRED_REG("cairo_new_sub_path", 1, plcairo_new_sub_path);
  PLGI_PRED_REG("cairo_path_extents", 5, plcairo_path_extents);
  PLGI_PRED_REG("cairo_rectangle", 5, plcairo_rectangle);
  PLGI_PRED_REG("cairo_rel_curve_to", 7, plcairo_rel_curve_to);
  PLGI_PRED_REG("cairo_rel_line_to", 3, plcairo_rel_line_to);
  PLGI_PRED_REG("cairo_rel_move_to", 3, plcairo_rel_move_to);
  PLGI_PRED_REG("cairo_text_path", 2, plcairo_text_path);

  /* Cairo Pattern */
  PLGI_PRED_REG("cairo_pattern_add_color_stop_rgb", 5, plcairo_pattern_add_color_stop_rgb);
  PLGI_PRED_REG("cairo_pattern_add_color_stop_rgba", 6, plcairo_pattern_add_color_stop_rgba);
  PLGI_PRED_REG("cairo_pattern_create_for_surface", 2, plcairo_pattern_create_for_surface);
  PLGI_PRED_REG("cairo_pattern_create_linear", 5, plcairo_pattern_create_linear);
  PLGI_PRED_REG("cairo_pattern_create_mesh", 1, plcairo_pattern_create_mesh);
  PLGI_PRED_REG("cairo_pattern_create_radial", 7, plcairo_pattern_create_radial);
  PLGI_PRED_REG("cairo_pattern_create_rgb", 4, plcairo_pattern_create_rgb);
  PLGI_PRED_REG("cairo_pattern_create_rgba", 5, plcairo_pattern_create_rgba);
  PLGI_PRED_REG("cairo_pattern_get_color_stop_count", 2, plcairo_pattern_get_color_stop_count);
  PLGI_PRED_REG("cairo_pattern_get_color_stop_rgba", 7, plcairo_pattern_get_color_stop_rgba);
  PLGI_PRED_REG("cairo_pattern_get_extend", 2, plcairo_pattern_get_extend);
  PLGI_PRED_REG("cairo_pattern_get_filter", 2, plcairo_pattern_get_filter);
  PLGI_PRED_REG("cairo_pattern_get_linear_points", 5, plcairo_pattern_get_linear_points);
  PLGI_PRED_REG("cairo_pattern_get_matrix", 2, plcairo_pattern_get_matrix);
  PLGI_PRED_REG("cairo_pattern_get_radial_circles", 7, plcairo_pattern_get_radial_circles);
  PLGI_PRED_REG("cairo_pattern_get_rgba", 5, plcairo_pattern_get_rgba);
  PLGI_PRED_REG("cairo_pattern_get_surface", 2, plcairo_pattern_get_surface);
  PLGI_PRED_REG("cairo_pattern_get_type", 2, plcairo_pattern_get_type);
  PLGI_PRED_REG("cairo_mesh_pattern_begin_patch", 1, plcairo_mesh_pattern_begin_patch);
  PLGI_PRED_REG("cairo_mesh_pattern_curve_to", 7, plcairo_mesh_pattern_curve_to);
  PLGI_PRED_REG("cairo_mesh_pattern_end_patch", 1, plcairo_mesh_pattern_end_patch);
  PLGI_PRED_REG("cairo_mesh_pattern_get_control_point", 5, plcairo_mesh_pattern_get_control_point);
  PLGI_PRED_REG("cairo_mesh_pattern_get_corner_color_rgba", 7, plcairo_mesh_pattern_get_corner_color_rgba);
  PLGI_PRED_REG("cairo_mesh_pattern_get_patch_count", 2, plcairo_mesh_pattern_get_patch_count);
  PLGI_PRED_REG("cairo_mesh_pattern_get_path", 3, plcairo_mesh_pattern_get_path);
  PLGI_PRED_REG("cairo_mesh_pattern_line_to", 3, plcairo_mesh_pattern_line_to);
  PLGI_PRED_REG("cairo_mesh_pattern_move_to", 3, plcairo_mesh_pattern_move_to);
  PLGI_PRED_REG("cairo_mesh_pattern_set_control_point", 4, plcairo_mesh_pattern_set_control_point);
  PLGI_PRED_REG("cairo_mesh_pattern_set_corner_color_rgb", 5, plcairo_mesh_pattern_set_corner_color_rgb);
  PLGI_PRED_REG("cairo_mesh_pattern_set_corner_color_rgba", 6, plcairo_mesh_pattern_set_corner_color_rgba);
  PLGI_PRED_REG("cairo_pattern_set_extend", 2, plcairo_pattern_set_extend);
  PLGI_PRED_REG("cairo_pattern_set_filter", 2, plcairo_pattern_set_filter);
  PLGI_PRED_REG("cairo_pattern_set_matrix", 2, plcairo_pattern_set_matrix);

  /* Cairo Region */
  PLGI_PRED_REG("cairo_region_contains_point", 3, plcairo_region_contains_point);
  PLGI_PRED_REG("cairo_region_contains_rectangle", 3, plcairo_region_contains_rectangle);
  PLGI_PRED_REG("cairo_region_create", 1, plcairo_region_create);
  PLGI_PRED_REG("cairo_region_create_rectangle", 2, plcairo_region_create_rectangle);
  PLGI_PRED_REG("cairo_region_create_rectangles", 2, plcairo_region_create_rectangles);
  PLGI_PRED_REG("cairo_region_equal", 2, plcairo_region_equal);
  PLGI_PRED_REG("cairo_region_get_extents", 2, plcairo_region_get_extents);
  PLGI_PRED_REG("cairo_region_get_rectangle", 3, plcairo_region_get_rectangle);
  PLGI_PRED_REG("cairo_region_intersect", 2, plcairo_region_intersect);
  PLGI_PRED_REG("cairo_region_intersect_rectangle", 2, plcairo_region_intersect_rectangle);
  PLGI_PRED_REG("cairo_region_is_empty", 1, plcairo_region_is_empty);
  PLGI_PRED_REG("cairo_region_num_rectangles", 2, plcairo_region_num_rectangles);
  PLGI_PRED_REG("cairo_region_subtract", 2, plcairo_region_subtract);
  PLGI_PRED_REG("cairo_region_subtract_rectangle", 2, plcairo_region_subtract_rectangle);
  PLGI_PRED_REG("cairo_region_translate", 3, plcairo_region_translate);
  PLGI_PRED_REG("cairo_region_union", 2, plcairo_region_union);
  PLGI_PRED_REG("cairo_region_union_rectangle", 2, plcairo_region_union_rectangle);
  PLGI_PRED_REG("cairo_region_xor", 2, plcairo_region_xor);
  PLGI_PRED_REG("cairo_region_xor_rectangle", 2, plcairo_region_xor_rectangle);

  /* Cairo Transformation */
  PLGI_PRED_REG("cairo_device_to_user", 5, plcairo_device_to_user);
  PLGI_PRED_REG("cairo_device_to_user_distance", 5, plcairo_device_to_user_distance);
  PLGI_PRED_REG("cairo_get_matrix", 2, plcairo_get_matrix);
  PLGI_PRED_REG("cairo_identity_matrix", 1, plcairo_identity_matrix);
  PLGI_PRED_REG("cairo_rotate", 2, plcairo_rotate);
  PLGI_PRED_REG("cairo_scale", 3, plcairo_scale);
  PLGI_PRED_REG("cairo_set_matrix", 2, plcairo_set_matrix);
  PLGI_PRED_REG("cairo_transform", 2, plcairo_transform);
  PLGI_PRED_REG("cairo_translate", 3, plcairo_translate);
  PLGI_PRED_REG("cairo_user_to_device", 5, plcairo_user_to_device);
  PLGI_PRED_REG("cairo_user_to_device_distance", 5, plcairo_user_to_device_distance);

  /* Cairo Text */
  plcairo_register_glyph_t();
  plcairo_register_text_cluster_t();
  PLGI_PRED_REG("cairo_font_extents", 2, plcairo_font_extents);
  PLGI_PRED_REG("cairo_get_font_face", 2, plcairo_get_font_face);
  PLGI_PRED_REG("cairo_get_font_matrix", 2, plcairo_get_font_matrix);
  PLGI_PRED_REG("cairo_get_font_options", 2, plcairo_get_font_options);
  PLGI_PRED_REG("cairo_get_scaled_font", 2, plcairo_get_scaled_font);
  PLGI_PRED_REG("cairo_glyph_extents", 3, plcairo_glyph_extents);
  PLGI_PRED_REG("cairo_select_font_face", 4, plcairo_select_font_face);
  PLGI_PRED_REG("cairo_set_font_face", 2, plcairo_set_font_face);
  PLGI_PRED_REG("cairo_set_font_matrix", 2, plcairo_set_font_matrix);
  PLGI_PRED_REG("cairo_set_font_options", 2, plcairo_set_font_options);
  PLGI_PRED_REG("cairo_set_font_size", 2, plcairo_set_font_size);
  PLGI_PRED_REG("cairo_set_scaled_font", 2, plcairo_set_scaled_font);
  PLGI_PRED_REG("cairo_show_glyphs", 2, plcairo_show_glyphs);
  PLGI_PRED_REG("cairo_show_text", 2, plcairo_show_text);
  PLGI_PRED_REG("cairo_show_text_glyphs", 5, plcairo_show_text_glyphs);
  PLGI_PRED_REG("cairo_text_extents", 3, plcairo_text_extents);
  PLGI_PRED_REG("cairo_toy_font_face_create", 4, plcairo_toy_font_face_create);
  PLGI_PRED_REG("cairo_toy_font_face_get_family", 2, plcairo_toy_font_face_get_family);
  PLGI_PRED_REG("cairo_toy_font_face_get_slant", 2, plcairo_toy_font_face_get_slant);
  PLGI_PRED_REG("cairo_toy_font_face_get_weight", 2, plcairo_toy_font_face_get_weight);

  /* Cairo Raster Source */
  PLGI_PRED_REG("cairo_pattern_create_raster_source", 4, plcairo_pattern_create_raster_source);

  /* Cairo Font Face */
  PLGI_PRED_REG("cairo_font_face_get_type", 2, plcairo_font_face_get_type);

  /* Cairo Scaled Font */
  plcairo_register_font_extents_t();
  plcairo_register_text_extents_t();
  PLGI_PRED_REG("cairo_scaled_font_create", 5, plcairo_scaled_font_create);
  PLGI_PRED_REG("cairo_scaled_font_extents", 2, plcairo_scaled_font_extents);
  PLGI_PRED_REG("cairo_scaled_font_get_ctm", 2, plcairo_scaled_font_get_ctm);
  PLGI_PRED_REG("cairo_scaled_font_get_font_face", 2, plcairo_scaled_font_get_font_face);
  PLGI_PRED_REG("cairo_scaled_font_get_font_matrix", 2, plcairo_scaled_font_get_font_matrix);
  PLGI_PRED_REG("cairo_scaled_font_get_font_options", 2, plcairo_scaled_font_get_font_options);
  PLGI_PRED_REG("cairo_scaled_font_get_scale_matrix", 2, plcairo_scaled_font_get_scale_matrix);
  PLGI_PRED_REG("cairo_scaled_font_get_type", 2, plcairo_scaled_font_get_type);
  PLGI_PRED_REG("cairo_scaled_font_glyph_extents", 3, plcairo_scaled_font_glyph_extents);
  PLGI_PRED_REG("cairo_scaled_font_text_extents", 3, plcairo_scaled_font_text_extents);
  PLGI_PRED_REG("cairo_scaled_font_text_to_glyphs", 7, plcairo_scaled_font_text_to_glyphs);

  /* Cairo Font Options */
  PLGI_PRED_REG("cairo_font_options_create", 1, plcairo_font_options_create);
  PLGI_PRED_REG("cairo_font_options_equal", 3, plcairo_font_options_equal);
  PLGI_PRED_REG("cairo_font_options_get_antialias", 2, plcairo_font_options_get_antialias);
  PLGI_PRED_REG("cairo_font_options_get_hint_metrics", 2, plcairo_font_options_get_hint_metrics);
  PLGI_PRED_REG("cairo_font_options_get_hint_style", 2, plcairo_font_options_get_hint_style);
  PLGI_PRED_REG("cairo_font_options_get_subpixel_order", 2, plcairo_font_options_get_subpixel_order);
  PLGI_PRED_REG("cairo_font_options_hash", 2, plcairo_font_options_hash);
  PLGI_PRED_REG("cairo_font_options_merge", 2, plcairo_font_options_merge);
  PLGI_PRED_REG("cairo_font_options_set_antialias", 2, plcairo_font_options_set_antialias);
  PLGI_PRED_REG("cairo_font_options_set_hint_metrics", 2, plcairo_font_options_set_hint_metrics);
  PLGI_PRED_REG("cairo_font_options_set_hint_style", 2, plcairo_font_options_set_hint_style);
  PLGI_PRED_REG("cairo_font_options_set_subpixel_order", 2, plcairo_font_options_set_subpixel_order);

  /* Cairo Device */
  PLGI_PRED_REG("cairo_device_acquire", 1, plcairo_device_acquire);
  PLGI_PRED_REG("cairo_device_finish", 1, plcairo_device_finish);
  PLGI_PRED_REG("cairo_device_flush", 1, plcairo_device_flush);
  PLGI_PRED_REG("cairo_device_get_type", 2, plcairo_device_get_type);
  PLGI_PRED_REG("cairo_device_observer_elapsed", 2, plcairo_device_observer_elapsed);
  PLGI_PRED_REG("cairo_device_observer_fill_elapsed", 2, plcairo_device_observer_fill_elapsed);
  PLGI_PRED_REG("cairo_device_observer_glyphs_elapsed", 2, plcairo_device_observer_glyphs_elapsed);
  PLGI_PRED_REG("cairo_device_observer_mask_elapsed", 2, plcairo_device_observer_mask_elapsed);
  PLGI_PRED_REG("cairo_device_observer_paint_elapsed", 2, plcairo_device_observer_paint_elapsed);
  PLGI_PRED_REG("cairo_device_observer_print", 3, plcairo_device_observer_print);
  PLGI_PRED_REG("cairo_device_observer_stroke_elapsed", 2, plcairo_device_observer_stroke_elapsed);
  PLGI_PRED_REG("cairo_device_release", 1, plcairo_device_release);

  /* Cairo Surface */
  PLGI_PRED_REG("cairo_surface_copy_page", 1, plcairo_surface_copy_page);
  PLGI_PRED_REG("cairo_surface_create_for_rectangle", 6, plcairo_surface_create_for_rectangle);
  PLGI_PRED_REG("cairo_surface_create_similar", 5, plcairo_surface_create_similar);
  PLGI_PRED_REG("cairo_surface_create_similar_image", 5, plcairo_surface_create_similar_image);
  PLGI_PRED_REG("cairo_surface_finish", 1, plcairo_surface_finish);
  PLGI_PRED_REG("cairo_surface_flush", 1, plcairo_surface_flush);
  PLGI_PRED_REG("cairo_surface_get_content", 2, plcairo_surface_get_content);
  PLGI_PRED_REG("cairo_surface_get_device", 2, plcairo_surface_get_device);
  PLGI_PRED_REG("cairo_surface_get_device_offset", 3, plcairo_surface_get_device_offset);
  PLGI_PRED_REG("cairo_surface_get_device_scale", 3, plcairo_surface_get_device_scale);
  PLGI_PRED_REG("cairo_surface_get_fallback_resolution", 3, plcairo_surface_get_fallback_resolution);
  PLGI_PRED_REG("cairo_surface_get_font_options", 2, plcairo_surface_get_font_options);
  PLGI_PRED_REG("cairo_surface_get_type", 2, plcairo_surface_get_type);
  PLGI_PRED_REG("cairo_surface_has_show_text_glyphs", 1, plcairo_surface_has_show_text_glyphs);
  PLGI_PRED_REG("cairo_surface_map_to_image", 3, plcairo_surface_map_to_image);
  PLGI_PRED_REG("cairo_surface_mark_dirty", 1, plcairo_surface_mark_dirty);
  PLGI_PRED_REG("cairo_surface_mark_dirty_rectangle", 5, plcairo_surface_mark_dirty_rectangle);
  PLGI_PRED_REG("cairo_surface_set_device_offset", 3, plcairo_surface_set_device_offset);
  PLGI_PRED_REG("cairo_surface_set_device_scale", 3, plcairo_surface_set_device_scale);
  PLGI_PRED_REG("cairo_surface_set_fallback_resolution", 3, plcairo_surface_set_fallback_resolution);
  PLGI_PRED_REG("cairo_surface_show_page", 1, plcairo_surface_show_page);
  PLGI_PRED_REG("cairo_surface_supports_mime_type", 2, plcairo_surface_supports_mime_type);
  PLGI_PRED_REG("cairo_surface_unmap_image", 2, plcairo_surface_unmap_image);

  /* Cairo Image Surface */
  PLGI_PRED_REG("cairo_image_surface_create", 4, plcairo_image_surface_create);
  PLGI_PRED_REG("cairo_image_surface_get_format", 2, plcairo_image_surface_get_format);
  PLGI_PRED_REG("cairo_image_surface_get_height", 2, plcairo_image_surface_get_height);
  PLGI_PRED_REG("cairo_image_surface_get_stride", 2, plcairo_image_surface_get_stride);
  PLGI_PRED_REG("cairo_image_surface_get_width", 2, plcairo_image_surface_get_width);

  /* Cairo PDF Surface */
  PLGI_PRED_REG("cairo_pdf_get_versions", 1, plcairo_pdf_get_versions);
  PLGI_PRED_REG("cairo_pdf_surface_create", 4, plcairo_pdf_surface_create);
  PLGI_PRED_REG("cairo_pdf_surface_create_for_stream", 4, plcairo_pdf_surface_create_for_stream);
  PLGI_PRED_REG("cairo_pdf_surface_restrict_to_version", 2, plcairo_pdf_surface_restrict_to_version);
  PLGI_PRED_REG("cairo_pdf_surface_set_size", 3, plcairo_pdf_surface_set_size);
  PLGI_PRED_REG("cairo_pdf_version_to_string", 2, plcairo_pdf_version_to_string);

  /* Cairo PNG Surface */
  PLGI_PRED_REG("cairo_image_surface_create_from_png", 2, plcairo_image_surface_create_from_png);
  PLGI_PRED_REG("cairo_image_surface_create_from_png_stream", 2, plcairo_image_surface_create_from_png_stream);
  PLGI_PRED_REG("cairo_surface_write_to_png", 2, plcairo_surface_write_to_png);
  PLGI_PRED_REG("cairo_surface_write_to_png_stream", 2, plcairo_surface_write_to_png_stream);

  /* Cairo PostScript Surface */
  PLGI_PRED_REG("cairo_ps_get_levels", 1, plcairo_ps_get_levels);
  PLGI_PRED_REG("cairo_ps_level_to_string", 2, plcairo_ps_level_to_string);
  PLGI_PRED_REG("cairo_ps_surface_create", 4, plcairo_ps_surface_create);
  PLGI_PRED_REG("cairo_ps_surface_create_for_stream", 4, plcairo_ps_surface_create_for_stream);
  PLGI_PRED_REG("cairo_ps_surface_dsc_begin_page_setup", 1, plcairo_ps_surface_dsc_begin_page_setup);
  PLGI_PRED_REG("cairo_ps_surface_dsc_begin_setup", 1, plcairo_ps_surface_dsc_begin_setup);
  PLGI_PRED_REG("cairo_ps_surface_dsc_comment", 2, plcairo_ps_surface_dsc_comment);
  PLGI_PRED_REG("cairo_ps_surface_get_eps", 2, plcairo_ps_surface_get_eps);
  PLGI_PRED_REG("cairo_ps_surface_restrict_to_level", 2, plcairo_ps_surface_restrict_to_level);
  PLGI_PRED_REG("cairo_ps_surface_set_eps", 2, plcairo_ps_surface_set_eps);
  PLGI_PRED_REG("cairo_ps_surface_set_size", 3, plcairo_ps_surface_set_size);

  /* Cairo Recording Surface */
  PLGI_PRED_REG("cairo_recording_surface_create", 3, plcairo_recording_surface_create);
  PLGI_PRED_REG("cairo_recording_surface_get_extents", 2, plcairo_recording_surface_get_extents);
  PLGI_PRED_REG("cairo_recording_surface_ink_extents", 5, plcairo_recording_surface_ink_extents);

  /* Cairo SVG Surface */
  PLGI_PRED_REG("cairo_svg_get_versions", 1, plcairo_svg_get_versions);
  PLGI_PRED_REG("cairo_svg_surface_create", 4, plcairo_svg_surface_create);
  PLGI_PRED_REG("cairo_svg_surface_create_for_stream", 4, plcairo_svg_surface_create_for_stream);
  PLGI_PRED_REG("cairo_svg_surface_restrict_to_version", 2, plcairo_svg_surface_restrict_to_version);
  PLGI_PRED_REG("cairo_svg_version_to_string", 2, plcairo_svg_version_to_string);

  /* Cairo Script Surface */
  PLGI_PRED_REG("cairo_script_create", 2, plcairo_script_create);
  PLGI_PRED_REG("cairo_script_create_for_stream", 2, plcairo_script_create_for_stream);
  PLGI_PRED_REG("cairo_script_from_recording_surface", 3, plcairo_script_from_recording_surface);
  PLGI_PRED_REG("cairo_script_get_mode", 2, plcairo_script_get_mode);
  PLGI_PRED_REG("cairo_script_set_mode", 2, plcairo_script_set_mode);
  PLGI_PRED_REG("cairo_script_surface_create", 5, plcairo_script_surface_create);
  PLGI_PRED_REG("cairo_script_surface_create_for_target", 3, plcairo_script_surface_create_for_target);
  PLGI_PRED_REG("cairo_script_write_comment", 2, plcairo_script_write_comment);

  /* Cairo Matrix */
  plcairo_register_matrix_t();
  PLGI_PRED_REG("cairo_matrix_init", 7, plcairo_matrix_init);
  PLGI_PRED_REG("cairo_matrix_init_identity", 1, plcairo_matrix_init_identity);
  PLGI_PRED_REG("cairo_matrix_init_rotate", 2, plcairo_matrix_init_rotate);
  PLGI_PRED_REG("cairo_matrix_init_scale", 3, plcairo_matrix_init_scale);
  PLGI_PRED_REG("cairo_matrix_init_translate", 3, plcairo_matrix_init_translate);
  PLGI_PRED_REG("cairo_matrix_invert", 1, plcairo_matrix_invert);
  PLGI_PRED_REG("cairo_matrix_multiply", 3, plcairo_matrix_multiply);
  PLGI_PRED_REG("cairo_matrix_rotate", 2, plcairo_matrix_rotate);
  PLGI_PRED_REG("cairo_matrix_scale", 3, plcairo_matrix_scale);
  PLGI_PRED_REG("cairo_matrix_transform_distance", 5, plcairo_matrix_transform_distance);
  PLGI_PRED_REG("cairo_matrix_transform_point", 5, plcairo_matrix_transform_point);
  PLGI_PRED_REG("cairo_matrix_translate", 3, plcairo_matrix_translate);

  /* Cairo Rectangle */
  plcairo_register_rectangle_int_t();
}
