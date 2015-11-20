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


static cairo_bool_t debug_active = FALSE;

cairo_bool_t plcairo_debug_active(void)
{
  return debug_active;
}


int plgi_exit_debug(int status, void *arg)
{
  debug_active = FALSE;

  return 0;
}



                 /*******************************
                 *      Foreign Predicates      *
                 *******************************/

PLGI_PRED_IMPL(plcairo_debug)
{
  term_t t = FA0;

  if ( !plcairo_term_to_bool(t, &debug_active) )
  { return FALSE;
  }

  return TRUE;
}
