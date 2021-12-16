#ifndef QDATA_H
#define QDATA_H

#include <QMainWindow>
#include <QMessageBox>

#include <QtSql>

namespace Ui {
class qdata;
}

class qdata : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit qdata(QWidget *parent = 0);
    ~qdata();
    
private:
    Ui::qdata *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QSqlQuery myquery;
    QString dbase;
    QString dtable;

private slots:
    void viewData(void);
};

#endif // QDATA_H
