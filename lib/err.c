#include <unistd.h>
#include "error.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* values for sys_err_str() */

extern int errno; /* Unix error number */

/* These values are obsolete in modern glibc and are replaced.
* extern int sys_nerr;  # of error message strings in sys table 
* extern char *sys_errlist[]; the system error message table 
*/

/* end values for sys_err_str() */

/* general syscall error

   param: const char * x a string to give information for perror()

   Taken from user "Patrik" on stackoverflow
   does not dump core
*/

void err_sys(const char* x){
	perror(x);
	exit(1);
}

/* another function for a general system call error, but returns a pointer
 * to an error string that it builds
*/


char * sys_err_str(){

	static char msgstr[200];
        
	if(errno != 0) {
		/*  This line is replaced 
                  * if(errno > 0 && errno < sys_nerr)
                  * and sys_errlist[errno] is replaced
                  * with strerror(errno)
                  * you can also replace sprintf with snprintf if you'd like
                */
		if(errno > 0)
			sprintf(msgstr, "(%s)", strerror(errno));     
                else 
			sprintf(msgstr, "(errno = %d)", errno);
	} else{
		msgstr[0] = '\0';
	}

	return(msgstr);
}
