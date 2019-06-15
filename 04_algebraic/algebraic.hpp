#ifndef ALGEBRAIC_HPP
#define ALGEBRAIC_HPP

#include <functional>
#include <math.h>
#include <type_traits>
#include <vector>

// --------- Greatest commond divisor ------------

namespace algo
{

    // GCDFunc - тип функции вычисления наибольшего общего делителя
    template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
    using GCDFunc = std::function<T(T, T)>;

    // GCDSub - алгоритм нахождения наибольшего общего делителя через классический алгоритм Евклида
    template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
    T GCDSub(T a, T b)
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

    // GCDMod - алгоритм нахождения наибольшего общего делителя через алгоритм Евклида через деление
    template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
    T GCDMod(T a, T b)
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

    // PowerFunc - тип функции для вычисления степени
    template <typename T>
    using PowerFunc = std::function<T(T, unsigned int)>;

    // PowerIterative - вычисление степени итеративным способом
    template <typename T>
    T PowerIterative(T base, unsigned int exponent)
    {
        T result(1);
        while (exponent--) {
            result *= base;
        }
        return result;
    }

    // PowerViaPowerOfTwo - возведение в степень через степень двойки с умножением
    template <typename T>
    T PowerViaPowerOfTwo(T base, unsigned int exponent)
    {
        if (exponent == 0) {
            return T(1);
        }
        if (exponent % 2 == 1) {
            return PowerViaPowerOfTwo(base, exponent - 1) * base;
        }
        T result = PowerViaPowerOfTwo(base, exponent / 2);
        return result * result;
    }

    // PowerViaExponentBinaryPartition - возведение в степень через бинарное разложение показателя степени
    template <typename T>
    T PowerViaExponentBinaryPartition(T base, unsigned int exponent)
    {
        // определяем первый значащий бит
        size_t           first_signed_bit_position = 0;
        constexpr size_t bits                      = sizeof(int) * 8 - 1;
        for (size_t pos = bits; pos >= 0; pos--) {
            if (exponent & size_t(1 << pos)) {
                first_signed_bit_position = pos;
                break;
            }
        }

        // начиная с первого значащего бита собираем результат
        T result = 1;
        for (int pos = first_signed_bit_position; pos >= 0; pos--) {
            if (exponent & size_t(1 << pos)) {
                result *= result;
                result *= base;
            } else {
                result *= result;
            }
        }

        return result;
    }

#ifdef __GNUC__
    // PowerViaExponentBinaryPartitionV2 -
    // возведение в степень через бинарное разложение показателя степени
    // с привлечением оптимизаций, встроенных в компилятор GCC
    template <typename T>
    T PowerViaExponentBinaryPartitionV2(T base, unsigned int exponent)
    {
        // определяем первый значащий бит
        size_t first_signed_bit_position = static_cast<size_t>(sizeof(T) * 8) - static_cast<size_t>(__builtin_clz(exponent));

        // начиная с первого значащего бита собираем результат
        T result = 1;
        for (int pos = first_signed_bit_position; pos >= 0; pos--) {
            if (exponent & (size_t(1) << pos)) {
                result *= result;
                result *= base;
            } else {
                result *= result;
            }
        }

        return result;
    }
#endif

    // PowerViaExponentBinaryPartition_fast
    template <typename T>
    T PowerViaExponentBinaryPartition_fast(T base, unsigned int exponent)
    {
        T result = 1;
        while (exponent > 1) {
            if (exponent % 2 == 1) {
                result *= base;
            }
            base *= base;
            exponent /= 2;
        }
        if (exponent > 0) {
            result *= base;
        }
        return result;
    }

    // --------- Fibonacci numbers ------------

    // FibonacciFunc - тип функции для вычисления чисел Фибоначчи
    template <typename T, typename N, typename = std::enable_if_t<std::is_integral_v<T> && std::is_integral_v<N>>>
    using FibonacciFunc = std::function<T(N)>;

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

    // FibonacciIterative - итеративный алгоритм вычисления чисел Фибоначчи
    template <typename T, typename N, typename = std::enable_if_t<std::is_integral_v<T> && std::is_integral_v<N>>>
    T FibonacciIterative(N n)
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

    // FibonacciGoldenRatio - алгоритм вычисления чисел Фибоначчи через золотое сечение
    template <typename T, typename N, typename = std::enable_if_t<std::is_integral_v<T> && std::is_integral_v<N>>>
    T FibonacciGoldenRatio(N n)
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
            *this = PowerViaPowerOfTwo<Matrix>(Matrix(1), static_cast<unsigned int>(n));
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

    // FibonacciMatrix - алгоритм вычисления чисел Фибоначчи через перемножение матриц
    template <typename T, typename N, typename = std::enable_if_t<std::is_integral_v<T> && std::is_integral_v<N>>>
    T FibonacciMatrix(N n)
    {
        if (n < 2) {
            return FibonacciIterative<T, N>(n);
        }

        return PowerViaPowerOfTwo<Matrix>(Matrix(1, 1, 1, 0), static_cast<unsigned int>(n)).get_fibonacci_value();
    }

    // --------- Prime numbers ------------

    template <typename T, typename = std::enable_if_t<std::is_unsigned_v<T>>>
    using PrimeNumbersFunc = std::function<void(T, std::vector<T>&)>;

    // PrimeNumbersBruteforce - простой перебор всех простых чисел без оптимизаций
    template <typename T, typename = std::enable_if_t<std::is_unsigned_v<T>>>
    void PrimeNumbersBruteforce(T n, std::vector<T>& result)
    {
        if (n <= 1) {
            return;
        }

        for (T i = 2; i <= n; i++) {
            bool is_prime = true;
            for (T j = 2; j < i - 1; j++) {
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

    // PrimeNumbersBruteforceOptimized - простой перебор всех простых чисел с некоторыми оптимизациями
    template <typename T, typename = std::enable_if_t<std::is_unsigned_v<T>>>
    void PrimeNumbersBruteforceOptimized(T n, std::vector<T>& result)
    {
        if (n <= 1) {
            return;
        }
        result.push_back(2);
        if (n == 2) {
            return;
        }

        for (T i = 3; i <= n; i += 2) {
            bool is_prime = true;
            for (T j = 3; j <= static_cast<T>(sqrt(i)); j++) {
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

    // PrimeNumbersEratosthenesSieve - поиск простых чисел с помощью решета Эратосфена
    template <typename T, typename = std::enable_if_t<std::is_unsigned_v<T>>>
    void PrimeNumbersEratosthenesSieve(T n, std::vector<T>& result)
    {
        if (n <= 2) {
            PrimeNumbersBruteforceOptimized(n, result);
            return;
        }

        auto flags = std::vector<bool>();
        for (size_t i = 0; i <= n; i++) {
            flags.push_back(true);
        }

        for (T i = 2; PowerViaExponentBinaryPartitionV2<T>(i, 2) <= n; i += 1) {
            if (flags[i]) {
                for (T j = PowerViaExponentBinaryPartitionV2<T>(i, 2); j <= n; j += i) {
                    flags[j] = false;
                }
            }
        }

        for (T i = 2; i <= n; i++) {
            if (flags[i]) {
                result.push_back(i);
            }
        }
    }

} // namespace algo

#endif