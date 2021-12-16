#include "qtfile.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qtfile w;
    w.show();

    return a.exec();
}
