% PLcairo port of 'curve rectangle' sample code at http://cairographics.org/samples/.
% The original C code snippets are considered to be part of the public domain.
% Keri Harris <keri.harris@gentoo.org>, 2015.



:- use_module(library(plgi)).
:- use_module(library(plcairo)).

:- plgi_use_namespace('Gtk').

on_draw_event(DrawingArea, CairoContext, _UserData, false) :-
	gtk_widget_get_allocated_width(DrawingArea, Width),
	gtk_widget_get_allocated_height(DrawingArea, Height),

	RectWidth is Width-25.6*2, RectHeight is Height-25.6*2,
	Radius = 102.4,
	X0 = 25.6, Y0 = 25.6,
	XR0 is X0+Radius, YR0 is Y0+Radius,
	X1 is Width-X0, Y1 is Height-Y0,
	XR1 is X1-Radius, YR1 is Y1-Radius,
	XC is Width/2,
	YC is Height/2,

	(   RectWidth/2 < Radius
	->  (   RectHeight/2 < Radius
	    ->  cairo_move_to(CairoContext, X0, YC),
	        cairo_curve_to(CairoContext, X0, Y0, X0, Y0, XC, Y0),
	        cairo_curve_to(CairoContext, X1, Y0, X1, Y0, X1, YC),
	        cairo_curve_to(CairoContext, X1, Y1, X1, Y1, XC, Y1),
	        cairo_curve_to(CairoContext, X0, Y1, X0, Y1, X0, YC)
	    ;   cairo_move_to(CairoContext, X0, YR0),
	        cairo_curve_to(CairoContext, X0, Y0, X0, Y0, XC, Y0),
	        cairo_curve_to(CairoContext, X1, Y0, X1, Y0, X1, YR0),
	        cairo_line_to(CairoContext, X1, YR1),
	        cairo_curve_to(CairoContext, X1, Y1, X1, Y1, XC, Y1),
	        cairo_curve_to(CairoContext, X0, Y1, X0, Y1, X0, YR1)
	    )
	;   (   RectHeight/2 < Radius
	    ->  cairo_move_to(CairoContext, X0, YC),
	        cairo_curve_to(CairoContext, X0, Y0, X0, Y0, XR0, Y0),
	        cairo_line_to(CairoContext, XR1, Y0),
	        cairo_curve_to(CairoContext, X1, Y0, X1, Y0, X1, YC),
	        cairo_curve_to(CairoContext, X1, Y1, X1, Y1, XR1, Y1),
	        cairo_line_to(CairoContext, XR0, Y1),
	        cairo_curve_to(CairoContext, X0, Y1, X0, Y1, X0, YC)
	    ;   cairo_move_to(CairoContext, X0, YR0),
	        cairo_curve_to(CairoContext, X0, Y0, X0, Y0, XR0, Y0),
	        cairo_line_to(CairoContext, XR1, Y0),
	        cairo_curve_to(CairoContext, X1, Y0, X1, Y0, X1, YR0),
	        cairo_line_to(CairoContext, X1, YR1),
	        cairo_curve_to(CairoContext, X1, Y1, X1, Y1, XR1, Y1),
	        cairo_line_to(CairoContext, XR0, Y1),
	        cairo_curve_to(CairoContext, X0, Y1, X0, Y1, X0, YR1)
	    )
	),

	cairo_close_path(CairoContext),

	cairo_set_source_rgb(CairoContext, 0.5, 0.5, 1.0),
	cairo_fill_preserve(CairoContext),
	cairo_set_source_rgba(CairoContext, 0.5, 0.0, 0.0, 0.5),
	cairo_set_line_width(CairoContext, 10.0),
	cairo_stroke(CairoContext).

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'Curve Rectangle'),
	gtk_window_set_default_size(Window, 256, 256),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
