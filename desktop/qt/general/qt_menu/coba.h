#ifndef COBA_H
#define COBA_H

#include <QMainWindow>

namespace Ui {
class coba;
}

class coba : public QMainWindow
{
    Q_OBJECT

public:
    explicit coba(QWidget *parent = 0);
    ~coba();

private slots:
    void on_actionAbout_triggered();

    void on_actionQuit_triggered();

private:
    Ui::coba *ui;
};

#endif // COBA_H
