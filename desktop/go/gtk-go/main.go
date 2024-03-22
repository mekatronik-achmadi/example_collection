// Package main provides ...
package main

import (
	"os"

	"github.com/gotk3/gotk3/glib"
	"github.com/gotk3/gotk3/gtk"
)

const appID = "gotk3.glade.template"

func main() {
    app,_ := gtk.ApplicationNew(appID,glib.APPLICATION_FLAGS_NONE)

    app.Connect("activate", func() {
        builder,_ := gtk.BuilderNewFromFile("main.glade")

        objWnd,_ := builder.GetObject("mWnd")
        wnd := objWnd.(*gtk.Window)

        /*signals := map[string]interface{}{*/
            /*"mBtnQuit_clicked_cb" : wnd.Close,*/
            /*"mBtnMsg_clicked_cb" : msg,*/
        /*}*/
        /*builder.ConnectSignals(signals)*/

        objBtnMsg,_ := builder.GetObject("mBtnMsg")
        btnMsg := objBtnMsg.(*gtk.Button)
        btnMsg.Connect("clicked",btnMsg_clicked)

        objBtnQuit,_ := builder.GetObject("mBtnQuit")
        btnQuit := objBtnQuit.(*gtk.Button)
        btnQuit.Connect("clicked",wnd.Close)

        wnd.SetDefaultSize(200,100)
        wnd.Show()

        app.AddWindow(wnd)
    })

    os.Exit(app.Run(os.Args))
}

func btnMsg_clicked() {
    dialog := gtk.MessageDialogNew(nil,
        gtk.DIALOG_MODAL,
        gtk.MESSAGE_INFO,
        gtk.BUTTONS_OK, "Template GTK3 GO")

    dialog.Run()
    dialog.Destroy()
}

