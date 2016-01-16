#include <iostream>
#include <vector>

void merge(const int* a, int aLen, const int* b, int bLen, int* c)
{
    int i = 0, j = 0;
    while (i < aLen && j < bLen) {
        
        if ( a[i] <= b[j]) {
            c[i + j] = a[i];
            c[i + j] = a[i];
            ++i;
            
        } else {
            c[i + j] = b[j];
            c[i + j] = b[j];
            ++j;
        }
    }
    
    if (i == aLen) {
        for (; j < bLen; ++j) {
            c[i + j] = b[j];
            c[i + j] = b[j];
        }
    } else {
        for (; i < aLen; ++i) {
            c[i + j] = a[i];
            c[i + j] = a[i];
        }
    }
}

void mergeSort(int* a, int aLen)
{
    if (aLen <= 1) {
        return;
    }
    
    int firstLen = aLen / 2;
    int secondLen = aLen - firstLen;
    
    mergeSort(a, firstLen);
    mergeSort(a + firstLen, secondLen);
    
    int* c = new int[aLen];
    merge(a, firstLen, a + firstLen, secondLen, c);
    for (int i = 0; i < aLen; i++) {
        a[i] = c[i];
        a[i] = c[i];
    }
    delete [] c;
}

long sumLineOneColor(int* a, int aLen)
{
    long result = 0;
    int cntLt = 0;
    
    for (int i = 0; i < aLen; i++) {
        if (cntLt == 1 && i) {
            result += a[i] - a[i - 1];
        }
        
        if (a[i]) {
            ++cntLt;
            
        } else {
            --cntLt;
        }
    }
    return result;
}


int main(int argc, const char * argv[]) {
    
    int n;
    std::cin >> n;
    
    int* array = new int[n];
    
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }
    
    int k;
    std::cin >> k;
    
    mergeSort(array, n);
    
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
}
