#include "qtserialterminal.h"
#include "ui_qtserialterminal.h"

qtserialterminal::qtserialterminal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qtserialterminal)
{
    ui->setupUi(this);
    ui->txtTerminal->installEventFilter(this);

    my_port= new QSerialPort(this);
    connect(my_port,SIGNAL(readyRead()),SLOT(read_data()));

    tmrReq= new QTimer(this);
    connect(tmrReq,SIGNAL(timeout()),this,SLOT(req_data()));
}

qtserialterminal::~qtserialterminal()
{
    delete ui;
}

bool qtserialterminal::eventFilter(QObject *obj, QEvent *event){
    if(event->type()== QEvent::KeyPress){
        QKeyEvent* keyEvent = static_cast<QKeyEvent* >(event);
        if(my_port->isOpen()){
            if( (keyEvent->key() == Qt::Key_Enter) || (keyEvent->key() == Qt::Key_Return)){
                QString eolStr = "\r\n";
                QByteArray eolByte = eolStr.toUtf8();
                my_port->write(eolByte);

                if(ui->chkLocalEcho->isChecked()){
                    ui->txtTerminal->insertPlainText(eolByte);
                }
            }
            else{
                QString s = keyEvent->text();
                if(s.length()){
                    char ch = s.at(0).toLatin1();
                    QByteArray chb= QByteArray::fromRawData(&ch,1);
                    my_port->write(chb);

                    if(ui->chkLocalEcho->isChecked()){
                        ui->txtTerminal->insertPlainText(chb);
                    }
                }
            }
        }
        return true;
    }
    else{
        return QObject::eventFilter(obj, event);
    }
}

void qtserialterminal::mydelay(int millisecondsToWait){
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
        while( QTime::currentTime() < dieTime ){
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        };
        return;
}

void qtserialterminal::req_data(){

    if(!my_port->isOpen()){return;}

    QString reqStr= ui->txtReqData->text();

    if(ui->chkNewRow->isChecked()){reqStr += "\r";}
    if(ui->chkNewLine->isChecked()){reqStr += "\n";}

    QByteArray reqByte = reqStr.toUtf8();

    my_port->write(reqByte);


    int delay_val=ui->txtDelay->text().toInt();
    if(ui->chkUseDelay->isChecked()){
        mydelay(delay_val);
    }
}

void qtserialterminal::read_data(){
    QByteArray rawdata=my_port->readAll();
    ui->txtTerminal->insertPlainText(rawdata);
}

void qtserialterminal::on_actionQuit_triggered()
{
    if(my_port->isOpen()){my_port->close();}
    QApplication::quit();
}

void qtserialterminal::on_actionAboutQt_triggered()
{
    QApplication::aboutQt();
}

void qtserialterminal::on_chkUseDelay_clicked(bool checked)
{
    ui->txtDelay->setEnabled(checked);
}

void qtserialterminal::on_btnOpen_clicked()
{
    QString dev_name="/dev/";
    dev_name += ui->cmbPort->currentText();

    QSerialPort::BaudRate dev_baud = QSerialPort::Baud9600;

    int baud_index=ui->cmbBaud->currentIndex();

    switch(baud_index){
    case 0: dev_baud=QSerialPort::Baud9600;break;
    case 1: dev_baud=QSerialPort::Baud38400;break;
    case 2: dev_baud=QSerialPort::Baud57600;break;
    case 3: dev_baud=QSerialPort::Baud115200;break;
    }

    if(ui->btnOpen->text()=="Open"){

        my_port->setPortName(dev_name);

        if(my_port->open(QIODevice::ReadWrite)){
            my_port->setBaudRate(dev_baud,QSerialPort::AllDirections);
            my_port->setDataBits(QSerialPort::Data8);
            my_port->setStopBits(QSerialPort::OneStop);
            my_port->setFlowControl(QSerialPort::NoFlowControl);
            my_port->setParity(QSerialPort::NoParity);
            QMessageBox::information(this,"success","port success on "+dev_name );
            ui->btnOpen->setText("Close");
        }
        else{
            QMessageBox::critical(this,"Failed","port failed on "+dev_name);
            ui->btnOpen->setText("Open");
        }
    }

    else{
        if(my_port->isOpen()){
            my_port->close();
        }
        ui->btnOpen->setText("Open");
    }
}

void qtserialterminal::on_btnStart_clicked()
{
    if(!my_port->isOpen()){return;}

    int val_interval = ui->txtReqInterval->text().toInt();

    if(ui->btnStart->text()=="Start"){
        tmrReq->start(val_interval);
        ui->btnStart->setText("Stop");
    }
    else{
        tmrReq->stop();
        ui->btnStart->setText("Start");
    }
}

void qtserialterminal::on_actionClear_triggered()
{
    ui->txtTerminal->clear();
}
