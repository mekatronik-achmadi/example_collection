/********************************************************************************
** Form generated from reading UI file 'imageview.ui'
**
** Created: Tue Sep 17 00:23:03 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVIEW_H
#define UI_IMAGEVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageView
{
public:
    QWidget *centralWidget;
    QLabel *lblDisplay;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageView)
    {
        if (ImageView->objectName().isEmpty())
            ImageView->setObjectName(QString::fromUtf8("ImageView"));
        ImageView->resize(751, 376);
        centralWidget = new QWidget(ImageView);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lblDisplay = new QLabel(centralWidget);
        lblDisplay->setObjectName(QString::fromUtf8("lblDisplay"));
        lblDisplay->setGeometry(QRect(30, 20, 701, 271));
        lblDisplay->setFrameShape(QFrame::Box);
        ImageView->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageView);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 751, 21));
        ImageView->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageView);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ImageView->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageView);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ImageView->setStatusBar(statusBar);

        retranslateUi(ImageView);

        QMetaObject::connectSlotsByName(ImageView);
    } // setupUi

    void retranslateUi(QMainWindow *ImageView)
    {
        ImageView->setWindowTitle(QApplication::translate("ImageView", "ImageView", 0, QApplication::UnicodeUTF8));
        lblDisplay->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ImageView: public Ui_ImageView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEW_H
