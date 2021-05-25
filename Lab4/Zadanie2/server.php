<?php
	#===================================================================
	function getTime( $data ) {
		
		$hex = dechex($data);
		
		#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		$stderr = fopen('php://stderr', 'w');
		fwrite( $stderr, "Client: $hex\n" );
		
		return $hex;
	}
	
	$server = new SoapServer("example.wsdl");
	$server->addFunction("getTime");
	$server->handle();
	#===================================================================

?>

