#include <sys/types.h> /* system type definitions */
#include <sys/socket.h> /*network system functions*/
#include <netinet/in.h> /* protocol and struct definitions */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int i,sock;
	struct sockaddr_in my_addr;
	unsigned short listen_port = 60070;

	/* socket has been created*/
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // domain,communication type,Protocol
	if(sock<0)
		printf("socket() failed\n");

	/*make local address structure */
	memset(&my_addr,0,sizeof(my_addr));/*clr structure */
	my_addr.sin_family = AF_INET; /* address family */
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* my ip */
	my_addr.sin_port = htons(listen_port);

	/* bind socket to the local address */
	i = bind(sock, (struct sockaddr *) &my_addr,sizeof(my_addr));
	if(i <0 )
		printf("bind() failed\n");
	
	i = listen(sock,5); // second arg is max # of connections in queue
	if(i<0)
		printf("listen() failed");

	int sock_recv,addr_size;
	struct sockaddr_in recv_addr;

	addr_size = sizeof(recv_addr);
	sock_recv = accept(sock, (struct sockaddr *) &recv_addr, &addr_size);

	int bytes_received;
	char text[80];

	while(1)
	{
		bytes_received = recv(sock_recv,text,80,0);
		text[bytes_received] = 0;
		printf("Received: %s\n",text );
		int k; 
		k = strcmp(text,"shutdown");
		printf("%d\n", k);
		if (strcmp(text,"shutdown") ==0)
			break;
	}
	

	close(sock_recv);
	close(sock);
}
