#ifndef COBA_H
#define COBA_H

#include <gtkmm-3.0/gtkmm.h>

class Coba : public Gtk::Window
{

public:
    Coba(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
    virtual ~Coba();

protected:
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::Label *m_lbl;
    Gtk::Button *m_btnUp;
    Gtk::Button *m_btnDown;

    unsigned int count;

    void on_btnUp(void);
    void on_btnDown(void);
};

#endif /* COBA_H */
