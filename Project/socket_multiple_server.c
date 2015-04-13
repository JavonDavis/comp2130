#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
  
#define PORT 60000
 
int main(int argc , char *argv[])
{
    int main_socket , addrlen , new_socket , client_socket[10] , max_clients = 30 , activity, i , num_bytes , sd;
    int max =10,send_len;
    int count = 0;
    int ips[30];
    struct sockaddr_in address,recv_addr;
    char names[3][14];
    char name[80],response[80];
    char online[5][2];
    int listening[5];
    char reply[30];
    char buffer[1025],buff[1024];  //data buffer of 1K
      
    //set of socket descriptors
    fd_set readfds;
      
    //a message
    char *message = "Enter your name:\n";

    for(i = 0; i<max_clients; i++)
    {
        client_socket[i] = 0;
    }

    main_socket = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
    if(main_socket == 0)
    {
        perror("socket creation failed\n");
        exit(0);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    //bind the socket to the port
    i = bind(main_socket, (struct sockaddr *) &address,sizeof(address));
    if(i<0)
    {
        perror("bind failed");
        exit(0);
    }

    printf("Listener on port %d \n", PORT);
     
    
    while(1)
    {
        //try to specify maximum of 3 pending connections for the master socket
        i = listen(main_socket, 3) ;
        if (i < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        addrlen = sizeof(address);
        printf("Waiting for connections...\n");


        //accept connection from an incoming client
        sd = accept(main_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (sd < 0)
        {
            perror("accept failed");
            return 1;
        }
        printf("Connection accepted from %d\n",sd);

        memset(name,'\0',2000);
        //Receive name from client
        i = recv(sd , name , 80 , 0);
        printf("name = %s\n",name);
        strcpy(names[count],name);
        client_socket[count] = sd;
        ips[count] = address.sin_addr.s_addr;

        write(sd,"Name saved\0",11);

        client_socket[count] = sd;
        count+=1;  
        
        if(!fork())
        {
            char busy[80],current[80],accept[1];
            memset(response,'\0',2000);
            printf("forked process\n");
            int size;
           
            while((size = recv(sd,response,2000,0)) >0)
            {
                // response[strlen(response)-1] = '\0';
                if(strcmp(response,"\\c")==0)
                {
                    //printf("Here\n");
                    //Begin chat process 
                    memset(response,'\0',2000);
                    recv(sd,response,2000,0);//stage 1 get name of other client

                    printf("Request to connect to %s\n",response);

                    int k = 0;
                    //char list[100];
                    //char socket[80];
                    //char ip[80];
                    int new_sock,new_ip,found =0;
                    for(k=0;k<max;k++)
                    {
                        if(client_socket[k]!=0)
                        {
                            if(strcmp(names[k],response) ==0)
                            {
                                new_sock = client_socket[k];
                                new_ip = ips[k];
                                found =1;
                            }
                        }
                        

                    }

                    if(!found)
                    {
                        printf("Name not found.\n");
                        memset(reply,'\0',1);
                        strcpy(reply,"n");
                        write(sd,reply,1);
                    }
                    else
                    {
                        printf("found user %s\n",response);
                        memset(reply,'\0',1); //TODO - investigate 
                        strcpy(reply,"b");

                        printf("Checking if user is busy\n");

                        write(sd,"Checking if user is busy\n\0",26);

                        write(new_sock,reply,1);


                        recv(new_sock,busy,80,0);
                        if(strcmp(busy,"y") == 0)
                        {
                            write(sd,"Cannot cannot client is busy.\0",42);
                        }
                        else //setup p2p
                        {
                            //write(sd,"Client not busy attempting to connect.\0",39);
                            
                            for(k=0;k<max;k++)
                            {
                                if(client_socket[k] == sd)
                                {
                                    strcpy(current,names[k]);
                                    break;
                                }
                                

                            }
                            
                            strcpy(reply,current);
                            strcat(reply," would like to chat with you? (y - yes,n- no)\n");

                            write(new_sock,reply,strlen(reply));

                            recv(new_sock,message,1,0);
                            if(strcmp(message,"y"))
                            {
                                memset(reply,'\0',2000);
                                int new_port;
                                char temp[80];
                                new_port = PORT + (k+1)*2;

                                sprintf(temp,"%d",new_ip);
                                strcpy(reply,"@");
                                strcat(reply,temp);
                                strcat(reply,",");

                                memset(temp,'\0',80);
                                sprintf(temp,"%d",new_port);

                                write(sd,temp,strlen(temp));

                                strcat(reply,temp);

                                printf("Message:%s\n", reply);

                                write(new_sock,reply,strlen(reply));

                                close(sd);
                                close(new_sock);

                                printf("Convo initiated\n");
                            }
                        }
                    }

                }
                else if(strcmp(response,"\\l") == 0)
                {
                    int k = 0;
                    char list[100];
                    char socket[80];
                    char ip[80];
                    for(k=0;k<max;k++)
                    {
                        if(client_socket[k]!=0)
                        {
                            printf("%d\n", k);
                           strcat(list,names[k]);
                            strcat(list,"\t");
                            sprintf(socket,"%d",client_socket[k]);
                            sprintf(ip,"%d",ips[k]);
                            strcat(list,socket);
                            strcat(list,"\t");
                            strcat(list,ip);
                            strcat(list,"\n"); 
                        }
                        

                    }
                    write(sd,list,strlen(list));
                    memset(list,'\0',sizeof(list));
                }
            }

            if(size == 0)
            {
                printf("Client %d disconnected\n",sd);
                fflush(stdout);
            }
        }      
    }

    
}