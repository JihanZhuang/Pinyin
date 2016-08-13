<?php
//
$a=new Pinyin();
//echo $a->format("üé  ǜ  à");
/*print_r($a->splitWords("üé  ǜ  à","ascii"));

$option="ascii";
$pinyin="üé  ǜ  à";
$split = array_filter(preg_split('/[^üāēīōūǖáéíóúǘǎěǐǒǔǚàèìòùǜa-z\d]+/iu', $pinyin));
	foreach ($split as $index => $pinyin) {

		$split[$index] = $a->format($pinyin, true);
		            }
print_r(array_values($split));
 *////home/jihanzhuang/code/Pinyin/data/
//print_r($a->romanize("  dà  i"));
	 //print_r($a->sentence("	dà	i"));
$a=new FileDictLoader("/home/jihanzhuang/code/Pinyin/data/");
//print_r($a->map('带着希望去旅行，比到达终点更美好'));
print_r($a->map('踉踉跄跄'));
//$a->permalink("","");
//echo realpath(__DIR__."/../data/words_0");
//print_r(parse_ini_file("./../data/words_0"));
