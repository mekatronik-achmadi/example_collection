extern crate fltk;

use fltk::{app, prelude::*, window::Window, button::Button, frame::Frame, dialog};

fn main() {
    let app = app::App::default().with_scheme(app::Scheme::Gtk);
    let mut wind = Window::new(100,100,200,100,"FLTK Rust");
    let _lbl_app = Frame::new(0,0,200,30,"FLTK Rust");
    let mut btn_msg = Button::new(0,30,200,30,"Message");
    let mut btn_quit = Button::new(0,70,200,30, "Quit");

    wind.end();
    wind.show();

    btn_msg.set_callback(move |_| {
        dialog::message_default( "Rust FLTK Template");
    });

    btn_quit.set_callback(move |_| {
        app::quit();
    });

    app.run().unwrap();
}
