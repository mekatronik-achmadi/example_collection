#ifndef QTSERTERM_H
#define QTSERTERM_H

#include <QWidget>
#include <QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QLineEdit>
#include <QTextEdit>
#include <QStatusBar>
#include <QPushButton>
#include <QMessageBox>

#include "../ceSerial/ceSerial.h"

class QtSerTerm: public QMainWindow {

    public:
        QtSerTerm (QWidget *parent = nullptr);
        void onOpen();
        void onClose();

    private slots:
        void onAbout();
        void onBtnOpen();
        void onSetBaud();
        void onRxClear();

    private:
        QPushButton *btnOpen;
        QPushButton *btnSend;
        QLineEdit *txtSend;
        QTextEdit *txtRx;
        ceSerial comport;
};

#endif
