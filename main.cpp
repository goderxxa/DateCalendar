#include <iostream>

using namespace std;

class Essence
{
public:

    //default constructor
    Essence()   {   }

    //more option constructor
    Essence(int n, string name) : n(n), name(name)  {   }

    //deep copy constructor
    Essence(const Essence& CopySource) : n(CopySource.n), name(CopySource.name)  {   }

    ~Essence() {   }

    void showEssence()
    {
        cout << n << " " << name ;
        cout << endl;
    }

private:
    int n=0;
    string name="default essence";
};


int main() {

    Essence e1;
    Essence e2(12,"xzxz");
    e1.showEssence();
    e2.showEssence();
    e1=e2;
    cout << endl;
    e1.showEssence();
    e2.showEssence();


    return 0;
}
