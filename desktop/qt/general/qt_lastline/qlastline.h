#ifndef QLASTLINE_H
#define QLASTLINE_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class qlastline;
}

class qlastline : public QMainWindow
{
    Q_OBJECT

public:
    explicit qlastline(QWidget *parent = 0);
    ~qlastline();

private slots:
    void add_data();
    void select_data();

private:
    Ui::qlastline *ui;
    QTimer* tmrData;
    QTimer* tmrSelect;
};

#endif // QLASTLINE_H
