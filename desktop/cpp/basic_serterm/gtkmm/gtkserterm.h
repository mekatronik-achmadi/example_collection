#ifndef GTKSERTERM_H
#define GTKSERTERM_H

#include <gtkmm/window.h>

class GtkSerTerm: public Gtk::Window
{
    public:
        GtkSerTerm();
        virtual ~GtkSerTerm();
};

#endif
