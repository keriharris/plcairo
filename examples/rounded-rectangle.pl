% PLcairo port of 'rounded rectangle' sample code at http://cairographics.org/samples/.
% The original C code snippets are considered to be part of the public domain.
% Keri Harris <keri.harris@gentoo.org>, 2015.



:- use_module(library(plgi)).
:- use_module(library(plcairo)).

:- plgi_use_namespace('Gtk').

on_draw_event(_DrawingArea, CairoContext, _UserData, false) :-
	X = 25.6,
	Y = 25.6,
	Width = 204.8,
	Height = 204.8,
	Aspect = 1.0,
	CornerRadius is Height / 10.0,

	Radius is CornerRadius / Aspect,
	Angle0 = 0.0,
	Angle90 is 90.0 * pi/180.0,
	Angle180 is 180.0 * pi/180.0,
	Angle270 is 270.0 * pi/180.0,
	AngleNeg90 is -90.0 * pi/180.0,

	X0 is X + Width - Radius,
	Y0 is Y + Radius,
	X1 is X + Radius,
	Y1 is Y + Height - Radius,

	cairo_new_sub_path(CairoContext),
	cairo_arc(CairoContext, X0, Y0, Radius, AngleNeg90, Angle0),
	cairo_arc(CairoContext, X0, Y1, Radius, Angle0, Angle90),
	cairo_arc(CairoContext, X1, Y1, Radius, Angle90, Angle180),
	cairo_arc(CairoContext, X1, Y0, Radius, Angle180, Angle270),
	cairo_close_path(CairoContext),

	cairo_set_source_rgb(CairoContext, 0.5, 0.5, 1.0),
	cairo_fill_preserve(CairoContext),
	cairo_set_source_rgba(CairoContext, 0.5, 0.0, 0.0, 0.5),
	cairo_set_line_width(CairoContext, 10.0),
	cairo_stroke(CairoContext).

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'Rounded Rectangle'),
	gtk_window_set_default_size(Window, 256, 256),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
