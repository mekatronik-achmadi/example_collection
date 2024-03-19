#include <FL/fl_ask.H>
#include "gui.h"

Gui *ui;

int main(int argc, char** argv){
    ui = new Gui();
    ui->show(argc, argv);

    Fl::scheme("gtk+");
    return Fl::run();
}

void onBtnMsg(Fl_Button *, void *){
    fl_message("Template FLTK C++");
}

void onBtnQuit(Fl_Button *, void *){
    ui->close();
}
