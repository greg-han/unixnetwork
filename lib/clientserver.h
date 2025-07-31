#ifndef CLIENTSERVER_H
#define CLIENTSERVER_H

/*Each client/server is a different client server for each IPC medium in the IPC section (chapter 3) of Unix Network Programming 1st edition */

void pipe_client(int readfd, int writefd);
void pipe_server(int readfd, int writefd);

#endif
