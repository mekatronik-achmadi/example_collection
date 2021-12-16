#include "tesclock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTabWidget mytab;
    mytab.addTab(new tesClock,"Clock");
    mytab.show();
    return a.exec();
}
