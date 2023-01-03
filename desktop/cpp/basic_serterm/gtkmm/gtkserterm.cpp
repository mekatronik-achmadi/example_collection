#include "gtkserterm.h"

GtkSerTerm::GtkSerTerm(){
    set_size_request(390,-1);
    set_title("Serial Port (Gtkmm-3)");

    add(m_Box);

    // MenuBar
    m_refActionGroup  = Gio::SimpleActionGroup::create();

    m_refActionGroup->add_action("quit",sigc::mem_fun(*this,&GtkSerTerm::on_action_file_quit));
    m_refActionGroup->add_action("selport",sigc::mem_fun(*this,&GtkSerTerm::on_action_edit_selport));
    m_refActionGroup->add_action("setbaud",sigc::mem_fun(*this,&GtkSerTerm::on_action_edit_setbaud));
    m_refActionGroup->add_action("clear",sigc::mem_fun(*this,&GtkSerTerm::on_action_edit_clear));
    m_refActionGroup->add_action("about",sigc::mem_fun(*this,&GtkSerTerm::on_action_help_about));

    insert_action_group("serportmenu", m_refActionGroup);

    m_refBuilder = Gtk::Builder::create();

    const char *ui_menu =
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
    "    <submenu>"
    "      <attribute name='label'>Edit</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label'>Serial Port</attribute>"
    "          <attribute name='action'>serportmenu.selport</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label'>Baud Rate</attribute>"
    "          <attribute name='action'>serportmenu.setbaud</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label'>Clear</attribute>"
    "          <attribute name='action'>serportmenu.clear</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label'>Help</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label'>About</attribute>"
    "          <attribute name='action'>serportmenu.about</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "  </menu>"
    "</interface>";

    try {
        m_refBuilder->add_from_string(ui_menu);
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
        m_boxMenu.add(*pMenuBar);
    }
    //menubar

    //button open send
    m_btnOpen.set_label("Open");
    m_btnOpen.signal_clicked().connect(sigc::mem_fun(*this,
    &GtkSerTerm::on_clicked_btnOpen));
    m_boxButton.add(m_btnOpen);

    m_btnSend.set_label("Send");
    m_btnSend.signal_clicked().connect(sigc::mem_fun(*this,
    &GtkSerTerm::on_clicked_btnSend));
    m_boxButton.add(m_btnSend);

    m_txtSend.set_max_length(50);
    m_txtSend.set_text("help");
    m_boxButton.add(m_txtSend);
    // button open send

    // text receive
    m_buffTxtRx = Gtk::TextBuffer::create();
    m_winTxtRx.set_size_request(-1,425);
    m_winTxtRx.add(m_txtRx);
    m_txtRx.set_buffer(m_buffTxtRx);
    m_boxRx.pack_start(m_winTxtRx,Gtk::PACK_EXPAND_WIDGET);
    // text receive

    // statusbar
    std::string sttMsg = "Port: 8-N-1-'\\r'-";
    sttMsg += comport.GetPort();
    sttMsg += " [CLOSED]";
    m_statusbar.push(sttMsg);
    // statusbar

    // packing all
    m_Box.add(m_boxMenu);
    m_Box.add(m_boxButton);
    m_Box.add(m_boxRx);
    m_Box.add(m_statusbar);

    //timer
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &GtkSerTerm::onTimer),1);

    // show all widgets
    show_all_children();
}

GtkSerTerm::~GtkSerTerm(){}

void GtkSerTerm::on_action_file_quit(){
    hide();
    comport.Close();
}

void GtkSerTerm::on_action_help_about(){
    std::string strAbout = "Serial Communication! \n ";
    strAbout += "Author: Yan Naing Aye \n ";
    strAbout += "Web: https://github.com/yan9a/serial";

    Gtk::MessageDialog dlgAbout(*this,strAbout);
    dlgAbout.run();
}

void GtkSerTerm::onOpen(){
    if( comport.Open() ) {
        std::string strRx = "Error on Port ";
        strRx += comport.GetPort();
        strRx += "\n";

        auto iter = m_buffTxtRx->get_iter_at_offset(-1);
        m_buffTxtRx->insert(iter, strRx);

        std::string sttMsg = "Port: 8-N-1-'\\r'-";
        sttMsg += comport.GetPort();
        sttMsg += " [CLOSED]";
        m_statusbar.push(sttMsg);

        m_btnOpen.set_label("Open");
    }
    else{
        std::string strRx = "Success on Port ";
        strRx += comport.GetPort();
        strRx += "\n";

        auto iter = m_buffTxtRx->get_iter_at_offset(-1);
        m_buffTxtRx->insert(iter, strRx);

        std::string sttMsg = "Port: 8-N-1-'\\r'-";
        sttMsg += comport.GetPort();
        sttMsg += " [OPENED]";
        m_statusbar.push(sttMsg);

        m_btnOpen.set_label("Close");
    }
}

void GtkSerTerm::onClose(){
        comport.Close();

        std::string strRx = "Closing Port ";
        strRx += comport.GetPort();
        strRx += "\n";

        auto iter = m_buffTxtRx->get_iter_at_offset(-1);
        m_buffTxtRx->insert(iter, strRx);

        std::string sttMsg = "Port: 8-N-1-'\\r'-";
        sttMsg += comport.GetPort();
        sttMsg += " [CLOSED]";
        m_statusbar.push(sttMsg);

        m_btnOpen.set_label("Open");
}

void GtkSerTerm::on_clicked_btnOpen(){
    if(m_btnOpen.get_label()=="Open"){
        onOpen();
    }
    else if(m_btnOpen.get_label()=="Close"){
        onClose();
    }
}

void GtkSerTerm::on_action_edit_clear(){
    m_buffTxtRx->set_text("");
}

void GtkSerTerm::on_clicked_btnSend(){
    auto strReq = m_txtSend.get_text();
    strReq += "\r";
    auto buffer = strdup(Glib::locale_to_utf8(strReq).c_str() );

    if(comport.Write(buffer)){
        auto iter = m_buffTxtRx->get_iter_at_offset(-1);
        m_buffTxtRx->insert(iter,strReq);
    }
    else{
        auto iter = m_buffTxtRx->get_iter_at_offset(-1);
        m_buffTxtRx->insert(iter,"Write error.\n");

    }
}

bool GtkSerTerm::onTimer(){
    char ch; bool r;
    do {ch = comport.ReadChar(r); if (r) ProcessChar(ch);} while(r);

    return true;
}

void GtkSerTerm::ProcessChar(char ch){
    if(ch=='\n'){
        // ignore linefeed
    }
    else{
        // check if character is printable or white-space
        if(isprint(ch) || isspace(ch)){
            auto iter = m_buffTxtRx->get_iter_at_offset(-1);
            m_buffTxtRx->insert(iter,Glib::ustring(sizeof(char),ch));
        }
    }
}
