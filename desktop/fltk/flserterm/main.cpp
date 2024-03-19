#include "gui.h"

int main(int argc, char** argv){
    Gui *ui = new Gui();
    ui->show(argc,argv);

    return Fl::run();
}

