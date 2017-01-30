<!DOCTYPE html>
<html>
<head>
    <meta charset='utf-8'>
    <link rel='stylesheet' href='css/index.css'>
    <link rel='stylesheet' href='css/bootstrap.css'>
    <script type='text/javascript' src='js/jquery.js'></script>
    <script type='text/javascript' src='js/bootstrap.js'></script>
    <title>AdminKrasty</title>
</head>
<body>
<?php
?>
<script type='text/javascript' src='main.js'></script>
<div class="container">
<div class="row">
    <div class="col-md-6">
        <table class="table table-bordered table-hover" id="tableControl">
            <tr>
                <th>#</th>
                <th>Элемент</th>
                <th>Управление</th>
            </tr>
            <tr id="wheel"><td>1</td><td data-toggle="tooltip" data-placement="left" title="Необходимо выставить штурвалы слева направо, сверху вниз в положения 12\6\3\12 часов">Штувалы</td><td></td></tr>
            <tr id="dollar"><td>3</td><td  data-toggle="tooltip" data-placement="left" title="Доллар в кассе? Что бы извлечь доллар из обменника Необходимо: выставить в обменнике 40 + 00 и закинуть 6 монет">Доллар</td><td></td></tr>
            <tr id="order"><td>4</td><td  data-toggle="tooltip" data-placement="left" title="Верный заказ: Маленький бокс, котлета, булка, игрушка, бесплатный сыр и секретный соус">Заказ</td><td></td></tr>
            <tr id="cheeze"><td>6</td><td  data-toggle="tooltip" data-placement="left" title="После верного заказа открвается мышкин домик, сыр из домика нужно вставить в сыроприёмник под окном, от чего поедет машинка на которой стоит бокс с палочкой.">Сыроприёмник</td><td></td></tr>
            <tr id="box"><td>8</td><td  data-toggle="tooltip" data-placement="left" title="Палочкой из бокса нужно нагреть трением бокс, после поднятия на один градус температуру, откроется дверь на кухню">Печь</td><td></td></tr>
            <tr id="kitchen"><td>9</td><td  data-toggle="tooltip" data-placement="left" title="Нагреть!">Дверь на кухню</td><td></td></tr>
            <tr id="lopatka"><td>10</td><td  data-toggle="tooltip" data-placement="left" title="Лопатка извлекается с помощю двух медалек со стены, достаточно приложить их одновременно на метки возле бокса, важна сторона медали, но не их последовательность.">Лопатка</td><td></td></tr>
            <tr id="kegi"><td>11</td><td  data-toggle="tooltip" data-placement="left" title="Наклонить нужно 1,2, 4 и 6 рычаги, тогда откроется дверь в кабинет">Кеги</td><td></td></tr>
            <tr id="kabinet"><td>12</td><td  data-toggle="tooltip" data-placement="left" title="Кеги!">Дверь в кабинет</td><td></td></tr>
            <tr id="final"><td>13</td><td  data-toggle="tooltip" data-placement="left" title="Пароль от кейса с рецептом (1), этот пароль игроки получат после танцев">Дверь на выход и рецепт</td><td></td></tr>
        </table>
        <h1   data-toggle="tooltip" data-placement="left" title="flush - перезапуск, starting - запуск, playing - игра идёт, end - конец игры">Состояние квеста: <p style="float: right;" id="status">1</p></h1>


        <!-- связь в малиной -->
        
        <?php
            function pingAddress($ip) {
                $pingresult = shell_exec("ping -n 3 $ip", $outcome, $status);
                // if (0 == $status) {
                //     $status = "alive";
                // } else {
                //     $status = "dead";
                // }
                    echo "The IP address, $ip, is  ".$status;
                }

            pingAddress("127.0.0.1");

        ?>
        
        <!-- !!! -->
    </div>
    <div class="col-md-6">
        <button id="start" type="button" class="btn btn-primary btn-lg btn-block">Запуск квеста</button>
        <button id="flushGame" type="button" class="btn btn-primary btn-lg btn-block">Сброс</button>
        <button id="pause" type="button" class="btn btn-primary btn-lg btn-block">Пауза</button>
        <h2 class="text-center">Время квеста <span class="glyphicon glyphicon-time" aria-hidden="true"></span></h2>
        <div class="panel panel-default">
          <div class="panel-body">
            <div style="float: left" id="time">
                <blockquote>
                  <h1></h1>
                  <footer></footer>
                </blockquote>
            </div>
            <div style="float: right" class="btn-group" role="group" aria-label="...">
              <button id="plus" type="button" class="btn btn-default">+5</button>
              <button id="minus" type="button" class="btn btn-default">-1</button>
              <button id="flush" type="button" class="btn btn-default">0</button>
            </div>
          </div>
          <div class="panel-footer"  style="overflow-x:hidden; height: 400px;"></div>
        </div>

    </div>
</div>
</div>
</body>
</html>