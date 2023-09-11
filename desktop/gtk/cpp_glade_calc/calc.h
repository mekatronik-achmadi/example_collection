#ifndef CALC_H
#define CALC_H

#include <gtkmm-3.0/gtkmm.h>

class Calc : public Gtk::Window
{
private:


public:
    Calc(BaseObjectType *cobject, Glib::RefPtr<Gtk::Builder> &refGlade);
    virtual ~Calc();

protected:
    Glib::RefPtr<Gtk::Builder> m_builder;
};

#endif /* CALC_H */
