#define SEQFILE "seqno" /* filename */
#define MAXBUFF 100
#include "unutils.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(){

             int fd, i, n, pid, seqno;
             char buff[MAXBUFF + 1];

             pid = getpid();
             
             if( (fd = open(SEQFILE, 2)) < 0)
		  err_sys("can't open %s");
        
          for(int i = 0; i < 20; i++){
             lseek(fd, 0L, 0); /* rewind before read */
             if( (n = read(fd, buff, MAXBUFF)) <= 0)
                      err_sys("read error");
              buff[n] = '\0';  /* null terminate for scanf */

              if( ( n = sscanf(buff, "%d\n", &seqno)) != 1)
                  err_sys("sscanf error");
 
                 printf("pid = %d, seq# = %d\n", pid, seqno);
 
                 seqno++; /* increment the sequence number */
 
                 sprintf(buff, "%03d\n", seqno);
                 n = strlen(buff);
                 lseek(fd, 0L, 0); /* rewind before write */
                 if(write(fd, buff, n) != n)
                         err_sys("write error");
 
                 //my_null_unlock(fd);
                 my_sv_unlock(fd);
                 printf("pid: %d unlocked\n", getpid());
          }
            return 0;
}
