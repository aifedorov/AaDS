#include <iostream>

int pushFront(int a, int* buffer, int bufferSize, int* head, int* tail);
int pushBack(int a, int* buffer, int bufferSize, int* head, int* tail);
int popFront(int *buffer, int bufferSize, int* head, int* tail);
int popBack(int *buffer, int bufferSize, int* head, int* tail);
bool const isEmpty(int head, int tail);

int main(int argc, const char * argv[]) {
    
    int n;
    std::cin >> n;
    
    int bufferSize = n + 1;
    int* buffer = new int[bufferSize];
    int head = 0;
    int tail = 0;
    int* pHead = &head;
    int* pTail = &tail;
    
    int* A = new int[n];
    int* B = new int[n];
    
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
        std::cin >> B[i];
    }
    
    for (int i = 0; i < n; i++) {
        
        if (A[i] == 1) {
            pushFront(B[i], buffer, bufferSize, pHead, pTail);
            
        } else if (A[i] == 2) {
            
            if (B[i] != popFront(buffer, bufferSize, pHead, pTail))
            {
                std::cout << "NO";
                std::cout << std::endl;
                return 0;
            }
        } else if (A[i] == 3)
        {
            pushBack(B[i], buffer, bufferSize, pHead, pTail);
            
        } else if (A[i] == 4)
        {
            if (B[i] != popBack(buffer, bufferSize, pHead, pTail))
            {
                std::cout << "NO";
                std::cout << std::endl;
                return 0;
            }
        }

    }
    
    std::cout << std::endl;
    std::cout << "YES" << std::endl;
    
    return 0;
}

bool const isEmpty(int head, int tail)
{
    return head == tail;
}

int pushFront(int a, int* buffer, int bufferSize, int* head, int* tail)
{
    if (isEmpty(*head, *tail)) {
        buffer[*head] = a;
        *tail = *tail + 1;
        return 1;
        
    } else {
        if (*head == 0 && *head + bufferSize - 1 != *tail) {
            *head = *head + bufferSize - 1;
            buffer[*head] = a;
            return 1;
        }
        
        if (*head - 1 != *tail) {
            *head = *head - 1;
            buffer[*head] = a;
            return 1;
        }
    }
    return 0;
}

int pushBack(int a, int* buffer, int bufferSize, int* head, int* tail)
{
    if ((*tail + 1) % bufferSize != *head) {
        buffer[*tail] = a;
        *tail = (*tail + 1) % bufferSize;
        return 1;
    }
    return 0;
}

int popFront(int *buffer, int bufferSize, int* head, int* tail)
{
    if (!isEmpty(*head, *tail)) {
        int result = buffer[*head];
        buffer[*head] = -1;
        *head = (*head + 1) % bufferSize;
        return result;
        
    } else {
        return -1;
    }
}

int popBack(int *buffer, int bufferSize, int* head, int* tail)
{
    if (!isEmpty(*head, *tail)) {
            if (*tail == 0) {
                int result = buffer[*tail + bufferSize - 1];
                buffer[*tail + bufferSize - 1] = -1;
                *tail = *tail + bufferSize - 1;
                
                return result;
                
            } else {
                int result = buffer[*tail - 1];
                buffer[*tail - 1] = -1;
                *tail = *tail - 1;
                
                return result;
            }
    } else
        return -1;
}