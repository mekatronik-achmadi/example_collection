#ifndef _HELLO_H_
#define _HELLO_H_

#include <wx/wx.h>
#include <wx/versioninfo.h>
#include <gtk/gtk.h>

class MyFrame: public wxFrame
{
public:
    MyFrame();

private:
    void OnHello(wxCommandEvent &evt);
    void OnExit(wxCommandEvent &evt);
    void OnAbout(wxCommandEvent &evt);
    void AllInfo(void);
};

enum{
    ID_Hello = 1
};

#endif
