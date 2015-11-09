% PLcairo port of 'dash' sample code at http://cairographics.org/samples/.
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

	X0 = XC, Y0 is YC-102.4,
	X1 is XC+102.4, Y1 is YC+102.4,
	XR is XC-76.8,

	cairo_set_dash(CairoContext, [50.0, 10.0, 10.0, 10.0], -50.0),
	cairo_set_line_width(CairoContext, 10.0),

	cairo_move_to(CairoContext, X0, Y0),
	cairo_line_to(CairoContext, X1, Y1),
	cairo_rel_line_to(CairoContext, -102.4, 0.0),
	cairo_curve_to(CairoContext, XR, Y1, XR, YC, XC, YC),

	cairo_stroke(CairoContext).

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'Dash'),
	gtk_window_set_default_size(Window, 256, 256),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
