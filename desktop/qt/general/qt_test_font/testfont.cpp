#include "testfont.h"
#include "ui_testfont.h"

testfont::testfont(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::testfont)
{
    ui->setupUi(this);

    connect(ui->cmbFont,SIGNAL(currentFontChanged(QFont)),this,SLOT(setfromCmbFont()));

    ui->lblFont->setFont(ui->cmbFont->font());
}

testfont::~testfont()
{
    delete ui;
}


void testfont::setfromCmbFont(){
    ui->lblFont->setFont(ui->cmbFont->font());
}
