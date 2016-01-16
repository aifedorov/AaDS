#include <iostream>
#include <vector>

typedef struct {
    bool local;
    int val;
} Point;

void merge(const Point* a, int aLen, const Point* b, int bLen, Point* c)
{
    int i = 0, j = 0;
    while (i < aLen && j < bLen) {
        
        if ( a[i].val <= b[j].val) {
            c[i + j].val = a[i].val;
            c[i + j].local = a[i].local;
            ++i;
            
        } else {
            c[i + j].val = b[j].val;
            c[i + j].local = b[j].local;
            ++j;
        }
    }
    
    if (i == aLen) {
        for (; j < bLen; ++j) {
            c[i + j].val = b[j].val;
            c[i + j].local = b[j].local;
        }
    } else {
        for (; i < aLen; ++i) {
            c[i + j].val = a[i].val;
            c[i + j].local = a[i].local;
        }
    }
}

void mergeSort(Point* a, int aLen)
{
    if (aLen <= 1) {
        return;
    }
    
    int firstLen = aLen / 2;
    int secondLen = aLen - firstLen;
    
    mergeSort(a, firstLen);
    mergeSort(a + firstLen, secondLen);
    
    Point* c = new Point[aLen];
    merge(a, firstLen, a + firstLen, secondLen, c);
    for (int i = 0; i < aLen; i++) {
        a[i].val = c[i].val;
        a[i].local = c[i].local;
    }
    delete [] c;
}

long sumLineOneColor(Point* a, int aLen)
{
    long result = 0;
    int cntLt = 0;
    
    for (int i = 0; i < aLen; i++) {
        if (cntLt == 1 && i) {
            result += a[i].val - a[i - 1].val;
        }
        
        if (a[i].local) {
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
    
    int pCnt = 2 * n;
    Point* array = new Point[pCnt];
    
    for (int i = 0; i < n; i++) {
        std::cin >> array[2*i].val >> array[2*i + 1].val;
        array[2*i].local = true;
        array[2*i + 1].local = false;
    }
    
    mergeSort(array, pCnt);
    
    std::cout << sumLineOneColor(array, pCnt) << std::endl;
    return 0;
}
