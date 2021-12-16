#include "qdata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qdata w;
    w.show();
    
    return a.exec();
}
