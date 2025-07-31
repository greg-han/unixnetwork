#include "unutils.h" 
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 1024

int main(){
	int n;
	char line[MAXLINE], command[MAXLINE + 10];
        FILE *fp;
	
       /*
 	* Read the filename from standard in
        * This doesn't read from stdin directly, it needs a filename
        * to do so, use read() instead of fgets()
        * eg. if you want to use "echo "Hello World!"" instead
 	*/

	if (fgets(line, MAXLINE, stdin) == NULL)
		err_sys("filename read error");


	/*
	* Use popen to create a pipe and execute the command
        */
	
	sprintf(command, "cat %s", line);

	if( (fp = popen(command, "r")) == NULL)
		err_sys("popen error");

	/* Read the data from the FILE pointer and write to
        * standard output
	*/

	while((fgets(line, MAXLINE, fp)) != NULL){
		n = strlen(line);
 		if (write(1, line, n) != n)
			err_sys("data write error");
        }
	
	if(ferror(fp))
		err_sys("fgets error");
 	
	pclose(fp);

	return 0;
}
