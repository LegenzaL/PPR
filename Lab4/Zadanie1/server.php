<?php
	#===================================================================
	function getTime( $data ) {
		
		#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		$stderr = fopen('php://stderr', 'w');
		fwrite( $stderr, "Client: $data\n" );
		
		echo dechex($data);
		
		return $data;
	}
	
	$server = new SoapServer("example.wsdl");
	$server->addFunction("getTime");
	$server->handle();
	#===================================================================

?>

