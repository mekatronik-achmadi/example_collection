#include "qtfile.h"
#include "ui_qtfile.h"

qtfile::qtfile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qtfile)
{
    ui->setupUi(this);
}

qtfile::~qtfile()
{
    delete ui;
}

void qtfile::on_actionSave_triggered()
{
    QString filename;
    QString filesave=QFileDialog::getSaveFileName(this,"save data","","Gea Tuning data (*.gea)");

    if(filesave.isEmpty()){return;}

    QStringList filenameparse = filesave.split(".");

    if(filenameparse.count()==2){
        filename=filenameparse[0];
    }
    else if(filenameparse.count()==1){
        filename=filesave;
    }

    filename += ".gea";

    QFile filestream(filename);
    if(!filestream.open(QFile::WriteOnly|QFile::Text|QFile::Truncate)){
        QMessageBox::critical(this,"Failed","File failed to save");
        return;
    }

    QTextStream filewrite(&filestream);

    filewrite << ui->txtText->toPlainText();

    filestream.flush();
    filestream.close();

}

void qtfile::on_actionClear_triggered()
{
    ui->txtText->clear();
}

void qtfile::on_actionOpen_triggered()
{
    QString filename;
    QString fileopen=QFileDialog::getOpenFileName(this,"load data","","Gea Tuning data (*.gea)");
    if(fileopen.isEmpty()){return;}
    filename=fileopen;

    QFile filestream(filename);

    if(!filestream.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::critical(this,"Failed","File failed to open");
        return;
    }

    QTextStream fileread(&filestream);

    while(!fileread.atEnd()){
        QString received=fileread.readAll();
        ui->txtText->insertPlainText(received);
    }

    filestream.close();
}
