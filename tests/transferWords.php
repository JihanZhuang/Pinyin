<?php
$arr=include $argv[1];
foreach($arr as $k => $v){
$str=sprintf("%s='%s'\n",$k,$v);
file_put_contents("/tmp/tmp.txt",$str,FILE_APPEND);

}
