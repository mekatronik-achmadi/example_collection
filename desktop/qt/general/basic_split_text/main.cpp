#include "splittext.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    splitText w;
    w.show();

    return a.exec();
}
