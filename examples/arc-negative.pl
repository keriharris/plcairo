% PLcairo port of 'arc negative' sample code at http://cairographics.org/samples/.
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
	Angle45 is 45.0 * pi/180.0,
	Angle180 is pi,
	Angle360 is 2*pi,

	cairo_set_line_width(CairoContext, 10.0),
	cairo_arc_negative(CairoContext, XC, YC, 100.0, Angle45, Angle180),
	cairo_stroke(CairoContext),

	cairo_set_source_rgba(CairoContext, 1.0, 0.2, 0.2, 0.6),
	cairo_set_line_width(CairoContext, 6.0),

	cairo_arc(CairoContext, XC, YC, 10.0, 0.0, Angle360),
	cairo_fill(CairoContext),

	cairo_arc(CairoContext, XC, YC, 100.0, Angle45, Angle45),
	cairo_line_to(CairoContext, XC, YC),
	cairo_arc(CairoContext, XC, YC, 100.0, Angle180, Angle180),
	cairo_line_to(CairoContext, XC, YC),
	cairo_stroke(CairoContext).

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'Arc Negative'),
	gtk_window_set_default_size(Window, 256, 256),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
