#ifndef _APP_H_
#define _APP_H_

#include <wx/wx.h>
#include <wx/versioninfo.h>
#include <gtk/gtk.h>

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

#endif
