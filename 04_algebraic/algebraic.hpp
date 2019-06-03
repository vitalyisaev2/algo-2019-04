#ifndef ALGEBRAIC_HPP
#define ALGEBRAIC_HPP

#include <functional>
#include <math.h>
#include <type_traits>
#include <vector>

// --------- Greatest commond divisor ------------

// gcd_func - тип функции вычисления наибольшего общего делителя
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
using gcd_func = std::function<T(T, T)>;

// gcd_sub - алгоритм нахождения наибольшего общего делителя через классический алгоритм Евклида
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
T gcd_sub(T a, T b)
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

// gcd_mod - алгоритм нахождения наибольшего общего делителя через алгоритм Евклида через деление
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
T gcd_mod(T a, T b)
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

// --------- Exponentiation ------------

// power_func - тип функции для вычисления степени
template <typename T>
using power_func = std::function<T(T, unsigned int)>;

// power_iterative - вычисление степени итеративным способом
template <typename T>
T power_iterative(T base, unsigned int exponent)
{
    T result(1);
    while (exponent--) {
        result *= base;
    }
    return result;
}

// power_via_power_of_2 - возведение в степень через степень двойки с умножением
template <typename T>
T power_via_power_of_two(T base, unsigned int exponent)
{
    if (exponent == 0) {
        return T(1);
    }
    if (exponent % 2 == 1) {
        return power_via_power_of_two(base, exponent - 1) * base;
    }
    T result = power_via_power_of_two(base, exponent / 2);
    return result * result;
}

// power_via_exponent_binary_partition - возведение в степень через бинарное разложение показателя степени
template <typename T>
T power_via_exponent_binary_partition(T base, unsigned int exponent)
{
    // определяем первый значащий бит
    int           first_signed_bit_position = 0;
    constexpr int bits                      = sizeof(int) * 8;
    for (int pos = bits; pos >= 0; pos--) {
        if (static_cast<T>(exponent) & (1 << pos)) {
            first_signed_bit_position = pos;
            break;
        }
    }

    // начиная с первого значащего бита собираем результат
    int result = 1;
    for (int pos = first_signed_bit_position; pos >= 0; pos--) {
        if (static_cast<T>(exponent) & (1 << pos)) {
            result *= result;
            result *= base;
        } else {
            result *= result;
        }
    }

    return result;
}

#ifdef __GNUC__
// power_via_exponent_binary_partition_with_gcc_extentions -
// возведение в степень через бинарное разложение показателя степени
// с привлечением оптимизаций, встроенных в компилятор GCC
template <typename T>
T power_via_exponent_binary_partition_with_gcc_extentions(T base, unsigned int exponent)
{
    // определяем первый значащий бит
    int first_signed_bit_position = static_cast<T>(sizeof(T) * 8) - __builtin_clz(exponent);

    // начиная с первого значащего бита собираем результат
    int result = 1;
    for (int pos = first_signed_bit_position; pos >= 0; pos--) {
        if (static_cast<T>(exponent) & (1 << pos)) {
            result *= result;
            result *= base;
        } else {
            result *= result;
        }
    }

    return result;
}
#endif

// --------- Fibonacci numbers ------------

// fibonacci_func - тип функции для вычисления чисел Фибоначчи
template <typename T, typename N, typename = std::enable_if_t<std::is_integral_v<T> && std::is_integral_v<N>>>
using fibonacci_func = std::function<T(N)>;

// fibonacci_recursive - рекурсивный алгоритм вычисления чисел Фибоначчи
template <typename T, typename N, typename = std::enable_if_t<std::is_integral_v<T> && std::is_integral_v<N>>>
T fibonacci_recursive(N n)
{
    switch (n) {
    case 0:
        return T(0);
    case 1:
        return T(1);
    default:
        return fibonacci_recursive<T, N>(n - 1) + fibonacci_recursive<T, N>(n - 2);
    }
}

// fibonacci_iterative - итеративный алгоритм вычисления чисел Фибоначчи
template <typename T, typename N, typename = std::enable_if_t<std::is_integral_v<T> && std::is_integral_v<N>>>
T fibonacci_iterative(N n)
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

const double golden_ratio = (1 + sqrt(5)) / 2;

// fibonacci_golden_ratio - алгоритм вычисления чисел Фибоначчи через золотое сечение
template <typename T, typename N, typename = std::enable_if_t<std::is_integral_v<T> && std::is_integral_v<N>>>
T fibonacci_golden_ratio(N n)
{
    auto value = (pow(golden_ratio, n) - pow(1 - golden_ratio, n)) / sqrt(5);
    return static_cast<int>(value);
}

// Matrix - вспомогательный тип матрицы размера 2x2
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

// fibonacci_matrix - алгоритм вычисления чисел Фибоначчи через перемножение матриц
template <typename T, typename N, typename = std::enable_if_t<std::is_integral_v<T> && std::is_integral_v<N>>>
T fibonacci_matrix(N n)
{
    if (n < 2) {
        return fibonacci_iterative<T, N>(n);
    }

    return power_via_power_of_two<Matrix>(Matrix(1, 1, 1, 0), static_cast<unsigned int>(n)).get_fibonacci_value();
}

#endif

// --------- Prime numbers ------------

template <typename T>
using prime_numbers_func = std::function<void(T, std::vector<T>&)>;

template <typename T>
void prime_numbers_bruteforce(T n, std::vector<T>& result)
{
    if (n == 0) {
        return;
    }

    result.push_back(1);

    if (n == 1) {
        return;
    }

    for (int i = 2; i <= n; i++) {
        bool is_prime = true;
        for (int j = 2; j < i - 1; j++) {
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            result.push_back(i);
        }
    }
}