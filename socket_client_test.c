#include <sys/types.h> /* system type definitions */
#include <sys/socket.h> /*network system functions*/
#include <netinet/in.h> /* protocol and struct definitions */
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(){
	int i,sock,buf_size = 1024;
	struct sockaddr_in addr_send;
	char *server_ip ="127.0.0.1";
	unsigned short server_port = 60000;

	/* socket has been created*/
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // domain,communication type,Protocol
	if(sock<0)
		printf("socket() failed\n");

	memset(&addr_send,0,sizeof(addr_send));/*clr structure */
	addr_send.sin_family = AF_INET; /* address family */
	addr_send.sin_addr.s_addr = inet_addr(server_ip); /* my ip */
	addr_send.sin_port = htons(server_port);

	i = connect(sock, (struct sockaddr *) &addr_send,sizeof(addr_send));

	if (i<0)
		printf("connect() failed\n");

	int bytes_sent,send_len;
	char text[80];
	char buf[buf_size];

	while(1)
	{
		printf("Send ?\n");
		fgets(text,80,stdin);
		text[strlen(text) -1] = '\0';
		if(strcmp(text,"quit")==0)
			break;

		strcpy(buf,text);
		send_len = strlen(text);


		bytes_sent = send(sock,buf,send_len,0);//socket identifier,address pointing to data,the number of bytes to send,flag settings

		

		printf("%d bytes sent\n",bytes_sent);

	}
	
	// i = close(sock);
	// if(i<0)
	// 	printf("close() failed\n");
	return 0;
}