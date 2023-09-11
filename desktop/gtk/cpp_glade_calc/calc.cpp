#include "calc.h"

Calc::Calc(BaseObjectType *cobject, Glib::RefPtr<Gtk::Builder> &refGlade)
    : Gtk::Window(cobject), m_builder(refGlade)
{
    set_title("Calculator");
}

Calc::~Calc()
{

}
