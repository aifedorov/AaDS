#include <iostream>
#include <queue>
#include <vector>

typedef struct {
    long long indexArr;
    int val;
    
} ElementHeap;

struct comparator {
    bool operator()(int i, int j) {
        return i > j;
    }
};

struct comparatorElementHeap {
    bool operator()(ElementHeap a, ElementHeap b) {
        return a.val > b.val;
    }
};

int main(int argc, const char * argv[]) {
    
    long long n;
    std::cin >> n;
    
    std::vector<int> a;
    for (long long i = 0; i < n; i++) {
        int tmp;
        std::cin >> tmp;
        a.push_back(tmp);
    }
    
    int k;
    std::cin >> k;
    
    std::vector<std::priority_queue<int, std::vector<int>, comparator>> arrays;
    long long sizeArrays = a.size() / k;
    if (a.size() % k) {
        ++sizeArrays;
    }
    
    for (long long i = 0; i < sizeArrays; i++) {
        
        std::priority_queue<int, std::vector<int>, comparator> curr;
        long long sizeCurr = k + i * k;
        if (i == sizeArrays - 1) {
            sizeCurr = a.size();
        }
        
        for (long long j = i * k; j < sizeCurr; j++) {
            curr.push(a[j]);
        }
        arrays.push_back(curr);
    }
    
    std::priority_queue<ElementHeap, std::vector<ElementHeap>, comparatorElementHeap> minHeap;
    
    for (int i = 0; i < arrays.size(); i++) {
        ElementHeap curr;
        curr.val = arrays[i].top();
        curr.indexArr = i;
        minHeap.push(curr);
        arrays[i].pop();
    }
    
    while (!minHeap.empty()) {
        std::cout << minHeap.top().val << " ";
        long long index = minHeap.top().indexArr;
        minHeap.pop();
        if (!arrays[index].empty()) {
            ElementHeap curr;
            curr.val = arrays[index].top();
            arrays[index].pop();
            curr.indexArr = index;
            minHeap.push(curr);
        }
    }
    return 0;
}
