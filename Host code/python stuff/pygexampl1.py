#!/usr/bin/env python 
import Gtk
win = Gtk.Window() 
win.connect("delete-event", Gtk.main_quit) 
win.show_all() 
Gtk.main()

