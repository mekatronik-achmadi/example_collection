#include "qtserterm.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    QtSerTerm serterm;

    serterm.resize(390,500);
    serterm.show();

    return app.exec();
    return 0;
}
