#include "cpuviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CpuViewer w;
    w.show();

    return a.exec();
}
