#include "serialrxtx.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serialrxtx w;
    w.show();

    return a.exec();
}
