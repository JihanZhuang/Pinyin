<?php
Reflection::export(new ReflectionClass('DictLoaderInterface'));
Reflection::export(new ReflectionClass('FileDictLoader'));
$a=new FileDictLoader(__DIR__."/words/");
$a->map("踉踉跄跄");
