#include "tesrpm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTabWidget mytab;
    mytab.addTab(new tesRPM,"RPM");
    mytab.show();
    return a.exec();
}
