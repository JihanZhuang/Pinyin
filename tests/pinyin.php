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
//var_dump($a->loader);
//print_r($a->romanize("  dà  i"));
//print_r($a->romanize("  dà  i"));
//print_r($a->romanize("  dà  i"));
//print_r($a->romanize("  dà  i"));
//print_r($a->loader);
//print_r($a->sentence("	dà	i")."\n");
//$a=new FileDictLoader("/home/jihanzhuang/code/Pinyin/data/");
	 //print_r($a->splitWords('   dà  i',"none"));
	 for($i=0;$i<2;$i++){

	 
echo '带着希望去旅行，比到达终点更美好'."\n";
print_r(implode($a->convert('带着希望去旅行，比到达终点更美好'),' ')."\n");
print_r(implode($a->convert('带着希望去旅行，比到达终点更美好',"unicode"),' ')."\n");
print_r(implode($a->convert('带着希望去旅行，比到达终点更美好',"ascii"),' ')."\n");
	 }//unset($a);
