<?php
Reflection::export(new ReflectionClass('DictLoaderInterface'));
Reflection::export(new ReflectionClass('FileDictLoader'));
$a=new FileDictLoader();
echo $a->segmentName;
