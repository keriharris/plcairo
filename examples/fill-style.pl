% PLcairo port of 'fill style' sample code at http://cairographics.org/samples/.
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
	Angle360N is -2*pi,

	cairo_set_line_width(CairoContext, 6.0),

	cairo_translate(CairoContext, 0, -128),

	X1 is XC-116, Y1 is YC+12,
	XR1 is XC-64, YR1 is YC+64,
	XR2 is XC+64, YR2 is YC+64,
	cairo_rectangle(CairoContext, X1, Y1, 232, 70),
	cairo_new_sub_path(CairoContext),
	cairo_arc(CairoContext, XR1, YR1, 40.0, 0.0, Angle360),
	cairo_new_sub_path(CairoContext),
	cairo_arc_negative(CairoContext, XR2, YR2, 40.0, 0.0, Angle360N),

	cairo_set_fill_rule(CairoContext, 'CAIRO_FILL_RULE_EVEN_ODD'),
	cairo_set_source_rgb(CairoContext, 0.0, 0.7, 0.0),
	cairo_fill_preserve(CairoContext),
	cairo_set_source_rgb(CairoContext, 0.0, 0.0, 0.0),
	cairo_stroke(CairoContext),

	cairo_translate(CairoContext, 0, 128),

	cairo_rectangle(CairoContext, X1, Y1, 232, 70),
	cairo_new_sub_path(CairoContext),
	cairo_arc(CairoContext, XR1, YR1, 40.0, 0.0, Angle360),
	cairo_new_sub_path(CairoContext),
	cairo_arc_negative(CairoContext, XR2, YR2, 40.0, 0.0, Angle360N),

	cairo_set_fill_rule(CairoContext, 'CAIRO_FILL_RULE_WINDING'),
	cairo_set_source_rgb(CairoContext, 0.0, 0.0, 0.9),
	cairo_fill_preserve(CairoContext),
	cairo_set_source_rgb(CairoContext, 0.0, 0.0, 0.0),
	cairo_stroke(CairoContext).

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'Fill Style'),
	gtk_window_set_default_size(Window, 256, 256),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
