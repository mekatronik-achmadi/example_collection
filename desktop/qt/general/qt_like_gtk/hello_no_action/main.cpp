#include <QApplication>
#include <QWidget>

int main(int argc,char *argv[]){
	QWidget *mywidget;
	
	QApplication app(argc,argv);
	mywidget = new QWidget();
	mywidget->show();
	return app.exec();
}
