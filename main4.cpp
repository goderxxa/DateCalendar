#include <iostream>
#include <string>

using namespace std;

class Fish {
public:
    virtual ~Fish() {
        std::cout << "Fish destructor" << std::endl;
    }

    virtual Fish* Clone() const = 0;
    virtual void show() =0;
};

class Tuna : public Fish{
public:
    void show() { cout << name << endl;}


    Tuna* Clone() const    {
        return new Tuna(*this);
    }

    ~Tuna() override { cout << "delete " << name << endl; }
private:
    string name = "i'm TUNA";

};

class Carp : public Fish {
public:
    void show() { cout << "Carp age: " << age << endl;}

    Carp* Clone() const {
        return new Carp(*this);
    }
    ~Carp() override { cout << "delete " << age << endl; }
private:
    int age = 2;
};


int main ()
{
    int* a = new int(20);
    cout << sizeof (a) << endl;
    cout << *a << endl;
    delete a;

    Fish *pFish[3];
    pFish[1] = new Tuna();
    pFish[0] = new Carp();
    pFish[1]->show();
    pFish[0]->show();
    delete pFish[1];
    delete pFish[0];

    const int ARRAY_SIZE=2;
    Fish* pFishes[ARRAY_SIZE];
    pFishes[0]=new Carp();
    pFishes[1]=new Tuna();

    Fish* myNewFishes[ARRAY_SIZE];
    for(int i=0;i<ARRAY_SIZE; ++i)
    {
        myNewFishes[i] = pFishes[i]->Clone();
    }

    for(int i=0;i<ARRAY_SIZE; ++i)
    {
        myNewFishes[i]->show();
    }
    for(int i=0;i<ARRAY_SIZE; ++i)
    {
        delete pFishes[i];
        delete myNewFishes[i];
    }



}