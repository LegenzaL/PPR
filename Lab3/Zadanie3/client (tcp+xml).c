/* ********************************************** */
/* Na podstawie: http://xmlrpc-c.sourceforge.net  */
/* ********************************************** */

#include <stdlib.h>
#include <stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>	
#include<unistd.h>	

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>

#define NAME "Xmlrpc-c Test Client"
#define VERSION "1.0"

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


//======================================================================
static void 
dieIfFaultOccurred (xmlrpc_env * const envP) {
    if (envP->fault_occurred) {
        fprintf( stderr, "ERROR: %s (%d)\n", envP->fault_string, envP->fault_code );
        exit(1);
    }
}
//======================================================================
int main(int const argc, char ** argv){

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
        //int max_size=0;
	while( (read_size = recv(client_sock , client_message , 100 , 0)) > 0 )
	{
        printf("%s\n", client_message);
	}
    
    char hex[100];
    for (int i=0; i < 100; ++i)
	{
		hex[i]=0;
    }
    
    string2hex(client_message, hex);
    
    //printf("%s\n", hex);
    
	/* zmienne predefiniowane *****************************************/
    const char * const serverUrl = "http://localhost:12345/RPC2";
    const char * const methodName = "sample.add";
	
	/* zmienne niezainicjowane ****************************************/
    xmlrpc_env env;
    xmlrpc_value * resultP;
    xmlrpc_int32 x;
    
    /* inicjujemy srodowisko ******************************************/
    xmlrpc_env_init(&env);

    /* inicjujemy xml-rpc po stronie klienta **************************/
    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, NAME, VERSION, NULL, 0);
    dieIfFaultOccurred(&env);	// sprawdzamy, czy wystapil blad 

    /* wywolujemy zdalna procedure ************************************/
    
    
    resultP = xmlrpc_client_call(&env, serverUrl, methodName, "s",  hex);
    dieIfFaultOccurred(&env);
    
    /* pobieramy wynik ************************************************/
    xmlrpc_read_int(&env, resultP, &x);
    dieIfFaultOccurred(&env);
    
    /* wypisujemy wynik ***********************************************/
    //printf("Wynik: %s\n", x);
    
    /* dekrementujemy licznik referencji ******************************/
    xmlrpc_DECREF(resultP);

    /* czyscimy srodowisko ********************************************/
    xmlrpc_env_clean(&env);
    
    /* konczymy prace klienta *****************************************/
    xmlrpc_client_cleanup();

    return 0;
}
//======================================================================
