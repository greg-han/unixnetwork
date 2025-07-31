#include "lib/fifo.h"

int main(){
	int readfd, writefd;
		
	/*
	* Create the FIFOs, then open them - one for reading
	* and one for writing.
	*/
		
	if ( (mknod(FIFO1, S_IFIFO | PERMS, 0) < 0) && (errno != EEXIST) )
		err_sys("can't create fifo1");
	if ( (mknod(FIFO2, S_IFIFO | PERMS, 0) < 0) && (errno != EEXIST) ){
		unlink(FIFO1);
		err_sys("can't create fifo2");
	}

	if( (readfd = open(FIFO1, 0)) < 0 )
		err_sys("server: can't open read fifo1");
	if( (writefd = open(FIFO2, 1)) < 0 )
		err_sys("server: can't open write fifo2");

	mesg_server(readfd,writefd);
			
	close(readfd);
	close(writefd);

	return 0;
}
