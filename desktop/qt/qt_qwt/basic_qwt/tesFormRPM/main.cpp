#include "formrpm.h"
#include "rpm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    formrpm myform;
    rpm myrpm;

    myform.show();
    myrpm.show();

    return a.exec();
}
