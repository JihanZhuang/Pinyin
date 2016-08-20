<?php
set_time_limit(0);
$s = microtime(true);
//require "vendor/autoload.php";
//use Overtrue\Pinyin\Pinyin;

$pinyin = new Pinyin();
$i = 0;
while($i < 1000) {
        $ret = $pinyin->convert("带着希望去旅行，比到达终点更美好");
            echo implode("-", $ret). "\n";
                $i++;
}
$e = microtime(true);

echo "使用时间【".($e - $s). "】s";
echo "最大使用内存【".memory_get_peak_usage(true)."bytes】";
