### Алгебраические алгоритмы

#### `Наибольший общий делитель`
Расширенный алгоритм Евклида демонстрирует логарифмическую сложность (на рисунке она кажется константной).
![GCD](https://github.com/vitalyisaev2/algo-2019-04/blob/master/04_algebraic/report/GCD.png)

#### `Возведение в степень`
Среди алгоритмов возведения в степень лучшую скорость демонстрирует алгоритм бинарного разложения показателя степени *(O(logN)).
Его можно улучшить на небольшую костанту, если воспользоваться специальными низкоуровневыми функциями для работы с CPU, встроенными в компилятор GCC.
![Power](https://github.com/vitalyisaev2/algo-2019-04/blob/master/04_algebraic/report/Power.png)

#### `Числа Фибоначчи`
Лучшую асимптотику (O(logN)) на исследованном диапазоне показал алгоритм с перемножением матриц, однако также весьма интересен алгоритм золотого сечения,
работающий за константное время.
![RemoveBack](https://github.com/vitalyisaev2/algo-2019-04/blob/master/04_algebraic/report/Fibonacci.png)

#### `Поиск простых чисел`
Наилучшую асимптотику показало Решета Эратосфена с базовыми оптимизациями (исключение чисел, кратных двойке, ограничение делителя значением корня делимого).
Дополнительное задание не стал делать, поскольку в C++ `std::vector<bool>` внутри имплеминтирован в виде последовательности битов, а не настоящих объектов
типа bool.
![RemoveFront](https://github.com/vitalyisaev2/algo-2019-04/blob/master/04_algebraic/report/Prime.png)
