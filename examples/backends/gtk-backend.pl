% Example of using PLcairo's Gtk+ Backend.
% Copyright (C) GNU Free Documentation License 1.3
% Keri Harris <keri.harris@gentoo.org>, 2015.



:- use_module(library(plgi)).
:- use_module(library(plcairo)).

:- plgi_use_namespace('Gtk').

on_draw_event(_DrawingArea, CairoContext, _UserData, false) :-
	cairo_set_source_rgb(CairoContext, 0, 0, 0),
	cairo_select_font_face(CairoContext, 'Sans', 'CAIRO_FONT_SLANT_NORMAL', 'CAIRO_FONT_WEIGHT_NORMAL'),
	cairo_set_font_size(CairoContext, 40.0),

	cairo_move_to(CairoContext, 10.0, 50.0),
	cairo_show_text(CairoContext, 'SWI-Prolog').

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'GTK Window'),
	gtk_window_set_default_size(Window, 250, 70),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
