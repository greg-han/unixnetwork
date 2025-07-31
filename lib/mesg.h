#ifndef MESG_H
#define MESG_H

/*
* Definition of a message
*
* Could change max message size (4096) to a smaller value if desired.
* especially if messages on any given system are smaller than 4096
*
*/

#define MAXMESGDATA (4096-16)

#define MESGHDRSIZE (sizeof(Mesg) - MAXMESGDATA) /* length of mesg_len and mesg_type */

typedef struct {
	int mesg_len; /* #bytes in mesg_data, can be 0 or > 0 */
	long mesg_type; /*message type, must be > 0 */
	char mesg_data[MAXMESGDATA];
} Mesg;

#endif
