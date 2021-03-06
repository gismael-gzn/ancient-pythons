/***********************************************************
Copyright 1991-1995 by Stichting Mathematisch Centrum, Amsterdam,
The Netherlands.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the names of Stichting Mathematisch
Centrum or CWI or Corporation for National Research Initiatives or
CNRI not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

While CWI is the initial source for this software, a modified version
is made available by the Corporation for National Research Initiatives
(CNRI) at the Internet address ftp://ftp.python.org.

STICHTING MATHEMATISCH CENTRUM AND CNRI DISCLAIM ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL STICHTING MATHEMATISCH
CENTRUM OR CNRI BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.

******************************************************************/

/* Readline interface for tokenizer.c.
   By default, we have a super simple my_readline function.
   Optionally, we can use the GNU readline library (to be found in the
   bash distribution).
   my_readline() has a different return value from GNU readline():
   - NULL if an interrupt occurred or if an error occurred
   - a malloc'ed empty string if EOF was read
   - a malloc'ed string ending in \n normally
*/

#include "config.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "myproto.h"
#include "mymalloc.h"
#include "intrcheck.h"

#ifdef WITH_READLINE

extern char *readline();
extern int rl_initialize();
extern int rl_insert();
extern char *rl_readline_name;

#include <setjmp.h>
#include <signal.h>

static jmp_buf jbuf;

/* ARGSUSED */
static RETSIGTYPE
onintr(sig)
	int sig;
{
	longjmp(jbuf, 1);
}

#else /* !WITH_READLINE */

/* This function restarts a fgets() after an EINTR error occurred
   except if intrcheck() returns true. */

static int
my_fgets(buf, len, fp)
	char *buf;
	int len;
	FILE *fp;
{
	char *p;
	for (;;) {
		errno = 0;
		p = fgets(buf, len, fp);
		if (p != NULL)
			return 0; /* No error */
		if (feof(fp)) {
			return -1; /* EOF */
		}
#ifdef EINTR
		if (errno == EINTR) {
			if (intrcheck()) {
				return 1; /* Interrupt */
			}
			continue;
		}
#endif
		if (intrcheck()) {
			return 1; /* Interrupt */
		}
		return -2; /* Error */
	}
	/* NOTREACHED */
}

#endif /* WITH_READLINE */


#ifdef WITH_READLINE
void
PyOS_ReadlineInit()
{
	static int been_here;
	if (!been_here) {
		/* Force rebind of TAB to insert-tab */
		rl_readline_name = "python";
		rl_initialize();
		rl_bind_key('\t', rl_insert);
		been_here++;
	}
}
#endif


char *
my_readline(prompt)
	char *prompt;
{
	int n;
	char *p;
#ifdef WITH_READLINE
	RETSIGTYPE (*old_inthandler)();
	PyOS_ReadlineInit();
	old_inthandler = signal(SIGINT, onintr);
	if (setjmp(jbuf)) {
#ifdef HAVE_SIGRELSE
		/* This seems necessary on SunOS 4.1 (Rasmus Hahn) */
		sigrelse(SIGINT);
#endif
		signal(SIGINT, old_inthandler);
		return NULL;
	}
	p = readline(prompt);
	signal(SIGINT, old_inthandler);
	if (p == NULL) {
		p = malloc(1);
		if (p != NULL)
			*p = '\0';
		return p;
	}
	n = strlen(p);
	if (n > 0)
		add_history(p);
	if ((p = realloc(p, n+2)) != NULL) {
		p[n] = '\n';
		p[n+1] = '\0';
	}
	return p;
#else /* !WITH_READLINE */
	n = 100;
	if ((p = malloc(n)) == NULL)
		return NULL;
	fflush(stdout);
	if (prompt)
		fprintf(stderr, "%s", prompt);
	fflush(stderr);
	switch (my_fgets(p, n, stdin)) {
	case 0: /* Normal case */
		break;
	case 1: /* Interrupt */
		free(p);
		return NULL;
	case -1: /* EOF */
	case -2: /* Error */
	default: /* Shouldn't happen */
		*p = '\0';
		break;
	}
#ifdef MPW
	/* Hack for MPW C where the prompt comes right back in the input */
	/* XXX (Actually this would be rather nice on most systems...) */
	n = strlen(prompt);
	if (strncmp(p, prompt, n) == 0)
		memmove(p, p + n, strlen(p) - n + 1);
#endif
	n = strlen(p);
	while (n > 0 && p[n-1] != '\n') {
		int incr = n+2;
		p = realloc(p, n + incr);
		if (p == NULL)
			return NULL;
		if (my_fgets(p+n, incr, stdin) != 0)
			break;
		n += strlen(p+n);
	}
	return realloc(p, n+1);
#endif /* !WITH_READLINE */
}
