#ifndef NUMBER_H
#define NUMBER_H

#include <QMainWindow>

namespace Ui {
class number;
}

class number : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit number(QWidget *parent = 0);
    ~number();
    
private:
    Ui::number *ui;

private slots:
    void convert(void);
};

#endif // NUMBER_H
