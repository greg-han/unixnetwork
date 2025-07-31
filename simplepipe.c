#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "unutils.h"

int main(){
	int pipefd[2], n;
	char buff[100];
	
	if (pipe(pipefd) < 0)
		err_sys("pipe error");

	printf("read fd = %d, write fd = %d\n", pipefd[0], pipefd[1]);

	if (write(pipefd[1], "hello world\n", 12) != 12)
		err_sys("write error");
	
	if( (n = read(pipefd[0], buff, sizeof(buff))) <= 0)
		err_sys("write error");

	write(1, buff, n); /*fd 1 = stdout */

	return 0;

}
