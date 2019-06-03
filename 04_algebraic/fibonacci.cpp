#include "algebraic.hpp"
#include <math.h>
#include <vector>

// recursive

int fibonacci_recursive(int n)
{
    switch (n) {
    case 0:
        return 0;
    case 1:
        return 1;
    default:
        return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
    }
}

// iterative

int fibonacci_iterative(int n)
{
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    int prev = 0;
    int next = 1;
    for (int i = 1; i < n; i++) {
        int curr = next + prev;
        prev     = next;
        next     = curr;
    }

    return next;
}

// golden_ratio

const double golden_ratio = (1 + sqrt(5)) / 2;

int fibonacci_golden_ratio(int n)
{
    auto value = (pow(golden_ratio, n) - pow(1 - golden_ratio, n)) / sqrt(5);
    return static_cast<int>(value);
}

// matrix

class Matrix
{
  public:
    Matrix(int n)
    {
        if (n == 1) {
            this->a00 = 1;
            this->a01 = 1;
            this->a10 = 1;
            this->a11 = 0;
            return;
        }
        *this = power_via_power_of_two<Matrix>(Matrix(1), static_cast<unsigned int>(n));
    }

    Matrix(int _a00, int _a01, int _a10, int _a11) : a00(_a00), a01(_a01), a10(_a10), a11(_a11){};

    Matrix operator*(const Matrix& other) const
    {
        int b00 = a00 * other.a00 + a01 * other.a10;
        int b01 = a00 * other.a01 + a01 * other.a11;
        int b10 = a10 * other.a00 + a11 * other.a10;
        int b11 = a10 * other.a01 + a11 * other.a11;
        return Matrix(b00, b01, b10, b11);
    }

    int get_fibonacci_value() const
    {
        return a01;
    }

  private:
    int a00;
    int a01;
    int a10;
    int a11;
};

int fibonacci_matrix(int n)
{
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    Matrix m(1, 1, 1, 0);
    Matrix result = power_via_power_of_two<Matrix>(m, static_cast<unsigned int>(n));
    return result.get_fibonacci_value();
}