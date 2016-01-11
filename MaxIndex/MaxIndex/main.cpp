//
//  main.cpp
//  MaxIndex
//
//  Created by Александр on 07.01.16.
//  Copyright © 2016 Alexandr Fedorov. All rights reserved.
//

#include <iostream>

int const maxSizeArray = 100000;
int maxIndexElement( const int* arr, int count, int start, int end);

int main(int argc, const char * argv[]) {
    
    int n;
    std::cin >> n;
    
    if ( n < 1 || n > maxSizeArray)
        return 1;
    
    int* A = new int[n];
    int* B = new int[n];
    
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    
    for (int i = 0; i < n; i++) {
        std::cin >> B[i];
    }
    
    int i1 = 0, j1 = 0;
    int maxSum = A[0] + B[0];
    
    int maxIndexA = maxIndexElement(A, n, 0, n);
    int maxIndexB = maxIndexElement(B, n, 0, n);
    
    if (maxIndexA <= maxIndexB ) {
        std::cout << maxIndexA << " " << maxIndexB << std::endl;
        return 0;
        
    } else {
        
        while (maxIndexA > maxIndexB) {
            
            int maxABeforeMaxB = maxIndexElement(A, n, 0, maxIndexB);
            int maxBAfterMaxA = maxIndexElement(B, n, maxIndexA, n);
            
            if (A[maxABeforeMaxB] + B[maxIndexB] > maxSum) {
                maxSum = A[maxABeforeMaxB] + B[maxIndexB];
                i1 = maxABeforeMaxB;
                j1 = maxIndexB;
            }
            
            if (A[maxIndexA] + B[maxBAfterMaxA] > maxSum) {
                maxSum = A[maxIndexA] + B[maxBAfterMaxA];
                i1 = maxIndexA;
                j1 = maxBAfterMaxA;
            }
            
            maxIndexA = maxIndexElement(A, n, 0, maxIndexA - 1);
            maxIndexB = maxIndexElement(B, n, maxIndexB + 1, n);
            
        }
        
        if (A[maxIndexA] + B[maxIndexB] > maxSum) {
            i1 = maxIndexA;
            j1 = maxIndexB;
            std::cout << i1 << " " << j1 << std::endl;
            return 0;
        }
        
        std::cout << i1 << " " << j1 << std::endl;
    }

    return 0;
}

int maxIndexElement( const int* arr, int count, int start, int end)
{
    
    int currentMax = arr[start];
    int indexMaxElement = start;
    for (int i = start; i < end; ++i) {
        if (arr[i] > currentMax) {
            currentMax = arr[i];
            indexMaxElement = i;
        }
    }
    return indexMaxElement;
}