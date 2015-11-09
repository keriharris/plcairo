% PLcairo port of 'curve to' sample code at http://cairographics.org/samples/.
% The original C code snippets are considered to be part of the public domain.
% Keri Harris <keri.harris@gentoo.org>, 2015.



:- use_module(library(plgi)).
:- use_module(library(plcairo)).

:- plgi_use_namespace('Gtk').

on_draw_event(DrawingArea, CairoContext, _UserData, false) :-
	gtk_widget_get_allocated_width(DrawingArea, Width),
	gtk_widget_get_allocated_height(DrawingArea, Height),

	XC is Width/2,
	YC is Height/2,

	X is XC-102.4, Y = YC,
	X1 is XC-25.6, Y1 is YC+102.4,
	X2 is XC+25.6, Y2 is YC-102.4,
	X3 is XC+102.4, Y3 = YC,

	cairo_move_to(CairoContext, X, Y),
	cairo_curve_to(CairoContext, X1, Y1, X2, Y2, X3, Y3),

	cairo_set_line_width(CairoContext, 10.0),
	cairo_stroke(CairoContext),

	cairo_set_source_rgba(CairoContext, 1.0, 0.2, 0.2, 0.6),
	cairo_set_line_width(CairoContext, 6.0),

	cairo_move_to(CairoContext, X, Y),
	cairo_line_to(CairoContext, X1, Y1),
	cairo_move_to(CairoContext, X2, Y2),
	cairo_line_to(CairoContext, X3, Y3),
	cairo_stroke(CairoContext).

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'Curve To'),
	gtk_window_set_default_size(Window, 256, 256),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
