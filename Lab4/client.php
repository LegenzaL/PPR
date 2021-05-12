#!/usr/bin/php

<?php
	#===================================================================
	$port 	= 7777;
	$host 	= '127.0.0.1';
	$wsdl 	= 'http://' . $host . ':' . $port . '?wsdl';
	#-------------------------------------------------------------------
	$soap = new SoapClient( $wsdl, array( 'proxy_host'   => "127.0.0.1",
                                          'proxy_port'   => 7777) );
	#$res  = $soap->getTime( 'Some data...' );
	$liczba1 = readline("Liczba1: ");
    readline_add_history($liczba1);
    #echo "$liczba1";
	#$soap->getTime( "$liczba1" );
	
	$liczba2 = readline("Liczba2: ");
    readline_add_history($liczba2);
    #echo "$liczba2";
	$soap->getTime( "$liczba1", "$liczba2" );
	
	
	
	#print_r( $soap->getTime( "$line" ) );
	
	#===================================================================
?>