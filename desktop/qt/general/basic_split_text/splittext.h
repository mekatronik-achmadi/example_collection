#ifndef SPLITTEXT_H
#define SPLITTEXT_H

#include <QMainWindow>

namespace Ui {
class splitText;
}

class splitText : public QMainWindow
{
    Q_OBJECT

public:
    explicit splitText(QWidget *parent = 0);
    ~splitText();

private slots:
    void on_actionTest_triggered();

private:
    Ui::splitText *ui;
};

#endif // SPLITTEXT_H
