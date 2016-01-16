#include <iostream>
#include <vector>

void grow(int* buffer, int* bufferSize)
{
    int newBufferSize = *bufferSize * 2;
    int* newBuffer = new int[newBufferSize];
    
    for (int i = 0; i < *bufferSize; i++) {
        newBuffer[i] = buffer[i];
    }
    
    buffer = newBuffer;
    *bufferSize = newBufferSize;
}

bool isEmpty (int top)
{
    return top == -1;
}

void push(int* buffer, int* bufferSize, int* top, int c)
{
    if (*top + 1 > *bufferSize) {
        grow(buffer, bufferSize);
    }
    buffer[++(*top)] = c;
}

int pop(int* buffer, int* top)
{
    if (!isEmpty(*top)) {
        return buffer[(*top)--];
    } else {
        return -1;
    }
    
}

int main(int argc, const char * argv[]) {
    
    int top = -1;
    int bufferSize = 1;
    int* buffer = new int[bufferSize];
    
    std::vector<char> brackets;
    char c;
    while ((c = getchar()) != '\n'){
        brackets.push_back(c);
    }
    
    char* stackLeftBrackets = new char[bufferSize];
    char* stackRightBrackets = new char[bufferSize];
    
//    for (int i = 0; i < brackets.size(); i++) {
//        std::cout << brackets[i] << " ";
//    }
    
    return 0;
}
