#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

/**
 * @brief Вычисляет значение полинома в заданной точке по схеме Горнера.
 * @param coefficients Вектор коэффициентов полинома.
 * @param x Точка, в которой вычисляется значение полинома.
 * @return Значение полинома в точке x.
 */
int evaluatePolynomial(const std::vector<int>& coefficients, int x);

/**
 * @brief Вычисляет разделённые разности для интерполяции методом Ньютона.
 * @param x Вектор координат x узлов интерполяции.
 * @param y Вектор значений y узлов интерполяции.
 * @return Матрица разделённых разностей.
 */
std::vector<std::vector<int>> calculateDividedDifferences(const std::vector<int>& x, const std::vector<int>& y);

/**
 * @brief Получает коэффициенты полинома Ньютона из разделённых разностей.
 * @param dividedDifferences Матрица разделённых разностей.
 * @return Вектор коэффициентов полинома.
 */
std::vector<double> extractNewtonCoefficients(const std::vector<std::vector<int>>& dividedDifferences);

/**
 * @brief Умножение двух чисел методом Тоома-Кука с разбиением на 3 части.
 * @param first Первый множитель.
 * @param second Второй множитель.
 * @param n Количество разрядов в числах.
 * @return Результат умножения.
 */
int multiplyToomCook3(int& first, int& second, size_t n);

/**
 * @brief Умножение двух чисел методом Карацубы.
 * @param first Первый множитель.
 * @param second Второй множитель.
 * @param n Количество разрядов в числах.
 * @return Результат умножения.
 */
long long multiplyKaratsuba(int& first, int& second, size_t n);

int main() {
    int num1 = 100000;
    int num2 = 100000;
    size_t digits = 6;

    std::cout << "Результат Тоома-Кука: " << multiplyToomCook3(num1, num2, digits) 
              << "\nОжидаемое значение: " << 123567 * 112567 << std::endl;

    return 0;
}

long long multiplyKaratsuba(int& first, int& second, size_t n) {
    if (n > 1 && n % 2 == 0) {
        int base = pow(10, n / 2);

        int a = first / base;
        int b = first % base;
        int c = second / base;
        int d = second % base;

        int ac = multiplyKaratsuba(a, c, n / 2);
        int bd = multiplyKaratsuba(b, d, n / 2);
        int abcd = multiplyKaratsuba(a + b, c + d, n / 2) - ac - bd;

        return pow(10, n) * ac + pow(10, n / 2) * abcd + bd;
    }
    return first * second;
}

int evaluatePolynomial(const std::vector<int>& coefficients, int x) {
    int result = 0;
    for (int i = coefficients.size() - 1; i >= 0; --i) {
        result = result * x + coefficients[i];
    }
    return result;
}

std::vector<std::vector<int>> calculateDividedDifferences(const std::vector<int>& x, const std::vector<int>& y) {
    size_t n = x.size();
    std::vector<std::vector<int>> dividedDifferences(n, std::vector<int>(n, 0));

    for (size_t i = 0; i < n; ++i) {
        dividedDifferences[i][0] = y[i];
    }

    for (size_t j = 1; j < n; ++j) {
        for (size_t i = 0; i < n - j; ++i) {
            dividedDifferences[i][j] = (dividedDifferences[i + 1][j - 1] - dividedDifferences[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    return dividedDifferences;
}

std::vector<double> extractNewtonCoefficients(const std::vector<std::vector<int>>& dividedDifferences) {
    std::vector<double> coefficients;
    for (size_t i = 0; i < dividedDifferences.size(); ++i) {
        coefficients.push_back(dividedDifferences[0][i]);
    }
    return coefficients;
}

int multiplyToomCook3(int& first, int& second, size_t n) {
    if (n % 3 != 0) {
        return 0;
    }

    size_t segmentSize = n / 3;
    int base = pow(10, segmentSize);

    std::vector<int> coefficients1{
        first % base,
        (first / base) % base,
        first / (base * base)
    };

    std::vector<int> coefficients2{
        second % base,
        (second / base) % base,
        second / (base * base)
    };

    std::vector<int> eval1, eval2, results;
    for (int point : {0, 1, 2, 3, 4}) {
        eval1.push_back(evaluatePolynomial(coefficients1, point));
        eval2.push_back(evaluatePolynomial(coefficients2, point));
    }

    for (size_t i = 0; i < eval1.size(); ++i) {
        results.push_back(eval1[i] * eval2[i]);
    }

    auto dividedDiffs = calculateDividedDifferences({0, 1, 2, 3, 4}, results);
    auto coeffs = extractNewtonCoefficients(dividedDiffs);

    int result = 0;
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result += coeffs[i] * pow(base, i);
    }
    return result;
}
