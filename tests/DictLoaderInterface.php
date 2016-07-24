<?php
Reflection::export(new ReflectionClass('DictLoaderInterface'));
Reflection::export(new ReflectionClass('FileDictLoader'));
$a=new FileDictLoader("123");
echo $a->path;
