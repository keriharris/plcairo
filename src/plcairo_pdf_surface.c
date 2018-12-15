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

#ifdef CAIRO_HAS_PDF_SURFACE
#include <cairo-pdf.h>


/* cairo_pdf_metadata_t */
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 16, 0)
static atom_t ATOM_cairo_pdf_metadata_title = 0;
static atom_t ATOM_cairo_pdf_metadata_author = 0;
static atom_t ATOM_cairo_pdf_metadata_subject = 0;
static atom_t ATOM_cairo_pdf_metadata_keywords = 0;
static atom_t ATOM_cairo_pdf_metadata_creator = 0;
static atom_t ATOM_cairo_pdf_metadata_create_date = 0;
static atom_t ATOM_cairo_pdf_metadata_mod_date = 0;

cairo_bool_t
plcairo_term_to_pdf_metadata(term_t                t,
                             cairo_pdf_metadata_t *metadata)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_pdf_metadata_t: %p", t, metadata);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoPdfMetadata", t);
  }

  if ( !ATOM_cairo_pdf_metadata_title )
  {
    ATOM_cairo_pdf_metadata_title = PL_new_atom("CAIRO_PDF_METADATA_TITLE");
    ATOM_cairo_pdf_metadata_author = PL_new_atom("CAIRO_PDF_METADATA_AUTHOR");
    ATOM_cairo_pdf_metadata_subject = PL_new_atom("CAIRO_PDF_METADATA_SUBJECT");
    ATOM_cairo_pdf_metadata_keywords = PL_new_atom("CAIRO_PDF_METADATA_KEYWORDS");
    ATOM_cairo_pdf_metadata_creator = PL_new_atom("CAIRO_PDF_METADATA_CREATOR");
    ATOM_cairo_pdf_metadata_create_date = PL_new_atom("CAIRO_PDF_METADATA_CREATE_DATE");
    ATOM_cairo_pdf_metadata_mod_date = PL_new_atom("CAIRO_PDF_METADATA_MOD_DATE");
  }

  if ( a == ATOM_cairo_pdf_metadata_title )
  { *metadata = CAIRO_PDF_METADATA_TITLE;
  }
  else if ( a == ATOM_cairo_pdf_metadata_author )
  { *metadata = CAIRO_PDF_METADATA_AUTHOR;
  }
  else if ( a == ATOM_cairo_pdf_metadata_subject )
  { *metadata = CAIRO_PDF_METADATA_SUBJECT;
  }
  else if ( a == ATOM_cairo_pdf_metadata_keywords )
  { *metadata = CAIRO_PDF_METADATA_KEYWORDS;
  }
  else if ( a == ATOM_cairo_pdf_metadata_creator )
  { *metadata = CAIRO_PDF_METADATA_CREATOR;
  }
  else if ( a == ATOM_cairo_pdf_metadata_create_date )
  { *metadata = CAIRO_PDF_METADATA_CREATE_DATE;
  }
  else if ( a == ATOM_cairo_pdf_metadata_mod_date )
  { *metadata = CAIRO_PDF_METADATA_MOD_DATE;
  }
  else
  { return PL_domain_error("CairoPdfMetadata", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_pdf_metadata_to_term(cairo_pdf_metadata_t metadata,
                             term_t               t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_pdf_metadata_t: %d  --->  term: 0x%lx", metadata, t);

  if ( !ATOM_cairo_pdf_metadata_title )
  {
    ATOM_cairo_pdf_metadata_title = PL_new_atom("CAIRO_PDF_METADATA_TITLE");
    ATOM_cairo_pdf_metadata_author = PL_new_atom("CAIRO_PDF_METADATA_AUTHOR");
    ATOM_cairo_pdf_metadata_subject = PL_new_atom("CAIRO_PDF_METADATA_SUBJECT");
    ATOM_cairo_pdf_metadata_keywords = PL_new_atom("CAIRO_PDF_METADATA_KEYWORDS");
    ATOM_cairo_pdf_metadata_creator = PL_new_atom("CAIRO_PDF_METADATA_CREATOR");
    ATOM_cairo_pdf_metadata_create_date = PL_new_atom("CAIRO_PDF_METADATA_CREATE_DATE");
    ATOM_cairo_pdf_metadata_mod_date = PL_new_atom("CAIRO_PDF_METADATA_MOD_DATE");
  }

  if ( metadata == CAIRO_PDF_METADATA_TITLE )
  { PL_put_atom(t0, ATOM_cairo_pdf_metadata_title);
  }
  else if ( metadata == CAIRO_PDF_METADATA_AUTHOR )
  { PL_put_atom(t0, ATOM_cairo_pdf_metadata_author);
  }
  else if ( metadata == CAIRO_PDF_METADATA_SUBJECT )
  { PL_put_atom(t0, ATOM_cairo_pdf_metadata_subject);
  }
  else if ( metadata == CAIRO_PDF_METADATA_KEYWORDS )
  { PL_put_atom(t0, ATOM_cairo_pdf_metadata_keywords);
  }
  else if ( metadata == CAIRO_PDF_METADATA_CREATOR )
  { PL_put_atom(t0, ATOM_cairo_pdf_metadata_creator);
  }
  else if ( metadata == CAIRO_PDF_METADATA_CREATE_DATE )
  { PL_put_atom(t0, ATOM_cairo_pdf_metadata_create_date);
  }
  else if ( metadata == CAIRO_PDF_METADATA_MOD_DATE )
  { PL_put_atom(t0, ATOM_cairo_pdf_metadata_mod_date);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}
#endif


/* cairo_pdf_outline_flags_t */
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 16, 0)
static atom_t ATOM_cairo_pdf_outline_flag_open = 0;
static atom_t ATOM_cairo_pdf_outline_flag_bold = 0;
static atom_t ATOM_cairo_pdf_outline_flag_italic = 0;

cairo_bool_t
plcairo_term_to_pdf_outline_flags(term_t                     t,
                                  cairo_pdf_outline_flags_t *flags)
{
  term_t list = PL_copy_term_ref(t);
  term_t head = PL_new_term_ref();
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_pdf_outline_flags_t: %p", t, flags);

  if ( !ATOM_cairo_pdf_outline_flag_open )
  {
    ATOM_cairo_pdf_outline_flag_open = PL_new_atom("CAIRO_PDF_OUTLINE_FLAG_OPEN");
    ATOM_cairo_pdf_outline_flag_bold = PL_new_atom("CAIRO_PDF_OUTLINE_FLAG_BOLD");
    ATOM_cairo_pdf_outline_flag_italic = PL_new_atom("CAIRO_PDF_OUTLINE_FLAG_ITALIC");
  }

  if ( PL_skip_list(list, 0, NULL) != PL_LIST )
  { return PL_type_error("list", t);
  }

  *flags = 0;
  while ( PL_get_list(list, head, list) )
  {
    if ( !PL_get_atom(head, &a) )
    { return PL_type_error("CairoPdfOutlineFlags", head);
    }

    if ( a == ATOM_cairo_pdf_outline_flag_open )
    { *flags |= CAIRO_PDF_OUTLINE_FLAG_OPEN;
    }
    else if ( a == ATOM_cairo_pdf_outline_flag_bold )
    { *flags |= CAIRO_PDF_OUTLINE_FLAG_BOLD;
    }
    else if ( a == ATOM_cairo_pdf_outline_flag_italic )
    { *flags |= CAIRO_PDF_OUTLINE_FLAG_ITALIC;
    }
    else
    { return PL_domain_error("CairoPdfOutlineFlags", t);
    }
  }

  return TRUE;
}

cairo_bool_t
plcairo_pdf_outline_flags_to_term(cairo_pdf_outline_flags_t flags,
                                  term_t                    t)
{
  term_t t0 = PL_new_term_ref();
  term_t list = PL_copy_term_ref(t0);
  term_t head = PL_new_term_ref();

  PLCAIRO_debug("    cairo_pdf_outline_flags_t: %d  --->  term: 0x%lx", flags, t);

  if ( !ATOM_cairo_pdf_outline_flag_open )
  {
    ATOM_cairo_pdf_outline_flag_open = PL_new_atom("CAIRO_PDF_OUTLINE_FLAG_OPEN");
    ATOM_cairo_pdf_outline_flag_bold = PL_new_atom("CAIRO_PDF_OUTLINE_FLAG_BOLD");
    ATOM_cairo_pdf_outline_flag_italic = PL_new_atom("CAIRO_PDF_OUTLINE_FLAG_ITALIC");
  }

  if ( flags & CAIRO_PDF_OUTLINE_FLAG_OPEN )
  { term_t a = PL_new_term_ref();
    PL_put_atom(a, ATOM_cairo_pdf_outline_flag_open);
    if ( !(PL_unify_list(list, head, list) &&
           PL_unify(head, a)) )
    { return FALSE;
    }
  }
  if ( flags & CAIRO_PDF_OUTLINE_FLAG_BOLD )
  { term_t a = PL_new_term_ref();
    PL_put_atom(a, ATOM_cairo_pdf_outline_flag_bold);
    if ( !(PL_unify_list(list, head, list) &&
           PL_unify(head, a)) )
    { return FALSE;
    }
  }
  if ( flags & CAIRO_PDF_OUTLINE_FLAG_ITALIC )
  { term_t a = PL_new_term_ref();
    PL_put_atom(a, ATOM_cairo_pdf_outline_flag_italic);
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
#endif


/* cairo_pdf_version_t */
static atom_t ATOM_cairo_pdf_version_1_4 = 0;
static atom_t ATOM_cairo_pdf_version_1_5 = 0;

cairo_bool_t
plcairo_term_to_pdf_version(term_t               t,
                            cairo_pdf_version_t *version)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_pdf_version_t: %p", t, version);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoPdfVersion", t);
  }

  if ( !ATOM_cairo_pdf_version_1_4 )
  {
    ATOM_cairo_pdf_version_1_4 = PL_new_atom("CAIRO_PDF_VERSION_1_4");
    ATOM_cairo_pdf_version_1_5 = PL_new_atom("CAIRO_PDF_VERSION_1_5");
  }

  if ( a == ATOM_cairo_pdf_version_1_4 )
  { *version = CAIRO_PDF_VERSION_1_4;
  }
  else if ( a == ATOM_cairo_pdf_version_1_5 )
  { *version = CAIRO_PDF_VERSION_1_5;
  }
  else
  { return PL_domain_error("CairoPdfVersion", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_pdf_version_to_term(cairo_pdf_version_t version,
                            term_t              t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_pdf_version_t: %d  --->  term: 0x%lx", version, t);

  if ( !ATOM_cairo_pdf_version_1_4 )
  {
    ATOM_cairo_pdf_version_1_4 = PL_new_atom("CAIRO_PDF_VERSION_1_4");
    ATOM_cairo_pdf_version_1_5 = PL_new_atom("CAIRO_PDF_VERSION_1_5");
  }

  if ( version == CAIRO_PDF_VERSION_1_4 )
  { PL_put_atom(t0, ATOM_cairo_pdf_version_1_4);
  }
  else if ( version == CAIRO_PDF_VERSION_1_5 )
  { PL_put_atom(t0, ATOM_cairo_pdf_version_1_5);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLCAIRO_PRED_IMPL(plcairo_pdf_get_versions)
{
  term_t t_versions = FA0;

  const cairo_pdf_version_t *versions;
  int num_versions;
  term_t list = PL_copy_term_ref(t_versions);
  term_t head = PL_new_term_ref();
  int i;

  cairo_pdf_get_versions(&versions, &num_versions);

  for ( i = 0; i < num_versions; i++ )
  {
    cairo_pdf_version_t version = versions[i];
    term_t a = PL_new_term_ref();

    if ( !plcairo_pdf_version_to_term(version, a) ) return FALSE;
    if ( !(PL_unify_list(list, head, list) &&
           PL_unify(head, a)) )
    { return FALSE;
    }
  }

  if ( !PL_unify_nil(list) )
  { return FALSE;
  }

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_pdf_surface_add_outline)
{
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 16, 0)
  term_t t_surface = FA0;
  term_t t_parent_id = FA1;
  term_t t_name = FA2;
  term_t t_link_attribs = FA3;
  term_t t_flags = FA4;
  term_t t_id = FA5;

  cairo_surface_t *surface;
  int parent_id;
  char *name;
  char *link_attribs;
  cairo_pdf_outline_flags_t flags;
  int id;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_int(t_parent_id, &parent_id) ) return FALSE;
  if ( !plcairo_term_to_string(t_name, &name) ) return FALSE;
  if ( !plcairo_term_to_string(t_link_attribs, &link_attribs) ) return FALSE;
  if ( !plcairo_term_to_pdf_outline_flags(t_flags, &flags) ) return FALSE;

  id = cairo_pdf_surface_add_outline(surface, parent_id, name, link_attribs, flags);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_int_to_term(id, t_id) ) return FALSE;

  return TRUE;
#else
  return plcairo_raise_error("cairo_pdf_surface_add_outline/6 requires Cairo >= v1.16");
#endif
}


PLCAIRO_PRED_IMPL(plcairo_pdf_surface_create)
{
  term_t t_filename = FA0;
  term_t t_width_in_points = FA1;
  term_t t_height_in_points = FA2;
  term_t t_surface = FA3;

  char *filename;
  double width_in_points, height_in_points;
  cairo_surface_t *surface;

  if ( !plcairo_term_to_string(t_filename, &filename) ) return FALSE;
  if ( !plcairo_term_to_double(t_width_in_points, &width_in_points) ) return FALSE;
  if ( !plcairo_term_to_double(t_height_in_points, &height_in_points) ) return FALSE;

  surface = cairo_pdf_surface_create(filename, width_in_points, height_in_points);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_pdf_surface_create_for_stream)
{
  term_t t_stream = FA0;
  term_t t_width_in_points = FA1;
  term_t t_height_in_points = FA2;
  term_t t_surface = FA3;

  void *closure;
  double width_in_points, height_in_points;
  cairo_surface_t *surface;

  if ( !plcairo_term_to_closure(t_stream, &closure) ) return FALSE;
  if ( !plcairo_term_to_double(t_width_in_points, &width_in_points) ) return FALSE;
  if ( !plcairo_term_to_double(t_height_in_points, &height_in_points) ) return FALSE;

  surface = cairo_pdf_surface_create_for_stream(&plcairo_write_func, closure, width_in_points, height_in_points);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_pdf_surface_restrict_to_version)
{
  term_t t_surface = FA0;
  term_t t_version = FA1;

  cairo_surface_t *surface;
  cairo_pdf_version_t version;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_pdf_version(t_version, &version) ) return FALSE;

  cairo_pdf_surface_restrict_to_version(surface, version);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_pdf_surface_set_metadata)
{
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 16, 0)
  term_t t_surface = FA0;
  term_t t_metadata = FA1;
  term_t t_value = FA2;

  cairo_surface_t *surface;
  cairo_pdf_metadata_t metadata;
  char *value;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_pdf_metadata(t_metadata, &metadata) ) return FALSE;
  if ( !plcairo_term_to_string(t_value, &value) ) return FALSE;

  cairo_pdf_surface_set_metadata(surface, metadata, value);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
#else
  return plcairo_raise_error("cairo_pdf_surface_set_metadata/3 requires Cairo >= v1.16");
#endif
}


PLCAIRO_PRED_IMPL(plcairo_pdf_surface_set_page_label)
{
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 16, 0)
  term_t t_surface = FA0;
  term_t t_label = FA1;

  cairo_surface_t *surface;
  char *label;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_string(t_label, &label) ) return FALSE;

  cairo_pdf_surface_set_page_label(surface, label);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
#else
  return plcairo_raise_error("cairo_pdf_surface_set_page_label/2 requires Cairo >= v1.16");
#endif
}


PLCAIRO_PRED_IMPL(plcairo_pdf_surface_set_size)
{
  term_t t_surface = FA0;
  term_t t_width_in_points = FA1;
  term_t t_height_in_points = FA2;

  cairo_surface_t *surface;
  double width_in_points, height_in_points;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_double(t_width_in_points, &width_in_points) ) return FALSE;
  if ( !plcairo_term_to_double(t_height_in_points, &height_in_points) ) return FALSE;

  cairo_pdf_surface_set_size(surface, width_in_points, height_in_points);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLCAIRO_PRED_IMPL(plcairo_pdf_surface_set_thumbnail_size)
{
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 16, 0)
  term_t t_surface = FA0;
  term_t t_width = FA1;
  term_t t_height = FA2;

  cairo_surface_t *surface;
  int width, height;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_int(t_width, &width) ) return FALSE;
  if ( !plcairo_term_to_int(t_height, &height) ) return FALSE;

  cairo_pdf_surface_set_thumbnail_size(surface, width, height);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
#else
  return plcairo_raise_error("cairo_pdf_surface_set_thumbnail_size/3 requires Cairo >= v1.16");
#endif
}


PLCAIRO_PRED_IMPL(plcairo_pdf_version_to_string)
{
  term_t t_version = FA0;
  term_t t_string = FA1;

  cairo_pdf_version_t version;
  const char *string;

  if ( !plcairo_term_to_pdf_version(t_version, &version) ) return FALSE;

  string = cairo_pdf_version_to_string(version);

  if ( !plcairo_string_to_term((char*)string, t_string) ) return FALSE;

  return TRUE;
}

#else

PLCAIRO_PRED_IMPL(plcairo_pdf_get_versions)
{ return plcairo_raise_error("cairo_pdf_get_versions/1 not supported");
}

PLCAIRO_PRED_IMPL(plcairo_pdf_surface_add_outline)
{ return plcairo_raise_error("cairo_pdf_surface_add_outline/6 not supported");
}

PLCAIRO_PRED_IMPL(plcairo_pdf_surface_create)
{ return plcairo_raise_error("cairo_pdf_surface_create/4 not supported");
}

PLCAIRO_PRED_IMPL(plcairo_pdf_surface_create_for_stream)
{ return plcairo_raise_error("cairo_pdf_surface_create_for_stream/4 not supported");
}

PLCAIRO_PRED_IMPL(plcairo_pdf_surface_restrict_to_version)
{ return plcairo_raise_error("cairo_pdf_surface_restrict_to_version/2 not supported");
}

PLCAIRO_PRED_IMPL(plcairo_pdf_surface_set_metadata)
{ return plcairo_raise_error("cairo_pdf_surface_set_metadata/3 not supported");
}

PLCAIRO_PRED_IMPL(plcairo_pdf_surface_set_page_label)
{ return plcairo_raise_error("cairo_pdf_surface_set_page_label/2 not supported");
}

PLCAIRO_PRED_IMPL(plcairo_pdf_surface_set_size)
{ return plcairo_raise_error("cairo_pdf_surface_set_size/3 not supported");
}

PLCAIRO_PRED_IMPL(plcairo_pdf_surface_set_thumbnail_size)
{ return plcairo_raise_error("cairo_pdf_surface_set_thumbnail_size/3 not supported");
}

PLCAIRO_PRED_IMPL(plcairo_pdf_version_to_string)
{ return plcairo_raise_error("cairo_pdf_version_to_string/2 not supported");
}

#endif
