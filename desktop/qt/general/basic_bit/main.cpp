#include <iostream>
#include <QString>

unsigned char v1=0x02,v2=0x03;
QString str1,str2;

unsigned int v3;
QString str3;

void calculate(void){
v3 = (v2 << 8) | v1 ;
}

void show_result(void){
    str1=QString::number(v1,8);
    std::cout<<"str1= 0x"<<str1.toStdString()<<std::endl;
    str2=QString::number(v2,8);
    std::cout<<"str2= 0x"<<str2.toStdString()<<std::endl;
    str3=QString::number(v3,16);
    std::cout<<"str3= 0x"<<str3.toStdString()<<std::endl;
}

int main(void)
{
    calculate();
    show_result();
}
