/**
 * @file wxSerial.cpp
 * @brief wxWidget Serial example
 *
 * @details Original works and credits: https://github.com/yan9a/serial
 *
 * @addtogroup WX
 * @{
 */

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "ceSerial.h"

class MyApp: public wxApp {
    public:
        virtual bool OnInit();
};

class MyFrame: public wxFrame {
public:
    MyFrame (const wxString &title);
    wxButton* btnSend;
    wxButton* btnOpen;
    wxTextCtrl* txtSend;
    wxTextCtrl* txtSelPort;
    wxTextCtrl* txtSetBaud;
    wxTimer m_timer;
    wxTextCtrl* txtRx;
    ceSerial comport;

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnOpen(void);
    void OnClose(void);
    void OnBtnOpen(wxCommandEvent& event);
    void SelPort(void);
    void SetBaud(void);
    void OnSend(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void ProcessChar(char ch);
    void ClearText(wxCommandEvent& event);
};

const int ID_BTNSEND = 101;
const int ID_BTNOPEN = 102;
const int ID_TXTSEND = 103;
const int ID_BAUDRATE = 104;
const int ID_TIMER = 105;
const int ID_TXTRX = 106;
const int ID_SELPORT = 107;

enum {
    Button_Send = ID_BTNSEND,
    Button_Open = ID_BTNOPEN,
    Txt_Send = ID_TXTSEND,
    Serial_Baud = ID_BAUDRATE,
    Tmr_Data = ID_TIMER,
    Txt_Rx =ID_TXTRX,
    Serial_Port = ID_SELPORT,
    Txt_Clear = wxID_CLEAR,
    Minimal_Quit = wxID_EXIT,
    Minimal_About = wxID_ABOUT
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit(){
    if(!wxApp::OnInit()) return false;

    MyFrame *frame = new MyFrame(wxT("Serial Port (wxWidget)"));
    frame->Show(true);

    return true;
}

MyFrame::MyFrame(const wxString &title)
    :wxFrame(NULL, wxID_ANY, title,wxDefaultPosition,wxSize(390, 500), wxDEFAULT_FRAME_STYLE ^ wxRESIZE_BORDER),m_timer(this, ID_TIMER)
{
    wxMenu *fileMenu = new wxMenu;
    wxMenu *editMenu = new wxMenu;
    wxMenu *helpMenu = new wxMenu;

    fileMenu->Append(Minimal_Quit,wxT("&Quit"),wxT("Quit Program"));
    editMenu->Append(Txt_Clear,wxT("C&lear"),wxT("Clear Console Text"));
    helpMenu->Append(Minimal_About,wxT("&About"),wxT("Show about Message"));

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(editMenu, wxT("&Edit"));
    menuBar->Append(helpMenu, wxT("&Help"));
    SetMenuBar(menuBar);

    CreateStatusBar(1);
    wxString strStatusBar = wxString::Format(wxT("Port: 8-N-1-'\\r'-%s [CLOSED]"),comport.GetPort());
    SetStatusText(strStatusBar);

    btnOpen = new wxButton(this,Button_Open,wxT("&Open"),wxPoint(5,5),wxSize(75,25));
    btnSend = new wxButton(this,Button_Send,wxT("&Send"),wxPoint(85, 5),wxSize(75, 25));
    txtSend = new wxTextCtrl(this,Txt_Send,wxT("help"),wxPoint(165,5),wxSize(215,25));
    txtSetBaud = new wxTextCtrl(this,Serial_Baud,wxT("9600"),wxPoint(5,35),wxSize(155,25));
    txtSelPort = new wxTextCtrl(this,Serial_Port,wxT("/dev/ttyUSB0"),wxPoint(165,35),wxSize(215,25));
    txtRx = new wxTextCtrl(this, Txt_Rx, wxT(""), wxPoint(5, 65), wxSize(375, 360), wxTE_MULTILINE | wxTE_READONLY);

    Connect(Minimal_Quit,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::OnQuit));
    Connect(Minimal_About,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::OnAbout));

    Connect(Txt_Clear, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::ClearText));
    Connect(Button_Open, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MyFrame::OnBtnOpen));
    Connect(Button_Send, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MyFrame::OnSend));
    Connect(Tmr_Data,wxEVT_TIMER,wxTimerEventHandler(MyFrame::OnTimer));

    m_timer.Start(1);
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event)){
    comport.Close();
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event)){
    wxMessageBox(wxString::Format(
        wxT("Serial Communication! \n ")
        wxT("Author: Yan Naing Aye \n ")
        wxT("Web: https://github.com/yan9a/serial")),
        wxT("About Serial Comm"),
        wxOK | wxICON_INFORMATION,
        this);
}

void MyFrame::OnOpen(void){
   SelPort();
   SetBaud();

   if(comport.Open()){
       txtRx->AppendText(wxString::Format(wxT("Error on port %s\n"),comport.GetPort()));

       wxString strStatusBar = wxString::Format(wxT("Port: 8-N-1-'\\r'-%s [CLOSED]"),comport.GetPort());
       SetStatusText(strStatusBar);
       btnOpen->SetLabelText(wxT("Open"));
   }
   else {
       txtRx->AppendText(wxString::Format(wxT("Success on port %s\n"),comport.GetPort()));

       wxString strStatusBar = wxString::Format(wxT("Port: 8-N-1-'\\r'-%s [OPENED]"),comport.GetPort());
       SetStatusText(strStatusBar);
       btnOpen->SetLabelText(wxT("Close"));
   }
}

void MyFrame::OnClose(void){
    comport.Close();
    wxString strStatusBar = wxString::Format(wxT("Port: 8-N-1-'\\r'-%s [CLOSED]"),comport.GetPort());
    SetStatusText(strStatusBar);
    btnOpen->SetLabelText(wxT("Open"));
    txtRx->AppendText(wxString::Format(wxT("Port %s is closed.\n"), comport.GetPort()));
}

void MyFrame::OnBtnOpen(wxCommandEvent& WXUNUSED(event)){
    if(btnOpen->GetLabelText()=="Open"){
        OnOpen();
    }
    else if(btnOpen->GetLabelText()=="Close"){
        OnClose();
    }
}

void MyFrame::SelPort(void){
    if (comport.IsOpened()) {
        txtRx->AppendText(wxString::Format(wxT("Close Port %s first.\n"), comport.GetPort()));
    }
    else {
        wxString device = txtSelPort->GetValue();
        std::string str = device.Trim().ToStdString();
        if (str.length() > 0) {
#ifdef ceWINDOWS
        comport.SetPortWin(str);
#else
        comport.SetPort(str);
#endif
        }
        txtRx->AppendText(wxString::Format(wxT("Port: %s\n"), comport.GetPort()));
    }
}

void MyFrame::SetBaud(void){
    if (comport.IsOpened()) {
        txtRx->AppendText(wxString::Format(wxT("Close port %s first.\n"), comport.GetPort()));
    }
    else {
        wxString baud = txtSetBaud->GetValue();
        long n = wxAtol(baud.Trim());
        if (n >= 0) {
            comport.SetBaudRate(n);
        }
        txtRx->AppendText(wxString::Format(wxT("Baud rate: %ld\n"), comport.GetBaudRate()));
    }
}

void MyFrame::ClearText(wxCommandEvent& WXUNUSED(event)){
    txtRx->Clear();
}

void MyFrame::OnSend(wxCommandEvent& WXUNUSED(event)){
    wxString strReq = txtSend->GetValue();
    strReq += wxString::Format("\r");
    wxCharBuffer buffer = strReq.ToUTF8();

    if (comport.Write(buffer.data())) {
        txtRx->AppendText(strReq);
    }
    else {
        txtRx->AppendText(wxT("Write error.\n"));
    }
}

void MyFrame::OnTimer(wxTimerEvent& WXUNUSED(event)){
    char ch; bool r;
    do {ch = comport.ReadChar(r);if (r) ProcessChar(ch);} while (r);
}

void MyFrame::ProcessChar(char ch){
    if(ch=='\n'){
        // ignore linefeed
    }
    else{
        // check if character is printable or white-space
        if(isprint(ch) || isspace(ch))
            txtRx->AppendText(wxString::Format(wxT("%c"), ch));
    }
}

/** @} */

