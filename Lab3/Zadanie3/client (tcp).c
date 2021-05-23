#include <stdio.h>	
#include <string.h>	
#include <sys/socket.h>	
#include <arpa/inet.h>	
#include <unistd.h>

int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
	char message[100];
    
	sock = socket(AF_INET , SOCK_STREAM , 0);
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	connect(sock , (struct sockaddr *)&server , sizeof(server));
	
	puts("Connected\n");
	
    printf("Enter message : ");
    scanf("%s" , message);
    
    send(sock , message , strlen(message) , 0);
    
	close(sock);
	
    return 0;
}
