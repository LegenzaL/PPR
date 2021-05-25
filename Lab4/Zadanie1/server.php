<?php
	#===================================================================
	function getTime( $data ) {
		
		#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		$stderr = fopen('php://stderr', 'w');
		fwrite( $stderr, "Client: $data\n" );
		
		$suma = $data[0] + $data[1];
		
		return $suma;
	}
	
	$server = new SoapServer("example.wsdl");
	$server->addFunction("getTime");
	$server->handle();
	#===================================================================

?>

