


#define DRAW_BLACK(cr)   cairo_set_source_rgb(cr,0,0,0)
#define DRAW_WHITE(cr)   cairo_set_source_rgb(cr,1,1,1)


#include <cairo/cairo-svg.h>
#include <stdio.h>
#include <math.h>

//----------------------------------------------------------------------------------------
int main(int argc, char **argv) 
{
    cairo_surface_t *surface = cairo_svg_surface_create("terminal.svg", 100.0, 100.0);
    cairo_t *cr = cairo_create(surface);

    DRAW_BLACK(cr);
    cairo_rectangle(cr,0,0,100,100);
    cairo_fill(cr);

    DRAW_WHITE(cr);

    cairo_select_font_face(cr,"monospace",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr,48);
    cairo_move_to(cr,7,55);
    cairo_show_text(cr,"CCC");

    cairo_move_to(cr,0,75);
    cairo_line_to(cr,100,75);
    cairo_set_line_width(cr,15);
    cairo_stroke(cr);


    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}

//----------------------------------------------------------------------------------------
