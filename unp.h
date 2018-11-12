#include <errno.h>
#include <stdarg.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <unistd.h>

#define MAXLINE 4096
/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag".
 */
static void
err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
    char    buf[MAXLINE];
    vsnprintf(buf, MAXLINE, fmt, ap);
    if (errnoflag)
        snprintf(buf+strlen(buf), MAXLINE-strlen(buf), ": %s",
    strerror(error));
    strcat(buf, "\n");
    fflush(stdout);     
    fputs(buf, stderr);
    fflush(NULL);
}

/*
 * Fatal error related to a system call.
 * Print a message and terminate.
 */
void
err_sys(const char *fmt, ...)
{
    va_list     ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}
