function buttonConfig(button) {
	//отправляю GET запрос и получаю ответ
	$.ajax({
		type:'get',//тип запроса: get,post либо head
		url:'button.php',//url адрес файла обработчика
		data:{'button':button},//параметры запроса
		response:'text',//тип возвращаемого ответа text либо xml
		success:function (data) {//возвращаемый результат от сервера
			$(".panel-footer").prepend(data);
		}
	});
}

$(document).ready(function() {
	$.ajaxSetup({ cache: false }); // вырубаем кэширование

	setInterval(function() {
		$.getJSON( "../config.json", function( data ) {
			// обновление кнопок
			$('#tableControl tr').each(function(tr) {

				var attrTr = $(this).attr('id');

				$(this).tooltip('show');

				$('td:last-child', this).empty();
				if(data[attrTr] == true) {
					$('td:last-child', this).append('<button type="button" id="'+attrTr+'" class="btn btn-primary btn-xs">ON</button>');
				} else {
					$('td:last-child', this).append('<button type="button" id="'+attrTr+'" class="btn btn-default btn-xs">OFF</button>');
				}
			});

			// обновление времени
			var min = 60 - (Math.ceil(data.now / 60) - 1) + data.plus;
			var sec = 60 - (data.now % 60) + data.plus;

			var timeBroser = parseInt(new Date().getTime()/1000);
			timeBroser = timeBroser - 5;
			console.log(data.timeWorld);
			console.log(timeBroser);
			if (data.timeWorld < timeBroser) {
				$('#status').empty();
				$('#startQuest_kk').show();
				$('#status').append('Нет связи с quest_kk на малинке!');
			} else {
				$('#status').empty();
				$('#startQuest_kk').hide();
				$('#status').append(data.status);
			}

			$('#time h1').empty();
			$('#time h1').append(min+':'+sec);
			$('#time footer').empty();
			$('#time footer').append('доп время ' + data.plus);
		});
	}, 1000);

	$('#start').click(function() {
		var button = 'start';
		buttonConfig(button);
	});
	$('#pause').click(function() {
		var button = 'pause';
		buttonConfig(button);
	});
	$('#flushGame').click(function() {
		var button = 'flushGame';
		buttonConfig(button);
	});
	$('#wheel').click(function() {
		var button = $(this).attr('id');
		buttonConfig(button);
	});
	$('#kegi').click(function() {
		var button = $(this).attr('id');
		buttonConfig(button);
	});
	$('#order').click(function() {
		var button = $(this).attr('id');
		buttonConfig(button);
	});
	$('#dollar').click(function() {
		var button = $(this).attr('id');
		buttonConfig(button);
	});
	$('#cheeze').click(function() {
		var button = $(this).attr('id');
		buttonConfig(button);
	});
	$('#plus').click(function() {
		var button = $(this).attr('id');
		buttonConfig(button);
	});
	$('#minus').click(function() {
		var button = $(this).attr('id');
		buttonConfig(button);
	});
	$('#flush').click(function() {
		var button = $(this).attr('id');
		buttonConfig(button);
	});
	$('#startQuest_kk').click(function() {
		var button = 'startQuest_kk';
		buttonConfig(button);
	});
	$('#sound').click(function() {
		var button = 'sound';
		buttonConfig(button);
	});
});