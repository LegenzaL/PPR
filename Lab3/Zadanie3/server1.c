#include <stdlib.h>
#include <stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>	
#include<unistd.h>	


//======================================================================
int main(int const argc, char ** argv){

    int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[10];
    
	for (int i=0; i < 10; ++i)
	{
		client_message[i]=0;
    }
    
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	bind(socket_desc,(struct sockaddr *)&server , sizeof(server));

	listen(socket_desc , 3);
	
	puts("Waiting for connection...");
	c = sizeof(struct sockaddr_in);
	
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        
	while( (read_size = recv(client_sock , client_message , 10 , 0)) > 0 )
	{
        printf("%s\n", client_message);
	}
    

    return 0;
}
//======================================================================
