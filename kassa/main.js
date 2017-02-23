function Order(orderNow) {
	//отправляю GET запрос и получаю ответ
	$.ajax({
		type:'get',//тип запроса: get,post либо head
		url:'order.php',//url адрес файла обработчика
		data:{'order':orderNow},//параметры запроса
		response:'text',//тип возвращаемого ответа text либо xml
		success:function (data) {//возвращаемый результат от сервера
			console.log(data);
		}
	});
}

$(document).ready(function(){

$.ajaxSetup({ cache: false }); // вырубаем кэширование

	var json;
	orderNow = 0;
	// ингредиенты
	var kotleta = 0;
	var igryshka = 0;
	var cheeze = 0;
	var bulka = 0;
	var soys = 0;
	var fail = 0;
	setInterval(function(){
		$.getJSON( "../config.json", function( data ) {
			// обработка доллара
			if(data.dollar) {
		  		$('.cash').empty();
		  		$('.cash').append('$ 3');
		  	} else {
		  		$('.cash').empty();
		  		$('.cash').append('$ 0');
		  	}
		  	json = data;
		});
	}, 1000);
	
	var rightBox = false;
	rightOrder = '';
	// обработка для боксов Картинка рецепта - не нужна
	$('#box1').click(function() {
		$('#box1').attr('src', 'images/box1.png');
		$('#box2').attr('src', 'images/box2_no.png');
		$('#box3').attr('src', 'images/box3_no.png');
		rightBox = true;
	});
	$('#box2').click(function() {
		$('#box1').attr('src', 'images/box1_no.png');
		$('#box2').attr('src', 'images/box2.png');
		$('#box3').attr('src', 'images/box3_no.png');
		rightBox = false;
	});
	$('#box3').click(function() {
		$('#box1').attr('src', 'images/box1_no.png');
		$('#box2').attr('src', 'images/box2_no.png');
		$('#box3').attr('src', 'images/box3.png');
		rightBox = false;
	});
		// обработка кнопок заказа
	$('.ingredient-button').click(function() {
		var ingredient = $(this).text();
		switch(ingredient) {
			case 'котлета' :
				kotleta++;
				break;
			case 'игрушка' :
				igryshka++;
				break;
			case 'бесплатный сыр' :
				cheeze++;
				break;
			case 'булочка' :
				bulka++;
				break;
			case 'секретный соус' :
				soys++;
				break;
			default:
				fail++;
				break;
		}
		$('#orderBox').append('<li>'+ingredient+'</li>');
	});
	$('#reset').click(function() {
		$('#orderBox').empty();
		$('#paper').attr('src', '');
		orderNow = 0;
		kotleta = 0;
		igryshka = 0;
		cheeze = 0;
		bulka = 0;
		soys = 0;
		fail = 0;
		console.log(kotleta, igryshka, cheeze, bulka, soys, fail);
		Order(orderNow);
	});

// обработка правильного заказа
	$('#pay').click(function(){
		console.log(kotleta, igryshka, cheeze, bulka, soys, fail);
		var box = $('#paper').attr('src');
		var rightOrder = $('#orderBox').text();
		if(json.dollar) {
			if(rightBox) {
				if(	kotleta == 1 
				&& igryshka == 1 
				&& cheeze 	== 1 
				&& bulka 	== 1 
				&& soys 	== 1
				&& fail 	== 0) {
					$('#orderBox').empty();
					$('#orderBox').append('не хватает бесплатного сыра :P');
					orderNow = 1;
					Order(orderNow);
				} else {
					if (rightOrder == '' 				||
						rightOrder == 'заказ не верен!' ||
						rightOrder == 'не выбран бокс' 	||
						rightOrder == 'не хватает' 		||
						rightOrder == 'пуст' 		||
						rightOrder == 'вставь деньги!' 	) {

						$('#orderBox').empty();
						$('#orderBox').append('заказ совсем пуст :(');
						rightOrder = '';
					} else {
						$('#orderBox').empty();
						$('#orderBox').append('а в меню по другому');
						rightOrder = '';
					}
				}
			} else {
				if(box == '') {
					$('#orderBox').empty();
					$('#orderBox').append('выбери Мил ');
					rightOrder = '';
				} else {
					$('#orderBox').empty();
					$('#orderBox').append('не хватает $$$');
					rightOrder = '';
				}
			}
		} else {
			$('#orderBox').empty();
			$('#orderBox').append('платить будем?');
			rightOrder = '';
		}
	});

});