#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

static int a[ 2000000 ] = {0};

int compare(const void * x1, const void * x2)
{
    return ( *(int*)x1 - *(int*)x2 );
}

int partion(int* array, int n)
{
    if ( n <= 1 ) {
        return 0;
    }
    const int& pivot = array[n - 1];
    int i = 0;
    int j = n - 2;
    while (i <= j) {
        for (; array[i] < pivot; ++i){}
        for (; j >= 0 && !(array[j] < pivot); --j){}
        
        if (i < j) {
            std::swap(array[i++], array[j--]);
        }
    }
    std::swap(array[i], array[n - 1]);
    
    return i;
}

void quickSort(int* array, int n)
{
    int part = partion(array, n);
    if (part > 0) {
        quickSort(array, part);
    }
    if (part + 1 < n) {
        quickSort(array + part + 1, n - (part + 1));
    }
}
int main(int argc, const char * argv[]) {
    
    int num_input = 0;
    int number;
    
    while( fscanf( stdin, "%d", &number ) != '\0') {
        a[ num_input++ ] = number;
    }
    
    quickSort(a, num_input);
    
    for (int i = 9; i < num_input; i+= 10) {
            std::cout << a[i] << " ";
    }
   
    return 0;
}
