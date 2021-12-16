#include "sate.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sate w;
    w.show();

    return a.exec();
}
