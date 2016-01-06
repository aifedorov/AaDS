//
//  main.cpp
//  simpleNumbers
//
//  Created by Александр on 06.01.16.
//  Copyright © 2016 Alexandr Fedorov. All rights reserved.
//

#include <iostream>

bool isPrime (int n);

int main(int argc, const char * argv[]) {
    
    int n;
    std::cin >> n;
    
    if (n <= 1) {
        return 1;
    }
    
    if (isPrime(n)) {
        std::cout << n << std::endl;
    }
    
    int i = 2, p = n;
    while (i < n) {
        if (isPrime(i)) {
            if (p % i == 0) {
                p /= i;
                std::cout << i << " ";
                i = 1;
            }
        }
        ++i;
    }
    
    return 0;
}

bool isPrime (int n)
{
    if (n == 1) {
        return false;
    }
    
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    
    return true;
}