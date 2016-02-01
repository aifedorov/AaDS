#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string dateDeleted = "Deleted";

typedef struct
{
    char type;
    string date;
    
} Command;

int getHash(string str, int size, int index)
{
    int hash = 0;
    if (index == 0) {
        int a = size - 1;
        for (int i = 0 ; i < str.length(); i++) {
            hash = ( hash * a + str[i] ) % size;
        }
        return hash;

    } else {
        hash = ( getHash(str, size, index - 1) + index ) % size;
        return hash;
    }
}

void grow (string** hashTable, int* size)
{
    int newSize = 2 * (*size);
    string* newHashTable = new string[newSize];
    
    for (int i = 0; i < *size; i++) {
        int key = getHash((*hashTable)[i], newSize, 0);
        newHashTable[key] = (*hashTable)[i];
    }
    
    swap(*hashTable, newHashTable);
    *size = newSize;
    
    delete [] newHashTable;
}

void addDate(string** hashTable, int* size, int* count, string date)
{
    float alpha = (float)*count / (float)*size;
    if ( alpha >= 3. / 4.) {
        grow(hashTable, size);
    }
    
    int i = 0;
    int key = getHash(date, *size, i);
    
    while ( !(*hashTable)[key].empty() && (*hashTable)[key].compare( dateDeleted ) != 0 ) {
        ++i;
        key = getHash(date, *size, i);
    }
    
    (*hashTable)[key] = date;
    ++(*count);
}

int searchDate(string* hashTable, int size, string date)
{
    int i = 0;
    int key = getHash(date, size, i);
    
    while ( !hashTable[key].empty() ) {
        
        if (hashTable[ key ].compare( date ) == 0) {
            return key;
            
        } else {
            ++i;
            key = getHash(date, size, i);
        }
    }
    
    return -1;
}

bool deleteDate(string* hashTable, int size, string date)
{
    int key = searchDate(hashTable, size, date);
    if ( key != -1) {
        hashTable[key] = dateDeleted;
        return true;
        
    } else {
        return false;
        
    }
}

int main(int argc, const char * argv[]) {

    int size = 32;
    int count = 0;
    
    std::vector<Command> commands;
    
    while (!cin.eof())
    {
        Command cmd;
        cin >> cmd.type;
        cin >> cmd.date;
        commands.push_back(cmd);
    }
    
    string* hashTable = new string[size];
    std::vector<string> result;
    
    for (int i = 0; i < size; i++) {
        switch (commands[i].type) {
            case '+':
            {
                if ( searchDate(hashTable, size, commands[i].date) == -1 )
                {
                    addDate(&hashTable, &size, &count, commands[i].date);
                    result.push_back("OK");
                } else {
                    result.push_back("FAIL");
                }
                break;
            }
            case '-':
            {
                if ( deleteDate(hashTable, size, commands[i].date) )
                {
                    result.push_back("OK");
                } else {
                    result.push_back("FAIL");
                }
                break;
            }
            case '?':
            {
                if ( searchDate(hashTable, size, commands[i].date) != -1 )
                {
                    result.push_back("OK");
                } else {
                    result.push_back("FAIL");
                }
                break;
            }

            default:
                break;
        }
    }
    
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }
    
    return 0;
}
