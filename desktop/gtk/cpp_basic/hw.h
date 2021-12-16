#ifndef _HW_H_
#define _HW_H_

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class HW: public  Gtk::Window
{
 public:
  HW();

 protected:
  void on_button_clicked();

  Gtk::Button m_button;
};

#endif
