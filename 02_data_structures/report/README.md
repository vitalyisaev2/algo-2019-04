### Readme 

В тестировании принимали участии следующие имплементации интерфейса `DynamicArray`:
* `SingleArray`
* `VectorArray` с длиной приращения массива 2 и 2 <sup>16</sup>;
* `FactorArray` с параметром роста 2;
* `MartixArray` с длиной ряда 2 и 2 <sup>16</sup>;
* `StdVectorArray`, построненной с использованием `std::vector` из стандартной библиотеки С++.

Тестировались методы:
* `Add` в начало и хвост массива;
* `Remove` из начала и хвоста массива;
* `Get` из произвольных мест массива.

Размеры массива:
* 2
* 2 <sup>4</sup>
* 2 <sup>8</sup>
* 2 <sup>12</sup>
* 2 <sup>16</sup>
* 2 <sup>18</sup>

Операция добавления элемента в конец массива для всех имплементаций имеет порядок роста O(N). Лучшую производительность демонстрируют
`StdVectorArray` и `FactorArray`. В свободное место в хвосте массива данные добавляются за O(1), однако периодически приходится выделять
больше памяти и проводить копирование данных за O(N), что в результате и даёт итоговую
![AddBack](https://github.com/vitalyisaev2/algo-2019-04/blob/master/02_data_structures/report/AddBack.png)
![AddFront](https://github.com/vitalyisaev2/algo-2019-04/blob/master/02_data_structures/report/AddFront.png)
![RemoveBack](https://github.com/vitalyisaev2/algo-2019-04/blob/master/02_data_structures/report/RemoveBack.png)
![RemoveFront](https://github.com/vitalyisaev2/algo-2019-04/blob/master/02_data_structures/report/RemoveFront.png)
![Get](https://github.com/vitalyisaev2/algo-2019-04/blob/master/02_data_structures/report/Get.png)