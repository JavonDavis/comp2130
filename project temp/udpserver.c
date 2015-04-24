#include <stdio.h>
#include <stdlib.h>
#include <string.h>	//strlen
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>	//write

int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c , read_size, usr, pswd;
/*	int new_server_sock, new_client_sock;*/
	
	struct sockaddr_in server , client;
/*	struct sockaddr_in new_server, new_client;*/

	char username[5][10] = {"User1","User2","User3","User4","User5"};
	char password[5][10] = {"User1","User2","User3","User4","User5"};
	int *sock_desc_client = (int *)malloc(5*sizeof(int));
	int *ip = (int *)malloc(5*sizeof(int));
	
	char online[5][10];	
	int online_count = 0;
		
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	printf("Socket created; socket no = %d\n",socket_desc);
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	while(1)
	{
		//Listen
		listen(socket_desc , 5);
	
		//Accept an incoming connection
		puts("Waiting for incoming connections...");
		c = sizeof(struct sockaddr_in);
	
		//accept connection from an incoming client
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_sock < 0)
		{
			perror("accept failed");
			return 1;
		}
		printf("Connection accepted from %d\n",client_sock);
	

			int flag=0,i, k;
			char uname[10], pwd[10];
			char client_message[2000];
			
			char remote_msg[2000];
			
			//login test
			while(1)
			{
				while(1)
				{
					memset(uname,'\0',10);
					memset(pwd,'\0',10);
			
					//Receive username from client
					if((usr = recv(client_sock , uname , 10 , 0)) > 0)
					{
						printf("username = %s\n",uname);
						for(i=0;i<5;i++)
						{
							if(strcmp(uname,username[i])==0)
							{
								flag = 1;
								k = i;
								break;	
							}
						}
				
						if(flag!=0)
							{
								write(client_sock , "y" , 1);
								break;
							}
						else
							write(client_sock , "n" , 1);								
					}				
				}
			
				flag = 0;
				//Receive password from client
				if((pswd = recv(client_sock , pwd , 10 , 0)) > 0)
				{
					printf("password = %s\n",pwd);
				
					if(strcmp(pwd,password[k])==0)
						flag = 1;
				
					if(flag!=0)
					{
						write(client_sock , "y" , 1);
						break;
					}
					else
						write(client_sock , "n" , 1);
								
				}
			}
			
		strcpy(online[online_count],uname);
		sock_desc_client[online_count] = client_sock;
		ip[online_count] = client.sin_addr.s_addr;	//redundant as same machine
		
		online_count++;
		
		FILE *f = fopen("online.txt","w");
		fprintf(f,"%d\n",online_count);
		
		for(i=0;i<online_count;i++)
		{	
			printf("%s\n",online[i]);
			fprintf(f,"%s\n",online[i]);	//username
			fprintf(f,"%d\n",sock_desc_client[i]);	//socket descriptor
			fprintf(f,"%d\n",ip[i]);	//ip
		}
		fclose(f);
		
		if(!fork())
		{	
			char busy_reply[1], talk_reply[1];
			char online_user[10];
			int var, k1, var1;
		//	printf("\n-------------Client Socket Descriptor : %d --------------- \n",client_sock);
			
			memset(client_message,'\0',2000);
			//Receive a message from client
			while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
			{
				//Send the message back to client
				//write(client_sock , client_message , strlen(client_message));
				if(strcmp(client_message,"\\join")==0)
				{
					memset(client_message,'\0',2000);
					recv(client_sock , client_message , 10 , 0);	//receive username of other client
					
					printf("\nJoin step 1: %s\n",client_message);
					
					FILE *f = fopen("online.txt","r");
					fscanf(f,"%d",&online_count);
			
					k = -1;	
	
					for(i=0;i<online_count;i++)
					{
						fscanf(f,"%s",online_user);		//username
						if(!strcmp(online_user,client_message))
							k=i;
							
						fscanf(f,"%d",&var);	//socket desc
						if(var==client_sock)
							k1 = i;
							
						fscanf(f,"%d",&var1);	//ip
					}
					fclose(f);	

					printf("\nJoin step 2: k = %d\n",k);
					
					if(k==-1)
					{
						puts("INVALID USERNAME !!");
						memset(talk_reply,'\0',1);
						strcpy(talk_reply,"z");	//invalid username notification to client
						write(client_sock , talk_reply , 1);
					}	
					else	//valid username
					{	
						printf("Index = %d \n",k);
					
						FILE *f = fopen("online.txt","r");
						fscanf(f,"%d\n",&online_count);
		
						for(i=0;i<=online_count;i++)
						{	
							fscanf(f,"%s",online[i]);
							fscanf(f,"%d",&sock_desc_client[i]);
							fscanf(f,"%d",&ip[i]);
						}
						fclose(f);
						
						printf("\nJoin Step 3 : sock_desc_client[k] = %d ; ip[k] = %d\n",sock_desc_client[k], ip[k]);
						
						memset(remote_msg,'\0',2000);
						strcpy(remote_msg,"\\is_busy");
						puts("Checking for is_busy now");
						
						
						strcpy(talk_reply,"x");	//send anything (say x) for positive username
						write(client_sock , talk_reply , 1);
						
						puts("between write");
						write(sock_desc_client[k] , remote_msg , strlen(remote_msg));
						
						//memset(busy_reply,'\0',1);
						//recv(sock_desc_client[k] ,busy_reply , 1 , 0);
						puts("back from is_busy");
						sleep(1);
						
						FILE *p;
						while(1)
						{
							p = fopen("reply.txt","r");
							if(p == NULL)
								puts("FILE ERROR" );
/*								i = 0; //timepass*/
							else
							{		
							fscanf(p,"%s",busy_reply);
							fclose(p);
							remove("reply.txt");
							break;
							}
						}
/*						remove("reply.txt");*/
						
						printf("\nJoin Step 4 : is_busy_reply = %s\n",busy_reply);
						
						if(!strcmp(busy_reply,"y"))	//busy
						{
							memset(client_message,'\0',2000);
							strcpy(client_message,"Cannot connect as the remote client is busy with someone else\n");
							write(client_sock , client_message , strlen(client_message));
						}
						else	//available to chat
						{
							//ask remote client if it wants to chat with the requesting one
							memset(remote_msg,'\0',2000);
							strcpy(remote_msg,"Do you wish to talk with ");
							strcat(remote_msg,online[k1]);
							strcat(remote_msg," ? (y/n)\n");
						
							printf("\nJoin Step 5 : remote_msg = %s\n",remote_msg);
							
							write(sock_desc_client[k] , remote_msg , strlen(remote_msg));
							
							sleep(1);
							
							FILE *p;
							while(1)
							{
							p = fopen("reply_remote.txt","r");
							if(p==NULL)
								puts("---FILE ERROR---");
/*								i=0;	//timepass*/
							else
								{	
								fscanf(p,"%s",busy_reply);
								fclose(p);
								remove("reply_remote.txt");
								break;
								}	
							}
/*							remove("reply_remote.txt");*/
								
							//recv(sock_desc_client[k] ,talk_reply , 1 , 0);
							printf("\nJoin Step 6 : interested ? => %s\n",busy_reply);
							
							if(!strcmp(busy_reply,"n"))	//Not interested
							{
								memset(client_message,'\0',2000);
								strcpy(client_message,"The requested client does not wish to talk with you. Sorry about that.\n");
								write(client_sock , client_message , strlen(client_message));
							}
							else
							{
								printf("\n----coming soon--\n");
								
								memset(remote_msg,'\0',2000);
								
								i = 8888 + (k+1)*2;
								
								char temp[50];
								memset(temp,'\0',50);
/*								sprintf(temp,"%d",server.sin_addr.s_addr);*/
								sprintf(temp,"%d",ip[k]);
								
								strcpy(remote_msg,"*");	//ip
								strcat(remote_msg,temp);
								strcat(remote_msg,",");
								
								memset(temp,'\0',50);	//port
								sprintf(temp,"%d",i);
								
								write(client_sock , temp , strlen(temp));	//send port number to server-client
								
								sleep(1);	//wait for server to get hosted
								
								strcat(remote_msg,temp);
								
								printf("\nJoin Step 7 : connection_msg = %s\n",remote_msg);
							
								write(sock_desc_client[k] , remote_msg , strlen(remote_msg));
								
								close(sock_desc_client[k]);
								close(client_sock);
								
								printf("\n----lets wait ----\n");
								
								
							}
						
						}
					}
				}
				puts(client_message);
				memset(client_message,'\0',2000);
			}
	
			if(read_size == 0)
			{
				printf("Client %d disconnected\n",client_sock);
				fflush(stdout);
			}
			else if(read_size == -1)
			{
				perror("recv failed");
			}
			return 1;
		} //end of fork
		//while(wait(NULL) != -1);
	}
	return 0;
}