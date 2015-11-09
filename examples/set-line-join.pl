% PLcairo port of 'set line join' sample code at http://cairographics.org/samples/.
% The original C code snippets are considered to be part of the public domain.
% Keri Harris <keri.harris@gentoo.org>, 2015.



:- use_module(library(plgi)).
:- use_module(library(plcairo)).

:- plgi_use_namespace('Gtk').

on_draw_event(_DrawingArea, CairoContext, _UserData, false) :-
	cairo_set_line_width(CairoContext, 40.96),

	cairo_move_to(CairoContext, 76.8, 84.48),
	cairo_rel_line_to(CairoContext, 51.2, -51.2),
	cairo_rel_line_to(CairoContext, 51.2, 51.2),
	cairo_set_line_join(CairoContext, 'CAIRO_LINE_JOIN_MITER'),
	cairo_stroke(CairoContext),

	cairo_move_to(CairoContext, 76.8, 161.28),
	cairo_rel_line_to(CairoContext, 51.2, -51.2),
	cairo_rel_line_to(CairoContext, 51.2, 51.2),
	cairo_set_line_join(CairoContext, 'CAIRO_LINE_JOIN_BEVEL'),
	cairo_stroke(CairoContext),

	cairo_move_to(CairoContext, 76.8, 238.08),
	cairo_rel_line_to(CairoContext, 51.2, -51.2),
	cairo_rel_line_to(CairoContext, 51.2, 51.2),
	cairo_set_line_join(CairoContext, 'CAIRO_LINE_JOIN_ROUND'),
	cairo_stroke(CairoContext).

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'Set Line Join'),
	gtk_window_set_default_size(Window, 256, 256),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
