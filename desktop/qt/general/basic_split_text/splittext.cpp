#include "splittext.h"
#include "ui_splittext.h"

splitText::splitText(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::splitText)
{
    ui->setupUi(this);
}

splitText::~splitText()
{
    delete ui;
}

void splitText::on_actionTest_triggered()
{
    QString str1=ui->txtText->toPlainText();
    QStringList str2=str1.split("\n");
    QString str3=str2[2];
    ui->lblText->setText(str3);
}
