#include <QApplication>
#include <QMainWindow>
#include "ui_hello.h"
#include "hello.h"

hello::hello() :
    QObject()
{
	
}

hello::~hello()
{
    
}

void hello::to_quit(void){
	QApplication::quit();
}

int main(int argc,char *argv[]){
	QApplication app(argc,argv);
	hello *myclass;
	Ui_MainWindow *myui;
	QMainWindow *mywindow;
	myclass = new hello();
	myui = new Ui_MainWindow();
	mywindow= new QMainWindow();
	myui-> setupUi(mywindow);
	//QObject::connect(myui->btnQuit,SIGNAL(clicked()),&app,SLOT(quit()));
	QObject::connect(myui->btnQuit,SIGNAL(clicked()),myclass,SLOT(to_quit()));
	mywindow->show();
	return app.exec();
}
