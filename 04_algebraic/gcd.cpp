#include "algebraic.hpp"

int gcd_sub(int a, int b)
{
    if (a < b) {
        throw "first value must be greater than second";
    }
    int k = 0;
    while (true) {
        while (a >= b) {
            a -= b;
        }
        if (a == 0) {
            return b;
        }
        k = a;
        a = b;
        b = k;
    }
}

int gcd_mod(int a, int b)
{
    if (a < b) {
        throw "first value must be greater than second";
    }
    int k = 0;
    while (true) {
        k = a % b;
        if (k == 0) {
            return b;
        }
        a = b;
        b = k;
    }
}

int gcd_mod_recursive(int a, int b)
{
    if (b == 0) {
        return a;
    }
    return gcd_mod_recursive(b, a % b);
}