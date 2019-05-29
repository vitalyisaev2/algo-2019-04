#include "algebraic.hpp"

int power_iterative(int base, int exponent)
{
    int result = 1;
    while (exponent--) {
        result *= base;
    }
    return result;
}

int power_binary(int base, int exponent)
{
    /*
    int last_power_of_2 = 1;
    int times           = 0;
    while (exponent > last_power_of_2) {
        last_power_of_2 *= 2;
        times++;
    }
    last_power_of_2 /= 2;
    times--;

    int result = base;
    while (times--) {
        result *= result;
    }

    int left = exponent - last_power_of_2;
    while (left--) {
        result *= base;
    }
    return result;
    */
    if (exponent == 0) {
        return 1;
    }
    if (exponent % 2 == 1) {
        return power_binary(base, exponent-1) * base;
    }
    int result = power_binary(base, exponent / 2);
    return result * result;
}