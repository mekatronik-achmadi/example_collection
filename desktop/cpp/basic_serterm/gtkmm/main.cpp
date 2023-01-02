#include "gtkserterm.h"

int main(int argc, char *argv[]){
    auto app = Gtk::Application::create(argc,argv,"org.gtkmm.serialport");
    GtkSerTerm serterm;
    return app->run(serterm);
}
