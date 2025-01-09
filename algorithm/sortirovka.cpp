#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

/**
 * @brief Генерирует вектор случайных чисел в заданном диапазоне.
 * 
 * @param min Минимальное значение диапазона.
 * @param max Максимальное значение диапазона.
 * @param size Размер создаваемого вектора.
 * @return std::vector<int> Вектор сгенерированных чисел.
 */
std::vector<int> createRandomVector(int min, int max, size_t size);

/**
 * @brief Сортирует вектор с использованием метода вставок.
 * 
 * @param vec Вектор для сортировки.
 * @return std::vector<int> Отсортированный вектор.
 */
std::vector<int> sortUsingInsertion(std::vector<int>& vec);

/**
 * @brief Сортирует вектор с использованием пузырьковой сортировки.
 * 
 * @param vec Вектор для сортировки.
 * @return std::vector<int> Отсортированный вектор.
 */
std::vector<int> sortUsingBubble(std::vector<int>& vec);

/**
 * @brief Сортирует вектор с использованием алгоритма быстрой сортировки.
 * 
 * @param vec Вектор для сортировки.
 * @return std::vector<int> Отсортированный вектор.
 */
std::vector<int> sortUsingQuickSort(std::vector<int>& vec);

/**
 * @brief Выводит содержимое вектора на экран.
 * 
 * @param vec Вектор для вывода.
 */
void displayVector(const std::vector<int>& vec);

int main() {
    try {
        int lowerBound = 0;
        int upperBound = 9999;
        size_t vectorSize = 10000;

        std::vector<int> data1 = createRandomVector(lowerBound, upperBound, vectorSize);
        std::vector<int> data2 = createRandomVector(lowerBound, upperBound, vectorSize);
        std::vector<int> data3 = createRandomVector(lowerBound, upperBound, vectorSize);

        std::cout << "Insertion Sort Result: ";
        displayVector(sortUsingInsertion(data1));

        std::cout << "Bubble Sort Result: ";
        displayVector(sortUsingBubble(data2));

        std::cout << "Quick Sort Result: ";
        displayVector(sortUsingQuickSort(data3));
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}

std::vector<int> createRandomVector(int min, int max, size_t size) {
    std::vector<int> result;
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> distribution(min, max);

    for (size_t i = 0; i < size; ++i) {
        result.push_back(distribution(generator));
    }

    return result;
}

std::vector<int> sortUsingInsertion(std::vector<int>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        int current = vec[i];
        size_t j = i;

        while (j > 0 && vec[j - 1] > current) {
            vec[j] = vec[j - 1];
            --j;
        }

        vec[j] = current;
    }

    return vec;
}

std::vector<int> sortUsingBubble(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        bool swapped = false;

        for (size_t j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }

    return vec;
}

std::vector<int> sortUsingQuickSort(std::vector<int>& vec) {
    if (vec.size() <= 1) return vec;

    int pivot = vec[vec.size() / 2];
    std::vector<int> leftPartition, rightPartition;

    for (size_t i = 0; i < vec.size(); ++i) {
        if (i != vec.size() / 2) {
            if (vec[i] < pivot) {
                leftPartition.push_back(vec[i]);
            } else {
                rightPartition.push_back(vec[i]);
            }
        }
    }

    leftPartition = sortUsingQuickSort(leftPartition);
    rightPartition = sortUsingQuickSort(rightPartition);

    leftPartition.push_back(pivot);
    leftPartition.insert(leftPartition.end(), rightPartition.begin(), rightPartition.end());

    return leftPartition;
}

void displayVector(const std::vector<int>& vec) {
    for (const int& item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}
