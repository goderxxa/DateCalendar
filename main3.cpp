#include <iostream>
#include <string>

using namespace std;

class Letter {
public:
    Letter() { cout << "I'm constructor Letter" << endl; }
    virtual void printInfo() = 0;

};

class A : public Letter {
public:
    A() {
        cout << "I'm constructor A" << endl;
    }
    A(string a) : a(a) {}

    void printInfo() override {
        cout << a << endl;
    }


    string a = "A classs";
};

class B : public A {
public:

    B() {
        cout << "I'm constructor B" << endl;
    }
    B(class A& a, string b) : a(a.a), b(b)  {
        cout << "I'm constructor B" << endl;
    }

    void printInfo() override {
        cout << a << " " << b << endl;
    }

private:
    string b = "B class";
    string a = "A";

};

int main() {
    A* a = new A;
    a->printInfo();

    B* b = new B( *a,"xaa");
    b->printInfo();

    delete a;
    delete b;

    return 0;
}
