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

#ifdef CAIRO_HAS_PS_SURFACE
#include <cairo-ps.h>


/* cairo_ps_level_t */
static atom_t ATOM_cairo_ps_level_2 = 0;
static atom_t ATOM_cairo_ps_level_3 = 0;

cairo_bool_t
plcairo_term_to_ps_level(term_t            t,
                         cairo_ps_level_t *level)
{
  atom_t a;

  PLGI_debug("    term: 0x%lx  --->  cairo_ps_level_t: %p", t, level);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoPSLevel", t);
  }

  if ( !ATOM_cairo_ps_level_2 )
  {
    ATOM_cairo_ps_level_2 = PL_new_atom("CAIRO_PS_LEVEL_2");
    ATOM_cairo_ps_level_3 = PL_new_atom("CAIRO_PS_LEVEL_3");
  }

  if ( a == ATOM_cairo_ps_level_2 )
  { *level = CAIRO_PS_LEVEL_2;
  }
  else if ( a == ATOM_cairo_ps_level_3 )
  { *level = CAIRO_PS_LEVEL_3;
  }
  else
  { return PL_domain_error("CairoPSLevel", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_ps_level_to_term(cairo_ps_level_t level,
                         term_t           t)
{
  term_t t0 = PL_new_term_ref();

  PLGI_debug("    cairo_ps_level_t: %d  --->  term: 0x%lx", level, t);

  if ( !ATOM_cairo_ps_level_2 )
  {
    ATOM_cairo_ps_level_2 = PL_new_atom("CAIRO_PS_LEVEL_2");
    ATOM_cairo_ps_level_3 = PL_new_atom("CAIRO_PS_LEVEL_3");
  }

  if ( level == CAIRO_PS_LEVEL_2 )
  { PL_put_atom(t0, ATOM_cairo_ps_level_2);
  }
  else if ( level == CAIRO_PS_LEVEL_3 )
  { PL_put_atom(t0, ATOM_cairo_ps_level_3);
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify(t, t0);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLGI_PRED_IMPL(plcairo_ps_get_levels)
{
  term_t t_levels = FA0;

  const cairo_ps_level_t *levels;
  int num_levels;
  term_t list = PL_copy_term_ref(t_levels);
  term_t head = PL_new_term_ref();
  int i;

  cairo_ps_get_levels(&levels, &num_levels);

  for ( i = 0; i < num_levels; i++ )
  {
    cairo_ps_level_t level = levels[i];
    term_t a = PL_new_term_ref();

    if ( !plcairo_ps_level_to_term(level, a) ) return FALSE;
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


PLGI_PRED_IMPL(plcairo_ps_level_to_string)
{
  term_t t_level = FA0;
  term_t t_string = FA1;

  cairo_ps_level_t level;
  const char *string;

  if ( !plcairo_term_to_ps_level(t_level, &level) ) return FALSE;

  string = cairo_ps_level_to_string(level);

  if ( !plcairo_string_to_term((char*)string, t_string) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_ps_surface_create)
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

  surface = cairo_ps_surface_create(filename, width_in_points, height_in_points);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_ps_surface_create_for_stream)
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

  surface = cairo_ps_surface_create_for_stream(&plcairo_write_func, closure, width_in_points, height_in_points);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_surface_to_term(surface, t_surface) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_ps_surface_dsc_begin_page_setup)
{
  term_t t_surface = FA0;

  cairo_surface_t *surface;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  cairo_ps_surface_dsc_begin_page_setup(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_ps_surface_dsc_begin_setup)
{
  term_t t_surface = FA0;

  cairo_surface_t *surface;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  cairo_ps_surface_dsc_begin_setup(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_ps_surface_dsc_comment)
{
  term_t t_surface = FA0;
  term_t t_comment = FA1;

  cairo_surface_t *surface;
  char *comment;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_string(t_comment, &comment) ) return FALSE;

  cairo_ps_surface_dsc_comment(surface, comment);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_ps_surface_get_eps)
{
  term_t t_surface = FA0;
  term_t t_eps = FA1;

  cairo_surface_t *surface;
  cairo_bool_t eps;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;

  eps = cairo_ps_surface_get_eps(surface);
  PLCAIRO_CHECK_SURFACE(surface);

  if ( !plcairo_bool_to_term(eps, t_eps) ) return FALSE;

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_ps_surface_restrict_to_level)
{
  term_t t_surface = FA0;
  term_t t_version = FA1;

  cairo_surface_t *surface;
  cairo_ps_level_t version;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_ps_level(t_version, &version) ) return FALSE;

  cairo_ps_surface_restrict_to_level(surface, version);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_ps_surface_set_eps)
{
  term_t t_surface = FA0;
  term_t t_eps = FA1;

  cairo_surface_t *surface;
  cairo_bool_t eps;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_bool(t_eps, &eps) ) return FALSE;

  cairo_ps_surface_set_eps(surface, eps);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}


PLGI_PRED_IMPL(plcairo_ps_surface_set_size)
{
  term_t t_surface = FA0;
  term_t t_width_in_points = FA1;
  term_t t_height_in_points = FA2;

  cairo_surface_t *surface;
  double width_in_points, height_in_points;

  if ( !plcairo_term_to_surface(t_surface, &surface) ) return FALSE;
  if ( !plcairo_term_to_double(t_width_in_points, &width_in_points) ) return FALSE;
  if ( !plcairo_term_to_double(t_height_in_points, &height_in_points) ) return FALSE;

  cairo_ps_surface_set_size(surface, width_in_points, height_in_points);
  PLCAIRO_CHECK_SURFACE(surface);

  return TRUE;
}

#else

PLGI_PRED_IMPL(plcairo_ps_get_levels)
{ return plgi_raise_error("cairo_ps_get_levels/1 not supported");
}

PLGI_PRED_IMPL(plcairo_ps_level_to_string)
{ return plgi_raise_error("cairo_ps_level_to_string/2 not supported");
}

PLGI_PRED_IMPL(plcairo_ps_surface_create)
{ return plgi_raise_error("cairo_ps_surface_create/4 not supported");
}

PLGI_PRED_IMPL(plcairo_ps_surface_create_for_stream)
{ return plgi_raise_error("cairo_ps_surface_create_for_stream/4 not supported");
}

PLGI_PRED_IMPL(plcairo_ps_surface_dsc_begin_page_setup)
{ return plgi_raise_error("cairo_ps_surface_dsc_begin_page_setup/1 not supported");
}

PLGI_PRED_IMPL(plcairo_ps_surface_dsc_begin_setup)
{ return plgi_raise_error("cairo_ps_surface_dsc_begin_setup/1 not supported");
}

PLGI_PRED_IMPL(plcairo_ps_surface_dsc_comment)
{ return plgi_raise_error("cairo_ps_surface_dsc_comment/2 not supported");
}

PLGI_PRED_IMPL(plcairo_ps_surface_get_eps)
{ return plgi_raise_error("cairo_ps_surface_get_eps/2 not supported");
}

PLGI_PRED_IMPL(plcairo_ps_surface_restrict_to_level)
{ return plgi_raise_error("cairo_ps_surface_restrict_to_level/2 not supported");
}

PLGI_PRED_IMPL(plcairo_ps_surface_set_eps)
{ return plgi_raise_error("cairo_ps_surface_set_eps/2 not supported");
}

PLGI_PRED_IMPL(plcairo_ps_surface_set_size)
{ return plgi_raise_error("cairo_ps_surface_set_size/3 not supported");
}

#endif
