#include "coba.h"

Coba::Coba(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::Window(cobject),m_builder(refGlade)
{
    m_builder->get_widget("m_btnup",m_btnUp);
    m_builder->get_widget("m_btndown",m_btnDown);
    m_builder->get_widget("m_lbl",m_lbl);

    m_btnUp->signal_clicked().connect(sigc::mem_fun(*this,&Coba::on_btnUp));
    m_btnDown->signal_clicked().connect(sigc::mem_fun(*this,&Coba::on_btnDown));

    count = 0;
    Glib::ustring amount = "Button Count= " + Glib::ustring::format(count);
    m_lbl->set_text(amount);

    set_title("Simple Gtk::Builder demo");
    set_default_size(200, 200);
}

Coba::~Coba(){}

void Coba::on_btnUp(){
    if(count<=9){
        count++;
    }

    Glib::ustring amount = "Button Count= " + Glib::ustring::format(count);
    m_lbl->set_text(amount);
}

void Coba::on_btnDown(){
    if(count>0){
        count--;
    }

    Glib::ustring amount = "Button Count= " + Glib::ustring::format(count);
    m_lbl->set_text(amount);
}

