#include <stdio.h>
#include "mesgs.h"

Mesg mesgc;
Mesg mesgs;

void mesg_client(int ipcreadfd, int ipcwritefd);

void mesg_server(int ipcreadfd, int ipcwritefd);


