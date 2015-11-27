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


                 /*******************************
                 *      Foreign Predicates      *
                 *******************************/

PLGI_PRED_IMPL(plcairo_version)
{
  term_t t_version = FA0;

  if ( !plcairo_int_to_term(PLCAIRO_VERSION, t_version) ) return FALSE;

  return TRUE;
}
