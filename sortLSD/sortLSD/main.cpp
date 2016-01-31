#include <iostream>
#define CNT_OF_DIGS 20

int getDigit(int64_t num, int r)
{
    if (r >= 0) {
        int digs[CNT_OF_DIGS];
        
        for (int i = 0; i < CNT_OF_DIGS; i++) {
            if (num >= 10) {
                digs[i] = num % 10;
                num /= 10;
                
            } else {
                digs[i] =  num % 10;
                return r <= i ? digs[r] : 0;
            }
        }
        return digs[r];
        
    } else {
        return 0;
    }
}

void countingSort (int64_t** a, int n, int r)
{
    int k = 10;
    int* c = new int[k];
    
    for (int i = 0; i < k; i++) {
        c[i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        ++c[ getDigit((*a)[i], r) ];
    }
    
    int sum = 0;
    for (int i = 0; i < k; i++) {
        int temp = c[i];
        c[i] = sum;
        sum += temp;
    }
    
    int64_t* b = new int64_t[n];
    
    for (int i = 0; i < n; i++) {
        b[ c[ getDigit((*a)[i], r) ]++ ] = (*a)[i];
    }
    
    std::swap(*a, b);
    
    delete [] c;
    delete [] b;
}

void sortLSD (int64_t** a, int n)
{
    for (int r = 0; r < CNT_OF_DIGS; r++) {
        countingSort(a, n, r);
    }
}

int main(int argc, const char * argv[]) {

    int n;
    std::cin >> n;
    
    int64_t* a = new int64_t[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    sortLSD(&a, n);
    
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }

    return 0;
}
