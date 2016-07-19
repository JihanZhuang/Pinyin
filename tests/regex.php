<?php
$string="asdfsd1234r123hjlhasf1234asfd";
$string=preg_replace('~[a-z0-9_-]~i', '\t', $string);

echo $string;
