<?php 
$string = "Some numbers: one: 12; two: 22; three: 3 end"; 
$ten = 10; 
$newstring = preg_replace_callback( 
	'/(\\d+)/', 
	function($match) use ($ten) {
		return (($match[0] + $ten)); }, 
			    $string 
				    ); 
		echo $newstring; 
