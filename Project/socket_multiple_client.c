#include <stdio.h>  //printf
#include <string.h> //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h>  //inet_addr

#define PORT 60000

int main(){
    int sock,i;
    char name[80],response[80],command[80],ip[80],port[10];
    struct sockaddr_in server,new_server,client, server_client,new_client;
    char remote_name[80],nIp[80],nPort[80];
    char client_msg[2000],message[1000];
    int in_conversation = 0;
    int size_new,new_client_socket;

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock < 0 )
    {
        printf("Could not create socket");
    }

    printf("Socket created; sock = %d\n", sock);

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( PORT );

    i = connect(sock, (struct sockaddr *) &server, sizeof(server));
    if(i<0)
    {
        perror("connect");
        return 1;
    }

    printf("Connected\n");
    while(1)
    {
        printf("Enter name: ");
        scanf("%s",name);

        i = send(sock,name,strlen(name),0);
        if(i<0)
        {
            printf("Could not send your name\n");
            return 1;
        }

        i = recv(sock,response,80,0);
        response[strlen(response) -1] = '\0';
        if(i<0)
        {
            printf("Server did not acknowledge your name\n");
            return 1;
        }
        else
        {
            printf("%s\n",response );
        }

        printf("\t\t\t%s\t\t\t\n",name );
        fd_set readfs;
        FD_ZERO(&readfs);
        printf("Command List:\n\\l - view available clients\n");
        printf("\\c - to communicate with a client\n");
        printf("\\g - to view groups\n");
        while(1)
        {
            FD_SET(sock, &readfs);
            FD_SET(0, &readfs);

            memset(response,'\0',2000);
            memset(command,'\0',1000);

            
            select(sock+1, &readfs, NULL, NULL, NULL);
            if(FD_ISSET(sock,&readfs))
            {
                i = recv(sock,response,2000,0);
                if(i<0){
                    printf("recv failed\n");
                    return 1;
                }
                printf("Server reply: \n");
                if(strcmp(response,"b")==0)
                {
                    //printf("\nConvo with:%d\n",in_conversation);
                    if(in_conversation ==0)
                    {
                        send(sock,"n\0",2,0);
                        send(sock,"n\0",2,0);
                        printf("client not busy\n");
                        
                        
                        memset(response,'\0',2000);
                    }
                    else
                    {
                        printf("Client busy\n");
                        send(sock,"y\0",2,0);
                    }
                }
                else if(strcmp(response,"n") ==0)
                {
                    printf("Server could not find user\n");
                }
                else if(!strncmp(response, "@",1))
                {
                    memset(nIp,'\0',30);
                    memset(nPort,'\0',10);

                    i=1;

                    while(response[i] != ',')
                    {
                        nIp[i-1] = response[i];
                        i++;
                    }
                    i++;
                    int j=0;
                    while(response[i] != '\0')
                    {
                        nPort[j] = response[i];
                        i++;
                        j++;
                    }

                    //printf("\nnew_ip : %s  ;  new_port = %s\nForking new process...\n", nIp,nPort);
                    if((i=fork())==0)
                    {
                        new_client_socket = socket(AF_INET , SOCK_STREAM , 0);
                        if(new_client_socket<0)
                        {
                            perror("socket");
                        }

                        server_client.sin_addr.s_addr = (long int)atoi(nIp);
                        server_client.sin_family = AF_INET;
                        server_client.sin_port = htons( atoi(nPort) );

                        printf("Attemptig to connect\n");

                        i = connect(new_client_socket,(struct sockaddr *) &server_client, sizeof(server_client));
                        if(i<0)
                        {
                            perror("Connect");
                            return 1;
                        }

                        printf("Converstion begun\n");
                        in_conversation = 1;
                        fd_set readfs_new; 
                        FD_ZERO(&readfs_new);
                        while(1)
                        {
                            FD_SET(new_client_socket, &readfs_new);
                            FD_SET(0, &readfs_new);
            
                            memset(response,'\0',2000);
                            memset(message,'\0',1000);
                            
                            printf("\nEnter message : ");
                            select(new_client_socket+1, &readfs_new, NULL, NULL, NULL);
                            
                            
                            // //If new server gets first
                            // if(FD_ISSET(new_client_socket, &readfs_new)) 
                            // {
                            //     recv(new_client_socket, response, 2000, 0);
                            //     printf("\nMsg from server : %s \n", response);
                            // }
                            
                            //If stdin gets first
                            if(FD_ISSET(0, &readfs_new)) 
                            {
    /*                              printf("Enter message : ");*/
                                scanf("%s", message);
                                send(new_client_socket  , message , strlen(message) , 0);
                        
                        
                            }
                            FD_CLR(new_client_socket, &readfs_new);
                            FD_CLR(0, &readfs_new);
                        }
                    }
                }
                else
                {
                    printf("%s\n",response );
                    //send(sock,response,strlen(response),0);
                }
                    
            }

            if(FD_ISSET(0, &readfs)) {

                scanf("%s",command);

                i = send(sock,command,strlen(command),0);
                if(strcmp(command,"y")==0)
                {
                    send(sock,command,1,0);
                    //send(sock,command,1,0);
                }
                else if(strcmp(command,"\\c") == 0)
                {
                    printf("Please enter the name of the client you wish to chat with\n");
                    scanf("%s",remote_name);
                    send(sock,remote_name,strlen(remote_name),0);

                    recv(sock,response,80,0);
                    //response[strlen(response) -1] = '\0';
                    //printf("Reply:%s\n",response );
                    if(strcmp(response,"n") ==0)
                    {
                        printf("Invalid name\n");
                    }
                    else
                    {
                        int port,new_sock;
                        printf("%s\n",response );
                        memset(response,'\0',2000);
                        recv(sock,response,2000,0);

                        printf("new port:%s\n", response);
                        port = atoi(response);

                        if((i = fork()) == 0)
                        {
                            new_sock = socket(AF_INET,SOCK_STREAM,0);
                            if(new_sock<0)
                            {
                                perror("socket");
                            }

                            printf("new socket created:%d\n",new_sock );

                            new_server.sin_family = AF_INET; 
                            new_server.sin_addr.s_addr = INADDR_ANY;
                            
                            new_server.sin_port = htons( port );

                            i = bind(new_sock, (struct sockaddr *) &new_server, sizeof(new_server));
                            if(i<0)
                            {
                                perror("bind");
                            }

                            listen(new_sock,1);

                            printf("Waiting for client to connect.\n");
                            
                            size_new = sizeof(struct sockaddr_in);

                            new_client_socket = accept(new_sock,(struct sockaddr *) &new_client, (socklen_t *)&size_new);

                            if(new_client_socket<0)
                            {
                                perror("accept");
                            }

                            printf("New connection accepted from %d\n", new_client_socket);
                            
                            memset(client_msg,'\0',2000);
                            int read_size;

                            printf("Conversation begun\n");
                            in_conversation =1;
                            fd_set readfs_new; 
                            FD_ZERO(&readfs_new);

                            while(1) 
                            {
    
                                FD_SET(new_client_socket , &readfs_new);
                                FD_SET(0, &readfs_new);
    
                                memset(client_msg,'\0',2000);
                                memset(message,'\0',1000);
    
                                printf("\nEnter message : ");
                                select(new_client_socket +1, &readfs_new, NULL, NULL, NULL);
                                
                                
                                //If new client gets first
                                if(FD_ISSET(new_client_socket , &readfs_new)) 
                                    {
                                        recv(new_client_socket, client_msg , 2000 , 0);
                                        //printf("\n\nwaiting for client to type something...");
                                        printf("\nNew reply : %s",client_msg);
                                        //send(new_client_socket , client_msg , strlen(client_msg) , 0);
                                    }
                                    
                                //If stdin gets first
                                if(FD_ISSET(0, &readfs_new)) 
                                {
/*                                          printf("\nEnter message : ");*/
                                    scanf("%s", message);
                                    send(new_client_socket  , message , strlen(message) , 0);
                                }
                                FD_CLR(new_client_socket , &readfs_new);
                                FD_CLR(0, &readfs_new);       
                
                            }
                        }while(wait(NULL) != -1);

                    }
                }
            }
        }
    }
}