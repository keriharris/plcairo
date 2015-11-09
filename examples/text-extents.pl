% PLcairo port of 'text extents' sample code at http://cairographics.org/samples/.
% The original C code snippets are considered to be part of the public domain.
% Keri Harris <keri.harris@gentoo.org>, 2015.



:- use_module(library(plgi)).
:- use_module(library(plcairo)).

:- plgi_use_namespace('Gtk').

on_draw_event(_DrawingArea, CairoContext, _UserData, false) :-
	Text = 'cairo',

	cairo_select_font_face(CairoContext, 'Sans', 'CAIRO_FONT_SLANT_NORMAL', 'CAIRO_FONT_WEIGHT_NORMAL'),
	cairo_set_font_size(CairoContext, 100.0),
	cairo_text_extents(CairoContext, Text, Extents),
	plgi_struct_get_field(Extents, 'x_bearing', XBearing),
	plgi_struct_get_field(Extents, 'y_bearing', YBearing),
	plgi_struct_get_field(Extents, 'width', Width),
	plgi_struct_get_field(Extents, 'height', Height),

	X = 25.0,
	Y = 150.0,
	X1 = Width,
	Y1 is -Height,
	X2 = XBearing,
	Y2 is -YBearing,

	cairo_move_to(CairoContext, X, Y),
	cairo_show_text(CairoContext, Text),

	Angle360 is 360.0 * pi/180.0,
	cairo_set_source_rgba(CairoContext, 1.0, 0.2, 0.2, 0.6),
	cairo_set_line_width(CairoContext, 6.0),
	cairo_arc(CairoContext, X, Y, 10.0, 0.0, Angle360),
	cairo_fill(CairoContext),
	cairo_move_to(CairoContext, X, Y),
	cairo_rel_line_to(CairoContext, 0.0, Y1),
	cairo_rel_line_to(CairoContext, X1, 0.0),
	cairo_rel_line_to(CairoContext, X2, Y2),
	cairo_stroke(CairoContext).

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'Text Extents'),
	gtk_window_set_default_size(Window, 256, 256),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
