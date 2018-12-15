/*  This file is part of PLcairo.

    Copyright (C) 2018 Keri Harris <keri@gentoo.org>

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


#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 16, 0)
static atom_t ATOM_cairo_tag_dest = 0;
static atom_t ATOM_cairo_tag_link = 0;

cairo_bool_t
plcairo_term_to_tag_name(term_t  t, char **tag_name)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  tag_name: %p", t, *tag_name);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("atom", t);
  }

  if ( !ATOM_cairo_tag_dest )
  {
    ATOM_cairo_tag_dest = PL_new_atom("CAIRO_TAG_DEST");
    ATOM_cairo_tag_link = PL_new_atom("CAIRO_TAG_LINK");
  }

  if ( a == ATOM_cairo_tag_dest )
  { *tag_name = CAIRO_TAG_DEST;
  }
  else if ( a == ATOM_cairo_tag_link )
  { *tag_name = CAIRO_TAG_LINK;
  }
  else
  { return plcairo_term_to_string(t, tag_name);
  }

  return TRUE;
}
#endif



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLCAIRO_PRED_IMPL(plcairo_tag_begin)
{
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 16, 0)
  term_t t_cr = FA0;
  term_t t_tag_name = FA1;
  term_t t_attributes = FA2;

  cairo_t *cr;
  char *tag_name;
  char *attributes;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_tag_name(t_tag_name, &tag_name) ) return FALSE;
  if ( !plcairo_term_to_string(t_attributes, &attributes) ) return FALSE;

  cairo_tag_begin(cr, tag_name, attributes);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
#else
  return plcairo_raise_error("cairo_tag_begin/3 requires Cairo >= v1.16");
#endif
}


PLCAIRO_PRED_IMPL(plcairo_tag_end)
{
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 16, 0)
  term_t t_cr = FA0;
  term_t t_tag_name = FA1;

  cairo_t *cr;
  char *tag_name;

  if ( !plcairo_term_to_context(t_cr, &cr) ) return FALSE;
  if ( !plcairo_term_to_tag_name(t_tag_name, &tag_name) ) return FALSE;

  cairo_tag_end(cr, tag_name);
  PLCAIRO_CHECK_CONTEXT(cr);

  return TRUE;
#else
  return plcairo_raise_error("cairo_tag_end/2 requires Cairo >= v1.16");
#endif
}
