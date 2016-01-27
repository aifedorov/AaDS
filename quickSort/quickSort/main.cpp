#include <iostream>
#include <sstream>
#include <vector>

long partion(long* array, long n)
{
    if ( n <= 1 ) {
        return 0;
    }
    const long& pivot = array[n - 1];
    long i = 0;
    long j = n - 2;
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

void quickSort(long* array, long n)
{
    long part = partion(array, n);
    if (part > 0) {
        quickSort(array, part);
    }
    if (part + 1 < n) {
        quickSort(array + part + 1, n - (part + 1));
    }
}
int main(int argc, const char * argv[]) {
    
    std::vector<long> array;
    long tmp;
    
    std::string line;
    getline(std::cin, line);
    std::istringstream iss(line);
    while (iss >> tmp)
    {
        array.push_back(tmp);
    }
    
    long n = array.size();
    long* a = new long[n];
    for (long i = 0 ; i < n; i++)
        a[i] = array[i];
    
    quickSort(a, n);
    for (long i = 0; i < n; i++) {
        if ((i + 1)  % 10 == 0) {
            std::cout << a[i] << " ";
        }
    }
   
    return 0;
}
