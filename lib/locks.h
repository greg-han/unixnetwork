#ifndef LOCKS_H
#define LOCKS_H


void my_null_lock(int fd);
void my_null_unlock(int fd);

void my_sv_lock(int fd);
void my_sv_unlock(int fd);
void my_sv_lock_nb(int fd);

#endif
