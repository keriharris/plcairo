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

#ifdef CAIRO_HAS_SVG_SURFACE
#include <cairo-svg.h>


/* cairo_svg_version_t */
static atom_t ATOM_cairo_svg_version_1_1 = 0;
static atom_t ATOM_cairo_svg_version_1_2 = 0;

cairo_bool_t
plcairo_term_to_svg_version(term_t               t,
                            cairo_svg_version_t *version)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_svg_version_t: %p", t, version);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoSvgVersion", t);
  }

  if ( !ATOM_cairo_svg_version_1_1 )
  {
    ATOM_cairo_svg_version_1_1 = PL_new_atom("CAIRO_SVG_VERSION_1_1");
    ATOM_cairo_svg_version_1_2 = PL_new_atom("CAIRO_SVG_VERSION_1_2");
  }

  if ( a == ATOM_cairo_svg_version_1_1 )
  { *version = CAIRO_SVG_VERSION_1_1;
  }
  else if ( a == ATOM_cairo_svg_version_1_2 )
  { *version = CAIRO_SVG_VERSION_1_2;
  }
  else
  { return PL_domain_error("CairoSvgVersion", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_svg_version_to_term(cairo_svg_version_t version,
                            term_t              t)
{
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    cairo_svg_version_t: %d  --->  term: 0x%lx", version, t);

  if ( !ATOM_cairo_svg_version_1_1 )
  {
    ATOM_cairo_svg_version_1_1 = PL_new_atom("CAIRO_SVG_VERSION_1_1");
    ATOM_cairo_svg_version_1_2 = PL_new_atom("CAIRO_SVG_VERSION_1_2");
  }

  if ( version == CAIRO_SVG_VERSION_1_1 )
  { PL_put_atom(t0, ATOM_cairo_svg_version_1_1);
  }
  else if ( version == CAIRO_SVG_VERSION_1_2 )
  { PL_put_atom(t0, ATOM_cairo_svg_version_1_2);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLGI_PRED_IMPL(plcairo_svg_get_versions)
{
  term_t t_versions = FA0;

  const cairo_svg_version_t *versions;
  int num_versions;
  term_t list = PL_copy_term_ref(t_versions);
  term_t head = PL_new_term_ref();
  int i;

  cairo_svg_get_versions(&versions, &num_versions);

  for ( i = 0; i < num_versions; i++ )
  {
    cairo_svg_version_t version = versions[i];
    term_t a = PL_new_term_ref();

    if ( !plcairo_svg_version_to_term(version, a) ) return FALSE;
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


PLGI_PRED_IMPL(plcairo_svg_surface_create)
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

  surface = cairo_svg_surface_create(filename, width_in_points, height_in_points);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_svg_surface_create_for_stream)
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

  surface = cairo_svg_surface_create_for_stream(&plcairo_write_func, closure, width_in_points, height_in_points);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_svg_surface_restrict_to_version)
{
  term_t t_surface = FA0;
  term_t t_version = FA1;

  cairo_surface_t *surface;
  cairo_svg_version_t version;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_svg_version(t_version, &version) ) return FALSE;

  cairo_svg_surface_restrict_to_version(surface, version);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_svg_version_to_string)
{
  term_t t_version = FA0;
  term_t t_string = FA1;

  cairo_svg_version_t version;
  const char *string;

  if ( !plcairo_term_to_svg_version(t_version, &version) ) return FALSE;

  string = cairo_svg_version_to_string(version);

  if ( !plcairo_string_to_term((char*)string, t_string) ) return FALSE;

  return TRUE;
}

#else

PLGI_PRED_IMPL(plcairo_svg_get_versions)
{ return plgi_raise_error("cairo_svg_get_versions/1 not supported");
}

PLGI_PRED_IMPL(plcairo_svg_surface_create)
{ return plgi_raise_error("cairo_svg_surface_create/4 not supported");
}

PLGI_PRED_IMPL(plcairo_svg_surface_create_for_stream)
{ return plgi_raise_error("cairo_svg_surface_create_for_stream/4 not supported");
}

PLGI_PRED_IMPL(plcairo_svg_surface_restrict_to_version)
{ return plgi_raise_error("cairo_svg_surface_restrict_to_version/2 not supported");
}

PLGI_PRED_IMPL(plcairo_svg_version_to_string)
{ return plgi_raise_error("cairo_svg_version_to_string/2 not supported");
}

#endif
