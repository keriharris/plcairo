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
  PLCAIRO_PRED_REG("cairo_clip", 1, plcairo_clip);
  PLCAIRO_PRED_REG("cairo_clip_extents", 5, plcairo_clip_extents);
  PLCAIRO_PRED_REG("cairo_clip_preserve", 1, plcairo_clip_preserve);
  PLCAIRO_PRED_REG("cairo_copy_clip_rectangle_list", 2, plcairo_copy_clip_rectangle_list);
  PLCAIRO_PRED_REG("cairo_copy_page", 1, plcairo_copy_page);
  PLCAIRO_PRED_REG("cairo_create", 2, plcairo_create);
  PLCAIRO_PRED_REG("cairo_fill", 1, plcairo_fill);
  PLCAIRO_PRED_REG("cairo_fill_extents", 5, plcairo_fill_extents);
  PLCAIRO_PRED_REG("cairo_fill_preserve", 1, plcairo_fill_preserve);
  PLCAIRO_PRED_REG("cairo_get_antialias", 2, plcairo_get_antialias);
  PLCAIRO_PRED_REG("cairo_get_dash", 3, plcairo_get_dash);
  PLCAIRO_PRED_REG("cairo_get_dash_count", 2, plcairo_get_dash_count);
  PLCAIRO_PRED_REG("cairo_get_fill_rule", 2, plcairo_get_fill_rule);
  PLCAIRO_PRED_REG("cairo_get_group_target", 2, plcairo_get_group_target);
  PLCAIRO_PRED_REG("cairo_get_line_cap", 2, plcairo_get_line_cap);
  PLCAIRO_PRED_REG("cairo_get_line_join", 2, plcairo_get_line_join);
  PLCAIRO_PRED_REG("cairo_get_line_width", 2, plcairo_get_line_width);
  PLCAIRO_PRED_REG("cairo_get_miter_limit", 2, plcairo_get_miter_limit);
  PLCAIRO_PRED_REG("cairo_get_operator", 2, plcairo_get_operator);
  PLCAIRO_PRED_REG("cairo_get_source", 2, plcairo_get_source);
  PLCAIRO_PRED_REG("cairo_get_target", 2, plcairo_get_target);
  PLCAIRO_PRED_REG("cairo_get_tolerance", 2, plcairo_get_tolerance);
  PLCAIRO_PRED_REG("cairo_in_clip", 3, plcairo_in_clip);
  PLCAIRO_PRED_REG("cairo_in_fill", 3, plcairo_in_fill);
  PLCAIRO_PRED_REG("cairo_in_stroke", 3, plcairo_in_stroke);
  PLCAIRO_PRED_REG("cairo_mask", 2, plcairo_mask);
  PLCAIRO_PRED_REG("cairo_mask_surface", 4, plcairo_mask_surface);
  PLCAIRO_PRED_REG("cairo_paint", 1, plcairo_paint);
  PLCAIRO_PRED_REG("cairo_paint_with_alpha", 2, plcairo_paint_with_alpha);
  PLCAIRO_PRED_REG("cairo_pop_group", 2, plcairo_pop_group);
  PLCAIRO_PRED_REG("cairo_pop_group_to_source", 1, plcairo_pop_group_to_source);
  PLCAIRO_PRED_REG("cairo_push_group", 1, plcairo_push_group);
  PLCAIRO_PRED_REG("cairo_push_group_with_content", 2, plcairo_push_group_with_content);
  PLCAIRO_PRED_REG("cairo_reset_clip", 1, plcairo_reset_clip);
  PLCAIRO_PRED_REG("cairo_restore", 1, plcairo_restore);
  PLCAIRO_PRED_REG("cairo_save", 1, plcairo_save);
  PLCAIRO_PRED_REG("cairo_set_antialias", 2, plcairo_set_antialias);
  PLCAIRO_PRED_REG("cairo_set_dash", 3, plcairo_set_dash);
  PLCAIRO_PRED_REG("cairo_set_fill_rule", 2, plcairo_set_fill_rule);
  PLCAIRO_PRED_REG("cairo_set_line_cap", 2, plcairo_set_line_cap);
  PLCAIRO_PRED_REG("cairo_set_line_join", 2, plcairo_set_line_join);
  PLCAIRO_PRED_REG("cairo_set_line_width", 2, plcairo_set_line_width);
  PLCAIRO_PRED_REG("cairo_set_miter_limit", 2, plcairo_set_miter_limit);
  PLCAIRO_PRED_REG("cairo_set_operator", 2, plcairo_set_operator);
  PLCAIRO_PRED_REG("cairo_set_source", 2, plcairo_set_source);
  PLCAIRO_PRED_REG("cairo_set_source_rgb", 4, plcairo_set_source_rgb);
  PLCAIRO_PRED_REG("cairo_set_source_rgba", 5, plcairo_set_source_rgba);
  PLCAIRO_PRED_REG("cairo_set_source_surface", 4, plcairo_set_source_surface);
  PLCAIRO_PRED_REG("cairo_set_tolerance", 2, plcairo_set_tolerance);
  PLCAIRO_PRED_REG("cairo_show_page", 1, plcairo_show_page);
  PLCAIRO_PRED_REG("cairo_stroke", 1, plcairo_stroke);
  PLCAIRO_PRED_REG("cairo_stroke_extents", 5, plcairo_stroke_extents);
  PLCAIRO_PRED_REG("cairo_stroke_preserve", 1, plcairo_stroke_preserve);

  /* Cairo Paths */
  PLCAIRO_PRED_REG("cairo_append_path", 2, plcairo_append_path);
  PLCAIRO_PRED_REG("cairo_arc", 6, plcairo_arc);
  PLCAIRO_PRED_REG("cairo_arc_negative", 6, plcairo_arc_negative);
  PLCAIRO_PRED_REG("cairo_close_path", 1, plcairo_close_path);
  PLCAIRO_PRED_REG("cairo_copy_path", 2, plcairo_copy_path);
  PLCAIRO_PRED_REG("cairo_copy_path_flat", 2, plcairo_copy_path_flat);
  PLCAIRO_PRED_REG("cairo_curve_to", 7, plcairo_curve_to);
  PLCAIRO_PRED_REG("cairo_get_current_point", 3, plcairo_get_current_point);
  PLCAIRO_PRED_REG("cairo_glyph_path", 2, plcairo_glyph_path);
  PLCAIRO_PRED_REG("cairo_has_current_point", 2, plcairo_has_current_point);
  PLCAIRO_PRED_REG("cairo_line_to", 3, plcairo_line_to);
  PLCAIRO_PRED_REG("cairo_move_to", 3, plcairo_move_to);
  PLCAIRO_PRED_REG("cairo_new_path", 1, plcairo_new_path);
  PLCAIRO_PRED_REG("cairo_new_sub_path", 1, plcairo_new_sub_path);
  PLCAIRO_PRED_REG("cairo_path_extents", 5, plcairo_path_extents);
  PLCAIRO_PRED_REG("cairo_rectangle", 5, plcairo_rectangle);
  PLCAIRO_PRED_REG("cairo_rel_curve_to", 7, plcairo_rel_curve_to);
  PLCAIRO_PRED_REG("cairo_rel_line_to", 3, plcairo_rel_line_to);
  PLCAIRO_PRED_REG("cairo_rel_move_to", 3, plcairo_rel_move_to);
  PLCAIRO_PRED_REG("cairo_text_path", 2, plcairo_text_path);

  /* Cairo Pattern */
  PLCAIRO_PRED_REG("cairo_pattern_add_color_stop_rgb", 5, plcairo_pattern_add_color_stop_rgb);
  PLCAIRO_PRED_REG("cairo_pattern_add_color_stop_rgba", 6, plcairo_pattern_add_color_stop_rgba);
  PLCAIRO_PRED_REG("cairo_pattern_create_for_surface", 2, plcairo_pattern_create_for_surface);
  PLCAIRO_PRED_REG("cairo_pattern_create_linear", 5, plcairo_pattern_create_linear);
  PLCAIRO_PRED_REG("cairo_pattern_create_mesh", 1, plcairo_pattern_create_mesh);
  PLCAIRO_PRED_REG("cairo_pattern_create_radial", 7, plcairo_pattern_create_radial);
  PLCAIRO_PRED_REG("cairo_pattern_create_rgb", 4, plcairo_pattern_create_rgb);
  PLCAIRO_PRED_REG("cairo_pattern_create_rgba", 5, plcairo_pattern_create_rgba);
  PLCAIRO_PRED_REG("cairo_pattern_get_color_stop_count", 2, plcairo_pattern_get_color_stop_count);
  PLCAIRO_PRED_REG("cairo_pattern_get_color_stop_rgba", 7, plcairo_pattern_get_color_stop_rgba);
  PLCAIRO_PRED_REG("cairo_pattern_get_extend", 2, plcairo_pattern_get_extend);
  PLCAIRO_PRED_REG("cairo_pattern_get_filter", 2, plcairo_pattern_get_filter);
  PLCAIRO_PRED_REG("cairo_pattern_get_linear_points", 5, plcairo_pattern_get_linear_points);
  PLCAIRO_PRED_REG("cairo_pattern_get_matrix", 2, plcairo_pattern_get_matrix);
  PLCAIRO_PRED_REG("cairo_pattern_get_radial_circles", 7, plcairo_pattern_get_radial_circles);
  PLCAIRO_PRED_REG("cairo_pattern_get_rgba", 5, plcairo_pattern_get_rgba);
  PLCAIRO_PRED_REG("cairo_pattern_get_surface", 2, plcairo_pattern_get_surface);
  PLCAIRO_PRED_REG("cairo_pattern_get_type", 2, plcairo_pattern_get_type);
  PLCAIRO_PRED_REG("cairo_mesh_pattern_begin_patch", 1, plcairo_mesh_pattern_begin_patch);
  PLCAIRO_PRED_REG("cairo_mesh_pattern_curve_to", 7, plcairo_mesh_pattern_curve_to);
  PLCAIRO_PRED_REG("cairo_mesh_pattern_end_patch", 1, plcairo_mesh_pattern_end_patch);
  PLCAIRO_PRED_REG("cairo_mesh_pattern_get_control_point", 5, plcairo_mesh_pattern_get_control_point);
  PLCAIRO_PRED_REG("cairo_mesh_pattern_get_corner_color_rgba", 7, plcairo_mesh_pattern_get_corner_color_rgba);
  PLCAIRO_PRED_REG("cairo_mesh_pattern_get_patch_count", 2, plcairo_mesh_pattern_get_patch_count);
  PLCAIRO_PRED_REG("cairo_mesh_pattern_get_path", 3, plcairo_mesh_pattern_get_path);
  PLCAIRO_PRED_REG("cairo_mesh_pattern_line_to", 3, plcairo_mesh_pattern_line_to);
  PLCAIRO_PRED_REG("cairo_mesh_pattern_move_to", 3, plcairo_mesh_pattern_move_to);
  PLCAIRO_PRED_REG("cairo_mesh_pattern_set_control_point", 4, plcairo_mesh_pattern_set_control_point);
  PLCAIRO_PRED_REG("cairo_mesh_pattern_set_corner_color_rgb", 5, plcairo_mesh_pattern_set_corner_color_rgb);
  PLCAIRO_PRED_REG("cairo_mesh_pattern_set_corner_color_rgba", 6, plcairo_mesh_pattern_set_corner_color_rgba);
  PLCAIRO_PRED_REG("cairo_pattern_set_extend", 2, plcairo_pattern_set_extend);
  PLCAIRO_PRED_REG("cairo_pattern_set_filter", 2, plcairo_pattern_set_filter);
  PLCAIRO_PRED_REG("cairo_pattern_set_matrix", 2, plcairo_pattern_set_matrix);

  /* Cairo Region */
  PLCAIRO_PRED_REG("cairo_region_contains_point", 3, plcairo_region_contains_point);
  PLCAIRO_PRED_REG("cairo_region_contains_rectangle", 3, plcairo_region_contains_rectangle);
  PLCAIRO_PRED_REG("cairo_region_create", 1, plcairo_region_create);
  PLCAIRO_PRED_REG("cairo_region_create_rectangle", 2, plcairo_region_create_rectangle);
  PLCAIRO_PRED_REG("cairo_region_create_rectangles", 2, plcairo_region_create_rectangles);
  PLCAIRO_PRED_REG("cairo_region_equal", 2, plcairo_region_equal);
  PLCAIRO_PRED_REG("cairo_region_get_extents", 2, plcairo_region_get_extents);
  PLCAIRO_PRED_REG("cairo_region_get_rectangle", 3, plcairo_region_get_rectangle);
  PLCAIRO_PRED_REG("cairo_region_intersect", 2, plcairo_region_intersect);
  PLCAIRO_PRED_REG("cairo_region_intersect_rectangle", 2, plcairo_region_intersect_rectangle);
  PLCAIRO_PRED_REG("cairo_region_is_empty", 1, plcairo_region_is_empty);
  PLCAIRO_PRED_REG("cairo_region_num_rectangles", 2, plcairo_region_num_rectangles);
  PLCAIRO_PRED_REG("cairo_region_subtract", 2, plcairo_region_subtract);
  PLCAIRO_PRED_REG("cairo_region_subtract_rectangle", 2, plcairo_region_subtract_rectangle);
  PLCAIRO_PRED_REG("cairo_region_translate", 3, plcairo_region_translate);
  PLCAIRO_PRED_REG("cairo_region_union", 2, plcairo_region_union);
  PLCAIRO_PRED_REG("cairo_region_union_rectangle", 2, plcairo_region_union_rectangle);
  PLCAIRO_PRED_REG("cairo_region_xor", 2, plcairo_region_xor);
  PLCAIRO_PRED_REG("cairo_region_xor_rectangle", 2, plcairo_region_xor_rectangle);

  /* Cairo Transformation */
  PLCAIRO_PRED_REG("cairo_device_to_user", 5, plcairo_device_to_user);
  PLCAIRO_PRED_REG("cairo_device_to_user_distance", 5, plcairo_device_to_user_distance);
  PLCAIRO_PRED_REG("cairo_get_matrix", 2, plcairo_get_matrix);
  PLCAIRO_PRED_REG("cairo_identity_matrix", 1, plcairo_identity_matrix);
  PLCAIRO_PRED_REG("cairo_rotate", 2, plcairo_rotate);
  PLCAIRO_PRED_REG("cairo_scale", 3, plcairo_scale);
  PLCAIRO_PRED_REG("cairo_set_matrix", 2, plcairo_set_matrix);
  PLCAIRO_PRED_REG("cairo_transform", 2, plcairo_transform);
  PLCAIRO_PRED_REG("cairo_translate", 3, plcairo_translate);
  PLCAIRO_PRED_REG("cairo_user_to_device", 5, plcairo_user_to_device);
  PLCAIRO_PRED_REG("cairo_user_to_device_distance", 5, plcairo_user_to_device_distance);

  /* Cairo Text */
  plcairo_register_glyph_t();
  plcairo_register_text_cluster_t();
  PLCAIRO_PRED_REG("cairo_font_extents", 2, plcairo_font_extents);
  PLCAIRO_PRED_REG("cairo_get_font_face", 2, plcairo_get_font_face);
  PLCAIRO_PRED_REG("cairo_get_font_matrix", 2, plcairo_get_font_matrix);
  PLCAIRO_PRED_REG("cairo_get_font_options", 2, plcairo_get_font_options);
  PLCAIRO_PRED_REG("cairo_get_scaled_font", 2, plcairo_get_scaled_font);
  PLCAIRO_PRED_REG("cairo_glyph_extents", 3, plcairo_glyph_extents);
  PLCAIRO_PRED_REG("cairo_select_font_face", 4, plcairo_select_font_face);
  PLCAIRO_PRED_REG("cairo_set_font_face", 2, plcairo_set_font_face);
  PLCAIRO_PRED_REG("cairo_set_font_matrix", 2, plcairo_set_font_matrix);
  PLCAIRO_PRED_REG("cairo_set_font_options", 2, plcairo_set_font_options);
  PLCAIRO_PRED_REG("cairo_set_font_size", 2, plcairo_set_font_size);
  PLCAIRO_PRED_REG("cairo_set_scaled_font", 2, plcairo_set_scaled_font);
  PLCAIRO_PRED_REG("cairo_show_glyphs", 2, plcairo_show_glyphs);
  PLCAIRO_PRED_REG("cairo_show_text", 2, plcairo_show_text);
  PLCAIRO_PRED_REG("cairo_show_text_glyphs", 5, plcairo_show_text_glyphs);
  PLCAIRO_PRED_REG("cairo_text_extents", 3, plcairo_text_extents);
  PLCAIRO_PRED_REG("cairo_toy_font_face_create", 4, plcairo_toy_font_face_create);
  PLCAIRO_PRED_REG("cairo_toy_font_face_get_family", 2, plcairo_toy_font_face_get_family);
  PLCAIRO_PRED_REG("cairo_toy_font_face_get_slant", 2, plcairo_toy_font_face_get_slant);
  PLCAIRO_PRED_REG("cairo_toy_font_face_get_weight", 2, plcairo_toy_font_face_get_weight);

  /* Cairo Raster Source */
  PLCAIRO_PRED_REG("cairo_pattern_create_raster_source", 4, plcairo_pattern_create_raster_source);

  /* Cairo Font Face */
  PLCAIRO_PRED_REG("cairo_font_face_get_type", 2, plcairo_font_face_get_type);

  /* Cairo Scaled Font */
  plcairo_register_font_extents_t();
  plcairo_register_text_extents_t();
  PLCAIRO_PRED_REG("cairo_scaled_font_create", 5, plcairo_scaled_font_create);
  PLCAIRO_PRED_REG("cairo_scaled_font_extents", 2, plcairo_scaled_font_extents);
  PLCAIRO_PRED_REG("cairo_scaled_font_get_ctm", 2, plcairo_scaled_font_get_ctm);
  PLCAIRO_PRED_REG("cairo_scaled_font_get_font_face", 2, plcairo_scaled_font_get_font_face);
  PLCAIRO_PRED_REG("cairo_scaled_font_get_font_matrix", 2, plcairo_scaled_font_get_font_matrix);
  PLCAIRO_PRED_REG("cairo_scaled_font_get_font_options", 2, plcairo_scaled_font_get_font_options);
  PLCAIRO_PRED_REG("cairo_scaled_font_get_scale_matrix", 2, plcairo_scaled_font_get_scale_matrix);
  PLCAIRO_PRED_REG("cairo_scaled_font_get_type", 2, plcairo_scaled_font_get_type);
  PLCAIRO_PRED_REG("cairo_scaled_font_glyph_extents", 3, plcairo_scaled_font_glyph_extents);
  PLCAIRO_PRED_REG("cairo_scaled_font_text_extents", 3, plcairo_scaled_font_text_extents);
  PLCAIRO_PRED_REG("cairo_scaled_font_text_to_glyphs", 7, plcairo_scaled_font_text_to_glyphs);

  /* Cairo Font Options */
  PLCAIRO_PRED_REG("cairo_font_options_create", 1, plcairo_font_options_create);
  PLCAIRO_PRED_REG("cairo_font_options_equal", 3, plcairo_font_options_equal);
  PLCAIRO_PRED_REG("cairo_font_options_get_antialias", 2, plcairo_font_options_get_antialias);
  PLCAIRO_PRED_REG("cairo_font_options_get_hint_metrics", 2, plcairo_font_options_get_hint_metrics);
  PLCAIRO_PRED_REG("cairo_font_options_get_hint_style", 2, plcairo_font_options_get_hint_style);
  PLCAIRO_PRED_REG("cairo_font_options_get_subpixel_order", 2, plcairo_font_options_get_subpixel_order);
  PLCAIRO_PRED_REG("cairo_font_options_hash", 2, plcairo_font_options_hash);
  PLCAIRO_PRED_REG("cairo_font_options_merge", 2, plcairo_font_options_merge);
  PLCAIRO_PRED_REG("cairo_font_options_set_antialias", 2, plcairo_font_options_set_antialias);
  PLCAIRO_PRED_REG("cairo_font_options_set_hint_metrics", 2, plcairo_font_options_set_hint_metrics);
  PLCAIRO_PRED_REG("cairo_font_options_set_hint_style", 2, plcairo_font_options_set_hint_style);
  PLCAIRO_PRED_REG("cairo_font_options_set_subpixel_order", 2, plcairo_font_options_set_subpixel_order);

  /* Cairo Device */
  PLCAIRO_PRED_REG("cairo_device_acquire", 1, plcairo_device_acquire);
  PLCAIRO_PRED_REG("cairo_device_finish", 1, plcairo_device_finish);
  PLCAIRO_PRED_REG("cairo_device_flush", 1, plcairo_device_flush);
  PLCAIRO_PRED_REG("cairo_device_get_type", 2, plcairo_device_get_type);
  PLCAIRO_PRED_REG("cairo_device_observer_elapsed", 2, plcairo_device_observer_elapsed);
  PLCAIRO_PRED_REG("cairo_device_observer_fill_elapsed", 2, plcairo_device_observer_fill_elapsed);
  PLCAIRO_PRED_REG("cairo_device_observer_glyphs_elapsed", 2, plcairo_device_observer_glyphs_elapsed);
  PLCAIRO_PRED_REG("cairo_device_observer_mask_elapsed", 2, plcairo_device_observer_mask_elapsed);
  PLCAIRO_PRED_REG("cairo_device_observer_paint_elapsed", 2, plcairo_device_observer_paint_elapsed);
  PLCAIRO_PRED_REG("cairo_device_observer_print", 3, plcairo_device_observer_print);
  PLCAIRO_PRED_REG("cairo_device_observer_stroke_elapsed", 2, plcairo_device_observer_stroke_elapsed);
  PLCAIRO_PRED_REG("cairo_device_release", 1, plcairo_device_release);

  /* Cairo Surface */
  PLCAIRO_PRED_REG("cairo_surface_copy_page", 1, plcairo_surface_copy_page);
  PLCAIRO_PRED_REG("cairo_surface_create_for_rectangle", 6, plcairo_surface_create_for_rectangle);
  PLCAIRO_PRED_REG("cairo_surface_create_similar", 5, plcairo_surface_create_similar);
  PLCAIRO_PRED_REG("cairo_surface_create_similar_image", 5, plcairo_surface_create_similar_image);
  PLCAIRO_PRED_REG("cairo_surface_finish", 1, plcairo_surface_finish);
  PLCAIRO_PRED_REG("cairo_surface_flush", 1, plcairo_surface_flush);
  PLCAIRO_PRED_REG("cairo_surface_get_content", 2, plcairo_surface_get_content);
  PLCAIRO_PRED_REG("cairo_surface_get_device", 2, plcairo_surface_get_device);
  PLCAIRO_PRED_REG("cairo_surface_get_device_offset", 3, plcairo_surface_get_device_offset);
  PLCAIRO_PRED_REG("cairo_surface_get_device_scale", 3, plcairo_surface_get_device_scale);
  PLCAIRO_PRED_REG("cairo_surface_get_fallback_resolution", 3, plcairo_surface_get_fallback_resolution);
  PLCAIRO_PRED_REG("cairo_surface_get_font_options", 2, plcairo_surface_get_font_options);
  PLCAIRO_PRED_REG("cairo_surface_get_type", 2, plcairo_surface_get_type);
  PLCAIRO_PRED_REG("cairo_surface_has_show_text_glyphs", 1, plcairo_surface_has_show_text_glyphs);
  PLCAIRO_PRED_REG("cairo_surface_map_to_image", 3, plcairo_surface_map_to_image);
  PLCAIRO_PRED_REG("cairo_surface_mark_dirty", 1, plcairo_surface_mark_dirty);
  PLCAIRO_PRED_REG("cairo_surface_mark_dirty_rectangle", 5, plcairo_surface_mark_dirty_rectangle);
  PLCAIRO_PRED_REG("cairo_surface_set_device_offset", 3, plcairo_surface_set_device_offset);
  PLCAIRO_PRED_REG("cairo_surface_set_device_scale", 3, plcairo_surface_set_device_scale);
  PLCAIRO_PRED_REG("cairo_surface_set_fallback_resolution", 3, plcairo_surface_set_fallback_resolution);
  PLCAIRO_PRED_REG("cairo_surface_show_page", 1, plcairo_surface_show_page);
  PLCAIRO_PRED_REG("cairo_surface_supports_mime_type", 2, plcairo_surface_supports_mime_type);
  PLCAIRO_PRED_REG("cairo_surface_unmap_image", 2, plcairo_surface_unmap_image);

  /* Cairo Image Surface */
  PLCAIRO_PRED_REG("cairo_image_surface_create", 4, plcairo_image_surface_create);
  PLCAIRO_PRED_REG("cairo_image_surface_get_format", 2, plcairo_image_surface_get_format);
  PLCAIRO_PRED_REG("cairo_image_surface_get_height", 2, plcairo_image_surface_get_height);
  PLCAIRO_PRED_REG("cairo_image_surface_get_stride", 2, plcairo_image_surface_get_stride);
  PLCAIRO_PRED_REG("cairo_image_surface_get_width", 2, plcairo_image_surface_get_width);

  /* Cairo PDF Surface */
  PLCAIRO_PRED_REG("cairo_pdf_get_versions", 1, plcairo_pdf_get_versions);
  PLCAIRO_PRED_REG("cairo_pdf_surface_create", 4, plcairo_pdf_surface_create);
  PLCAIRO_PRED_REG("cairo_pdf_surface_create_for_stream", 4, plcairo_pdf_surface_create_for_stream);
  PLCAIRO_PRED_REG("cairo_pdf_surface_restrict_to_version", 2, plcairo_pdf_surface_restrict_to_version);
  PLCAIRO_PRED_REG("cairo_pdf_surface_set_size", 3, plcairo_pdf_surface_set_size);
  PLCAIRO_PRED_REG("cairo_pdf_version_to_string", 2, plcairo_pdf_version_to_string);

  /* Cairo PNG Surface */
  PLCAIRO_PRED_REG("cairo_image_surface_create_from_png", 2, plcairo_image_surface_create_from_png);
  PLCAIRO_PRED_REG("cairo_image_surface_create_from_png_stream", 2, plcairo_image_surface_create_from_png_stream);
  PLCAIRO_PRED_REG("cairo_surface_write_to_png", 2, plcairo_surface_write_to_png);
  PLCAIRO_PRED_REG("cairo_surface_write_to_png_stream", 2, plcairo_surface_write_to_png_stream);

  /* Cairo PostScript Surface */
  PLCAIRO_PRED_REG("cairo_ps_get_levels", 1, plcairo_ps_get_levels);
  PLCAIRO_PRED_REG("cairo_ps_level_to_string", 2, plcairo_ps_level_to_string);
  PLCAIRO_PRED_REG("cairo_ps_surface_create", 4, plcairo_ps_surface_create);
  PLCAIRO_PRED_REG("cairo_ps_surface_create_for_stream", 4, plcairo_ps_surface_create_for_stream);
  PLCAIRO_PRED_REG("cairo_ps_surface_dsc_begin_page_setup", 1, plcairo_ps_surface_dsc_begin_page_setup);
  PLCAIRO_PRED_REG("cairo_ps_surface_dsc_begin_setup", 1, plcairo_ps_surface_dsc_begin_setup);
  PLCAIRO_PRED_REG("cairo_ps_surface_dsc_comment", 2, plcairo_ps_surface_dsc_comment);
  PLCAIRO_PRED_REG("cairo_ps_surface_get_eps", 2, plcairo_ps_surface_get_eps);
  PLCAIRO_PRED_REG("cairo_ps_surface_restrict_to_level", 2, plcairo_ps_surface_restrict_to_level);
  PLCAIRO_PRED_REG("cairo_ps_surface_set_eps", 2, plcairo_ps_surface_set_eps);
  PLCAIRO_PRED_REG("cairo_ps_surface_set_size", 3, plcairo_ps_surface_set_size);

  /* Cairo Recording Surface */
  PLCAIRO_PRED_REG("cairo_recording_surface_create", 3, plcairo_recording_surface_create);
  PLCAIRO_PRED_REG("cairo_recording_surface_get_extents", 2, plcairo_recording_surface_get_extents);
  PLCAIRO_PRED_REG("cairo_recording_surface_ink_extents", 5, plcairo_recording_surface_ink_extents);

  /* Cairo SVG Surface */
  PLCAIRO_PRED_REG("cairo_svg_get_versions", 1, plcairo_svg_get_versions);
  PLCAIRO_PRED_REG("cairo_svg_surface_create", 4, plcairo_svg_surface_create);
  PLCAIRO_PRED_REG("cairo_svg_surface_create_for_stream", 4, plcairo_svg_surface_create_for_stream);
  PLCAIRO_PRED_REG("cairo_svg_surface_restrict_to_version", 2, plcairo_svg_surface_restrict_to_version);
  PLCAIRO_PRED_REG("cairo_svg_version_to_string", 2, plcairo_svg_version_to_string);

  /* Cairo Script Surface */
  PLCAIRO_PRED_REG("cairo_script_create", 2, plcairo_script_create);
  PLCAIRO_PRED_REG("cairo_script_create_for_stream", 2, plcairo_script_create_for_stream);
  PLCAIRO_PRED_REG("cairo_script_from_recording_surface", 3, plcairo_script_from_recording_surface);
  PLCAIRO_PRED_REG("cairo_script_get_mode", 2, plcairo_script_get_mode);
  PLCAIRO_PRED_REG("cairo_script_set_mode", 2, plcairo_script_set_mode);
  PLCAIRO_PRED_REG("cairo_script_surface_create", 5, plcairo_script_surface_create);
  PLCAIRO_PRED_REG("cairo_script_surface_create_for_target", 3, plcairo_script_surface_create_for_target);
  PLCAIRO_PRED_REG("cairo_script_write_comment", 2, plcairo_script_write_comment);

  /* Cairo Matrix */
  plcairo_register_matrix_t();
  PLCAIRO_PRED_REG("cairo_matrix_init", 7, plcairo_matrix_init);
  PLCAIRO_PRED_REG("cairo_matrix_init_identity", 1, plcairo_matrix_init_identity);
  PLCAIRO_PRED_REG("cairo_matrix_init_rotate", 2, plcairo_matrix_init_rotate);
  PLCAIRO_PRED_REG("cairo_matrix_init_scale", 3, plcairo_matrix_init_scale);
  PLCAIRO_PRED_REG("cairo_matrix_init_translate", 3, plcairo_matrix_init_translate);
  PLCAIRO_PRED_REG("cairo_matrix_invert", 1, plcairo_matrix_invert);
  PLCAIRO_PRED_REG("cairo_matrix_multiply", 3, plcairo_matrix_multiply);
  PLCAIRO_PRED_REG("cairo_matrix_rotate", 2, plcairo_matrix_rotate);
  PLCAIRO_PRED_REG("cairo_matrix_scale", 3, plcairo_matrix_scale);
  PLCAIRO_PRED_REG("cairo_matrix_transform_distance", 5, plcairo_matrix_transform_distance);
  PLCAIRO_PRED_REG("cairo_matrix_transform_point", 5, plcairo_matrix_transform_point);
  PLCAIRO_PRED_REG("cairo_matrix_translate", 3, plcairo_matrix_translate);

  /* Cairo Rectangle */
  plcairo_register_rectangle_int_t();

  /* PLcairo Specific */
  PLCAIRO_PRED_REG("plcairo_debug", 1, plcairo_debug);
  PLCAIRO_PRED_REG("plcairo_version", 1, plcairo_version);

  PL_on_halt(plcairo_exit_debug, NULL);
}
