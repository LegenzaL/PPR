/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "app.h"

wyjscie *
obliczenia_1_svc(wejscie *argp, struct svc_req *rqstp)
{
	static wyjscie  result;

	/*
	 * insert server code here
	 */
    
    //printf("%x\n", argp->size);
    
    printf("%s\n", argp->buffer);
	

	return &result;
}
