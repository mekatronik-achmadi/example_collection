#include "gui.h"

static void onBtnOpen(Fl_Widget *w, void *p){
    ((Gui*)p)->portOpen();
}

static void onBtnSend(Fl_Widget *w, void *p){
    std::cout <<  ((Fl_Input*)p)->value() << std::endl;
}

static void onBtnClear(Fl_Widget *w, void *p){
    ((Gui*)p)->bufOutput->text("");
}

static void onBtnQuit(Fl_Widget *w, void *p){
    ((Gui*)p)->close();
}

static void onSerialTimer(void *p){
    char ch; bool r;

    if(((Gui*)p)->comPort.IsOpened()){
        do {
            ch = ((Gui*)p)->comPort.ReadChar(r);
            if(r) ((Gui*)p)->serialChar(ch);
        } while(r);
    }

    Fl::repeat_timeout(0.01, onSerialTimer,p);
}


Gui::Gui() {
    mainWnd = new Fl_Window(380,500, "FLTK Serial");

    btnOpen = new Fl_Button(5,10,85,20,"Open");
    btnSend = new Fl_Button(95,10,85,20,"Send");
    btnClr  = new Fl_Button(5,35,85,20, "Clear");
    btnQuit = new Fl_Button(95,35,85,20, "Quit");

    txtSend = new Fl_Input(185,10,190,20);
    txtPort = new Fl_Input(185,35,95,20);
    cmbBaud = new Fl_Choice(285,35,90,20);

    txtOutput = new Fl_Text_Display(5, 65,370,400);
    statusBar = new Fl_Box(5,475,370,20);

    bufOutput = new Fl_Text_Buffer();
    txtOutput->buffer(bufOutput);
    bufOutput->text("");

    statusBar->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    status("Ready");

    btnSend->callback(onBtnSend,txtSend);
    btnOpen->callback(onBtnOpen,this);
    btnClr->callback(onBtnClear,this);
    btnQuit->callback(onBtnQuit,this);

    sttOpen = false;

    cmbBaud->add("9600");
    cmbBaud->add("38400");
    cmbBaud->add("57600");
    cmbBaud->add("74880");
    cmbBaud->add("115200");
    cmbBaud->value(0);

    txtPort->insert("/dev/ttyUSB0");

#ifdef ceWINDOWS
    comPort.SetPort("\\\\.\\COM1");
#else
	comPort.SetPort("/dev/ttyUSB0");
#endif

    Fl::add_timeout(0.01, onSerialTimer,this);

    Fl::scheme("gtk+");
    mainWnd->end();
}

void Gui::portOpen(){
    if(sttOpen){
        if(comPort.IsOpened()) {
            comPort.Close();
            btnOpen->label("Open");
            sttOpen = false;

        }
    }
    else {
        if(comPort.IsOpened()) return;
        if(std::string(txtPort->value()).length()<3) return;

        long vBaud = 9600;
        switch(cmbBaud->value()){
            case 0: vBaud = 9600; break;
            case 1: vBaud = 38400; break;
            case 2: vBaud = 57600; break;
            case 3: vBaud = 74880; break;
            case 4: vBaud = 115200; break;
        }

        comPort.SetBaudRate(115200);
        comPort.SetPort(std::string(txtPort->value()));

        if(comPort.Open()){
            btnOpen->label("Close");
            sttOpen = true;

            status("Open Port: " +
                    std::string(txtPort->value()) +
                    "-" +
                    std::to_string(vBaud));
        }
        else {
            btnOpen->label("Open");
            sttOpen = false;

            status("Failed Port: " +
                    std::string(txtPort->value()) +
                    "-" +
                    std::to_string(vBaud));

        }
    }
}

void Gui::serialChar(char ch){
    if(ch=='\n'){}
    else{
        if(isprint(ch) || isspace(ch))
            bufOutput->append(&ch);
    }
}

void Gui::status(std::string msg){
    statusBar->copy_label(msg.c_str());
    statusBar->redraw();
}

void Gui::show(int argc, char* argv[]){
    mainWnd->show(argc,argv);
}

void Gui::close(){
    if(comPort.IsOpened()) comPort.Close();
    mainWnd->hide();
}

