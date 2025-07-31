#include "mesgs.h"
#include "err.h"
#include <unistd.h>

void mesg_send(int fd, Mesg *mesgptr){
	int n;
	/* Write the message header and the optional data.
	* first calculate the length of the length field,
	* plus the type field, plus the optional data.
	*/
	n = MESGHDRSIZE + mesgptr->mesg_len;

	if (write(fd, (char *) mesgptr, n) != n)
		err_sys("Message write error");
}

int mesg_recv(int fd, Mesg *mesgptr){
	int n;
	
	/*
	* Read the message header first. This tells us how much
	* data follows the message for the next read.
	* An end-of-file on the file descriptor causes us to
	* return 0. Hence, we force the assumption on the caller
	* that a 0-length message means EOF.
	*/

	if( (n = read(fd, (char *) mesgptr, MESGHDRSIZE)) == 0)
		return 0; /* End of File */
	else if (n != MESGHDRSIZE)
		err_sys("message header read error");

	/*
	* Read the actual dta, if there is any.
	*/

	if( (n = mesgptr->mesg_len) > 0)
 		if(read(fd, mesgptr->mesg_data, n) != n)
			err_sys("data read error");
	return n;
}	
