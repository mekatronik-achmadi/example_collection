#include "qdata.h"
#include "ui_qdata.h"

qdata::qdata(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qdata)
{
    ui->setupUi(this);
    connect(ui->btnData,SIGNAL(clicked()),this,SLOT(viewData()));

    dbase += "mydata";

    db.setHostName("localhost");
    db.setDatabaseName(dbase);
    db.setUserName("root");
    db.setPassword("kde");

    if (db.open()){
        QMessageBox::information(this,"connected","database connected");
        ui->lblDBase->setText("Database = " + dbase);
    }
    else{
        QMessageBox::critical(this,"failed","database failed to connect");
        return;
    }
}

qdata::~qdata()
{
    delete ui;
}

void qdata::viewData(){

    int i,j;

    ui->tblData->clear();

    dtable ="select * from ";
    dtable += ui->lneData->text();

    myquery.exec(dtable);

    ui->tblData->setColumnCount(myquery.record().count());
    ui->tblData->setRowCount(myquery.size());

    ui->lblColumn->setText("Column = " + QString::number(myquery.record().count()));
    ui->lblRow->setText("Row = " + QString::number(myquery.size()));

    i=0;
    j=0;
    while (myquery.next())
    {
        for(j=0;j<myquery.record().count();j++){
            ui->tblData->setItem(i,j,new QTableWidgetItem(myquery.value(j).toString()));
        }
        i++;
    };
}
