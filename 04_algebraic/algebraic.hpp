#ifndef ALGEBRAIC_HPP
#define ALGEBRAIC_HPP

// gcd_sub - алгоритм нахождения наибольшего общего делителя через классический алгоритм Евклида
int gcd_sub(int a, int b);

// gcd_mod - алгоритм нахождения наибольшего общего делителя через алгоритм Евклида через деление
int gcd_mod(int a, int b);

// power_iterative - вычисление степени итеративным способом
int power_iterative(int base, int exponent);

// power_binary - возведение в степень через степень двойки с умножением
int power_binary(int base, int exponent);

#endif