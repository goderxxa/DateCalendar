#include <iostream>
#include <string.h>

using namespace std;

class MyString
{
public:
    MyString(const char* newString) {
        buffer = nullptr;
        if(newString != nullptr)
        {
            buffer = new char[strlen(newString)+1];
            strcpy(buffer,newString);
        }
    }
    MyString(const MyString& copySource) {
        buffer = nullptr;
        if(copySource.buffer!= nullptr)
        {
            this->buffer = new char(strlen(copySource.buffer)+1);
            strcpy(this->buffer,copySource.buffer);
        }
    }

    ~MyString() {
        delete[] buffer;
    }

    char* buffer;

};


int main() {

    MyString* b = new MyString("xxa");
    MyString* a = new MyString("XYuq");
    cout << a->buffer << endl;

    a = b;
    cout << a->buffer << endl;

    return 0;
}
