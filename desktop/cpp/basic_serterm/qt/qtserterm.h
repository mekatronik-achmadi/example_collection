/**
 * @file qtserterm.h
 * @brief Qt5 Serial example (header)
 *
 * @details Original works and credits: https://github.com/yan9a/serial
 *
 * @addtogroup QT5
 * @{
 */

#ifndef QTSERTERM_H
#define QTSERTERM_H

#include <QDebug>
#include <QWidget>
#include <QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QTimer>
#include <QAction>
#include <QLineEdit>
#include <QTextEdit>
#include <QInputDialog>
#include <QStatusBar>
#include <QPushButton>
#include <QMessageBox>

#include "../ceSerial/ceSerial.h"

class QtSerTerm: public QMainWindow {

    public:
        QtSerTerm (QWidget *parent = nullptr);
        void onOpen();
        void onClose();
        void onSetBaud();
        void onSelPort();
        void ProcessChar(char ch);

    private slots:
        void onAbout();
        void onBtnOpen();
        void onBtnSend();
        void onRxClear();
        void onTimer();

    private:
        QPushButton *btnOpen;
        QPushButton *btnSend;
        QLineEdit *txtSend;
        QLineEdit *txtSetBaud;
        QLineEdit *txtSelPort;
        QTextEdit *txtRx;
        ceSerial comport;
        QTimer *m_timer;
};

#endif

/** @} */
