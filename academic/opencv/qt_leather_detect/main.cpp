#include "leather.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    leather w;
    w.show();

    return a.exec();
}
