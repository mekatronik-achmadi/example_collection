#include "fuse_calc.h"
#include "ui_fuse_calc.h"

extern u_int8_t val_EFUSE;
extern u_int8_t val_HFUSE;
extern u_int8_t val_LFUSE;

void fuse_calc::program_statusbar_set(){
    QString msg;

    msg += "Chip=" + ui->cmbSelectChip->currentText() + " || ";
    msg += "LFUSE=0x" + QString("%1").arg(val_LFUSE, 2, 16, QChar('0')).toUpper() + " || ";
    msg += "HFUSE=0x" + QString("%1").arg(val_HFUSE, 2, 16, QChar('0')).toUpper() + " || ";
    msg += "EFUSE=0x" + QString("%1").arg(val_EFUSE, 2, 16, QChar('0')).toUpper() + " || ";

    ui->statusBar->showMessage(msg);
}

void fuse_calc::program_chkfuse_assign(){
    chkLFUSE[0] = ui->chkFUSE0_0;
    chkLFUSE[1] = ui->chkFUSE1_0;
    chkLFUSE[2] = ui->chkFUSE2_0;
    chkLFUSE[3] = ui->chkFUSE3_0;
    chkLFUSE[4] = ui->chkFUSE4_0;
    chkLFUSE[5] = ui->chkFUSE5_0;
    chkLFUSE[6] = ui->chkFUSE6_0;
    chkLFUSE[7] = ui->chkFUSE7_0;

    chkHFUSE[0] = ui->chkFUSE0_1;
    chkHFUSE[1] = ui->chkFUSE1_1;
    chkHFUSE[2] = ui->chkFUSE2_1;
    chkHFUSE[3] = ui->chkFUSE3_1;
    chkHFUSE[4] = ui->chkFUSE4_1;
    chkHFUSE[5] = ui->chkFUSE5_1;
    chkHFUSE[6] = ui->chkFUSE6_1;
    chkHFUSE[7] = ui->chkFUSE7_1;

    chkEFUSE[0] = ui->chkFUSE0_2;
    chkEFUSE[1] = ui->chkFUSE1_2;
    chkEFUSE[2] = ui->chkFUSE2_2;
    chkEFUSE[3] = ui->chkFUSE3_2;
    chkEFUSE[4] = ui->chkFUSE4_2;
    chkEFUSE[5] = ui->chkFUSE5_2;
    chkEFUSE[6] = ui->chkFUSE6_2;
    chkEFUSE[7] = ui->chkFUSE7_2;
}

void fuse_calc::program_widget_ability(bool ability){
    ui->cmbSelectChip->setEnabled(!ability);
    ui->btnFuseHexDefault->setEnabled(ability);
    ui->btnFuseHexApply->setEnabled(ability);

    ui->tabFuseBit->setEnabled(ability);
    ui->tabBOD->setEnabled(ability);
    ui->tabBootSz->setEnabled(ability);
    ui->tabOsc->setEnabled(ability);

    ui->statusBar->setEnabled(ability);
}

void fuse_calc::program_fuse_unrestrict(){
    u_int8_t i;

    for(i=0;i<8;i++){
        chkLFUSE[i]->setEnabled(true);
        chkHFUSE[i]->setEnabled(true);
        chkEFUSE[i]->setEnabled(true);
    }
}

void fuse_calc::program_fuse_default(){
    val_LFUSE = v_chip.fuse_default(ui->cmbSelectChip->currentIndex(),LFUSE);
    val_HFUSE = v_chip.fuse_default(ui->cmbSelectChip->currentIndex(),HFUSE);
    val_EFUSE = v_chip.fuse_default(ui->cmbSelectChip->currentIndex(),EFUSE);

    program_fuse_set_hexa();
    program_fuse_set_bit();
}

void fuse_calc::program_fuse_restrict(){
    u_int8_t restric_lfuse = v_chip.fuse_restrict(ui->cmbSelectChip->currentIndex(),LFUSE);
    u_int8_t restric_hfuse = v_chip.fuse_restrict(ui->cmbSelectChip->currentIndex(),HFUSE);
    u_int8_t restric_efuse = v_chip.fuse_restrict(ui->cmbSelectChip->currentIndex(),EFUSE);

    u_int8_t i;

    for(i=0;i<8;i++){
        chkLFUSE[i]->setEnabled( !(restric_lfuse & (1<< i)) );
        chkHFUSE[i]->setEnabled( !(restric_hfuse & (1<< i)) );
        chkEFUSE[i]->setEnabled( !(restric_efuse & (1<< i)) );
    }
}

void fuse_calc::program_fuse_string(){
    QStringList str_list_lfuse = v_chip.fuse_string(ui->cmbSelectChip->currentIndex(),LFUSE);
    QStringList str_list_hfuse = v_chip.fuse_string(ui->cmbSelectChip->currentIndex(),HFUSE);
    QStringList str_list_efuse = v_chip.fuse_string(ui->cmbSelectChip->currentIndex(),EFUSE);

    u_int8_t i;

    for(i=0;i<8;i++){
        chkLFUSE[i]->setText(str_list_lfuse[i]);
        chkHFUSE[i]->setText(str_list_hfuse[i]);
        chkEFUSE[i]->setText(str_list_efuse[i]);
    }
}

void fuse_calc::program_fuse_tooltip(){
    QStringList str_list_lfuse = v_chip.fuse_tooltip(ui->cmbSelectChip->currentIndex(),LFUSE);
    QStringList str_list_hfuse = v_chip.fuse_tooltip(ui->cmbSelectChip->currentIndex(),HFUSE);
    QStringList str_list_efuse = v_chip.fuse_tooltip(ui->cmbSelectChip->currentIndex(),EFUSE);

    u_int8_t i;

    for(i=0;i<8;i++){
        chkLFUSE[i]->setToolTip(str_list_lfuse[i]);
        chkHFUSE[i]->setToolTip(str_list_hfuse[i]);
        chkEFUSE[i]->setToolTip(str_list_efuse[i]);
    }
}

void fuse_calc::program_fuse_set_hexa(void){
    QString str_lfuse=QString("%1").arg(val_LFUSE, 2, 16, QChar('0'));
    ui->txtLFUSE->setText(str_lfuse.toUpper());

    QString str_hfuse=QString("%1").arg(val_HFUSE, 2, 16, QChar('0'));
    ui->txtHFUSE->setText(str_hfuse.toUpper());

    QString str_efuse=QString("%1").arg(val_EFUSE, 2, 16, QChar('0'));
    ui->txtEFUSE->setText(str_efuse.toUpper());
}

void fuse_calc::program_fuse_set_bit(void){

    u_int8_t i;
    u_int8_t l_fuse = ~val_LFUSE;
    u_int8_t h_fuse = ~val_HFUSE;
    u_int8_t e_fuse = ~val_EFUSE;

    for(i=0;i<8;i++){
        if(l_fuse & (1<< i)){
            chkLFUSE[i]->setChecked(true);
        }
        else{
            chkLFUSE[i]->setChecked(false);
        }
    }

    for(i=0;i<8;i++){
        if(h_fuse & (1<< i)){
            chkHFUSE[i]->setChecked(true);
        }
        else{
            chkHFUSE[i]->setChecked(false);
        }
    }

    for(i=0;i<8;i++){
        if(e_fuse & (1<< i)){
            chkEFUSE[i]->setChecked(true);
        }
        else{
            chkEFUSE[i]->setChecked(false);
        }
    }
}

void fuse_calc::program_fuse_get_hexa(){
    val_LFUSE = ui->txtLFUSE->text().toUInt(0,16);
    val_HFUSE = ui->txtHFUSE->text().toUInt(0,16);
    val_EFUSE = ui->txtEFUSE->text().toUInt(0,16);
}

void fuse_calc::program_fuse_get_bit(){
    u_int8_t i;

    u_int8_t vl_fuse = 0x00;
    u_int8_t vh_fuse = 0x00;
    u_int8_t ve_fuse = 0x00;

    for(i=0;i<8;i++){

        if(chkLFUSE[i]->isChecked()){
            vl_fuse |= (1<<i);
        }
        else{
            vl_fuse &= ~(1<<i);
        }

        if(chkHFUSE[i]->isChecked()){
            vh_fuse |= (1<<i);
        }
        else{
            vh_fuse &= ~(1<<i);
        }

        if(chkEFUSE[i]->isChecked()){
            ve_fuse |= (1<<i);
        }
        else{
            ve_fuse &= ~(1<<i);
        }
    }

    val_LFUSE = ~vl_fuse;
    val_HFUSE = ~vh_fuse;
    val_EFUSE = ~ve_fuse;
}

void fuse_calc::program_bod_string(){
    ui->cmbBOD->clear();
    ui->cmbBOD->insertItems(0,v_chip.bod_string(ui->cmbSelectChip->currentIndex()));
}

void fuse_calc::program_bod_get(){
    val_LFUSE = v_chip.bod_get(ui->cmbSelectChip->currentIndex(),LFUSE,val_LFUSE,ui->cmbBOD->currentIndex());
    val_HFUSE = v_chip.bod_get(ui->cmbSelectChip->currentIndex(),HFUSE,val_HFUSE,ui->cmbBOD->currentIndex());
    val_EFUSE = v_chip.bod_get(ui->cmbSelectChip->currentIndex(),EFUSE,val_EFUSE,ui->cmbBOD->currentIndex());
}

void fuse_calc::program_bod_set(){
    ui->cmbBOD->setCurrentIndex(v_chip.bod_set(ui->cmbSelectChip->currentIndex(),val_LFUSE,val_HFUSE,val_EFUSE));
}

void fuse_calc::program_bootsz_string(){
    ui->cmbBootSz->clear();
    ui->cmbBootSz->insertItems(0,v_chip.bootsz_string(ui->cmbSelectChip->currentIndex()));
}

void fuse_calc::program_bootsz_get(){
    val_LFUSE = v_chip.bootsz_get(ui->cmbSelectChip->currentIndex(),LFUSE,val_LFUSE,ui->cmbBootSz->currentIndex());
    val_HFUSE = v_chip.bootsz_get(ui->cmbSelectChip->currentIndex(),HFUSE,val_HFUSE,ui->cmbBootSz->currentIndex());
    val_EFUSE = v_chip.bootsz_get(ui->cmbSelectChip->currentIndex(),EFUSE,val_EFUSE,ui->cmbBootSz->currentIndex());
}

void fuse_calc::program_bootsz_set(){
    ui->cmbBootSz->setCurrentIndex(v_chip.bootsz_set(ui->cmbSelectChip->currentIndex(),val_LFUSE,val_HFUSE,val_EFUSE));
}

void fuse_calc::program_osc_string(){
    ui->cmbOsc->clear();
    ui->cmbOsc->insertItems(0,v_chip.osc_string(ui->cmbSelectChip->currentIndex()));
}

void fuse_calc::program_osc_get(){
    val_LFUSE = v_chip.osc_get(ui->cmbSelectChip->currentIndex(),LFUSE,val_LFUSE,ui->cmbOsc->currentIndex());
    val_HFUSE = v_chip.osc_get(ui->cmbSelectChip->currentIndex(),HFUSE,val_HFUSE,ui->cmbOsc->currentIndex());
    val_EFUSE = v_chip.osc_get(ui->cmbSelectChip->currentIndex(),EFUSE,val_EFUSE,ui->cmbOsc->currentIndex());
}

void fuse_calc::program_osc_set(){
    ui->cmbOsc->setCurrentIndex(v_chip.osc_set(ui->cmbSelectChip->currentIndex(),val_LFUSE,val_HFUSE,val_EFUSE));
}

