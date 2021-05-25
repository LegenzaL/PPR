#!/usr/bin/php

<?php
	#===================================================================
	$port 	= 7777;
	$host 	= '127.0.0.1';
	$wsdl 	= 'http://' . $host . ':' . $port . '/?wsdl';
	#-------------------------------------------------------------------
	$soap = new SoapClient( $wsdl, array( 'proxy_host'   => "127.0.0.1", 'proxy_port'   => 7777) );
	
	$liczby[0]=$argv[1];
	$liczby[1]=$argv[2];
	
	#print($liczby[0]);
	#print($liczby[1]);
	
	print_r( $soap->getTime( $liczby ) );
	
	
	print("\n\n");
	#===================================================================
?>