
all: simpleio

simpleio: simpleio.c lib/unutils.h lib/err.h
	gcc -Ilib simpleio.c -o simpleio lib/err.o

simpleioasync: simpleioasync.c lib/unutils.h lib/err.h
	gcc -Ilib simpleioasync.c -o simpleioasync lib/err.o

lockme: lockme.c lib/unutils.h lib/err.h lib/locks.h
	gcc -Ilib lockme.c -o lockme lib/err.o lib/locks.o

simplepipe: simplepipe.c lib/unutils.h lib/err.h
	gcc -Ilib simplepipe.c -o simplepipe lib/err.o

pipepopen: pipepopen.c lib/unutils.h lib/err.h
	gcc -Ilib pipepopen.c -o pipepopen lib/err.o

pipeclientserver: pipeclientserver.c lib/unutils.h lib/err.h lib/clientserver.h
	gcc -Ilib pipeclientserver.c -o pipeclientserver lib/err.o lib/clientserver.o

fifomain: fifomain.c lib/unutils.h lib/err.h lib/clientserver.h
	gcc -Ilib fifomain.c -o fifomain lib/err.o lib/clientserver.o

fifoclient: fifoclient.c lib/fifo.h lib/err.h lib/clientserver.h
	gcc -Ilib fifoclient.c -o fifoclient lib/err.o lib/clientserver.o

fifoserver: fifoserver.c lib/fifo.h lib/err.h lib/clientserver.h
	gcc -Ilib fifoserver.c -o fifoserver lib/err.o lib/clientserver.o

mesgclient: mesgclient.c lib/fifo.h lib/err.h lib/mesg_clientserver.h lib/unutils.h
	gcc -Ilib mesgclient.c -o mesgclient lib/err.o lib/mesg_clientserver.o lib/mesgs.o

mesgserver: mesgserver.c lib/fifo.h lib/err.h lib/mesg_clientserver.h lib/unutils.h
	gcc -Ilib mesgserver.c -o mesgserver lib/err.o lib/mesg_clientserver.o lib/mesgs.o

clean: 
	rm simpleio simpleioasync
