
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "unutils.h"

#define BUFFSIZE 4096
int sigflag;

/* From Unix Network Programming 6.12 Asynchronous I/O

   Many signal things were replaced with non-deprecated equivalents.
   These replacements will be commented out, and there will be a comment
   above additions and removals to clarify.

*/

/* position of sigio_func() moved up here, and type changed from int to static void */
static void sigio_func(){
  sigflag = 1;
}

int main()
{

	int n;
	char buff[BUFFSIZE];
        /* masks added to program */
	sigset_t blockingMask, emptyMask, pauseMask;
        /* sigaction struct added to program */
        struct sigaction sa;
 
        /* (void) added to program  signal repalced with sigaction */
        /* (void) signal(SIGIO, sigio_func); */
        sa.sa_handler = sigio_func;
        sa.sa_flags = 0;
 
        if(sigaction(SIGIO, &sa, NULL) == -1)
           err_sys("sigaction error");

        /* Sets the owner of fd 0 to this process */
        if(fcntl(0, F_SETOWN, getpid()) < 0)
		err_sys("F_SETOWN error");

       /* Sets the process to send SIGIO when fd 0 has some kind of input */ 
      /* Sent to process owning fd 0 from above */
	if(fcntl(0, F_SETFL, FASYNC) < 0)
		err_sys("F_SETFL FASYNC error");

        printf("My pid is: %ld . Signal me! \n", getpid());
	for( ; ; ){

                /* *removed* sigblock(sigmask(SIGIO)); */
                /* replaced with sigaddset and sigprocmask */

                sigemptyset(&blockingMask);
                if(sigaddset(&blockingMask, SIGIO) == -1){
                   err_sys("sig add set error");
                }

                if(sigprocmask(SIG_BLOCK, &blockingMask, NULL) == -1){
                   err_sys("sigprocmask error when blocking");
                }
          
               /* end replacements */

                     
               while(sigflag == 0){

                      /* 
                       * sigpause(0); // wait for a signal 
                       * replaced this with sigsuspend() with error checking
                      */

 		      if(sigsuspend(&blockingMask) == -1){
                          err_sys("sig suspend error");
                      }
                }
                     

              /*
               * This simulates an area that we are "in" until (sigflag != 0)
               * We also know that the SIGIO signal is currently blocked.
               */

              if(( n = read(0, buff, BUFFSIZE)) > 0) {
              		if(write(1, buff, n) != n)
				err_sys("Write error");
	      }else if (n < 0)
	       	  err_sys("read error"); 
              else if(n == 0)
		  exit(0);
              sigflag = 0;

              /* 
               * *removed* sigsetmask(0); * re-enable signals *  
               * *added* sigprocmask instead 
               */

              sigemptyset(&emptyMask);
              sigprocmask(SIG_SETMASK, &emptyMask, NULL); 
             
              /* This simulates an area where the process is good for all signals again
               * but we loop back up to the beginning */
      
       }
}
