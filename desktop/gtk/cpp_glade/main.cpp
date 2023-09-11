#include "coba.h"

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc,argv,"org.example.Glade");

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create()->create_from_file("coba.glade");
    Coba *wnd = 0;
    builder->get_widget_derived("m_wnd",wnd);

    return app->run(*wnd);
}
