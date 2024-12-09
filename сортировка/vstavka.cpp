#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void insertionSort(vector<int>& array)
{
    int n = array.size();
    for (int i = 1; i < n; i++)
    {
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
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

    insertionSort(array);

    cout << "sort array:\n\n";
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
        if (i % 20 == 19) cout << "\n";  
    }
    cout << "\n";

    return 0;
}