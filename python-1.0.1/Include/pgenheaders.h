#ifndef Py_PGENHEADERS_H
#define Py_PGENHEADERS_H
#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************
Copyright 1991, 1992, 1993, 1994 by Stichting Mathematisch Centrum,
Amsterdam, The Netherlands.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Stichting Mathematisch
Centrum or CWI not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior permission.

STICHTING MATHEMATISCH CENTRUM DISCLAIMS ALL WARRANTIES WITH REGARD TO
THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS, IN NO EVENT SHALL STICHTING MATHEMATISCH CENTRUM BE LIABLE
FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

******************************************************************/

/* Include files and extern declarations used by most of the parser.
   This is a precompiled header for THINK C. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef THINK_C
#define macintosh
#endif

#include <stdio.h>
#include <string.h>

#ifdef THINK_C
#define label label_
#undef label
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "myproto.h"
#include "mymalloc.h"

extern void fatal PROTO((char *));

#ifdef __cplusplus
}
#endif
#endif /* !Py_PGENHEADERS_H */
