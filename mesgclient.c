#include "lib/fifo.h"

int main(){
	int readfd, writefd;
        /* open fifos that we assume server has already created */
	
	if( (writefd = open(FIFO1, 1)) < 0)
		err_sys("client can't open write fifo1");
	if( (readfd = open(FIFO2, 0)) < 0)
		err_sys("client can't open read fifo2");

	mesg_client(readfd, writefd);

 	close(readfd);
	close(writefd);

        /* 
	* Delete the FIFOs, now that we're finished.
        */

	if(unlink(FIFO1) < 0)
		err_sys("client: can't unlink fifo1");
	if(unlink(FIFO2) < 0)
		err_sys("client: can't unlink fifo2");

	return 0;
}
