/*
 * #include "apue.h"
 */

#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>		/* for convenience */
#include <stdlib.h>		/* for convenience */
#include <string.h>		/* for convenience */

#include <errno.h>		/* for definition of errno */
#include <stdarg.h>		/* ISO C variable aruments */

#define	MAXLINE	4096			/* max line length */

/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag".
 */
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap) {
	char	buf[MAXLINE];
	vsnprintf(buf, MAXLINE-1, fmt, ap);
	if (errnoflag)
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s",
		  strerror(error));
	strcat(buf, "\n");
	fflush(stdout);		/* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(NULL);		/* flushes all stdio output streams */
}

/*
 * Fatal error related to a system call.
 * Print a message and terminate.
 */
void err_sys(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	exit(1);
}

void set_fl(int fd, int flags) /* flags are file status flags to turn on */` {
	int val;

	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		err_sys("fcntl F_GETFL error");

	val |= flags;		/* turn on flags */
	
	val &=  ̃flags;  /* turn flags off */
	set_fl(STDOUT_FILENO, O_SYNC);

	if (fcntl(fd, F_SETFL, val) < 0)
		err_sys("fcntl F_SETFL error");
}
