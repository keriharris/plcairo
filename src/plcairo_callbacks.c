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
plcairo_term_to_closure(term_t t_closure, void **closure)
{
  *closure = PL_record(t_closure);

  return TRUE;
}


/* cairo_write_func_t */
cairo_status_t
plcairo_write_func(void *closure,
                   const unsigned char *data,
                   unsigned int length)
{
  term_t t_stream = PL_new_term_ref();
  IOSTREAM *stream;
  size_t written;
  cairo_status_t status;

  PLCAIRO_debug_header;

  if ( !closure )
  { status = CAIRO_STATUS_WRITE_ERROR;
    goto cleanup;
  }

  if ( !PL_recorded(closure, t_stream) )
  { status = CAIRO_STATUS_WRITE_ERROR;
    goto cleanup;
  }

  if ( !PL_get_stream_handle(t_stream, &stream) )
  { status = CAIRO_STATUS_WRITE_ERROR;
    goto cleanup;
  }

  written = Sfwrite(data, 1, length, stream);
  PL_release_stream(stream);

  PLCAIRO_debug("  wrote %ld bytes to stream: %p", written, stream);

  if ( written == length )
  { status = CAIRO_STATUS_SUCCESS;
  }
  else
  { status = CAIRO_STATUS_WRITE_ERROR;
  }

cleanup:

  PLCAIRO_debug_trailer;

  return status;
}


/* cairo_read_func_t */
cairo_status_t
plcairo_read_func(void *closure,
                  unsigned char *data,
                  unsigned int length)
{
  term_t t_stream = PL_new_term_ref();
  IOSTREAM *stream;
  size_t read;
  cairo_status_t status;

  PLCAIRO_debug_header;

  if ( !closure )
  { status = CAIRO_STATUS_WRITE_ERROR;
    goto cleanup;
  }

  if ( !PL_recorded(closure, t_stream) )
  { status = CAIRO_STATUS_WRITE_ERROR;
    goto cleanup;
  }

  if ( !PL_get_stream_handle(t_stream, &stream) )
  { status = CAIRO_STATUS_WRITE_ERROR;
    goto cleanup;
  }

  read = Sfread(data, 1, length, stream);
  PL_release_stream(stream);

  PLCAIRO_debug("  read %ld bytes from stream: %p", read, stream);

  if ( read == length )
  { status = CAIRO_STATUS_SUCCESS;
  }
  else
  { status = CAIRO_STATUS_READ_ERROR;
  }

cleanup:

  PLCAIRO_debug_trailer;

  return status;
}
