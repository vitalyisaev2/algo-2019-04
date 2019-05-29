#ifndef ALGEBRAIC_HPP
#define ALGEBRAIC_HPP

// gcd_sub - алгоритм нахождения наибольшего общего делителя через классический алгоритм Евклида
int gcd_sub(int a, int b);

// gcd_mod - алгоритм нахождения наибольшего общего делителя через алгоритм Евклида через деление
int gcd_mod(int a, int b);
int gcd_mod_recursive(int a, int b);

#endif