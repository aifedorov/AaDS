#include <iostream>
#include <vector>

void insertionSort(std::vector<int>* array, int size)
{
    for (int i = 1; i < size; ++i) {
        int tmp = (*array)[i];
        
        int j = i - 1;
        for (; j >= 0 && (*array)[j] > tmp; --j) {
            (*array)[j + 1] = (*array)[j];
        }
        (*array)[j + 1] = tmp;
    }
}
int main(int argc, const char * argv[]) {

    int tmp;
    std::vector<int> array;
    
    while(std::cin >> tmp)
        array.push_back(tmp);
    
    insertionSort(&array, (int)array.size());
    
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    return 0;
}
