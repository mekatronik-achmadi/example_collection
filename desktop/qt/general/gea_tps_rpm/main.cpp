#include "gea.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gea w;
    w.show();
    
    return a.exec();
}
