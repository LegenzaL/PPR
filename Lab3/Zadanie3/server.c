/* ********************************************** */
/* Na podstawie: http://xmlrpc-c.sourceforge.net  */
/* ********************************************** */
#define WIN32_LEAN_AND_MEAN  /* wymagane przez xmlrpc-c/server_abyss.h */

#include <stdlib.h>
#include <stdio.h>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include <string.h>	
#include <sys/socket.h>	
#include <arpa/inet.h>	
#include <unistd.h>

//======================================================================
static xmlrpc_value * sample_add(
			xmlrpc_env *   const envP,
			xmlrpc_value * const paramArrayP,
			void *         const serverInfo,
			void *         const channelInfo) {

    xmlrpc_int32 message;

    /* Parsujemy tablice z argumentami ********************************/
    
    xmlrpc_decompose_value( envP, paramArrayP, "(i)", &message );
    if (envP->fault_occurred)
        return NULL;

    /* Konwersja i wysłanie *********************************************/
    char hex[10];
    for (int i=0; i < 10; ++i)
	{
		hex[i]=0;
    }
    
    int sock;
	struct sockaddr_in server;
    
	sock = socket(AF_INET , SOCK_STREAM , 0);
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	connect(sock , (struct sockaddr *)&server , sizeof(server));
	
	sprintf(hex, "%x\n", message);
    
    send(sock , hex , strlen(hex) , 0);
    
	close(sock);

    /* Zwracamy wynik *************************************************/
    return xmlrpc_build_value(envP, "i", message);
}
//======================================================================
int main( void ){

	/* zmienne predefiniowane *****************************************/
	int  port   = 12345;
	//------------------------------------------------------------------
    struct xmlrpc_method_info3 const methodInfo = {
        /* .methodName     = */ "sample.add",
        /* .methodFunction = */ &sample_add,
    };
    
	/* zmienne niezainicjowane ****************************************/
    xmlrpc_server_abyss_parms serverparm;
    xmlrpc_registry * registryP;
    xmlrpc_env env;

    /* inicjujemy serwer **********************************************/
    xmlrpc_env_init(&env);

	/* rejestrujemy zmienne srodowiskowe ******************************/
    registryP = xmlrpc_registry_new(&env);
    if (env.fault_occurred){
        printf( "xmlrpc_registry_new(): %s\n", env.fault_string);
        exit(1);
    }

	/* rejestrujemy nasza metode/funkcje ******************************/
    xmlrpc_registry_add_method3( &env, registryP, &methodInfo );
    if (env.fault_occurred) {
        printf( "xmlrpc_registry_add_method3(): %s\n", env.fault_string );
        exit(1);
    }

	/* ustawiamy parametry serwera ************************************/
    serverparm.config_file_name = NULL;
    serverparm.registryP        = registryP;
    serverparm.port_number      = port;
    serverparm.log_file_name    = "/tmp/xmlrpc_log";

	/* uruchamiamy serwer *********************************************/
    xmlrpc_server_abyss(&env, &serverparm, XMLRPC_APSIZE(log_file_name));
    if( env.fault_occurred ){
        printf("xmlrpc_server_abyss(): %s\n", env.fault_string);
        exit(1);
    }

    
    return 0;
}
//======================================================================


