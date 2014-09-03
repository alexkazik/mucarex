<?php
	
	if($argc != 3){
		die('usage: '.$argv[0].' <source> <dep-file>'.PHP_EOL);
	}
	
	if(substr($argv[1], -4) != '.asm' || !file_exists(substr($argv[1], 0, -4).'.lst')){
		die('error: can\'t find .lst file'.PHP_EOL);
	}
	
	$incs = array();
	
	foreach(explode(PHP_EOL, file_get_contents(substr($argv[1], 0, -4).'.lst')) AS $ln){
		if(preg_match("!^([ \t]*\([0-9]+\))?[ \t]*[0-9]+/[ \t]*[0-9a-fA-F]+[ \t]*:[ \t]*b?include[ \t]*\"([^\"]+)\"!", $ln, $r)){
			$incs[] = $r[2];
		}
	}
	
	file_put_contents($argv[2], substr($argv[1], 0, -4).'.p: '.$argv[1].' '.implode(' \\'.PHP_EOL."\t", $incs).PHP_EOL);
	
?>