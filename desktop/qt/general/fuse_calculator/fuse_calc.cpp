#include "fuse_calc.h"
#include "ui_fuse_calc.h"

u_int8_t val_EFUSE;
u_int8_t val_HFUSE;
u_int8_t val_LFUSE;

fuse_calc::fuse_calc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fuse_calc)
{
    ui->setupUi(this);

    ui->tabFuseCalc->setCurrentIndex(0);

    program_chkfuse_assign();

    ui->cmbSelectChip->clear();
    ui->cmbSelectChip->insertItems(0,v_chip.list());

    program_widget_ability(false);

    ui->cmbSelectChip->setCurrentIndex(25);
}

fuse_calc::~fuse_calc()
{
    delete ui;
}

void fuse_calc::on_txtEFUSE_textChanged(const QString &arg1)
{
    (void) arg1;
    ui->txtEFUSE->setText(ui->txtEFUSE->text().toUpper());
}

void fuse_calc::on_txtHFUSE_textChanged(const QString &arg1)
{
    (void) arg1;
    ui->txtHFUSE->setText(ui->txtHFUSE->text().toUpper());
}

void fuse_calc::on_txtLFUSE_textChanged(const QString &arg1)
{
    (void) arg1;
    ui->txtLFUSE->setText(ui->txtLFUSE->text().toUpper());
}

void fuse_calc::on_btnSelectChip_clicked()
{
    if(ui->btnSelectChip->text() == "Select Chip"){
        program_widget_ability(true);

        program_fuse_string();
        program_fuse_tooltip();
        program_fuse_default();

        program_fuse_restrict();
        ui->btnSelectChip->setText("Unrestrict");

        program_bod_string();
        program_bootsz_string();
        program_osc_string();

        program_bod_set();
        program_bootsz_set();
        program_osc_set();

        program_statusbar_set();

        ui->btnSelectChip->setText("Deselect Chip");
    }
    else{
        program_widget_ability(false);

        ui->btnSelectChip->setText("Select Chip");
    }
}

void fuse_calc::on_btnFuseHexDefault_clicked()
{
    program_fuse_default();
    program_bod_set();
    program_bootsz_set();
    program_osc_set();
    program_statusbar_set();
}

void fuse_calc::on_btnFuseHexApply_clicked()
{
    program_fuse_get_hexa();
    program_fuse_set_bit();
    program_bod_set();
    program_bootsz_set();
    program_osc_set();
    program_statusbar_set();
}

void fuse_calc::on_btnFuseBitDefault_clicked()
{
    program_fuse_default();
    program_bod_set();
    program_bootsz_set();
    program_osc_set();
    program_statusbar_set();
}

void fuse_calc::on_btnFuseBitApply_clicked()
{
    program_fuse_get_bit();
    program_fuse_set_hexa();
    program_bod_set();
    program_bootsz_set();
    program_osc_set();
    program_statusbar_set();
}

void fuse_calc::on_btnFuseBitUnrestrict_clicked()
{
    if(ui->btnFuseBitUnrestrict->text()=="Unrestrict"){

        program_fuse_unrestrict();
        ui->btnFuseBitUnrestrict->setText("Restrict");
    }
    else{

        program_fuse_restrict();
        ui->btnFuseBitUnrestrict->setText("Unrestrict");
    }
}

void fuse_calc::on_btnBODApply_clicked()
{
    program_bod_get();
    program_fuse_set_bit();
    program_fuse_set_hexa();
    program_statusbar_set();
}

void fuse_calc::on_btnBootSzApply_clicked()
{
    program_bootsz_get();
    program_fuse_set_bit();
    program_fuse_set_hexa();
    program_statusbar_set();
}

void fuse_calc::on_btnOscApply_clicked()
{
    program_osc_get();
    program_fuse_set_bit();
    program_fuse_set_hexa();
    program_statusbar_set();
}

