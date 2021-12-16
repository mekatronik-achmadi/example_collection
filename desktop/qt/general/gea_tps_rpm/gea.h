#ifndef GEA_H
#define GEA_H

#include <QMainWindow>

#define tabrpm 7
#define tabtps 7

namespace Ui {
class gea;
}

class gea : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit gea(QWidget *parent = 0);
    ~gea();
    
private:
    Ui::gea *ui;
    int tab_rpm[tabrpm]={0, 1000, 2000, 3000, 4000, 5000, 6000};
    int tab_tps[tabtps]={0, 250, 500, 750, 1000, 1250, 1400};

    int tab_inj_start[tabtps][tabrpm]={
        {6, 6, 5, 4, 2, 0, 22},
        {6, 6, 5, 4, 2, 0, 22},
        {6, 6, 5, 4, 2, 0, 22},
        {6, 6, 5, 4, 2, 0, 22},
        {6, 6, 5, 4, 2, 0, 22},
        {6, 6, 5, 4, 2, 0, 22},
        {6, 6, 5, 4, 2, 0, 22}
    };

    int tab_inj_stop[tabtps][tabrpm]={
        {8, 8, 8, 8, 8, 8, 8},
        {8, 8, 8, 8, 8, 8, 8},
        {8, 8, 8, 8, 8, 8, 8},
        {8, 8, 8, 8, 8, 8, 8},
        {8, 8, 8, 8, 8, 8, 8},
        {8, 8, 8, 8, 8, 8, 8},
        {8, 8, 8, 8, 8, 8, 8}
    };

    int tab_ign_start[tabtps][tabrpm]={
        {5, 5, 5, 5, 5, 5, 5},
        {4, 4, 4, 4, 4, 4, 4},
        {4, 4, 4, 4, 4, 4, 4},
        {3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3},
        {4, 4, 4, 4, 4, 4, 4},
        {4, 4, 4, 4, 4, 4, 4}
    };

    int tab_ign_stop[tabtps][tabrpm]={
        {8, 8, 8, 8, 8, 8, 8},
        {7, 7, 7, 7, 7, 7, 7},
        {7, 7, 7, 7, 7, 7, 7},
        {6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6},
        {7, 7, 7, 7, 7, 7, 7},
        {7, 7, 7, 7, 7, 7, 7}
    };

    QString arrtps,arrrpm;
    int tps,rpm;
    int inj_start,inj_stop;
    int ign_start,ign_stop;

private slots:
    void checkview(void);
};

#endif // GEA_H
