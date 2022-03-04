#include "hello.h"

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Hello World")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello,"&Hello...\tCtrl-H","Hello Message");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("wxWidgets example");

    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnHello,this, ID_Hello);
}

void MyFrame::OnExit(wxCommandEvent &evt){
    Close(true);
}

void MyFrame::AllInfo(void){
    wxString strInfo = "";

    strInfo += "Informations:\n";
    strInfo += "\n";

    strInfo += wxVERSION_STRING;
    strInfo += "\n";

    strInfo += "GTK ";
    strInfo += wxString::Format(wxT("%i"),GTK_MAJOR_VERSION);
    strInfo += ".";
    strInfo += wxString::Format(wxT("%i"),GTK_MINOR_VERSION);
    strInfo += "\n";

    wxMessageBox(strInfo, "Information", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnAbout(wxCommandEvent &evt){
    AllInfo();
}

void MyFrame::OnHello(wxCommandEvent &evt){
    wxLogMessage("Hello world from wxWidgets!");
}

