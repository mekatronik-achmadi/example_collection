#include "test.h"
#include "ui_test.h"

test::test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
}

test::~test()
{
    delete ui;
}

void test::on_btnMsg_clicked(){
    QApplication::aboutQt();
}
