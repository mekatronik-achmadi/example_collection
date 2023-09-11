#include <iostream>
#include "hw.h"

HW::HW()
 : m_button("Hello World")
{
 set_border_width(10);
 m_button.signal_clicked().connect(sigc::mem_fun(*this,&HW::on_button_clicked));
 add(m_button);
 m_button.show();
}

HW::~HW()
{
}

void HW::on_button_clicked(){
 std::cout << "Hello World" << std::endl;
}
