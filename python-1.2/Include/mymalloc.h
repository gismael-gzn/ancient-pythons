#ifndef Py_MYMALLOC_H
#define Py_MYMALLOC_H
/***********************************************************
Copyright 1991-1995 by Stichting Mathematisch Centrum, Amsterdam,
The Netherlands.

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

/* Lowest-level memory allocation interface */

#ifdef macintosh
#define ANY void
#endif

#ifdef __STDC__
#define ANY void
#endif

#ifdef __TURBOC__
#define ANY void
#endif

#ifdef __GNUC__
#define ANY void
#endif

#ifndef ANY
#define ANY char
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef __cplusplus
// Move this down here since some C++ #include's don't like to be included
// inside an extern "C"
extern "C" {
#endif

#ifdef __CFM68K__
#pragma lib_export on
#endif

#ifndef HAVE_STDLIB_H
extern ANY *malloc Py_PROTO((size_t));
extern ANY *calloc Py_PROTO((size_t, size_t));
extern ANY *realloc Py_PROTO((ANY *, size_t));
extern void free Py_PROTO((ANY *)); /* XXX sometimes int on Unix old systems */
#endif /* !HAVE_STDLIB */

#ifndef NULL
#define NULL ((ANY *)0)
#endif

/* XXX Always allocate one extra byte, since some malloc's return NULL
   XXX for malloc(0) or realloc(p, 0). */
#define PyMem_NEW(type, n) ( (type *) malloc(1 + (n) * sizeof(type)) )
#define PyMem_RESIZE(p, type, n) \
	if ((p) == NULL) \
		(p) =  (type *) malloc(1 + (n) * sizeof(type)); \
	else \
		(p) = (type *) realloc((ANY *)(p), 1 + (n) * sizeof(type))
#define PyMem_DEL(p) free((ANY *)p)
#define PyMem_XDEL(p) if ((p) == NULL) ; else PyMem_DEL(p)

#ifdef __cplusplus
}
#endif

#ifndef Py_USE_NEW_NAMES
#include "rename2.h"
#endif
#endif /* !Py_MYMALLOC_H */
