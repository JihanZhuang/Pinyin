<?php
$pinyin=new Pinyin();
$a="123我asdf123们12sa当dfsa12312cao啊啊沙发是萨芬撒1`412412我";
echo $pinyin->prepare($a);
echo "\n";
$string="123我asdf123们12sa当dfsa12312cao啊啊沙发是萨芬撒1`412412我";
$string = preg_replace_callback('~[a-z0-9_-]+~i', function ($matches) {
	return "\t".$matches[0];
	        }, $string);
echo preg_replace("~[^\p{Han}\p{P}\p{Z}\p{M}\p{N}\p{L}\t]~u", '', $string);
