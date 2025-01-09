#include "Header.h"

int main() {
    setlocale(LC_ALL, "ru");
    
    // Тестирование MillerRabin
    std::cout << "Miller-Rabin Test for 849177: " << (MillerRabin(849177, 3) ? "Prime" : "Composite") << "\n";
    
    // Тестирование FermaTest
    std::cout << "Fermat Test for 849177: " << (FermaTest(849177, 3) ? "Prime" : "Composite") << "\n";
    
    // Тестирование SoloveiShtrassen
    std::cout << "Solovay-Strassen Test for 849177: " << (SoloveiShtrassen(849177, 3) ? "Prime" : "Composite") << "\n";
    
    return 0;
}

int getRandomNumber(int max, int min)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> uniformIntDistribution(min, max);
	return(uniformIntDistribution(gen));
}

long long modExp(long long base, long long exp, long long mod) {
	long long result = 1;
	base %= mod;
	while (exp > 0) {
		if (exp % 2 == 1)
		{
			result = (result * base) % mod;
		}
		base = (base * base) % mod;
		exp /= 2;
	}
	return result;
}

bool FermaTest(int n, size_t t)
{
	bool fl = false;
	for (size_t i = 0; i < t; i++)
	{
		int a = getRandomNumber(n - 2, 2);
		if (modExp(a, n - 1, n) == 1)
		{
			fl = true;
		}
		else
		{
			fl = false;
			break;
		}
	}
	return fl;
}

int JacobiSign(size_t a, size_t  n)
{
	if (a == 0)
	{
		return a;

	}
	else if (a == 1)
	{
		return a;
	}
	else
	{
		int s;
		size_t counter = 0;
		while (a % 2 == 0)
		{
			a = a / 2;
			counter += 1;
		}
		if (counter % 2 == 0)
		{
			s = 1;
		}
		else if ((n % 8 == 1) or (n % 8 == 7))
		{
			s = 1;
		}
		else
		{
			s = -1;
		}
		if ((n % 4 == 3) and (a % 4 == 3))
		{
			s = -s;
		}
		if (a == 1)
		{
			return s;
		}
		else
		{
			return s * JacobiSign(n % a, a);
		}
	}
}

bool SoloveiShtrassen(int n, size_t t)
{
	bool fl = true;
	for (size_t i = 0; i < t; i++)
	{
		int a = getRandomNumber(n - 2, 2);
		int r = modExp(a, ((n - 1) / 2), n);
		if ((r != 1) and (r != (n - 1)))
		{
			fl = false;
			break;
		}
		if (r == n - 1)
		{
			r = -1;
		}
		if (JacobiSign(a, n) != r)
		{
			fl = false;
			break;
		}
	}
	return fl;
}

bool MillerRabin(int n, size_t t)
{
	bool fl = true;
	int newN = n;
	newN -= 1;
	int counter = 0;
	while (newN % 2 == 0)
	{
		counter += 1;
		newN /= 2;
	}
	int r = newN;
	for (size_t i = 0; i < t; i++)
	{
		int b = getRandomNumber(n - 2, 2);
		int y = modExp(b, r, n);
		if (y == n - 1)
		{
			y = -1;
		}
		if (y != 1 and y != -1)
		{
			int j = 1;
			while (j < counter and y != -1)
			{
				y = modExp(y, 2, n);
				if (y == 1)
				{
					return false;
					break;
				}
				j += 1;
			}
			if (y != n - 1)
			{
				return false;
				break;
			}
		}

	}
	return fl;
}
