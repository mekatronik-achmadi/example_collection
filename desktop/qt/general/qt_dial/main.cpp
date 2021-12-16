#include "dialtest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialtest w;
    w.show();
    
    return a.exec();
}
