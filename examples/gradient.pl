% PLcairo port of 'gradient' sample code at http://cairographics.org/samples/.
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
	Angle360 is 2*pi,

	X1 is XC-128.0, Y1 is YC-128.0,
	cairo_pattern_create_linear(0.0, 0.0, 0.0, 256.0, Pattern1),
	cairo_pattern_add_color_stop_rgba(Pattern1, 1.0, 0.0, 0.0, 0.0, 1.0),
	cairo_pattern_add_color_stop_rgba(Pattern1, 0.0, 1.0, 1.0, 1.0, 1.0),
	cairo_rectangle(CairoContext, X1, Y1, 256, 256),
	cairo_set_source(CairoContext, Pattern1),
	cairo_fill(CairoContext),

	CX0 is XC-12.8, CY0 is YC-25.6,
	CX1 is XC-25.6, CY1 is YC-25.6,
	cairo_pattern_create_radial(CX0, CY0, 25.6, CX1, CY1, 128.0, Pattern2),
	cairo_pattern_add_color_stop_rgba(Pattern2, 0.0, 1.0, 1.0, 1.0, 1.0),
	cairo_pattern_add_color_stop_rgba(Pattern2, 1.0, 0.0, 0.0, 0.0, 1.0),
	cairo_set_source(CairoContext, Pattern2),
	cairo_arc(CairoContext, XC, YC, 76.8, 0.0, Angle360),
	cairo_fill(CairoContext).

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'Gradient'),
	gtk_window_set_default_size(Window, 256, 256),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
