/*  This file is part of PLcairo.

    Copyright (C) 2017 Keri Harris <keri@gentoo.org>

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

#include <limits.h>



                 /*******************************
                 *             NULL             *
                 *******************************/

cairo_bool_t
plcairo_get_null(term_t t, void **v)
{ atom_t name;
  size_t arity;

  if ( PL_get_name_arity(t, &name, &arity) )
  { const char* s;
    s = PL_atom_chars(name);
    if ( strcmp(s, "{}") == 0 && arity == 1 )
    { term_t a = PL_new_term_ref();
      _PL_get_arg(1, t, a);
      if ( PL_get_atom_chars(a, (gchar**)&s) && strcmp(s, "null") == 0 )
      { *v = NULL;
        return TRUE;
      }
    }
  }

  return FALSE;
}

cairo_bool_t
plcairo_put_null(term_t t)
{ term_t a = PL_new_term_ref();
  functor_t f = PL_new_functor(PL_new_atom("{}"), 1);

  if ( PL_put_atom_chars(a, "null") && PL_cons_functor(t, f, a) )
  { return TRUE;
  }

  return FALSE;
}



                 /*******************************
                 *         cairo_bool_t         *
                 *******************************/

cairo_bool_t
plcairo_term_to_bool(term_t t, cairo_bool_t *v)
{ gint i;

  if ( PL_get_bool(t, &i) )
  { *v = i;
    PLCAIRO_debug("    term: 0x%lx  --->  cairo_bool_t: %d", t, *v);
    return TRUE;
  }

  return PL_type_error("boolean", t);
}

cairo_bool_t
plcairo_bool_to_term(cairo_bool_t v, term_t t)
{
  PLCAIRO_debug("    cairo_bool_t: %d  --->  term: 0x%lx", v, t);

  return PL_unify_bool(t, v);
}



                 /*******************************
                 *             int              *
                 *******************************/

cairo_bool_t
plcairo_term_to_int(term_t t, int *v)
{ int64_t i;

  if ( PL_get_int64(t, &i) )
  { if ( i >= INT_MIN && i <= INT_MAX )
    { *v = i;
      PLCAIRO_debug("    term: 0x%lx  --->  int: %d", t, *v);
      return TRUE;
    }
  }

  return PL_type_error("integer", t);
}

cairo_bool_t
plcairo_int_to_term(int v, term_t t)
{
  PLCAIRO_debug("    int: %d  --->  term: 0x%lx", v, t);

  return PL_unify_integer(t, v);
}



                 /*******************************
                 *         unsigned int         *
                 *******************************/

cairo_bool_t
plcairo_term_to_unsigned_int(term_t t, unsigned int *v)
{ int64_t i;

  if ( PL_get_int64(t, &i) )
  { if ( i >= 0 && i <= UINT_MAX )
    { *v = i;
      PLCAIRO_debug("    term: 0x%lx  --->  unsigned int: %u", t, *v);
      return TRUE;
    }
  }

  return PL_type_error("unsigned integer", t);
}

cairo_bool_t
plcairo_unsigned_int_to_term(unsigned int v, term_t t)
{
  PLCAIRO_debug("    unsigned int: %d  --->  term: 0x%lx", v, t);

  return PL_unify_integer(t, v);
}



                 /*******************************
                 *             long             *
                 *******************************/

cairo_bool_t
plcairo_term_to_long(term_t t, long *v)
{ int64_t i;

  if ( PL_get_int64(t, &i) )
  { if ( i >= LONG_MIN && i <= LONG_MAX )
    { *v = i;
      PLCAIRO_debug("    term: 0x%lx  --->  long: %ld", t, *v);
      return TRUE;
    }
  }

  return PL_type_error("long integer", t);
}

cairo_bool_t
plcairo_long_to_term(long v, term_t t)
{
  PLCAIRO_debug("    long: %ld  --->  term: 0x%lx", v, t);

  return PL_unify_int64(t, v);
}



                 /*******************************
                 *        unsigned long         *
                 *******************************/

cairo_bool_t
plcairo_term_to_unsigned_long(term_t t, unsigned long *v)
{ int64_t i;

  if ( PL_get_int64(t, &i) )
  { if ( i >= 0 )
    { *v = i;
      PLCAIRO_debug("    term: 0x%lx  --->  unsigned long: %lu", t, *v);
      return TRUE;
    }
  }
  else
  { mpz_t mpz;
    mpz_init(mpz);
    if ( PL_get_mpz(t, mpz) )
    { if ( mpz_cmp_ui(mpz, 0) >= 0 && mpz_cmp_ui(mpz, ULONG_MAX) <= 0 )
      { *v = mpz_get_ui(mpz);
        mpz_clear(mpz);
        PLCAIRO_debug("    term: 0x%lx  --->  unsigned long: %lu", t, *v);
        return TRUE;
      }
    }
    mpz_clear(mpz);
  }

  return PL_type_error("long integer", t);
}

cairo_bool_t
plcairo_unsigned_long_to_term(unsigned long v, term_t t)
{
  PLCAIRO_debug("    unsigned long: %ld  --->  term: 0x%lx", v, t);

  if ( v > LONG_MAX )
  { mpz_t mpz;
    int ret;
    mpz_init(mpz);
    mpz_set_ui(mpz, v);
    ret = PL_unify_mpz(t, mpz);
    mpz_clear(mpz);
    return ret;
  }

  return PL_unify_int64(t, v);
}



                 /*******************************
                 *            double            *
                 *******************************/

cairo_bool_t
plcairo_term_to_double(term_t t, double *v)
{ double f;

  if ( PL_get_float(t, &f) )
  { *v = f;
    PLCAIRO_debug("    term: 0x%lx  --->  double: %lf", t, *v);
    return TRUE;
  }

  return PL_type_error("double", t);
}

cairo_bool_t
plcairo_double_to_term(double v, term_t t)
{
  PLCAIRO_debug("    double: %lf  --->  term: 0x%lx", v, t);

  return PL_unify_float(t, v);
}



                 /*******************************
                 *             utf8             *
                 *******************************/

cairo_bool_t
plcairo_term_to_string(term_t t, char **v)
{ gchar *s;

  if ( PL_get_chars(t, &s, CVT_ATOM|REP_UTF8) )
  { *v = strdup(s);
    PLCAIRO_debug("    term: 0x%lx  --->  string: %s", t, *v);
    return TRUE;
  }

  return PL_type_error("atom", t);
}

cairo_bool_t
plcairo_string_to_term(char *v, term_t t)
{
  PLCAIRO_debug("    string: %s  --->  term: 0x%lx", v, t);

  if ( !v )
  { return plcairo_put_null(t);
  }
  if ( !*v )
  { PL_put_atom_chars(t, v);
    return TRUE;
  }

  return PL_unify_chars(t, PL_ATOM|REP_UTF8, -1, v);
}
