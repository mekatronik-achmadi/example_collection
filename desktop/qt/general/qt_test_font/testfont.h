#ifndef TESTFONT_H
#define TESTFONT_H

#include <QMainWindow>

namespace Ui {
class testfont;
}

class testfont : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit testfont(QWidget *parent = 0);
    ~testfont();
    
private:
    Ui::testfont *ui;

private slots:
    void setfromCmbFont(void);
};

#endif // TESTFONT_H
