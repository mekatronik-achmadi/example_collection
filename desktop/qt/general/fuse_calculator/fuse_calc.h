#ifndef FUSE_CALC_H
#define FUSE_CALC_H

#include <QMainWindow>
#include <QtWidgets/QCheckBox>
#include "bit_value.h"
#include "chip/chip.h"

namespace Ui {
class fuse_calc;
}

class fuse_calc : public QMainWindow
{
    Q_OBJECT

public:
    explicit fuse_calc(QWidget *parent = 0);
    ~fuse_calc();

private slots:
    void program_statusbar_set(void);
    void program_chkfuse_assign(void);
    void program_widget_ability(bool ability);
    void program_fuse_unrestrict(void);
    void program_fuse_default(void);
    void program_fuse_restrict(void);
    void program_fuse_string(void);
    void program_fuse_tooltip(void);
    void program_fuse_set_hexa(void);
    void program_fuse_set_bit(void);
    void program_fuse_get_hexa(void);
    void program_fuse_get_bit(void);
    void program_bod_string(void);
    void program_bod_get(void);
    void program_bod_set(void);
    void program_bootsz_string(void);
    void program_bootsz_get(void);
    void program_bootsz_set(void);
    void program_osc_string(void);
    void program_osc_get(void);
    void program_osc_set(void);

    void on_txtEFUSE_textChanged(const QString &arg1);
    void on_txtHFUSE_textChanged(const QString &arg1);
    void on_txtLFUSE_textChanged(const QString &arg1);

    void on_btnSelectChip_clicked();
    void on_btnFuseHexDefault_clicked();
    void on_btnFuseHexApply_clicked();

    void on_btnFuseBitDefault_clicked();
    void on_btnFuseBitApply_clicked();
    void on_btnFuseBitUnrestrict_clicked();

    void on_btnBODApply_clicked();
    void on_btnBootSzApply_clicked();
    void on_btnOscApply_clicked();

private:
    Ui::fuse_calc *ui;

    QCheckBox *chkLFUSE[8];
    QCheckBox *chkHFUSE[8];
    QCheckBox *chkEFUSE[8];

    chip v_chip;
};

#endif // FUSE_CALC_H
