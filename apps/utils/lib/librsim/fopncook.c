/* This file is part of the RSIM Applications Library and was modified
from the GNU C library as follows:

Separate initialization calls for stdio streams
Testing against the UNIX stdio streams to determine if the user
is using those structures instead. */  
/* Copyright (C) 1991, 1992 Free Software Foundation, Inc.
This file is part of the GNU C Library.

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the GNU C Library; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 675 Mass Ave,
Cambridge, MA 02139, USA.  */

#include <ansidecl.h>
#include <stdio.h>


/* Defined in fopen.c.  */
extern int EXFUN(__getmode, (CONST char *mode, __io_mode *mptr));

/* Open a new stream on the given magic cookie descriptor.  */
FILE *
DEFUN(fopencookie, (cookie, mode, functions),
      PTR cookie AND CONST char *mode AND __io_functions functions)
{
  __io_mode m;
  FILE *f;

  if (!__stdio_inited) __init_stdio();

  if (!__getmode (mode, &m))
    return NULL;

  f = __newstream ();
  if (f == NULL)
    return NULL;

  f->__cookie = cookie;
  f->__mode = m;
  f->__io_funcs = functions;
  f->__room_funcs = __default_room_functions;
  f->__seen = 1;

  return f;
}