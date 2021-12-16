#include "app.h"
#include "ui_app.h"

app::app(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::app)
{
    ui->setupUi(this);

    connect(&process, SIGNAL(readyReadStandardError()),this, SLOT(processOnGoing()));
    connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)),this,SLOT(processFinished(int, QProcess::ExitStatus)));
    connect(&process, SIGNAL(error(QProcess::ProcessError)),this,SLOT(processError(QProcess::ProcessError)));

    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(app_quit()));
    connect(ui->actionHelp,SIGNAL(triggered()),this,SLOT(app_help()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(app_about()));

    connect(ui->btnAvrBrowse,SIGNAL(clicked()),this,SLOT(avr_browse()));
    connect(ui->btnAvrTest,SIGNAL(clicked()),this,SLOT(avr_test()));
    connect(ui->btnAvrErase,SIGNAL(clicked()),this,SLOT(avr_erase()));
    connect(ui->btnAvrWrite,SIGNAL(clicked()),this,SLOT(avr_write()));

    connect(ui->btnStlinkBrowse,SIGNAL(clicked()),this,SLOT(stlink_browse()));
    connect(ui->btnStlinkErase,SIGNAL(clicked()),this,SLOT(stlink_erase()));
    connect(ui->btnStlinkWrite,SIGNAL(clicked()),this,SLOT(stlink_write()));

    connect(ui->btnSTFlashBrowse,SIGNAL(clicked()),this,SLOT(stflash_browse()));
    connect(ui->btnSTFlashErase,SIGNAL(clicked()),this,SLOT(stflash_erase()));
    connect(ui->btnSTFlashWrite,SIGNAL(clicked()),this,SLOT(stflash_write()));
    connect(ui->btnSTFlashTest,SIGNAL(clicked()),this,SLOT(stflash_test()));
}

app::~app()
{
    delete ui;
}

/*
 * Process section
 */

void app::processOnGoing(){
//    QByteArray newData = process.readAllStandardError();
    QByteArray newData = process.readAllStandardOutput();
    QString text = ui->txtOutput->toPlainText()
                       + QString::fromLocal8Bit(newData);
    ui->txtOutput->setPlainText(text);
}

void app::processFinished(int exitCode, QProcess::ExitStatus exitStatus){
    if (exitStatus == QProcess::CrashExit) {
            ui->txtOutput->append(tr("Program crashed\n"));
        } else if (exitCode != 0) {
            ui->txtOutput->append(tr("Action failed\n"));
        } else {
            ui->txtOutput->append(tr("Done\n"));
        }

    ui->btnAvrBrowse->setEnabled(true);
    ui->btnAvrWrite->setEnabled(true);
    ui->btnAvrErase->setEnabled(true);
    ui->btnAvrTest->setEnabled(true);

    ui->btnStlinkBrowse->setEnabled(true);
    ui->btnStlinkErase->setEnabled(true);
    ui->btnStlinkWrite->setEnabled(true);

    ui->btnSTFlashBrowse->setEnabled(true);
    ui->btnSTFlashErase->setEnabled(true);
    ui->btnSTFlashWrite->setEnabled(true);
    ui->btnSTFlashTest->setEnabled(true);
}

void app::processError(QProcess::ProcessError error){
    if (error == QProcess::FailedToStart) {
            ui->txtOutput->append(tr("Main Program not found. Please install all required programs first\n"));
    }

    ui->btnAvrBrowse->setEnabled(true);
    ui->btnAvrWrite->setEnabled(true);
    ui->btnAvrErase->setEnabled(true);
    ui->btnAvrTest->setEnabled(true);

    ui->btnStlinkBrowse->setEnabled(true);
    ui->btnStlinkErase->setEnabled(true);
    ui->btnStlinkWrite->setEnabled(true);

    ui->btnSTFlashBrowse->setEnabled(true);
    ui->btnSTFlashErase->setEnabled(true);
    ui->btnSTFlashWrite->setEnabled(true);
    ui->btnSTFlashTest->setEnabled(true);
}

/*
 * App section
 */

void app::app_quit(){
    QApplication::quit();
}

void app::app_about(){
    QApplication::aboutQt();
}

void app::app_help(){
    QString avrdude_msg;
    QString stlink_msg;
    QString stflash_msg;
    QString message;

    avrdude_msg="To using avrdude, please make sure:\n";
    avrdude_msg+="1. avrdude is installed. If not, open the shell and type \"sudo apt-get install avrdude\"\n";
    avrdude_msg+="2. you have usbasp tool or usbasploader on your device.If not,please visit:\n";
    avrdude_msg+="http://www.fischl.de/usbasp/ or http://www.obdev.at/products/vusb/usbasploader.html\n";
    avrdude_msg+="you may need gcc-avr and avr-libc to build it. If not installed, open the shell and type\n";
    avrdude_msg+="sudo apt-get install gcc-avr avr-libc\n";

    stlink_msg="To using st-link, please make sure:\n";
    stlink_msg+="1. st-link is installed. If not, get latest sources from:\n";
    stlink_msg+="https://github.com/texane/stlink . Don't forget read the README to know how to build it\n";
    stlink_msg+="2. you have st-link device (standalone tool or embedded on certain evaluation board). If not, order it from ST.\n";

    stflash_msg="To using stflash, please make sure:\n";
    stflash_msg+="1. stflash is installed. If not, get latest sources from:\n";
    stflash_msg+="https://github.com/texane/stlink . Don't forget read the README to know how to build it\n";
    stflash_msg+="2. you have a serial-ftdi circuit connected to your board on USART1\n";
    stflash_msg+="3. your board can boot from system memory to activate bootloader";

    message="Please read carefully. You may need some help from uncle Google, so you have to get an internet connection\n";
    message+="\n\n";

    message+=avrdude_msg;
    message+="\n\n";

    message+=stlink_msg;
    message+="\n\n";

    message+=stflash_msg;
    message+="\n\n";

    message+="Author Contact= https://www.facebook.com/arramadhandevelopment\n\n";
    message+="This tool currently for Linux Box only. I'm no interest to develop on Windows or Mac ^_^\n";

    QMessageBox::information(this,"Help Message",message);
}

/*
 * AVRDude Section
 */

void app::avr_browse(){
    avr_path=QFileDialog::getOpenFileName(this, "Open AVR Flash File","Intel Hexadecimal *.hex","*.hex");
    ui->txtAvrFile->setText(avr_path);
}

void app::avr_test(){
    QStringList avr_args;

    ui->txtOutput->clear();

    avr_arg_core="-p";
    if(ui->optM8->isChecked()){avr_arg_core+="m8";}
    if(ui->optM16->isChecked()){avr_arg_core+="m16";}
    if(ui->optM32->isChecked()){avr_arg_core+="m32";}
    if(ui->optM8535->isChecked()){avr_arg_core+="m8535";}
    if(ui->optM1280->isChecked()){avr_arg_core+="m1280";}
    if(ui->optM2560->isChecked()){avr_arg_core+="m2560";}

    avr_arg_tool="-cusbasp";
    avr_arg_port="-Pusb";

    avr_args << avr_arg_core;
    avr_args << avr_arg_tool;
    avr_args << avr_arg_port;

    ui->btnAvrBrowse->setEnabled(false);
    ui->btnAvrWrite->setEnabled(false);
    ui->btnAvrErase->setEnabled(false);
    ui->btnAvrTest->setEnabled(false);

    process.start("avrdude", avr_args);
}

void app::avr_erase(){
    QStringList avr_args;

    ui->txtOutput->clear();

    avr_arg_core="-p";
    if(ui->optM8->isChecked()){avr_arg_core+="m8";}
    if(ui->optM16->isChecked()){avr_arg_core+="m16";}
    if(ui->optM32->isChecked()){avr_arg_core+="m32";}
    if(ui->optM8535->isChecked()){avr_arg_core+="m8535";}
    if(ui->optM1280->isChecked()){avr_arg_core+="m1280";}
    if(ui->optM2560->isChecked()){avr_arg_core+="m2560";}

    avr_arg_tool="-cusbasp";
    avr_arg_port="-Pusb";
    avr_arg_load="-e";

    avr_args << avr_arg_core;
    avr_args << avr_arg_tool;
    avr_args << avr_arg_port;
    avr_args << avr_arg_load;

    ui->btnAvrBrowse->setEnabled(false);
    ui->btnAvrWrite->setEnabled(false);
    ui->btnAvrErase->setEnabled(false);
    ui->btnAvrTest->setEnabled(false);

    process.start("avrdude", avr_args);
}

void app::avr_write(){
    QStringList avr_args;

    ui->txtOutput->clear();

    avr_arg_core="-p";
    if(ui->optM8->isChecked()){avr_arg_core+="m8";}
    if(ui->optM16->isChecked()){avr_arg_core+="m16";}
    if(ui->optM32->isChecked()){avr_arg_core+="m32";}
    if(ui->optM8535->isChecked()){avr_arg_core+="m8535";}
    if(ui->optM1280->isChecked()){avr_arg_core+="m1280";}
    if(ui->optM2560->isChecked()){avr_arg_core+="m2560";}

    avr_arg_tool="-cusbasp";
    avr_arg_port="-Pusb";

    avr_arg_load="-Uflash:w:";
    avr_arg_load+=ui->txtAvrFile->text();
    avr_arg_load+=":i";

    avr_args << avr_arg_core;
    avr_args << avr_arg_tool;
    avr_args << avr_arg_port;
    avr_args << avr_arg_load;

    if(ui->txtAvrFile->text().length()==0){
        QMessageBox::critical(this,"No File Selected","Select File to Upload into AVR Memory first");
        return;
    }

    ui->btnAvrBrowse->setEnabled(false);
    ui->btnAvrWrite->setEnabled(false);
    ui->btnAvrErase->setEnabled(false);
    ui->btnAvrTest->setEnabled(false);

    process.start("avrdude", avr_args);
}

/*
 * ST-Link section
 */

void app::stlink_browse(){
    stlink_path=QFileDialog::getOpenFileName(this, "Open RAW Binary File","RAW Binary File *.bin","*.bin");
    ui->txtStlinkFile->setText(stlink_path);
}

void app::stlink_erase(){
    QStringList stlink_args;

    ui->txtOutput->clear();

    stlink_arg_action="erase";

    stlink_args << stlink_arg_action;

    ui->btnStlinkBrowse->setEnabled(false);
    ui->btnStlinkErase->setEnabled(false);
    ui->btnStlinkWrite->setEnabled(false);

    process.start("st-flash", stlink_args);
}

void app::stlink_write(){
    QStringList stlink_args;

    ui->txtOutput->clear();

    stlink_arg_action="write";
    stlink_arg_load=ui->txtStlinkFile->text();
    stlink_arg_size="0x8000000";

    stlink_args << stlink_arg_action;
    stlink_args << stlink_arg_load;
    stlink_args << stlink_arg_size;

    if(ui->txtStlinkFile->text().length()==0){
        QMessageBox::critical(this,"No File Selected","Select File to Upload into STM32 Memory first");
        return;
    }

    ui->btnStlinkBrowse->setEnabled(false);
    ui->btnStlinkErase->setEnabled(false);
    ui->btnStlinkWrite->setEnabled(false);

    process.start("st-flash", stlink_args);
}

/*
 * STFlash section
 */

void app::stflash_browse(){
    stflash_path=QFileDialog::getOpenFileName(this, "Open RAW Binary File","RAW Binary File *.bin","*.bin");
    ui->txtSTFlashFile->setText(stflash_path);
}

void app::stflash_write(){}

void app::stflash_erase(){
    QStringList stflash_args;

    stflash_arg_serial=ui->txtSTFlashSerial->text();
    stflash_arg_action="-o";

    stflash_args << stflash_arg_action;
    stflash_args << stflash_arg_serial;


    ui->btnSTFlashBrowse->setEnabled(false);
    ui->btnSTFlashErase->setEnabled(false);
    ui->btnSTFlashWrite->setEnabled(false);
    ui->btnSTFlashTest->setEnabled(false);

    process.start("stm32flash",stflash_args);
}

void app::stflash_test(){
    QStringList stflash_args;

    stflash_arg_serial=ui->txtSTFlashSerial->text();

    stflash_args << stflash_arg_serial;

    ui->btnSTFlashBrowse->setEnabled(false);
    ui->btnSTFlashErase->setEnabled(false);
    ui->btnSTFlashWrite->setEnabled(false);
    ui->btnSTFlashTest->setEnabled(false);

    process.start("stm32flash",stflash_args);
}
