### Readme 

В тестировании принимали участии следующие имплементации интерфейса `DynamicArray`:
* `SingleArray`
* `VectorArray` с длиной приращения массива 2 и 2 <sup>16</sup>;
* `FactorArray` с фактором роста 2;
* `MartixArray` с длиной ряда 2 и 2 <sup>16</sup>;
* `StdVectorArray`, построненной с использованием `std::vector` из стандартной библиотеки С++.

Тестировались методы:
* Добавление в начало и хвост массива (`AddFront` и `AddBack`) ;
* Удаление из начала и хвоста массива (`RemoveFront` и `RemoveBack`);
* Извлечение данных из середины массива (`Get`).

Размеры массива:
* 2
* 2 <sup>4</sup>
* 2 <sup>8</sup>
* 2 <sup>12</sup>
* 2 <sup>16</sup>
* 2 <sup>18</sup>

Операция добавления элемента в конец массива у оптимизированных имплементаций `DynamicArray` имеет порядок роста O(1). 
Лучшую производительность демонстрируют `StdVectorArray` и `FactorArray`. В свободное место в хвосте массива данные добавляются за O(1),
реаллокации случаются редко и не играют значительной роли. В имплементациях `SingleArray`, `VectorArray` и `MatrixArray`,
где реаллокации и копирование случаются значительно чаще, наблюдаются скорости роста, превышающие O(N).
![AddBack](https://github.com/vitalyisaev2/algo-2019-04/blob/master/02_data_structures/report/AddBack.png)
![AddFront](https://github.com/vitalyisaev2/algo-2019-04/blob/master/02_data_structures/report/AddFront.png)
![RemoveBack](https://github.com/vitalyisaev2/algo-2019-04/blob/master/02_data_structures/report/RemoveBack.png)
![RemoveFront](https://github.com/vitalyisaev2/algo-2019-04/blob/master/02_data_structures/report/RemoveFront.png)

Извлечение элемента массива по индексу - операция, выполняющаяся за константное время. У `MatrixArray` она 
выполняется несколько медленнее, чем у других имплементаций, за счёт большего количества арифметических операций для вычисления адреса ячейки.
![Get](https://github.com/vitalyisaev2/algo-2019-04/blob/master/02_data_structures/report/Get.png)