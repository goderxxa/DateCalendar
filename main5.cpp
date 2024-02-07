#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Digit {
private:
    int digit=0;
    string name;

public:
    Digit(int a ) : digit(a) {
        cout << "Digit is created: " <<endl;
    }
    ~Digit() {
        cout << "Digit is deleted: " << digit <<endl;
    }
    Digit& operator ++ ()
    {
        ++digit;
        return *this;
    }
    Digit operator ++ (int)
    {
        Digit copyDigit(*this);
        digit++;
        return copyDigit;
    }
    Digit& operator=(int value) {
        digit = value;
        return *this;
    }

//    operator int()
//    {
//        return digit;
//    }
    operator const char* ()
    {
        name = "digit " + to_string(digit);
        return name.c_str() ;
    }

};


int main ()
{
    unique_ptr<Digit> digS(new Digit(4));

    cout << digS->operator const char *() << endl;
    *digS = 10;
    cout << digS->operator const char *() << endl;

    Digit* a = new Digit(5);

    *a=6;

    cout << *a <<endl;

    delete a;


}