#!/usr/bin/php

<?php
	#===================================================================
	$port 	= 7777;
	$host 	= '127.0.0.1';
	$wsdl 	= 'http://' . $host . ':' . $port . '/?wsdl';
	#-------------------------------------------------------------------
	$soap = new SoapClient( $wsdl, array( 'proxy_host'   => "127.0.0.1", 'proxy_port'   => 7777) );
	
	
	
	$message=readline(' Podaj liczbe do konwersji: ');
	
	#print($message);
	
	
	print_r( $soap->getTime( $message ) );
	print("\n\n");
	#===================================================================
?>