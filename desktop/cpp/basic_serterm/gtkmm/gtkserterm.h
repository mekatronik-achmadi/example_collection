#ifndef GTKSERTERM_H
#define GTKSERTERM_H

#include <iostream>
#include <gtkmm.h>
#include "../ceSerial/ceSerial.h"

class GtkSerTerm: public Gtk::Window
{
    public:
        GtkSerTerm();
        virtual ~GtkSerTerm();

    private:
        void onOpen();
        void on_action_file_quit();
        void on_action_help_about();
        void on_clicked_btnOpen();

        Gtk::VBox m_Box;
        Gtk::Box m_boxMenu;
        Gtk::HBox m_boxButton;

        Glib::RefPtr<Gtk::Builder> m_refBuilder;
        Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;
        Gtk::Button m_btnOpen;
        Gtk::Button m_btnSend;
        Gtk::Entry m_txtSend;
        ceSerial comport;
};

#endif
