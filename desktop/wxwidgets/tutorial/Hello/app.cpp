#include "app.h"
#include "hello.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit(){
    MyFrame *mainFrame = new MyFrame();
    mainFrame->SetSize(wxSize(240,240));
    mainFrame->Show();

    return true;
}
