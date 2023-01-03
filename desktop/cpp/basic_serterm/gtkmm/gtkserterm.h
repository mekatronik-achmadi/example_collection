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
        void onClose();
        bool onTimer();
        void ProcessChar(char ch);

        void on_action_file_quit();
        void on_action_edit_selport();
        void on_action_edit_setbaud();
        void on_action_edit_clear();
        void on_action_help_about();
        void on_clicked_btnOpen();
        void on_clicked_btnSend();

        Gtk::VBox m_Box;
        Gtk::Box m_boxMenu;
        Gtk::HBox m_boxButton;
        Gtk::Box m_boxRx;

        Glib::RefPtr<Gtk::Builder> m_refBuilder;
        Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;

        Gtk::Button m_btnOpen;
        Gtk::Button m_btnSend;
        Gtk::Entry m_txtSend;

        Gtk::TextView m_txtRx;
        Gtk::ScrolledWindow m_winTxtRx;
        Glib::RefPtr<Gtk::TextBuffer> m_buffTxtRx;

        Gtk::Statusbar m_statusbar;

        ceSerial comport;
};

#endif
