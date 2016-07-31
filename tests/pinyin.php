<?php
//
$a=new Pinyin();
//echo $a->format("üé  ǜ  à");
print_r($a->splitWords("üé  ǜ  à","ascii"));

$option="ascii";
$pinyin="üé  ǜ  à";
$split = array_filter(preg_split('/[^üāēīōūǖáéíóúǘǎěǐǒǔǚàèìòùǜa-z\d]+/iu', $pinyin));
	foreach ($split as $index => $pinyin) {

		$split[$index] = $a->format($pinyin, true);
		            }
print_r(array_values($split));

