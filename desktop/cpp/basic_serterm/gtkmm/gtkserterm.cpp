#include "gtkserterm.h"

GtkSerTerm::GtkSerTerm(){
    set_default_size(390,500);

    add(m_Box);

    m_refActionGroup  = Gio::SimpleActionGroup::create();
    m_refActionGroup->add_action("quit",
    sigc::mem_fun(*this,&GtkSerTerm::on_action_file_quit));

    insert_action_group("serportmenu", m_refActionGroup);

    m_refBuilder = Gtk::Builder::create();

    const char *ui_info =
    "<interface>"
    "  <menu id='menubar'>"
    "    <submenu>"
    "      <attribute name='label'>File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label'>Quit</attribute>"
    "          <attribute name='action'>serportmenu.quit</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "  </menu>"
    "</interface>";

    try {
        m_refBuilder->add_from_string(ui_info);
    } catch (const Glib::Error &ex) {
        std::cerr << "Building Menu Failed: " << ex.what();
    }

    auto object = m_refBuilder->get_object("menubar");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    if(!gmenu){
        g_warning("GMenu not found");
    }
    else{
        auto pMenuBar = Gtk::make_managed<Gtk::MenuBar>(gmenu);
        m_Box.pack_start(*pMenuBar,Gtk::PACK_SHRINK);
    }

    show_all_children();
}

GtkSerTerm::~GtkSerTerm(){}

void GtkSerTerm::on_action_file_quit(){
    hide();
}
