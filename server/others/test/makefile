all: client server

.client: client
client:
	gcc client.c my_recv.c -o client
.server: server
server: 
	gcc server.c my_recv.c -o server

clean:
	-rm *.o client server
