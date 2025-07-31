#include "locks.h"
#include "err.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

void my_null_lock(int fd){
     return;
}

void my_null_unlock(int fd){
     return;
}

void my_sv_lock(int fd){
    lseek(fd, 0L, 0); /* rewind before lock */
    if(lockf(fd, F_LOCK, 0L) == -1) /* 0L -> lock entire field */
         err_sys("can't F_LOCK");
}

void my_sv_unlock(int fd){
    lseek(fd, 0L, 0);
    if(lockf(fd, F_ULOCK, 0L) == -1)
    	err_sys("cant F_ULOCK");
}

void my_sv_lock_nb(int fd){
    lseek(fd, 0L, 0); /* rewind before lock */
    if(lockf(fd, F_TLOCK, 0L) == -1){ /* 0L -> lock entire field */
       if(errno == EACCES || errno == EAGAIN){
          printf("PID %d: lock busy\n", getpid());
          return;
       } 
       else{
         err_sys("can't F_LOCK");
       }
    }
}


