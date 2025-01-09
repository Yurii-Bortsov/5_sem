#include <iostream>
#include <random>
#include <cmath>

/*
 * brief Возведение числа в степень по модулю
 * param base Основание
 * param exp Показатель степени
 * param mod Модуль
 * return Результат возведения base в степень exp по модулю mod
 */
long long PowerMod(long long base, long long exp, long long mod);

/*
 * brief Генерация случайного числа в заданном диапазоне
 * param min Нижняя граница
 * param max Верхняя граница
 * return Случайное число в пределах [min, max]
 */
long long GenerateRandomInRange(int min, int max);

/*
 * brief Генерация случайной дроби в диапазоне от 0 до 1
 * param t Размерность числа
 * return Случайная дробь в диапазоне (0, 1)
 */
double GenerateRandomFraction(size_t t);

/*
 * brief Генерация простого числа по алгоритму ГОСТ
 * param q Простое число
 * param t Размерность числа (в битах)
 * return Простое число длины t бит
 */
long long GenerateGostPrime(long long q, size_t t);

int main()
{
    std::cout << GenerateGostPrime(17, 10) << std::endl;
    return 0;
}

long long PowerMod(long long base, long long exp, long long mod)
{
    long long result = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long GenerateRandomInRange(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

double GenerateRandomFraction(size_t t)
{
    size_t base = 16;
    int initialValue = GenerateRandomInRange(32768, 65536);
    int offset = GenerateRandomInRange(32768, 65536);
    long long newValue = ((19381 * initialValue) + offset) % static_cast<int>(std::pow(2, 16));
    size_t iterations = t / base;
    double fraction = static_cast<double>(newValue) / static_cast<double>(std::pow(2, 16));
    return fraction;
}

long long GenerateGostPrime(long long q, size_t t)
{
    bool isPrimeFound = false;
    int offsetMultiplier = 0;
    int N = 0;
    long long candidatePrime = 0;

    while (candidatePrime > std::pow(2, t) || candidatePrime == 0)
    {
        N = static_cast<long long>(std::pow(2, t - 1) / q) +
            static_cast<long long>((std::pow(2, t - 1) / q) * GenerateRandomFraction(t));

        if (N % 2 != 0)
        {
            ++N;
        }

        candidatePrime = q * (N + offsetMultiplier) + 1;
    }

    while (!isPrimeFound)
    {
        if ((PowerMod(2, candidatePrime - 1, candidatePrime) == 1) &&
            (PowerMod(2, N + offsetMultiplier, candidatePrime) != 1))
        {
            isPrimeFound = true;
        }
        else
        {
            offsetMultiplier += 2;
            candidatePrime = q * (N + offsetMultiplier) + 1;
        }
    }
    return candidatePrime;
}
