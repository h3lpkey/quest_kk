<?php

if(isset($_GET['order'])) {

	$json = file_get_contents('../config.json');
	// Декодируем
	$json = json_decode($json, true);

	echo $json['order'];
	
	if($_GET['order'] == 1) {
		$json['order'] = 1;
	} 
	if($_GET['order'] == 0) {
		$json['order'] = 0;
	}
	
	// Превращаем опять в JSON
	$json = json_encode($json);
	// Перезаписываем файл
	file_put_contents('../config.json', $json);
}

?>