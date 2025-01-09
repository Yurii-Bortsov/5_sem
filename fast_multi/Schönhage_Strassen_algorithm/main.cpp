#include "header.h"

int main() {
    int n = 4;
    int p = 5;
    int w = 2;
    int wRev = 16;
    int N = 64;

    std::vector<int> a = { 81,135,1,140 };
    std::vector<int> b = { 0,1,2,3 };
    std::vector<int> v = { 0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1 };
    std::vector<int> u = { 0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1 };
    std::vector<int> result2 = iFFT(a, 241, 257, 193);
    std::vector<int> aa = { 5,1,0,0 };
    std::vector<int> bb = { 5,1,0,0 };
    std::vector<int> e = calculateNegativeConvolution(aa, bb, 4);
    int result = SchonhageStrassen(80, 80, 16);
    std::cout << result;
    return 0;
}

unsigned int reverseBits(unsigned int x, int bitSize)
{
    unsigned int result = 0;
    for (int i = 0; i < bitSize; ++i)
    {
        if (x & (1 << i))
        {
            result |= (1 << (bitSize - 1 - i));
        }
    }
    return result;
}


std::vector<int> decimalToBinaryVector(int number, int N) {
    std::vector<int> binaryBits;
    if (number == 0) {
        binaryBits.push_back(0);
    }
    else {
        while (number > 0) {
            binaryBits.push_back(number % 2);
            number /= 2;
        }
        std::reverse(binaryBits.begin(), binaryBits.end());
    }
    if (binaryBits.size() < N) {
        binaryBits.insert(binaryBits.begin(), N - binaryBits.size(), 0);
    }
    return binaryBits;
}

size_t modExp(size_t base, int exp, size_t mod)
{
    size_t result = 0;
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

static std::vector<int> FFT(const std::vector<int>& a, size_t w, size_t p)
{
    int n = a.size();
    int k = static_cast<size_t>(log2(n));
    std::vector<int> R(n), S(n);

    for (size_t i = 0; i < n; ++i) {
        R[i] = a[i];
    }

    for (int l = k - 1; l >= 0; --l) {
        for (size_t i = 0; i < n; ++i) {
            S[i] = R[i];
        }

        for (size_t i = 0; i < n; ++i) {
            int mask = (1 << l) - 1;
            int base = i >> (l + 1);
            int low = i & mask;
            int i0 = (base << (l + 1)) | low;
            int i1 = i0 | (1 << l);

            int rev_i = reverseBits(i, k);
            int preFactor = static_cast<int>(pow(2, l));
            int reversedFactor = reverseBits(i / preFactor, k);
            int factor = static_cast<int>(pow(w, reversedFactor));
            R[i] = (S[i0] + factor * S[i1]) % p;
            if (R[i] < 0) R[i] += p;
        }
    }



    std::vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        b[reverseBits(i, k)] = R[i];
    }

    return b;
}

std::vector<int> iFFT(const std::vector<int>& a, size_t wRev, size_t p, int nInverse)
{
    int n = a.size();
    int k = static_cast<int>(log2(n));
    std::vector<int> R(n), S(n);

    for (size_t i = 0; i < n; ++i)
    {
        R[i] = a[i];
    }

    for (int l = k - 1; l >= 0; --l)
    {
        for (size_t i = 0; i < n; ++i)
        {
            S[i] = R[i];
        }
        for (size_t i = 0; i < n; ++i)
        {
            int mask = (1 << l) - 1;
            int base = i >> (l + 1);
            int low = i & mask;
            int i0 = (base << (l + 1)) | low;
            int i1 = i0 | (1 << l);

            int rev_i = reverseBits(i, k);
            int preFactor = static_cast<int>(pow(2, l));
            int reversedFactor = reverseBits(i / preFactor, k);
            int factor = static_cast<int>(pow(wRev, reversedFactor)) % p;
            R[i] = (S[i0] + factor * S[i1]) % p;
            if (R[i] < 0) R[i] += p;
        }
    }
    std::vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        b[reverseBits(i, k)] = (R[i] * nInverse) % p;

    }
    return b;
}

int binaryToDecimal(const std::vector<int>& binaryVector) {
    int decimalValue = 0;
    int size = binaryVector.size();
    for (int i = 0; i < size; ++i) {
        decimalValue += binaryVector[i] * std::pow(2, size - 1 - i);
    }

    return decimalValue;
}

std::vector<std::vector<int>> splitBinaryVector(const std::vector<int>& binaryVector, int numberOfGroups, int digits)
{
    std::vector<std::vector<int>> groups;
    for (int i = 0; i < numberOfGroups; ++i) {
        std::vector<int> group(binaryVector.begin() + i * digits, binaryVector.begin() + (i + 1) * digits);
        groups.push_back(group);
    }
    return groups;
}

std::vector<int> polinomByModulo(std::vector<int> vector, int p)
{
    for (size_t i = 0; i < vector.size(); i++)
    {
        vector[i] %= p;
    }
    return vector;
}

std::vector<int> calculateNegativeConvolution(std::vector<int> a, std::vector<int> b, int N) {
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    std::vector<int> e(N, 0);

    for (int i = 0; i < N; ++i) {
        int sum1 = 0;
        for (int j = 0; j <= i; ++j) {
            sum1 += a[j] * b[i - j];
        }

        int sum2 = 0;
        for (int j = i + 1; j < N; ++j) {
            sum2 += a[i + N - j] * b[j];
        }

        e[i] = sum1 - sum2;
    }

    return e;
}

std::vector<int> createPsiVectors(std::vector<int> vector, int psi, int K)
{
    std::reverse(vector.begin(), vector.end());
    for (size_t i = 0; i < K; i++)
    {
        vector[i] *= pow(psi, i);
    }
    return vector;
}

int SchonhageStrassen(int first, int second, int N)
{
    int n = log2(N);
    int l = n / 2;
    int k = n - l;
    int K = pow(2, k);
    int L = pow(2, l);
    int psi = pow(2, (2 * L) / K);
    int m = pow(2, 2 * L) + 1;
    int w = pow(2, 4 * L / K);
    int wRev = m - (pow(2, (2 * L) - (4 * L / K)));
    int KRev = m - (pow(2, 2 * L - k));
    int psiRev = m - (pow(2, (2 * L) - (2 * L / K)));

    std::vector<int> firstBinary = decimalToBinaryVector(first, N);
    std::vector<int> secondBinary = decimalToBinaryVector(second, N);
    std::vector<int> firstNew;
    std::vector<int> secondNew;

    std::vector<std::vector<int>> firstSplit = splitBinaryVector(firstBinary, K, L);
    std::vector<std::vector<int>> secondSplit = splitBinaryVector(secondBinary, K, L);

    for (size_t i = 0; i < K; i++)
    {
        firstNew.push_back(binaryToDecimal(firstSplit[i]));
        secondNew.push_back(binaryToDecimal(secondSplit[i]));
    }


    std::vector<int> W = calculateNegativeConvolution(firstNew, secondNew, K);

    std::vector<int> W1 = polinomByModulo(W, K);
    std::vector<int> W2 = polinomByModulo(W, pow(2, 2 * L) + 1);

    std::vector<int>firstPsiVector = createPsiVectors(firstNew, psi, K);
    std::vector<int>secondPsiVector = createPsiVectors(secondNew, psi, K);

    std::vector<int> firstValues = FFT(firstPsiVector, w, m);
    std::vector<int> secondValues = FFT(secondPsiVector, w, m);
    std::vector<int> resultValues;
    for (size_t i = 0; i < K; i++)
    {
        resultValues.push_back((firstValues[i] * secondValues[i]) % m);
    }
    std::vector<int> koeffs = iFFT(resultValues, wRev, m, KRev);

    std::vector<int> d(koeffs.size());

    for (size_t i = 0; i < koeffs.size(); i++)
    {
        d[i] = pow(psiRev, i) * koeffs[i]; //;
    }
    std::vector<int>W2new = polinomByModulo(d, m); //w2new = 
    std::vector<int>W3;
    for (size_t i = 0; i < K; i++)
    {

        W3.push_back(pow(2, 2 * L) * ((W1[i] - W2new[i]) % K) + W2new[i]);
    }
    for (size_t i = 0; i < K; i++)
    {
        if (W3[i] < ((i + 1) * pow(2, 2 * L)))
        {
            W[i] = W3[i];
        }
        else
        {
            W[i] = W3[i] - K * (pow(2, 2 * L) + 1);
        }
    }
    int result = 0;
    for (size_t i = 0; i < K; i++)
    {
        result += W[i] * pow(2, 4 * i);
    }
    return result;
}
