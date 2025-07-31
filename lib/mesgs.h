#include "mesg.h"

/* send (write) a "Mesg" struct into a fd*
* all fields must be filled
*/
void mesg_send(int fd, Mesg *mesgptr);

/* recieve (read) a "Mesg" struct from a fd.
* fill in mesg_len, mesg_type, and mesg_data fields, and return
* mesg_len as the return value also.
*/
int mesg_recv(int fd, Mesg *mesgptr);


