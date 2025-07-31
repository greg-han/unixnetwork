#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "unutils.h"
extern int errno;

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define PERMS 0666


int main(){
	int childpid, readfd, writefd;
	
	if ( (mknod(FIFO1, S_IFIFO | PERMS, 0) < 0 ) && (errno != EEXIST) )
		err_sys("can't create fifo 1");
	if ( (mknod(FIFO2, S_IFIFO | PERMS, 0) < 0 ) && (errno != EEXIST) ){
		unlink(FIFO1);
		err_sys("can't create fifo 2");
	}

	if ( (childpid = fork()) < 0){
		err_sys("can't fork");
	} else if (childpid > 0){ /* parent */
		if ((writefd = open(FIFO1, 1)) < 0)
			err_sys("parent: can't open write fifo");
		if((readfd = open(FIFO2, 0)) < 0)
			err_sys("parent: can't open read fifo");

		pipe_client(readfd,writefd);
		
		while(wait( (int *) 0) != childpid); /* wait for child */
	        
                close(readfd);
		close(writefd);
       
                if(unlink(FIFO1) < 0)
			err_sys("parent: can't unlink fifo1");
		if(unlink(FIFO2) < 0)
			err_sys("parent: can't unlink fifo2");

		return 0;
	} else { /* child */
                /* use the below code to create deadlock. 1 is not a fd, but
                 * fcntl flag for open. it will open both for read (blocking)
                 * ,while both parent and child sleep.
                 *  and wait for another process to open for writing
                 *  before being awoken by the OS
                 * you can also set O_NDELAY open to open, and it would not
                 * deadlock anymore.
                 */ 
                /*               
		if( ( readfd = open(FIFO1, 1)) < 0)
			err_sys("child: can't open read fifo");
                */
		if( ( readfd = open(FIFO1, 0)) < 0)
			err_sys("child: can't open read fifo");
		if( ( writefd = open(FIFO2, 1)) < 0)
			err_sys("child can't open write fifo");
	
		pipe_server(readfd,writefd);

		close(readfd);
		close(writefd);

		return 0;
	}

	return 0;
}
