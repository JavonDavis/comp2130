/*
	C ECHO client example using sockets
*/
#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr

int main(int argc , char *argv[])
{
	int sock, sock_client,online_count,i,k;
	struct sockaddr_in server, server_client;
	
	int new_server_sock, new_client_sock;
	struct sockaddr_in new_server, new_client;
	
	char message[1000] , server_reply[2000], login[1];
	char username[10], password[10];
	char online_user[10] ,to_chat[10];
	int scl, talking_to = 0, var;
	char new_ip[30],new_port[10];
	char index[100];
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	printf("Socket created; sock = %d\n", sock);
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	
	puts("Connected\n");
	
	//Login Procedure
		while(1)
		{
			while(1)
			{
				printf("Enter username : ");
				scanf("%s" , username);
				//Send username
				if( send(sock , username , strlen(username) , 0) < 0)
				{
					puts("Sending username failed");
					return 1;
				}		
		
				//Receive acknowledgement for username
				if( recv(sock , login , 1 , 0) < 0)
				{
					puts("recv username failed");
					break;
				}
				
				//printf("login = %s\n",login);
				if(strcmp(login,"y")!=0)
					printf("Invalid Username\n");
				else
					break;	
			}	
			
		
		printf("Enter password : ");
		scanf("%s" , password);
	
		//Send password
		if( send(sock , password , strlen(password) , 0) < 0)
		{
			puts("Sending password failed");
			return 1;
		}
		//Receive acknowledgement for password
		if( recv(sock , login , 1 , 0) < 0)
		{
			puts("recv password failed");
			break;
		}
		
		//printf("login = %s\n",login);
		if(strcmp(login,"y")!=0)
			printf("Wrong Password\n");
		else
			break;	
		}
	
		printf("\n------------------- LOGIN SUCCESSFUL -----------------------\n");
				
		char reply[1];
		
	/* ----------- SELECT function block begins here ----------*/
		
		fd_set readfds; 
		FD_ZERO(&readfds);
	
		while(1) 
		{
		
		puts("waiting....");
		FD_SET(sock, &readfds);
		FD_SET(0, &readfds);
		
		memset(server_reply,'\0',2000);
		memset(message,'\0',1000);
		
		select(sock+1, &readfds, NULL, NULL, NULL);
		
		//If server gets first
		if(FD_ISSET(sock, &readfds)) {
		
			puts("server got here first");
			if(recv(sock, server_reply, 2000, 0)<0)
			{
				puts("recv failed");
				return 1;
			}
			
			printf("\nserver_reply = %s\n",server_reply);
			
			if(strcmp(server_reply,"\\is_busy")==0)
			{
				printf("\ntalking to value = %d\n",talking_to);
				
				if(talking_to == 0)	//not busy
				{
					//send(sock,"n",1,0);
					printf("\nreached here -- remote client not busy\n");
					
					FILE *p = fopen("reply.txt","w");
					if(p == NULL)
						puts("FILE ERROR" );
					fprintf(p,"n\n");
					fclose(p);
					
					memset(server_reply,'\0',2000);			
					printf("\nI am not busy\n");	
				}	
				else
				{
					//send(sock,"y",1,0);
					FILE *p = fopen("reply.txt","w");
					if(p == NULL)
							puts("FILE ERROR" );
					fprintf(p,"y\n");
					fclose(p);
					
					printf("\nI am busy, you know\n");	
				}	
			}	//end of is_busy
			else if(!strncmp(server_reply, "*",1))	//if first character is * then server is sending ip
			{
				memset(new_ip,'\0',30);
				memset(new_port,'\0',10);
				i = 1;
				while(server_reply[i] != ',')
				{
					new_ip[i-1] = server_reply[i];
					i++;
				}
				i++;
				int j=0;
				while(server_reply[i] != '\0')
				{
					new_port[j] = server_reply[i];
					i++;j++;
				}
				printf("\nnew_ip : %s  ;  new_port = %s\nCreating a new process for client now...\n", new_ip,new_port);
				
				/* -------------- same client code as above -----------------------*/
				
				if(!fork())
				{
					//Create socket
					sock_client = socket(AF_INET , SOCK_STREAM , 0);
					if (sock_client == -1)
					{
						printf("Could not create socket for the new connection");
					}
					printf("New client Socket created; sock_client = %d\n", sock_client);
					printf("\nTesting port number int new_port = %d \n",atoi(new_port));
	
/*					server_client.sin_addr.s_addr = inet_addr(new_ip);*/
					server_client.sin_addr.s_addr = (long int)atoi(new_ip);
					server_client.sin_family = AF_INET;
					server_client.sin_port = htons( atoi(new_port) );

					puts("Attempting to connect to other server...");
					
					//Connect to remote server
					if (connect(sock_client , (struct sockaddr *)&server_client , sizeof(server_client)) < 0)
					{
						perror("connect failed in client side. Error");
						return 1;
					}
	
					puts("Yoyo Connected with remote server-client\n");
					
					fd_set readfds_new; 
					FD_ZERO(&readfds_new);
	
					while(1) 
					{
		
						FD_SET(sock_client, &readfds_new);
						FD_SET(0, &readfds_new);
		
						memset(server_reply,'\0',2000);
						memset(message,'\0',1000);
						
						printf("\nEnter message : ");
						select(sock_client+1, &readfds_new, NULL, NULL, NULL);
						
						
						//If new server gets first
						if(FD_ISSET(sock_client, &readfds_new)) 
							{
								recv(sock_client, server_reply, 2000, 0);
								printf("\nMsg from server : %s \n", server_reply);
							}
						
						//If stdin gets first
						if(FD_ISSET(0, &readfds_new)) 
							{
/*								printf("Enter message : ");*/
								scanf("%s", message);
								send(sock_client  , message , strlen(message) , 0);
						
						
							}
						FD_CLR(sock_client, &readfds_new);
						FD_CLR(0, &readfds_new);		
					
					}
				
					return 1;
				}
				while(wait(NULL) != -1);	
				/* -------------- same client code as above -----------------------*/
				
			}
			else
			{
				//reply from server
				printf("Server reply :\n");
				puts(server_reply);
			}
				
		}	//end of server first
	
		
		//if stdin gets first
		if(FD_ISSET(0, &readfds)) {
			
			puts("stdin got here first");
/*			printf("Enter message : ");*/
			scanf("%s", message);
/*			send(sock , message , strlen(message) , 0);*/
			
			if(!strcmp(message,"y") || !strcmp(message,"n"))
			{
				FILE *p = fopen("reply_remote.txt","w");
				fflush(p);
				if(p==NULL)
					puts("---FILE ERROR---");
				fprintf(p,"%s",message);
				fclose(p);
				puts("I just typed y/n wrt intereseted");
				//send(sock , message , strlen(message) , 0);
			}
			
			else if(strcmp(message,"\\join")==0)
			{
				send(sock , message , strlen(message) , 0);
				
				puts("Enter the username you wish to chat with :");
				scanf("%s",to_chat);
			
				send(sock , to_chat , strlen(to_chat) , 0);
				
				recv(sock, server_reply, 2000, 0);
				if(!strcmp(server_reply,"z"))	//invalid
				{
					puts("INVALID USERNAME !!!!!!");
				}	
				else
				{
					puts("VALID USERNAME, connecting now ... ");
					memset(server_reply,'\0',2000);
					recv(sock, server_reply, 2000, 0);	//receive port number
					
					printf("\nblah blah server reply = %s \n",server_reply);
					i = atoi(server_reply);	//new port number
					
					printf("\nNew port number received = %d \n",i);
		/*--------------------------Same server code as above -----------------------*/
						if(!fork())
						{
								//Create socket
								new_server_sock = socket(AF_INET , SOCK_STREAM , 0);
								if (new_server_sock == -1)
								{
									printf("Could not create new socket");
								}
								printf("yoyo new Socket created; socket no = %d\n",new_server_sock);
	
								//Prepare the sockaddr_in structure
								new_server.sin_family = AF_INET; 
								new_server.sin_addr.s_addr = INADDR_ANY;
								
								new_server.sin_port = htons( i );
	
								//Bind
								if( bind(new_server_sock,(struct sockaddr *)&new_server , sizeof(new_server)) < 0)
								{
									//print the error message
									perror("Shit, new bind failed. Error");
									return 1;
								}
								puts("Yoyo, new bind done");
								
								//Listen
								listen(new_server_sock , 5);
	
								//Accept an incoming connection
								puts("Waiting for other client to connect...");
								int c;
								c = sizeof(struct sockaddr_in);
	
								//accept connection from an incoming client
								new_client_sock = accept(new_server_sock, (struct sockaddr *)&new_client, (socklen_t*)&c);
								if (new_client_sock < 0)
								{
									perror("Shit, new accept failed");
									return 1;
								}
								printf("yoyoyoy new Connection accepted from %d\n",new_client_sock);
								//return 1;
								
								char new_client_msg[2000];
								memset(new_client_msg,'\0',2000);
								int read_size;
								
								puts("Here we are..");
								
								
								fd_set readfds_new1; 
								FD_ZERO(&readfds_new1);
	
								while(1) 
								{
		
									FD_SET(new_client_sock , &readfds_new1);
									FD_SET(0, &readfds_new1);
		
									memset(new_client_msg,'\0',2000);
									memset(message,'\0',1000);
		
									printf("\nEnter message : ");
									select(new_client_sock +1, &readfds_new1, NULL, NULL, NULL);
									
									
									//If new client gets first
									if(FD_ISSET(new_client_sock , &readfds_new1)) 
										{
											recv(new_client_sock, new_client_msg , 2000 , 0);
											//printf("\n\nwaiting for client to type something...");
											printf("\nNew reply : %s",new_client_msg);
											send(new_client_sock , new_client_msg , strlen(new_client_msg) , 0);
										}
										
									//If stdin gets first
									if(FD_ISSET(0, &readfds_new1)) 
										{
/*											printf("\nEnter message : ");*/
											scanf("%s", message);
											send(new_client_sock  , message , strlen(message) , 0);
										}
									FD_CLR(new_client_sock , &readfds_new1);
									FD_CLR(0, &readfds_new1);		
					
								}
								
/*								*/
/*								*/
/*								//Receive a message from new client*/
/*								while( (read_size = recv(new_client_sock, new_client_msg , 2000 , 0)) > 0 )*/
/*								{*/
/*									printf("\n\nwaiting for client to type something...");*/
/*									printf("\nNew reply : %s",new_client_msg);*/
/*									send(new_client_sock , new_client_msg , strlen(new_client_msg) , 0);*/
/*									*/
/*									memset(new_client_msg,'\0',2000);*/
/*								}*/
/*	*/
/*								if(read_size == 0)*/
/*								{*/
/*									printf("Client %d disconnected\n",new_client_sock);*/
/*									fflush(stdout);*/
/*								}*/
/*								else if(read_size == -1)*/
/*								{*/
/*									perror("recv failed");*/
/*								}*/
								return 1;
								
								
						}	
						while(wait(NULL) != -1);	
				/*--------------------------Same server code as above -----------------------*/			
					
					
					
				}	
			}	//end of JOIN
		
			else if(strcmp(message,"\\list")==0)
			{
					send(sock , message , strlen(message) , 0);
					
					puts("===> CURRENTLY ONLINE USERS : ");
					FILE *f = fopen("online.txt","r");
					fscanf(f,"%d",&online_count);
					
					for(i=0;i<online_count;i++)
					{
						fscanf(f,"%s",online_user);
						fscanf(f,"%d",&scl);
						fscanf(f,"%d",&var);
						
						printf("%s ; Socket Descriptor = %d ; ip = %d\n",online_user,scl, var);
					}
					fclose(f);	
			}	//end of LIST
			else
				send(sock , message , strlen(message) , 0);

	
			
		}	//end of stdin first
		
		FD_CLR(sock, &readfds);
		FD_CLR(0, &readfds);
		
		}	//end of while(1) loop
		
		
		
//	}
	
	close(sock);
	return 0;
}