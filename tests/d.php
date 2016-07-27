<?php
//Reflection::export(new ReflectionClass('FileDictLoader'));
//$string="万俟";
//echo mb_substr($string, mb_strlen("万俟", 'UTF-8'), mb_strlen("万俟", 'UTF-8') - 1, 'UTF-8');
$a=new FileDictLoader(__DIR__."/words/");
echo $a->mapSurname("单于");
