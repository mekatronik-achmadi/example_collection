int main(string[] args){
    Gtk.init(ref args);

    try{
        var builder = new Gtk.Builder();
        builder.add_from_file("main.glade");
        builder.connect_signals(null);

        var mWnd = builder.get_object("mWnd") as Gtk.Window;
        mWnd.set_default_size(200,100);
        mWnd.set_resizable(false);
        mWnd.show_all();

        Gtk.main();
    } catch (Error e){
        stderr.printf("Error %s\n",e.message);
        return 1;
    }

    return 0;
}

public void mBtnMsg_clicked_cb(Gtk.Button source){
    var msgbox = new Gtk.MessageDialog(null,
        Gtk.DialogFlags.MODAL,
        Gtk.MessageType.INFO,
        Gtk.ButtonsType.OK,
        "Template GTK Vala");

    msgbox.run();
    msgbox.destroy();
}

public void mBtnQuit_clicked_cb(Gtk.Button source){
    Gtk.main_quit();
}

