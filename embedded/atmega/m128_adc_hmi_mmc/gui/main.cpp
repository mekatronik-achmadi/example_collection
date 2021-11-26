#include "ta_hmi.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TA_HMI w;
    w.show();

    return a.exec();
}
