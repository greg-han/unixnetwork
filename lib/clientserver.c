#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "unutils.h"
#include "clientserver.h"
#include "err.h"

#define MAXBUFF 1024

void pipe_client(int readfd, int writefd){

	char buff[MAXBUFF];
	int n;

	/*
	* Read the filename from standard input.
	* write it to the IPC descriptor
        */
	
	if(fgets(buff, MAXBUFF, stdin) == NULL)
		err_sys("client: filename read error");

	n = strlen(buff);
	if(buff[n-1] == '\n')
		n--; /*ignore newline from fgets() */
	if(write(writefd, buff, n) != n)
		err_sys("client: filename write error");	
	
	/*
	* Read the data from the IPC descriptor and write
        * to standard output
       */

        while( ( n = read(readfd, buff, MAXBUFF)) > 0)
		if (write(1, buff, n) != n)  /*fd 1 = stdout */
			err_sys("client: data write error");
	if(n < 0)
		err_sys("client: data read error"); 
}

void pipe_server(int readfd, int writefd){
	char buff[MAXBUFF];
	char errmesg[256], *sys_err_str();
        int n, fd;
        extern int errno;

        /*
        * Read the filename from the IPC descriptor.
        */

	if( ( n = read(readfd, buff, MAXBUFF)) <= 0)
		err_sys("server: filename read error");
	buff[n] = '\0';  /*null terminate the filename */

	if( (fd = open(buff, 0)) < 0){
   	/*
        * Error. Format an error message and send it back to the client.
        */
	
	sprintf(errmesg, ": can't open, %s\n", sys_err_str());
	strcat(buff, errmesg);
 	n = strlen(buff);
	if (write(writefd, buff, n) != n)
		err_sys("server: errmesg write error");
	} else {
		/*
 		* Read the data from the file and write to
                * the IPC descriptor
		*/

		while( (n = read(fd, buff, MAXBUFF)) > 0)
			if (write(writefd, buff, n) != n)
				err_sys("server: data write error");
		if(n < 0)
			err_sys("server: read error");

		}

}


