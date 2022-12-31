#include "qtserterm.h"

QtSerTerm::QtSerTerm(QWidget *parent):
    QMainWindow(parent)
{

    QMenu *fileMenu = menuBar()->addMenu("&File");
    QMenu *editMenu = menuBar()->addMenu("&Edit");
    QMenu *helpMenu = menuBar()->addMenu("&Help");

    QAction *appQuit = new QAction("&Quit",this);
    QAction *selPort = new QAction("Serial &Port",this);
    QAction *setBaud = new QAction("&Baud Rate",this);
    QAction *txtClear = new QAction("C&lear",this);
    QAction *appAbout = new QAction("&About",this);

    fileMenu->addAction(appQuit);
    editMenu->addAction(selPort);
    editMenu->addAction(setBaud);
    editMenu->addSeparator();
    editMenu->addAction(txtClear);
    helpMenu->addAction(appAbout);

    btnOpen = new QPushButton("Open",this);
    btnOpen->setGeometry(5,25,75,25);

    btnSend = new QPushButton("Send",this);
    btnSend->setGeometry(85,25,75,25);

    txtSend = new QLineEdit(this);
    txtSend->setGeometry(165,25,215,25);

    txtRx = new QTextEdit(this);
    txtRx->setGeometry(5,55,375,425);

    QString dbgSerial = "Port: 8-N-1-'\\r'-";
    dbgSerial += QString::fromStdString(comport.GetPort());
    dbgSerial += " [CLOSED]";
    statusBar()->showMessage(dbgSerial);

    connect(appQuit,&QAction::triggered,qApp,&QApplication::quit);
    connect(appAbout,&QAction::triggered,this,&QtSerTerm::onAbout);
    connect(setBaud,&QAction::triggered,this,&QtSerTerm::onSetBaud);
    connect(txtClear,&QAction::triggered,this,&QtSerTerm::onRxClear);
    connect(btnOpen,&QPushButton::clicked,this,&QtSerTerm::onBtnOpen);
}

void QtSerTerm::onAbout(){
    QString strAbout = "Serial Communication! \n ";
    strAbout += "Author: Yan Naing Aye \n ";
    strAbout += "Web: https://github.com/yan9a/serial";

    QMessageBox::information(this,"About Serial Comm",strAbout);
}

void QtSerTerm::onOpen(){
    if(comport.Open()){
        QString strRx = "Error on port ";
        strRx += QString::fromStdString(comport.GetPort());
        strRx += "\n";
        txtRx->append(strRx);

        QString dbgSerial = "Port: 8-N-1-'\\r'-";
        dbgSerial += QString::fromStdString(comport.GetPort());
        dbgSerial += " [CLOSED]";
        statusBar()->showMessage(dbgSerial);

        btnOpen->setText("Open");
    }
    else{
        QString strRx = "Success on port ";
        strRx += QString::fromStdString(comport.GetPort());
        strRx += "\n";
        txtRx->append(strRx);

        QString dbgSerial = "Port: 8-N-1-'\\r'-";
        dbgSerial += QString::fromStdString(comport.GetPort());
        dbgSerial += " [OPENED]";
        statusBar()->showMessage(dbgSerial);

        btnOpen->setText("Close");
    }
}

void QtSerTerm::onClose(){
    comport.Close();

    QString strRx = "Closed port ";
    strRx += QString::fromStdString(comport.GetPort());
    strRx += "\n";
    txtRx->append(strRx);

    QString dbgSerial = "Port: 8-N-1-'\\r'-";
    dbgSerial += QString::fromStdString(comport.GetPort());
    dbgSerial += " [CLOSED]";
    statusBar()->showMessage(dbgSerial);

    btnOpen->setText("Open");
}

void QtSerTerm::onBtnOpen(){
    if(btnOpen->text()=="Open"){
        onOpen();
    }
    else if(btnOpen->text()=="Close"){
        onClose();
    }
}

void QtSerTerm::onSetBaud(){
    if(comport.IsOpened()){
        txtRx->append("Close port first.\n");
    }
    else{
    }
}

void QtSerTerm::onRxClear(){
    txtRx->clear();
}
