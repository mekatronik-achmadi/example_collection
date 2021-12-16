#include "testfont.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testfont w;
    w.show();
    
    return a.exec();
}
