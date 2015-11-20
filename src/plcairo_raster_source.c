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
                 *     Published Predicates     *
                 *******************************/

PLCAIRO_PRED_IMPL(plcairo_pattern_create_raster_source)
{
  term_t t_content = FA0;
  term_t t_width = FA1;
  term_t t_height = FA2;
  term_t t_pattern = FA3;

  cairo_content_t content;
  int width, height;
  cairo_pattern_t *pattern;

  if ( !plcairo_term_to_content(t_content, &content) ) return FALSE;
  if ( !plcairo_term_to_int(t_height, &height) ) return FALSE;
  if ( !plcairo_term_to_int(t_width, &width) ) return FALSE;

  pattern = cairo_pattern_create_raster_source(NULL, content, width, height);
  PLCAIRO_CHECK_PATTERN(pattern);

  if ( !plcairo_pattern_to_term(pattern, t_pattern) ) return FALSE;

  return TRUE;
}
