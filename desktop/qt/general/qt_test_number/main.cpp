#include "number.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    number w;
    w.show();
    
    return a.exec();
}
