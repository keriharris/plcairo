% Example of using PLcairo's PNG Backend.
% Copyright (C) GNU Free Documentation License 1.3
% Keri Harris <keri.harris@gentoo.org>, 2015.



:- use_module(library(plcairo)).

main :-
	cairo_image_surface_create('CAIRO_FORMAT_ARGB32', 250, 70, Surface),
	cairo_create(Surface, CairoContext),

	cairo_set_source_rgb(CairoContext, 0, 0, 0),
	cairo_select_font_face(CairoContext, 'Sans', 'CAIRO_FONT_SLANT_NORMAL', 'CAIRO_FONT_WEIGHT_NORMAL'),
	cairo_set_font_size(CairoContext, 40.0),

	cairo_move_to(CairoContext, 10.0, 50.0),
	cairo_show_text(CairoContext, 'SWI-Prolog'),

	cairo_surface_write_to_png(Surface, '/tmp/plcairo-image.png'),
	format('/tmp/plcairo-image.png created~n', []),
	halt.

:- main.
