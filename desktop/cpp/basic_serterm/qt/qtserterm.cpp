/**
 * @file qtserterm.h
 * @brief Qt5 Serial example (code)
 *
 * @details Original works and credits: https://github.com/yan9a/serial
 *
 * @addtogroup QT5
 * @{
 */

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
    txtSend->setText("help");

    txtRx = new QTextEdit(this);
    txtRx->setGeometry(5,55,375,425);
    txtRx->setReadOnly(true);

    QString dbgSerial = "Port: 8-N-1-'\\r'-";
    dbgSerial += QString::fromStdString(comport.GetPort());
    dbgSerial += " [CLOSED]";
    statusBar()->showMessage(dbgSerial);

    connect(appQuit,&QAction::triggered,qApp,&QApplication::quit);
    connect(appAbout,&QAction::triggered,this,&QtSerTerm::onAbout);
    connect(setBaud,&QAction::triggered,this,&QtSerTerm::onSetBaud);
    connect(selPort,&QAction::triggered,this,&QtSerTerm::onSelPort);
    connect(txtClear,&QAction::triggered,this,&QtSerTerm::onRxClear);
    connect(btnOpen,&QPushButton::clicked,this,&QtSerTerm::onBtnOpen);
    connect(btnSend,&QPushButton::clicked,this,&QtSerTerm::onBtnSend);

    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&QtSerTerm::onTimer);
    m_timer->start(1);
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
        long n = QInputDialog::getInt(this,"Set Baud Rate", "Enter the Baud Rate",comport.GetBaudRate(),0,1000000);
        if(n>=0) comport.SetBaudRate(n);

        QString strRx = "Set Baud Rate: ";
        strRx += QString::number(comport.GetBaudRate());
        strRx += "\n";
        txtRx->append(strRx);
    }
}

void QtSerTerm::onSelPort(){
    if(comport.IsOpened()){
        txtRx->append("Close port first.\n");
    }
    else{
        QString dev = QInputDialog::getText(this, "Set Port", "Enter Port",QLineEdit::Normal,QString::fromStdString(comport.GetPort()));
        std::string strDev = dev.toStdString();
        if (strDev.length() > 0) {
#ifdef ceWINDOWS
            comport.SetPortWin(strDev);
#else
            comport.SetPort(strDev);
#endif

        QString strRx = "Set Port: ";
        strRx += QString::fromStdString(comport.GetPort());
        strRx += "\n";
        txtRx->append(strRx);

        }
    }
}

void QtSerTerm::onRxClear(){
    txtRx->clear();
}

void QtSerTerm::onBtnSend(){
    QString strReq = txtSend->text();
    strReq += "\r";
    QByteArray buffer = strReq.toUtf8();

    if(comport.Write(buffer.data())){
        txtRx->append(strReq);
    }
    else{
        txtRx->append("Write error.\n");
    }
}

void QtSerTerm::onTimer(){
    char ch; bool r;
    do {ch = comport.ReadChar(r); if (r) ProcessChar(ch);} while(r);
}

void QtSerTerm::ProcessChar(char ch){
    if(ch=='\n'){
        // ignore linefeed
    }
    else{
        // check if character is printable or white-space
        if(isprint(ch) || isspace(ch)){
            // Qt text append() always add new paragraph
            txtRx->moveCursor(QTextCursor::End);
            txtRx->insertPlainText(QChar(ch));
        }
    }
}

/** @} */