#include <iostream>
#include <vector>

typedef struct
{
    int x;
    int y;
} Point;

void shiftDown (std::vector<Point>* heap, int heapSize, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    
    if (left < heapSize && (*heap)[left].x > (*heap)[i].x) {
        largest = left;
    }
    if (right < heapSize && (*heap)[right].x > (*heap)[largest].x) {
        largest = right;
    }
    
    if (left < heapSize && (*heap)[left].x == (*heap)[largest].x && (*heap)[left].y > (*heap)[largest].y) {
        largest = left;
    }
    
    if (right < heapSize && (*heap)[right].x == (*heap)[largest].x && (*heap)[right].y > (*heap)[largest].y) {
        largest = right;
    }
    
    if (largest != i) {
        std::swap( (*heap)[i], (*heap)[largest]);
        shiftDown(heap, heapSize, largest);
    }
}

void buildHeap(std::vector<Point>* array, int i)
{
    for (int i = (int)(*array).size() / 2 - 1; i >= 0; --i) {
        shiftDown(array, (int)(*array).size(), i);
    }
}

void heapsort (std::vector<Point>* heap)
{
    int heapSize = (int)(*heap).size();
    buildHeap(heap, heapSize);
    
    while (heapSize > 1) {
        std::swap((*heap)[0], (*heap)[heapSize - 1]);
        --heapSize;
        shiftDown(heap, heapSize, 0);
    }
}

int main(int argc, const char * argv[]) {
    
    int n;
    std::cin >> n;
    
    std::vector<Point> pointsPolyline;
    
    for (int i = 0; i < n; i++) {
        Point curr;
        std::cin >> curr.x >> curr.y;
        pointsPolyline.push_back(curr);
    }
    
    heapsort(&pointsPolyline);
    
    for (int i; i < pointsPolyline.size(); i++) {
        std::cout << pointsPolyline[i].x << " " << pointsPolyline[i].y << std::endl;
    }
    
    return 0;
}
