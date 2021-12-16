#include "qhsv.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qhsv w;
    w.show();

    return a.exec();
}
