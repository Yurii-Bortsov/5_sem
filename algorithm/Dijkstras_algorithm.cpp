#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <algorithm>

/**
 * @brief Создает случайную матрицу смежности для графа.
 * 
 * @param numNodes Количество вершин графа.
 * @param minWeight Минимально возможный вес ребра.
 * @param maxWeight Максимально возможный вес ребра.
 * @return Матрица смежности графа.
 */
std::vector<std::vector<int>> createRandomAdjacencyMatrix(size_t numNodes, int minWeight, int maxWeight);

/**
 * @brief Выводит матрицу смежности графа в консоль.
 * 
 * @param adjacencyMatrix Матрица смежности графа.
 */
void displayGraph(const std::vector<std::vector<int>>& adjacencyMatrix);

/**
 * @brief Реализует алгоритм Дейкстры для поиска кратчайших путей.
 * 
 * @param start Узел, с которого начинается поиск.
 * @param adjacencyMatrix Матрица смежности графа.
 * @return Вектор расстояний от начального узла до всех остальных.
 */
std::vector<int> dijkstraAlgorithm(size_t start, const std::vector<std::vector<int>>& adjacencyMatrix);

/**
 * @brief Находит вершину с минимальным расстоянием, которая еще не обработана.
 * 
 * @param distances Вектор расстояний.
 * @param processed Массив флагов обработки вершин.
 * @return Индекс вершины с минимальным расстоянием.
 */
size_t getNextMinNode(const std::vector<int>& distances, const std::vector<bool>& processed);

int main() {
    try {
        size_t numNodes = 6;
        int minWeight = 3;
        int maxWeight = 150;
        size_t startNode = 4;

        // Генерация графа
        auto adjacencyMatrix = createRandomAdjacencyMatrix(numNodes, minWeight, maxWeight);

        // Вывод графа
        std::cout << "Graph (Adjacency Matrix):\n";
        displayGraph(adjacencyMatrix);

        // Поиск кратчайших путей
        auto shortestDistances = dijkstraAlgorithm(startNode, adjacencyMatrix);

        // Вывод результатов
        std::cout << "\nShortest Paths from Node " << startNode << ":\n";
        for (size_t i = 0; i < shortestDistances.size(); ++i) {
            std::cout << "To Node " << i << ": " << shortestDistances[i] << "\n";
        }

        return 0;
    } catch (const std::exception& err) {
        std::cerr << "Error: " << err.what() << std::endl;
        return 1;
    }
}

std::vector<std::vector<int>> createRandomAdjacencyMatrix(size_t numNodes, int minWeight, int maxWeight) {
    std::vector<std::vector<int>> matrix(numNodes, std::vector<int>(numNodes, 0));

    // Инициализация генератора случайных чисел
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> weightDist(minWeight, maxWeight);

    // Заполнение матрицы смежности
    for (size_t i = 0; i < numNodes; ++i) {
        for (size_t j = i + 1; j < numNodes; ++j) {
            int weight = weightDist(generator);
            matrix[i][j] = weight;
            matrix[j][i] = weight; // Симметричное заполнение для неориентированного графа
        }
    }

    return matrix;
}

void displayGraph(const std::vector<std::vector<int>>& adjacencyMatrix) {
    for (const auto& row : adjacencyMatrix) {
        for (int value : row) {
            std::cout << value << "\t";
        }
        std::cout << "\n";
    }
}

std::vector<int> dijkstraAlgorithm(size_t start, const std::vector<std::vector<int>>& adjacencyMatrix) {
    size_t numNodes = adjacencyMatrix.size();
    std::vector<int> distances(numNodes, std::numeric_limits<int>::max());
    std::vector<bool> processed(numNodes, false);

    distances[start] = 0;

    for (size_t i = 0; i < numNodes; ++i) {
        size_t currentNode = getNextMinNode(distances, processed);
        processed[currentNode] = true;

        for (size_t neighbor = 0; neighbor < numNodes; ++neighbor) {
            if (!processed[neighbor] && adjacencyMatrix[currentNode][neighbor] > 0 &&
                distances[currentNode] != std::numeric_limits<int>::max()) {
                int potentialDistance = distances[currentNode] + adjacencyMatrix[currentNode][neighbor];
                if (potentialDistance < distances[neighbor]) {
                    distances[neighbor] = potentialDistance;
                }
            }
        }
    }

    return distances;
}

size_t getNextMinNode(const std::vector<int>& distances, const std::vector<bool>& processed) {
    int minDistance = std::numeric_limits<int>::max();
    size_t minIndex = -1;

    for (size_t i = 0; i < distances.size(); ++i) {
        if (!processed[i] && distances[i] < minDistance) {
            minDistance = distances[i];
            minIndex = i;
        }
    }

    return minIndex;
}
