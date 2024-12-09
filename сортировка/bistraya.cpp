#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int& a, int& b) 
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector<int>& array, int low, int high)
{
    int pivot = array[high];  
    int i = (low - 1);  

    for (int j = low; j <= high - 1; j++)
    {
        if (array[j] <= pivot)
        {
            i++;  
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    return (i + 1);
}

void quickSort(vector<int>& array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

int main() 
{
    const int size = 10000;
    vector<int> array(size);

    srand(time(0));
    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % 100000;
    }

    cout << "input array:\n\n";
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
        if (i % 20 == 19) cout << "\n";  
    }
    cout << "\n\n";

    quickSort(array, 0, size - 1);

    cout << "sort array:\n\n";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
        if (i % 20 == 19) cout << "\n";  
    }
    cout << "\n";

    return 0;
}