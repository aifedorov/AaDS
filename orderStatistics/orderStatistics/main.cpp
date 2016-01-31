#include <iostream>

int compare(const void * x1, const void * x2)
{
    return ( *(int*)x1 - *(int*)x2 );
}

int partion(int* array, int n, const int pivot)
{
    if ( n <= 1 ) {
        return 0;
    }
    
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

int kStatDC (int* a, int n, int k)
{
    const int pivot = n / 2;
    int p = partion(a, n, pivot);
    if (p == k) {
        return a[k];
    } else if (p > k) {
        kStatDC(a, n - p, k);
    } else {
        kStatDC(a + (p + 1), n - (p + 1), k - (p + 1));
    }
    
    return a[k];
}

int kStatLin (int* a, int n, int k)
{
    int sizeArrays;
    if (n % 5) {
        sizeArrays = n / 5 + 1;
        
    } else {
        sizeArrays = n / 5;
        
    }
    int** b = new int*[sizeArrays];
//    int* mediauns = new int[sizeArrays];
    
    for (int i = 0; i < sizeArrays; i++) {
        
        int sizeCurr = 5 + i * 5;
        if (i == sizeArrays - 1) {
            sizeCurr = n;
        }
        
        b[i] = new int[sizeCurr];
        int tmp = 0;
        for (int j = i * 5; j < sizeCurr; j++) {
            b[i][tmp++] = a[j];

        }
        std::qsort(b[i], 5, sizeof(int), compare);
//        mediauns[i] = b[i][5 / 2];
    }

//    for (int i = 0; i < sizeArrays; i++) {
//        for (int j = 0; j < 5; j++) {
//            std::cout << b[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//    
//    for (int i = 0; i < sizeArrays; i++) {
//        std::cout << mediauns[i] << " ";
//    }
//    std::cout << std::endl;
    
    return 0;
}


long long kth(int* arr, int l,int r,int k)
{
    long long x = arr[(l+r) / 2];
    int i=l,j=r;
    while(i<=j)
    {
        while(arr[i] < x) i++;
        while(arr[j] > x) j--;
        
        if(i<=j)
        {
            std::swap(arr[i],arr[j]);
            i++;
            j--;
        }
    }
    if(l <= k && k <= j)
        return kth(arr,l,j,k);
    
    if( i <= k && k <= r)
        return kth(arr,i,r,k);
    
    return arr[k];
}

int main(int argc, const char * argv[]) {
    
    int n, k;
    std::cin >> n >> k;
    
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        int tmp;
        std::cin >> tmp;
        a[i] = tmp;
    }
//    std::cout << kth(a, 0, n - 1, k) << std::endl;
    std::cout << kStatDC(a, n, k) << std::endl;
    
    return 0;
}
