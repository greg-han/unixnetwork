#include "mesg_clientserver.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void mesg_client(int ipcreadfd, int ipcwritefd){
	int n;
	/* Read the filename from standard input, write it as
 	* a message to the IPC descriptor.
	*/

	if(fgets(mesgc.mesg_data, MAXMESGDATA, stdin) == NULL)
		err_sys("filename read error");
	n = strlen(mesgc.mesg_data);
	if (mesgc.mesg_data[n-1] == '\n')
		n--; /* ignore newline from fgets()  */	
	mesgc.mesg_len = n;
	mesgc.mesg_type = 1L;
	mesg_send(ipcwritefd, &mesgc);
				
  	/* Receive the message from the PIC descriptor and write
	* the data to standard output.
	*/

	while ( (n = mesg_recv(ipcreadfd, &mesgc)) > 0)
		if(write(1, mesgc.mesg_data, n) != n)
			err_sys("data write error");

	if(n < 0)
		err_sys("data read error");
}

extern int errno;

void mesg_server(int ipcreadfd, int ipcwritefd){
	int n, filefd;
	char errmesg[256], *sys_err_str();

	/*
	* Read the filename from the IPC descriptor
	*/
	mesgs.mesg_type = 1L;
	if( (n = mesg_recv(ipcreadfd, &mesgs)) <= 0)
		err_sys("server: filename read error");
	mesgs.mesg_data[n] = '\0'; /* null terminate filename */
	if ( (filefd = open(mesgs.mesg_data, 0)) < 0) {
		/*
		* Error. Format an error message and send it back
		* to the client.
		*/
		sprintf(errmesg, ": can't open, %s\n", sys_err_str());
	        strcat(mesgs.mesg_data, errmesg);		
		mesgs.mesg_len = strlen(mesgs.mesg_data);
		mesg_send(ipcwritefd, &mesgs);
	} else{
		/*
		* Read the data from the file and send a message
		* to the IPC descriptor.
		*/

		while( (n = read(filefd, mesgs.mesg_data, MAXMESGDATA)) > 0){
			mesgs.mesg_len = n;
			mesg_send(ipcwritefd, &mesgs);
		}
		close(filefd);

		if (n < 0)
			err_sys("server: read error");

	}
	/*
	* Send a message with a length of 0 to signify the end.
	*/
	
	mesgs.mesg_len = 0;
	mesg_send(ipcwritefd, &mesgs);
}
