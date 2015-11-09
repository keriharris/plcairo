% PLcairo port of 'multi segment caps' sample code at http://cairographics.org/samples/.
% The original C code snippets are considered to be part of the public domain.
% Keri Harris <keri.harris@gentoo.org>, 2015.



:- use_module(library(plgi)).
:- use_module(library(plcairo)).

:- plgi_use_namespace('Gtk').

on_draw_event(_DrawingArea, CairoContext, _UserData, false) :-
	cairo_move_to(CairoContext, 50.0, 75.0),
	cairo_line_to(CairoContext, 200.0, 75.0),

	cairo_move_to(CairoContext, 50.0, 125.0),
	cairo_line_to(CairoContext, 200.0, 125.0),

	cairo_move_to(CairoContext, 50.0, 175.0),
	cairo_line_to(CairoContext, 200.0, 175.0),

	cairo_set_line_width(CairoContext, 30.0),
	cairo_set_line_cap(CairoContext, 'CAIRO_LINE_CAP_ROUND'),
	cairo_stroke(CairoContext).

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'Multi Segment Caps'),
	gtk_window_set_default_size(Window, 256, 256),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
