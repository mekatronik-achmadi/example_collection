#include <iostream>

using namespace std;

namespace itung {

int fak(int a)
{
    int hasil,count;
    hasil=1;
    for(count=1;count<=a;count++)
    {
        hasil=hasil*count;
    }
    return hasil;
}


}

using namespace itung; //use if namespace declared in library


int main()
{
    int val,nil;
    std::cout<<"angka yang akan dihitung = ";
    std::cin>>nil;
    val=itung::fak(nil);
    cout<<"hasil faktorial = "<<val<<endl;
    return 0;
}

