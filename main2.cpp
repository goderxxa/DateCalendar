#include <iostream>
#include <string.h>

using namespace std;

class Letter {
public:
    virtual void printInfo() = 0;


private:

};


class A : public Letter
{
public:
    void printInfo() override {
        cout << a << endl;
    }

private:
    string a = "A class";

};

class B : public Letter
{
public:
    void printInfo() override {
        cout << b << endl;
    }

private:
    string b = "B class";

};


int main() {
    A* a = new A;
    a->printInfo();

    B* b = new B;
    b->printInfo();

    return 0;
}
