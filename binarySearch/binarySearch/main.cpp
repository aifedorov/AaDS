#include <iostream>
#include <cmath>

int binarySearch (int* arr, int count, int element);

int main(int argc, const char * argv[]) {

    
    int n;
    std::cin >> n;
    
    int* A = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    
    int m;
    std::cin >> m;
    
    int* B = new int[m];
    
    for (int i = 0; i < m; i++) {
        std::cin >> B[i];
    }
    
    for (int i = 0; i < m; i++) {
        int minIndex = binarySearch(A, n, B[i]);
        std::cout << minIndex << " ";
    }
    
    return 0;
}

int binarySearch (int* arr, int count, int element)
{
    int first = 0;
    int last = count;
    int result = 0;
    int diff = abs(arr[first] - element);
    
    while (first < last) {
        
        int mid = (first + last) / 2;
        
        if (element <= arr[mid])
            last = mid;
        else
            first = mid + 1;
        
        if (abs(arr[mid] - element) < diff ) {
            result = mid;
            diff = abs(arr[mid] - element);
        }
        
        if (abs(arr[mid] - element) == diff && mid < result ){
            result = mid;
            diff = abs(arr[mid] - element);
        }
    }
    
    return (first == count)? count - 1 : result;
}