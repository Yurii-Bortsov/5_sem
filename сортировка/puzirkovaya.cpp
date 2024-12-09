#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


void bubbleSort(vector<int>& array) 
{
    int n = array.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
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

    
    bubbleSort(array);

    cout << "sort array:\n\n";
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
        if (i % 20 == 19) cout << "\n";  
    }
    cout << "\n";

    return 0;
}