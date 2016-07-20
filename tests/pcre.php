<?php
$string="asdf12312sadfsa12312";
$string = preg_replace_callback('/[a-z0-9_-]+/i', function ($matches) {

	return "\t".$matches[0];
	        }, $string);
echo $string;
