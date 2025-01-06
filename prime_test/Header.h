#pragma once
#include <iostream>
#include <random>
/*
*@brief getRandomNumber - функция для получения случайного числа в диапозоне
*@param - max максимальное значение в диапозоне
*@param - min минимальное значение в диапозоне
*@return возвращает случайное число в заданном диапозоне
*/
int getRandomNumber(int max, int min);

/*
*@brief modExp - функция для получения остатка от числа в степени
*@param - base основание степени
*@param - exp степень в которую надо возвести основание
*@param - mod число остаток по каторому надо брать
*@return возвращает остаток от деления base в степени exp на mod
*/
long long modExp(long long base, long long exp, long long mod);

/*
*@brief FermaTest - функция для проверки числа на простоту методом Ферма
*@param - n число на проверку
*@param - t степень доверия
*@return true - если число простое false - если число составное
*/
bool FermaTest(int n, size_t t);

/*
*@brief JacobiSigh - функция вычисляющая символ Якоби для пары чисел a , n
*@param - a числитель в знаке Якоби
*@param - n знаменатель в знаке Якоби
*@return Символ Якоби
*/
int JacobiSign(size_t a, size_t  n);

/*
*@brief SoloveiShtrassen - функция для проверки числа на простоту методом Соловея-Штрассена
*@param - n число на проверку
*@param - t степень доверия
*@return true - если число простое false - если число составное
*/
bool SoloveiShtrassen(int n, size_t t);

/*
*@brief MillerRabin - функция для проверки числа на простоту методом Миллера - Рабина
*@param - n число на проверку
*@param - t степень доверия
*@return true - если число простое false - если число составное
*/
bool MillerRabin(int n, size_t t);
