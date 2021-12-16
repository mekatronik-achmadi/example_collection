#ifndef QTFILE_H
#define QTFILE_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

namespace Ui {
class qtfile;
}

class qtfile : public QMainWindow
{
    Q_OBJECT

public:
    explicit qtfile(QWidget *parent = 0);
    ~qtfile();

private slots:
    void on_actionSave_triggered();

    void on_actionClear_triggered();

    void on_actionOpen_triggered();

private:
    Ui::qtfile *ui;
};

#endif // QTFILE_H
