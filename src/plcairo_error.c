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


cairo_bool_t
plcairo_raise_error(char *message)
{
  PLCAIRO_debug("!!! raising exception: %s", message);

  term_t except = PL_new_term_ref();
  if ( !PL_unify_term(except,
                      PL_FUNCTOR_CHARS, "error", 2,
                        PL_FUNCTOR_CHARS, "plcairo_error", 1,
                          PL_UTF8_CHARS, message,
                        PL_VARIABLE) )
  { return FALSE;
  }
  return PL_raise_exception(except);
}


cairo_bool_t
plcairo_raise_error__va(char *fmt, ...)
{
  char message[1024];

  va_list args;
  va_start(args, fmt);
  vsnprintf(message, sizeof(message), fmt, args);
  va_end(args);

  return plcairo_raise_error(message);
}


cairo_bool_t
plcairo_raise_error_status(int status)
{
  PLCAIRO_debug("!!! raising exception: %s", cairo_status_to_string(status));

  term_t except = PL_new_term_ref();
  if ( !PL_unify_term(except,
                      PL_FUNCTOR_CHARS, "error", 2,
                        PL_FUNCTOR_CHARS, "cairo_error", 2,
                          PL_INT, status,
                          PL_UTF8_CHARS, cairo_status_to_string(status),
                        PL_VARIABLE) )
  { return FALSE;
  }
  return PL_raise_exception(except);
}
