<?php
$connection = ssh2_connect('192.168.1.116', 22);
ssh2_auth_password($connection, 'pi', 'raspberry');



if(isset($_GET['button'])) {
	$json = file_get_contents('../config.json');
	// Декодируем
	$json = json_decode($json, true);

	switch ($_GET['button']) {
		case 'start':
			$json['status'] = 'starting';

			echo '<p  class="text-warning">Запускаю игру, статус: '.$json['status'].'</p>';
			break;
		case 'pause':
			$json['status'] = 'pause';
			echo '<p  class="text-warning" >Торможу игру, статус: '.$json['status'].'</p>';
			break;
		case 'flushGame':
			$json["status"] = 'flush';
			$json = file_get_contents('../flushConfig.json');
			$json = json_decode($json, true);
			echo '<p class="text-warning">Сброс игры, статус: '.$json["status"].'</p>';
			break;
		case 'wheel':
			if ($json['wheel'] == 1) {
				$json['wheel'] = 0;
				echo '<p class="text-success">Отрубил питание на окно</p>';

			} else {
				$json['wheel'] = 1;
				echo '<p class="text-success">Врубил питание на окно</p>';

			}
			break;
		case 'kegi':
			$json["kegi"] = 1;
			echo '<p class="text-success">Типо решил задачку с кегами '.$json['kegi'].' в '. $json["now"] .'</p>';
			break;
		case 'order':
			$json["order"] = 1;
			echo '<p class="text-success">Выставляю верный заказ '.$json['order'].' в '. $json["now"] .'</p>';
			break;
		case 'dollar':
			$json["dollar"] = 1;
			echo '<p class="text-success">Обманнываю кассу '.$json['dollar'].' в '. $json["now"] .'</p>';
			break;
		case 'cheeze':
			$json["cheeze"] = 1;
			echo '<p class="text-success">Эммитирую падение сыра! '.$json['cheeze'].' в '. $json["now"] .'</p>';
			break;
		case 'plus':
			$json["plus"] = $json["plus"] + 5;
			echo '<p class="text-muted">+ 5 минут к bonus time ['.$json['plus'].']</p>';
			break;
		case 'minus':
			$json["plus"] = $json["plus"] - 1;
			echo '<p class="text-muted">- 1 минута от bonus time ['.$json['plus'].']</p>';
			break;
		case 'flush':
			$json["plus"] = 0;
			echo '<p class="text-warning">Сброс времени, вернуть bonus time в [0]</p>';
			break;
		case 'startQuest_kk':
			echo '<p class="text-warning">Запуская программу на сервере</p>';
			shell_exec('sudo -S /var/www/qf2016.pro/quest_kk');
			break;
		case 'sound':
			// $output1 = shell_exec('ssh pi@192.168.1.116 sudo -S killall omxplayer.bin');
			// $output2 = shell_exec('ssh pi@192.168.1.116 /home/pi/kk_music');
			$stream = ssh2_exec($connection, '/usr/local/bin/php -i');

			echo '<p class="text-warning">Перезапускаю звук</p>';
			break;
		default:
			echo '<p class="text-warning" >game ???</p>';
			break;
	}

	// Превращаем опять в JSON
	$json = json_encode($json);
	// Перезаписываем файл
	file_put_contents('../config.json', $json);
}

?>