#ifndef DIALTEST_H
#define DIALTEST_H

#include <QMainWindow>

namespace Ui {
class dialtest;
}

class dialtest : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit dialtest(QWidget *parent = 0);
    ~dialtest();
    
private:
    Ui::dialtest *ui;

private slots:
    void lcdNumberSet(void);
    void dialNumberSet(void);
    void dialNumberSet2(void);
};

#endif // DIALTEST_H
