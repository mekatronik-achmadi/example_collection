/**
 * @file qtserterm.h
 * @brief Qt5 Serial example (main code)
 *
 * @details Original works and credits: https://github.com/yan9a/serial
 *
 * @addtogroup QT5
 * @{
 */

#include "qtserterm.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    QtSerTerm serterm;

    serterm.resize(390,500);
    serterm.setWindowTitle("Serial Port");
    serterm.show();

    return app.exec();
    return 0;
}

/** @} */
