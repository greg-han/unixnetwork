#include "unutils.h"
#include <unistd.h>
#include <sys/wait.h>


int main(){
	int childpid, pipe1[2], pipe2[2];

	if(pipe(pipe1) < 0 || pipe(pipe2) < 0)
		err_sys("can't create pipes");

	if( (childpid = fork()) < 0){
		err_sys("can't fork");
	}else if (childpid > 0){  /* parent */
		close(pipe1[0]);
		close(pipe2[1]);
		
		pipe_client(pipe2[0], pipe1[1]);
		
		while (wait ((int *) 0) != childpid); /*wait for child */

		close(pipe1[1]);
		close(pipe2[0]);
                
		return 0;
 	}else{ /*child */
		close(pipe1[1]);
		close(pipe2[0]);

		pipe_server(pipe1[0], pipe2[1]);

		close(pipe1[0]);
		close(pipe2[1]);
		
		return 0;
	}
	return 0;
}
