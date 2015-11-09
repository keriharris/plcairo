% PLcairo port of 'clip image' sample code at http://cairographics.org/samples/.
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

	cairo_arc(CairoContext, XC, YC, 76.8, 0.0, Angle360),
	cairo_clip(CairoContext),
	cairo_new_path(CairoContext),

	predicate_property(user:main, file(File)),
	file_directory_name(File, Directory),
	atom_concat(Directory, '/vermeer.png', ImageFile),

	cairo_image_surface_create_from_png(ImageFile, Image),
	cairo_image_surface_get_width(Image, ImageWidth),
	cairo_image_surface_get_height(Image, ImageHeight),

	SX is 256/ImageWidth,
	SY is 256/ImageHeight,
	cairo_scale(CairoContext, SX, SY),

	cairo_set_source_surface(CairoContext, Image, 0, 0),
	cairo_paint(CairoContext).

main :-
	gtk_window_new('GTK_WINDOW_TOPLEVEL', Window),
	gtk_window_set_title(Window, 'Clip Image'),
	gtk_window_set_default_size(Window, 256, 256),

	gtk_drawing_area_new(DrawingArea),
	gtk_container_add(Window, DrawingArea),
	g_signal_connect(DrawingArea, 'draw', on_draw_event/4, {null}, _),

	g_signal_connect(Window, 'destroy', gtk_main_quit/0, {null}, _),
	gtk_widget_show_all(Window),
	gtk_main,
	halt.

:- main.
