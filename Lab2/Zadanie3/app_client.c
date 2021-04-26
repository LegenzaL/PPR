#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>	
#include<unistd.h>	
#include "app.h"


void string2hex(char* input, char* output)
{
    int loop;
    int i; 
    
    i=0;
    loop=0;
    
    while(input[loop] != '\0')
    {
        sprintf((char*)(output+i),"%02X", input[loop]);
        loop+=1;
        i+=2;
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';
}


void
testowy_1(char *host, char *message)
{
    char hex[100];
    for (int i=0; i < 100; ++i)
	{
		hex[i]=0;
    }
    
    string2hex(message, hex);
    
    CLIENT *clnt;
	wyjscie  *result_1;
	wejscie  obliczenia_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, TESTOWY, PROBNA, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */


    for (int a=0; a < 100; ++a)
	{
		obliczenia_1_arg.buffer[a]=0;
    }

    obliczenia_1_arg.size=0;
    int j = 0;
    
    while(hex[j]!=0)
    {
		obliczenia_1_arg.buffer[j] = hex[j];
        obliczenia_1_arg.size++;
        j++;
    }
	
	
		
    result_1 = obliczenia_1(&obliczenia_1_arg, clnt);
	
	


#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[100];
    
	for (int i=0; i < 100; ++i)
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
        int max_size=0;
	while( (read_size = recv(client_sock , client_message , 100 , 0)) > 0 )
	{
        printf("%s\n", client_message);
	}
	
    
	
	char *host;

	if (argc < 1) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	testowy_1 (host, client_message);
    
	return 0;
}

