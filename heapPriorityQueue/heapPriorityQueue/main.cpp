#include <iostream>
#include <queue>

int weightSum (std::vector<int> currentWeight)
{
    int sum = 0;
    for (int i = 0; i < currentWeight.size(); i++) {
        sum += currentWeight[i];
    }
    return sum;
}

void actionCountPriority(std::priority_queue<int>& heap, int& capacity) {
    int actCount = 0;
    std::vector<int> currentWeight;
    
    while (!heap.empty())  {
        
        currentWeight.push_back(heap.top());
        heap.pop();
        
        while(!heap.empty()) {
            
            if (weightSum(currentWeight) == capacity) {
                break;
            }
            
            if (weightSum(currentWeight) + heap.top() <= capacity) {
                currentWeight.push_back(heap.top());
                heap.pop();
                
            } else {
                break;
            }
        }
        
        for (auto& elem : currentWeight) {
            if (elem <= 1) {
                
            } else {
                int result = elem/2;
                heap.push(result);
            }
        }
        
        currentWeight.clear();
        ++actCount;
    }
    std::cout << actCount;
}

int main(int argc, const char * argv[]) {

    int n;
    std::cin >> n;
    
    std::priority_queue<int> arrayFruits;
    for (int i = 0; i < n; i++) {
        int curr;
        std::cin >> curr;
        arrayFruits.push(curr);
    }
    
    int capacity;
    std::cin >> capacity;

    actionCountPriority(arrayFruits,capacity);
    
    return 0;
}
