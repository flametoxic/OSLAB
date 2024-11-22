<H1> Монитор </H1>

Данное решение представляет из себя монитор с двумя потоками:
1. Поток-поставщик: генерирует число которое является событием, и отправляется потоку-потребителю.
2. Поток-потребитель: принимает событие которые было сгенерировано потоком-поставщиком.
Реализация передачи происходит через объект класса Monitor с двумя основными методами:
1. addEvent: метод внутри класса Monitor, который добавляет события для отправки в очередь
2. getEvent: метод внутри класса Monitor, который достаёт события из очереди.
В функции main создаётся экземпляр класса Monitor, и передаётся в два потока, поток-поставщик и поток-потребитель.
<hr>
Код можно посмотреть тут: [исходный код](https://github.com/flametoxic/OSLAB1/monitor.cpp);

