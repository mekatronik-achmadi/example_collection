#include <iostream>

using namespace std;

class kelas
{

 //private automically
 int A; //properties of object (can trigger an event)
 int B;

 public:
 void setA(int AA); //method of object (can trigger an event)
 int getA();
 void showA();

};

//========= Referencing ===========
void kelas::setA(int AA)
{
    A=AA;
}

int kelas::getA()
{
    cin>>A;
	
    this->B=A; //pointer 'this' is meaning 'class::'

    return A;
}

void kelas::showA()
{
    cout<<"nilai A = "<<A<<endl;
}

//===================================

int main()
{
    kelas *tes; //defining object (as pointer)
    kelas test; //defining object

    tes= new kelas; //allocate pointer class object in memory

    tes->setA(100);
    tes->showA();

    test.setA(25);
    test.showA();

    return 0; 
    delete tes; //deallocate pointer class object in memory
}
