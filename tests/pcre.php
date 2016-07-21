<?php
$string="我asdf123们12sa当dfsa12312";
$string = preg_replace_callback('#[a-z0-9_-]#i', function ($matches) {
	return "\t".$matches[0];
	        }, $string);
echo $string;
