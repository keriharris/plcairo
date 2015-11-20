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



/* cairo_font_face_t */
cairo_bool_t
plcairo_term_to_font_face(term_t              t,
                          cairo_font_face_t **font_face)
{
  PLGIBlob *blob;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_font_face_t: %p", t, *font_face);

  if ( !plgi_get_blob(t, &blob) )
  { return PL_type_error("CairoFontFace", t);
  }

  if ( blob->gtype != G_TYPE_NONE &&
       !g_type_is_a( blob->gtype, CAIRO_GOBJECT_TYPE_FONT_FACE ) )
  { return PL_type_error("CairoFontFace", t);
  }

  *font_face = blob->data;

  return TRUE;
}

cairo_bool_t
plcairo_font_face_to_term(cairo_font_face_t *font_face,
                          term_t             t)
{
  PLGIBlobType blob_type;
  gpointer data;
  term_t t0 = PL_new_term_ref();

  PLCAIRO_debug("    CairoFontFace: %p  --->  term: 0x%lx", font_face, t);

  if ( !font_face )
  { return ( plgi_put_null(t0) && PL_unify(t, t0) );
  }

  data = font_face;
  blob_type = PLGI_BLOB_BOXED;

  if ( !plgi_put_blob(blob_type, CAIRO_GOBJECT_TYPE_FONT_FACE,
                      PL_new_atom("CairoFontFace"), TRUE, data, t0) )
  { return FALSE;
  }

  return PL_unify(t, t0);
}


/* cairo_font_type_t */
static atom_t ATOM_cairo_font_type_toy = 0;
static atom_t ATOM_cairo_font_type_ft = 0;
static atom_t ATOM_cairo_font_type_win32 = 0;
static atom_t ATOM_cairo_font_type_quartz = 0;
static atom_t ATOM_cairo_font_type_user = 0;

cairo_bool_t
plcairo_term_to_font_type(term_t             t,
                          cairo_font_type_t *type)
{
  atom_t a;

  PLCAIRO_debug("    term: 0x%lx  --->  cairo_font_type_t: %p", t, type);

  if ( !PL_get_atom(t, &a) )
  { return PL_type_error("CairoFontType", t);
  }

  if ( !ATOM_cairo_font_type_toy )
  {
    ATOM_cairo_font_type_toy = PL_new_atom("CAIRO_FONT_TYPE_TOY");
    ATOM_cairo_font_type_ft = PL_new_atom("CAIRO_FONT_TYPE_FT");
    ATOM_cairo_font_type_win32 = PL_new_atom("CAIRO_FONT_TYPE_WIN32");
    ATOM_cairo_font_type_quartz = PL_new_atom("CAIRO_FONT_TYPE_QUARTZ");
    ATOM_cairo_font_type_user = PL_new_atom("CAIRO_FONT_TYPE_USER");
  }

  if ( a == ATOM_cairo_font_type_toy )
  { *type = CAIRO_FONT_TYPE_TOY;
  }
  else if ( a == ATOM_cairo_font_type_ft )
  { *type = CAIRO_FONT_TYPE_FT;
  }
  else if ( a == ATOM_cairo_font_type_win32 )
  { *type = CAIRO_FONT_TYPE_WIN32;
  }
  else if ( a == ATOM_cairo_font_type_quartz )
  { *type = CAIRO_FONT_TYPE_QUARTZ;
  }
  else if ( a == ATOM_cairo_font_type_user )
  { *type = CAIRO_FONT_TYPE_USER;
  }
  else
  { return PL_domain_error("CairoFontType", t);
  }

  return TRUE;
}

cairo_bool_t
plcairo_font_type_to_term(cairo_font_type_t type,
                          term_t            t)
{
  atom_t a;

  PLCAIRO_debug("    cairo_font_type_t: %d  --->  term: 0x%lx", type, t);

  if ( !ATOM_cairo_font_type_toy )
  {
    ATOM_cairo_font_type_toy = PL_new_atom("CAIRO_FONT_TYPE_TOY");
    ATOM_cairo_font_type_ft = PL_new_atom("CAIRO_FONT_TYPE_FT");
    ATOM_cairo_font_type_win32 = PL_new_atom("CAIRO_FONT_TYPE_WIN32");
    ATOM_cairo_font_type_quartz = PL_new_atom("CAIRO_FONT_TYPE_QUARTZ");
    ATOM_cairo_font_type_user = PL_new_atom("CAIRO_FONT_TYPE_USER");
  }

  if ( type == CAIRO_FONT_TYPE_TOY )
  { a = ATOM_cairo_font_type_toy;
  }
  else if ( type == CAIRO_FONT_TYPE_FT )
  { a = ATOM_cairo_font_type_ft;
  }
  else if ( type == CAIRO_FONT_TYPE_WIN32 )
  { a = ATOM_cairo_font_type_win32;
  }
  else if ( type == CAIRO_FONT_TYPE_QUARTZ )
  { a = ATOM_cairo_font_type_quartz;
  }
  else if ( type == CAIRO_FONT_TYPE_USER )
  { a = ATOM_cairo_font_type_user;
  }
  else
  { g_assert_not_reached();
  }

  return PL_unify_atom(t, a);
}



                 /*******************************
                 *     Published Predicates     *
                 *******************************/

PLCAIRO_PRED_IMPL(plcairo_font_face_get_type)
{
  term_t t_font_face = FA0;
  term_t t_font_type = FA1;

  cairo_font_face_t *font_face;
  cairo_font_type_t font_type;

  if ( !plcairo_term_to_font_face(t_font_face, &font_face) ) return FALSE;

  font_type = cairo_font_face_get_type(font_face);
  PLCAIRO_CHECK_FONT_FACE(font_face);

  if ( !plcairo_font_type_to_term(font_type, t_font_type) ) return FALSE;

  return TRUE;
}
