#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include "qtserterm.h"

QtSerTerm::QtSerTerm(QWidget *parent):
    QMainWindow(parent)
{
    QAction *fileQuit = new QAction("&Quit",this);

    QMenu *file = menuBar()->addMenu("&File");
    file->addAction(fileQuit);

    connect(fileQuit,&QAction::triggered,qApp,&QApplication::quit);
}
