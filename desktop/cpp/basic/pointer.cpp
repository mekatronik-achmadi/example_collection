#include <iostream>

using namespace std;

int main()
{
    int *p;
    int x;
	
	int *v;
	int i;
    int y[4]={25,50,75,100};

    char *ch;
    char z[]="hai";

    p=new int; //allocate in memory (same as malloc() in C)
	x=25;
	
	i=3;
	v=new int[i]; //pointer array element amount can declare as variable
    ch=new char[4];

    p=&x; //reference

    cout<<"x = "<<x<<endl;
    cout<<"&x = "<<&x<<endl;
    cout<<"p = "<<p<<endl;
    cout<<"*p = "<<*p<<endl;

    cout<<endl;

    *p=75; //dereference
    x=*p;

    cout<<"x = "<<x<<endl;
    cout<<"&x = "<<&x<<endl;
    cout<<"p = "<<p<<endl;
    cout<<"*p = "<<*p<<endl;

    cout<<endl;

    p=&y[1];
    cout<<"*p in y = "<<*p<<endl;

    p=p-1;
    cout<<"*(p-1) in y = "<<*p<<endl;

    cout<<endl;

    ch=&z[1];
    cout<<"*ch in z = "<<*ch<<endl;

    ch=ch+1;
    cout<<"*(ch-1) in z = "<<*ch<<endl;

	return 0; //back to operating system (before deallocate memory)
	
    delete p; //deallocate in memory (same as free() in C) if system can't deallocate pointer variable automically
    delete[] v;
	delete[] ch;
}

