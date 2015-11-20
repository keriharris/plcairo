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


/* cairo_region_t */
cairo_bool_t
plcairo_term_to_region(term_t           t,
                       cairo_region_t **region)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_region_t: %p", t, *region);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoRegion", t);
  }

  if ( blob->gtype != G_TYPE_NONE &&
       !g_type_is_a( blob->gtype, CAIRO_GOBJECT_TYPE_REGION ) )
  { return PL_type_error("CairoRegion", t);
  }

  *region = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_region_to_term(cairo_region_t *region,
                       term_t          t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_region_t: %p  --->  term: 0x%lx", region, t);

  if ( !region )
  { return ( plgi_put_null(t0) && PL_unify(t, t0) );
  }

  data = region;
  blob_type = PLGI_BLOB_BOXED;

  if ( !plgi_put_blob(blob_type, CAIRO_GOBJECT_TYPE_REGION,
                      PL_new_atom("Cairoregion"), TRUE, data, t0) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}


/* cairo_region_overlap_t */
static atom_t ATOM_cairo_region_overlap_in = 0;
static atom_t ATOM_cairo_region_overlap_out = 0;
static atom_t ATOM_cairo_region_overlap_part = 0;

cairo_bool_t
plcairo_term_to_region_overlap(term_t                  t,
                               cairo_region_overlap_t *region_overlap)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_region_overlap_t: %p", t, region_overlap);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoRegionOverlap", t);
  }

  if ( !ATOM_cairo_region_overlap_in )
  {
    ATOM_cairo_region_overlap_in = PL_new_atom("CAIRO_REGION_OVERLAP_IN");
    ATOM_cairo_region_overlap_out = PL_new_atom("CAIRO_REGION_OVERLAP_OUT");
    ATOM_cairo_region_overlap_part = PL_new_atom("CAIRO_REGION_OVERLAP_PART");
  }

  if ( a == ATOM_cairo_region_overlap_in )
  { *region_overlap = CAIRO_REGION_OVERLAP_IN;
  }
  else if ( a == ATOM_cairo_region_overlap_out )
  { *region_overlap = CAIRO_REGION_OVERLAP_OUT;
  }
  else if ( a == ATOM_cairo_region_overlap_part )
  { *region_overlap = CAIRO_REGION_OVERLAP_PART;
  }
  else
  { return PL_domain_error("CairoRegionOverlap", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_region_overlap_to_term(cairo_region_overlap_t region_overlap,
                               term_t                 t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_region_overlap_t: %d  --->  term: 0x%lx", region_overlap, t);

  if ( !ATOM_cairo_region_overlap_in )
  {
    ATOM_cairo_region_overlap_in = PL_new_atom("CAIRO_REGION_OVERLAP_IN");
    ATOM_cairo_region_overlap_out = PL_new_atom("CAIRO_REGION_OVERLAP_OUT");
    ATOM_cairo_region_overlap_part = PL_new_atom("CAIRO_REGION_OVERLAP_PART");
  }

  if ( region_overlap == CAIRO_REGION_OVERLAP_IN )
  { PL_put_atom(t0, ATOM_cairo_region_overlap_in);
  }
  else if ( region_overlap == CAIRO_REGION_OVERLAP_OUT )
  { PL_put_atom(t0, ATOM_cairo_region_overlap_out);
  }
  else if ( region_overlap == CAIRO_REGION_OVERLAP_PART )
  { PL_put_atom(t0, ATOM_cairo_region_overlap_part);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}


// FIXME: move to cairo_types
/* cairo_rectangle_int_t */
void plcairo_register_rectangle_int_t(void)
{
  PLGIStructInfo *struct_info;
  PLGIFieldInfo *field_info;
  int n_fields, offset;

  PLCAIRO_debug("registering struct: CairoRectangleInt");

  n_fields = 6;
  offset = 0;

  struct_info = g_malloc0(sizeof(*struct_info));
  struct_info->info = NULL;
  struct_info->namespace = PL_new_atom("cairo");
  struct_info->name = PL_new_atom("CairoRectangleInt");
  struct_info->gtype = CAIRO_GOBJECT_TYPE_RECTANGLE_INT;
  struct_info->size = sizeof(cairo_rectangle_int_t);
  struct_info->n_fields = n_fields;
  struct_info->fields_info = g_malloc0_n(n_fields, sizeof(*struct_info->fields_info));

  plcairo_alloc_struct_int_field(0, "x");
  plcairo_alloc_struct_int_field(1, "y");
  plcairo_alloc_struct_int_field(2, "width");
  plcairo_alloc_struct_int_field(3, "height");

  plgi_cache_struct_info(struct_info);
}

cairo_bool_t
plcairo_term_to_rectangle_int(term_t                  t,
                              cairo_rectangle_int_t **rectangle)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_rectangle_int_t: %p", t, *rectangle);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoRectangleInt", t);
  }

  if ( blob->gtype != G_TYPE_NONE &&
       !g_type_is_a( blob->gtype, CAIRO_GOBJECT_TYPE_RECTANGLE_INT ) )
  { return PL_type_error("CairoRectangleInt", t);
  }

  *rectangle = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_rectangle_int_to_term(cairo_rectangle_int_t *rectangle,
                              term_t                 t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_rectangle_int_t: %p  --->  term: 0x%lx", rectangle, t);

  if ( !rectangle )
  { return ( plgi_put_null(t0) && PL_unify(t, t0) );
  }

  data = rectangle;
  blob_type = PLGI_BLOB_BOXED;

  if ( !plgi_put_blob(blob_type, CAIRO_GOBJECT_TYPE_RECTANGLE_INT,
                      PL_new_atom("CairoRectangleInt"), TRUE, data, t0) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLGI_PRED_IMPL(plcairo_region_contains_point)
{
  term_t t_region = FA0;
  term_t t_x = FA1;
  term_t t_y = FA2;

  cairo_region_t *region;
  int x, y;
  cairo_bool_t ret;

  if ( !plcairo_term_to_region(t_region, &region) ) return FALSE;
  if ( !plcairo_term_to_int(t_x, &x) ) return FALSE;
  if ( !plcairo_term_to_int(t_y, &y) ) return FALSE;

  ret = cairo_region_contains_point(region, x, y);
  PLCAIRO_CHECK_REGION(region);

  return (ret != 0);
}


PLGI_PRED_IMPL(plcairo_region_contains_rectangle)
{
  term_t t_region = FA0;
  term_t t_rectangle = FA1;
  term_t t_overlap = FA2;

  cairo_region_t *region;
  cairo_rectangle_int_t *rectangle;
  cairo_region_overlap_t overlap;

  if ( !plcairo_term_to_region(t_region, &region) ) return FALSE;
  if ( !plcairo_term_to_rectangle_int(t_rectangle, &rectangle) ) return FALSE;

  overlap = cairo_region_contains_rectangle(region, rectangle);
  PLCAIRO_CHECK_REGION(region);

  if ( !plcairo_region_overlap_to_term(overlap, t_overlap) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_create)
{
  term_t t_region = FA0;

  cairo_region_t *region;

  region = cairo_region_create();
  PLCAIRO_CHECK_REGION(region);

  if ( !plcairo_region_to_term(region, t_region) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_create_rectangle)
{
  term_t t_rectangle = FA0;
  term_t t_region = FA1;

  cairo_rectangle_int_t *rectangle;
  cairo_region_t *region;

  if ( !plcairo_term_to_rectangle_int(t_rectangle, &rectangle) ) return FALSE;

  region = cairo_region_create_rectangle(rectangle);
  PLCAIRO_CHECK_REGION(region);

  if ( !plcairo_region_to_term(region, t_region) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_create_rectangles)
{
  term_t t_rectangles = FA0;
  term_t t_region = FA1;

  cairo_rectangle_int_t *rectangles;
  int num_rectangles;
  size_t len;
  cairo_region_t *region;
  term_t list = PL_copy_term_ref(t_rectangles);
  term_t head = PL_new_term_ref();
  int i = 0;

  if ( PL_skip_list(list, 0, &len) != PL_LIST )
  { return PL_type_error("list", t_rectangles);
  }

  num_rectangles = len;
  rectangles = g_malloc0_n(num_rectangles, sizeof(cairo_rectangle_int_t));

  while ( PL_get_list(list, head, list) )
  { cairo_rectangle_int_t *rectangle = rectangles + i++;

    if ( !plcairo_term_to_rectangle_int(head, &rectangle) )
    { g_free(rectangles);
      return PL_type_error("CairoRectangleInt", head);
    }
  }

  region = cairo_region_create_rectangles(rectangles, num_rectangles);
  g_free(rectangles);
  PLCAIRO_CHECK_REGION(region);

  if ( !plcairo_region_to_term(region, t_region) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_equal)
{
  term_t t_a = FA0;
  term_t t_b = FA1;

  cairo_region_t *a, *b;
  cairo_bool_t ret;

  if ( !plcairo_term_to_region(t_a, &a) ) return FALSE;
  if ( !plcairo_term_to_region(t_b, &b) ) return FALSE;

  ret = cairo_region_equal(a, b);
  PLCAIRO_CHECK_REGION(a);
  PLCAIRO_CHECK_REGION(b);

  return (ret != 0);
}


PLGI_PRED_IMPL(plcairo_region_get_extents)
{
  term_t t_region = FA0;
  term_t t_extents = FA1;

  cairo_region_t *region;
  cairo_rectangle_int_t extents;

  if ( !plcairo_term_to_region(t_region, &region) ) return FALSE;

  cairo_region_get_extents(region, &extents);
  PLCAIRO_CHECK_REGION(region);

  if ( !plcairo_rectangle_int_to_term(&extents, t_extents) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_get_rectangle)
{
  term_t t_region = FA0;
  term_t t_nth = FA1;
  term_t t_rectangle = FA1;

  cairo_region_t *region;
  int nth;
  cairo_rectangle_int_t rectangle;

  if ( !plcairo_term_to_region(t_region, &region) ) return FALSE;
  if ( !plcairo_term_to_int(t_nth, &nth) ) return FALSE;

  cairo_region_get_rectangle(region, nth, &rectangle);
  PLCAIRO_CHECK_REGION(region);

  if ( !plcairo_rectangle_int_to_term(&rectangle, t_rectangle) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_intersect)
{
  term_t t_dst = FA0;
  term_t t_other = FA2;

  cairo_region_t *dst, *other;
  cairo_status_t status;

  if ( !plcairo_term_to_region(t_dst, &dst) ) return FALSE;
  if ( !plcairo_term_to_region(t_other, &other) ) return FALSE;

  status = cairo_region_intersect(dst, other);
  PLCAIRO_CHECK_REGION(dst);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_intersect_rectangle)
{
  term_t t_dst = FA0;
  term_t t_rectangle = FA2;

  cairo_region_t *dst;
  cairo_rectangle_int_t *rectangle;
  cairo_status_t status;

  if ( !plcairo_term_to_region(t_dst, &dst) ) return FALSE;
  if ( !plcairo_term_to_rectangle_int(t_rectangle, &rectangle) ) return FALSE;

  status = cairo_region_intersect_rectangle(dst, rectangle);
  PLCAIRO_CHECK_REGION(dst);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_is_empty)
{
  term_t t_region = FA0;

  cairo_region_t *region;
  cairo_bool_t ret;

  if ( !plcairo_term_to_region(t_region, &region) ) return FALSE;

  ret = cairo_region_is_empty(region);
  PLCAIRO_CHECK_REGION(region);

  return (ret != 0);
}


PLGI_PRED_IMPL(plcairo_region_num_rectangles)
{
  term_t t_region = FA0;
  term_t t_num_rectangles = FA1;

  cairo_region_t *region;
  int num_rectangles;

  if ( !plcairo_term_to_region(t_region, &region) ) return FALSE;

  num_rectangles = cairo_region_num_rectangles(region);
  PLCAIRO_CHECK_REGION(region);

  if ( !plcairo_int_to_term(num_rectangles, t_num_rectangles) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_subtract)
{
  term_t t_dst = FA0;
  term_t t_other = FA2;

  cairo_region_t *dst, *other;
  cairo_status_t status;

  if ( !plcairo_term_to_region(t_dst, &dst) ) return FALSE;
  if ( !plcairo_term_to_region(t_other, &other) ) return FALSE;

  status = cairo_region_subtract(dst, other);
  PLCAIRO_CHECK_REGION(dst);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_subtract_rectangle)
{
  term_t t_dst = FA0;
  term_t t_rectangle = FA2;

  cairo_region_t *dst;
  cairo_rectangle_int_t *rectangle;
  cairo_status_t status;

  if ( !plcairo_term_to_region(t_dst, &dst) ) return FALSE;
  if ( !plcairo_term_to_rectangle_int(t_rectangle, &rectangle) ) return FALSE;

  status = cairo_region_subtract_rectangle(dst, rectangle);
  PLCAIRO_CHECK_REGION(dst);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_translate)
{
  term_t t_region = FA0;
  term_t t_dx = FA1;
  term_t t_dy = FA2;

  cairo_region_t *region;
  int dx, dy;

  if ( !plcairo_term_to_region(t_region, &region) ) return FALSE;
  if ( !plcairo_term_to_int(t_dx, &dx) ) return FALSE;
  if ( !plcairo_term_to_int(t_dy, &dy) ) return FALSE;

  cairo_region_translate(region, dx, dy);
  PLCAIRO_CHECK_REGION(region);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_union)
{
  term_t t_dst = FA0;
  term_t t_other = FA2;

  cairo_region_t *dst, *other;
  cairo_status_t status;

  if ( !plcairo_term_to_region(t_dst, &dst) ) return FALSE;
  if ( !plcairo_term_to_region(t_other, &other) ) return FALSE;

  status = cairo_region_union(dst, other);
  PLCAIRO_CHECK_REGION(dst);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_union_rectangle)
{
  term_t t_dst = FA0;
  term_t t_rectangle = FA2;

  cairo_region_t *dst;
  cairo_rectangle_int_t *rectangle;
  cairo_status_t status;

  if ( !plcairo_term_to_region(t_dst, &dst) ) return FALSE;
  if ( !plcairo_term_to_rectangle_int(t_rectangle, &rectangle) ) return FALSE;

  status = cairo_region_union_rectangle(dst, rectangle);
  PLCAIRO_CHECK_REGION(dst);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_xor)
{
  term_t t_dst = FA0;
  term_t t_other = FA2;

  cairo_region_t *dst, *other;
  cairo_status_t status;

  if ( !plcairo_term_to_region(t_dst, &dst) ) return FALSE;
  if ( !plcairo_term_to_region(t_other, &other) ) return FALSE;

  status = cairo_region_xor(dst, other);
  PLCAIRO_CHECK_REGION(dst);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_region_xor_rectangle)
{
  term_t t_dst = FA0;
  term_t t_rectangle = FA2;

  cairo_region_t *dst;
  cairo_rectangle_int_t *rectangle;
  cairo_status_t status;

  if ( !plcairo_term_to_region(t_dst, &dst) ) return FALSE;
  if ( !plcairo_term_to_rectangle_int(t_rectangle, &rectangle) ) return FALSE;

  status = cairo_region_xor_rectangle(dst, rectangle);
  PLCAIRO_CHECK_REGION(dst);
  if ( status != CAIRO_STATUS_SUCCESS )
  { plcairo_raise_error_status(status);
  }

  return TRUE;
}
