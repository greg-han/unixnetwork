/* From Unix Network Programming 1st Edition, 6.12 "Asynchronous I/O".
  A simple non-asynchronous program that copies standard input to standard output 
*/

#include <stdlib.h>
#include <unistd.h>
#include "unutils.h"

#define BUFFSIZE 4096

//put something simple in here that shows it's process id
int main()
{

	int n;
	char buff[BUFFSIZE];

	while ( (n = read(0, buff, BUFFSIZE)) > 0)
              if (write(1,buff,n) != n)
                      err_sys("write error");

        if(n < 0)
              err_sys("read error");

        exit(0);
}
