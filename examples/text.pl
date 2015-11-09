% PLcairo port of 'text' sample code at http://cairographics.org/samples/.
% The original C code snippets are considered to be part of the public domain.
% Keri Harris <keri.harris@gentoo.org>, 2015.



:- use_module(library(plgi)).
:- use_module(library(plcairo)).

:- plgi_use_namespace('Gtk').

on_draw_event(_DrawingArea, CairoContext, _UserData, false) :-
	cairo_select_font_face(CairoContext, 'Sans', 'CAIRO_FONT_SLANT_NORMAL', 'CAIRO_FONT_WEIGHT_BOLD'),
	cairo_set_font_size(CairoContext, 90.0),

	cairo_move_to(CairoContext, 10.0, 135.0),
	cairo_show_text(CairoContext, 'Hello'),

	cairo_move_to(CairoContext, 70.0, 165.0),
	cairo_text_path(CairoContext, 'void'),
	cairo_set_source_rgb(CairoContext, 0.5, 0.5, 1.0),
	cairo_fill_preserve(CairoContext),
	cairo_set_source_rgb(CairoContext, 0.0, 0.0, 0.0),
	cairo_set_line_width(CairoContext, 2.56),
	cairo_stroke(CairoContext),

	Angle360 is 360.0 * pi/180.0,
	cairo_set_source_rgba(CairoContext, 1.0, 0.2, 0.2, 0.6),
	cairo_arc(CairoContext, 10.0, 135.0, 5.12, 0.0, Angle360),
	cairo_close_path(CairoContext),
	cairo_arc(CairoContext, 70.0, 165.0, 5.12, 0.0, Angle360),
	cairo_fill(CairoContext).

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'Text'),
	gtk_window_set_default_size(Window, 256, 256),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
