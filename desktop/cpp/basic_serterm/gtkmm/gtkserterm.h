#ifndef GTKSERTERM_H
#define GTKSERTERM_H

#include <iostream>
#include <gtkmm.h>

class GtkSerTerm: public Gtk::Window
{
    public:
        GtkSerTerm();
        virtual ~GtkSerTerm();

    private:
        void on_action_file_quit();
        void on_action_help_about();

        Gtk::Box m_Box;
        Glib::RefPtr<Gtk::Builder> m_refBuilder;
        Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;
};

#endif
