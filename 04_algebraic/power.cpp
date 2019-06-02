#include "algebraic.hpp"
#include <iostream>

int power_iterative(int base, int exponent)
{
    int result = 1;
    while (exponent--) {
        result *= base;
    }
    return result;
}

int power_via_power_of_two(int base, int exponent)
{
    if (exponent == 0) {
        return 1;
    }
    if (exponent % 2 == 1) {
        return power_via_power_of_two(base, exponent - 1) * base;
    }
    int result = power_via_power_of_two(base, exponent / 2);
    return result * result;
}

int power_via_exponent_binary_partition(int base, int exponent)
{
    // определяем первый значащий бит
    int first_signed_bit_position = 0;
    for (int pos = sizeof(int)*8; pos >= 0; pos--) {
        if (exponent & (1 << pos)) {
            first_signed_bit_position = pos;
            break;
        }
    }

    // начиная с первого значащего бита собираем результат
    int result = 1;
    for (int pos = first_signed_bit_position; pos >= 0; pos--) {
        if (exponent & (1 << pos)) {
            result *= result;
            result *= base;
        } else {
            result *= result;
        }
    }

    return result;
}