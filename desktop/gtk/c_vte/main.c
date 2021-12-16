#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include <vte/vte.h>

static const GdkColor COLOR_BG = { 0, 0x0000, 0x0000, 0x0000 };
static const GdkColor COLOR_FG = { 0, 0xffff, 0xffff, 0xffff };
static const GdkColor COLOR_PALETTE[] =
{
    { 0, 0x0000, 0x0000, 0x0000 },
    { 0, 0xaaaa, 0x0000, 0x0000 },
    { 0, 0x0000, 0xaaaa, 0x0000 },
    { 0, 0xaaaa, 0x5555, 0x0000 },
    { 0, 0x0000, 0x0000, 0xaaaa },
    { 0, 0xaaaa, 0x0000, 0xaaaa },
    { 0, 0x0000, 0xaaaa, 0xaaaa },
    { 0, 0xaaaa, 0xaaaa, 0xaaaa },
    { 0, 0x5555, 0x5555, 0x5555 },
    { 0, 0xffff, 0x5555, 0x5555 },
    { 0, 0x5555, 0xffff, 0x5555 },
    { 0, 0xffff, 0xffff, 0x5555 },
    { 0, 0x5555, 0x5555, 0xffff },
    { 0, 0xffff, 0x5555, 0xffff },
    { 0, 0x5555, 0xffff, 0xffff },
    { 0, 0xffff, 0xffff, 0xffff },
};
#define COLOR_PALETTE_LENGTH 16

static gboolean handle_key_press (GtkWidget *widget, GdkEventKey *event, gpointer userdata){
    GtkWidget *vtterm = userdata;
    guint key = event->keyval;
    
    if (event->type != GDK_KEY_PRESS) {
        return FALSE;
    }
    
    if ((event->state & (GDK_CONTROL_MASK|GDK_SHIFT_MASK)) == (GDK_CONTROL_MASK|GDK_SHIFT_MASK)){
	    if (key == GDK_KEY_C) {
		    vte_terminal_copy_clipboard(VTE_TERMINAL(vtterm));
		    vte_terminal_copy_primary(VTE_TERMINAL (vtterm));
		    return TRUE;
	    }
	    if (key == GDK_KEY_V) {
		    vte_terminal_paste_clipboard(VTE_TERMINAL(vtterm));
		    return TRUE;
	    }
    }

    return FALSE;
}

static GtkWidget* create_vte(void){
    GtkWidget* vteterm;
    
    vteterm = vte_terminal_new();
    
    char *startterm[2]={0,0};
    startterm[0]=(char*)"/bin/bash";
    vte_terminal_fork_command_full(VTE_TERMINAL(VTE_TERMINAL(vteterm)),
				   VTE_PTY_DEFAULT,
				   NULL,
				   startterm,
				   NULL,
				   (GSpawnFlags)(G_SPAWN_DO_NOT_REAP_CHILD | G_SPAWN_SEARCH_PATH),
				   NULL,
				   NULL,
				   NULL,
				   NULL);

    vte_terminal_set_size(VTE_TERMINAL(vteterm),90,30);
    vte_terminal_set_allow_bold(VTE_TERMINAL(vteterm), TRUE);
    vte_terminal_set_font_from_string(VTE_TERMINAL(vteterm), "monospace 8");
    vte_terminal_set_colors(VTE_TERMINAL(vteterm), &COLOR_FG, &COLOR_BG, COLOR_PALETTE, COLOR_PALETTE_LENGTH);
    vte_terminal_set_color_bold(VTE_TERMINAL(vteterm), &COLOR_FG);
    
    return vteterm;
}

static GtkWidget* create_window (void){
	GtkWidget* window;
	GtkWidget* box;
	GtkWidget* vterm; 
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Simple Terminal Emulator");
	
	vterm = create_vte();
	
	box = gtk_hbox_new (TRUE, 2);
	gtk_box_pack_start (GTK_BOX (box), vterm, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (window), box);
	
	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect (window, "key-press-event", G_CALLBACK (handle_key_press), vterm);
	
	return window;
}

int main(int argc, char *argv[]){
	GtkWidget* gtk_win;
	
	gtk_init(&argc,&argv);
	
	gtk_win = create_window();

	gtk_widget_show_all(gtk_win);
	gtk_main();
	
	return 0;
}
