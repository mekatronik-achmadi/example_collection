#include "calc.h"

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc,argv, "org.gtkmm.Calc");

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create()->create_from_file("calc.glade");
    Calc *window = 0;
    builder->get_widget_derived("m_wndCalc",window);

    return app->run(*window);
}
