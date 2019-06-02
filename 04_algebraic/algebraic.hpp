#ifndef ALGEBRAIC_HPP
#define ALGEBRAIC_HPP

// gcd_sub - алгоритм нахождения наибольшего общего делителя через классический алгоритм Евклида
int gcd_sub(int a, int b);

// gcd_mod - алгоритм нахождения наибольшего общего делителя через алгоритм Евклида через деление
int gcd_mod(int a, int b);

// power_iterative - вычисление степени итеративным способом
int power_iterative(int base, unsigned int exponent);

// power_via_power_of_2 - возведение в степень через степень двойки с умножением
int power_via_power_of_two(int base, unsigned int exponent);

// power_via_exponent_binary_partition - возведение в степень через бинарное разложение показателя степени
int power_via_exponent_binary_partition(int base, unsigned int exponent);

#ifdef __GNUC__
// power_via_exponent_binary_partition_with_gcc_extentions - 
// возведение в степень через бинарное разложение показателя степени
// с привлечением оптимизаций, встроенных в компилятор GCC
int power_via_exponent_binary_partition_with_gcc_extentions(int base, unsigned int exponent);
#endif

// fibonacci_recursive - рекурсивный алгоритм вычисления чисел Фибоначчи
int fibonacci_recursive(int n); 

// fibonacci_iterative - итеративный алгоритм вычисления чисел Фибоначчи
int fibonacci_iterative(int n);

// fibonacci_golden_ratio - алгоритм вычисления чисел Фибоначчи через золотое сечение
int fibonacci_golden_ratio(int n);

// fibonacci_matrix - алгоритм вычисления чисел Фибоначчи через перемножение матриц
int fibonacci_matrix(int n);

#endif