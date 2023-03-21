#include "turtle.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#include <math.h>

#define ABS(X) ((X)>0 ? (X) : (-(X)))

#define PI 3.141

typedef struct RGB_Col
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
} RGB_Col;

typedef struct turtle_t
{
    double  x0;
    double  y0;
    double  heading;

    RGB_Col  colour;
    bool   pendown;
} turtle_t;

turtle_t turtle;
turtle_t turtle2;

void turtle_reset(SDL_Renderer* renderer)
{
    turtle.x0 = 400;
    turtle.y0 = 400;

    turtle.heading = 0;

    turtle.colour.r = 255;
    turtle.colour.g = 0;
    turtle.colour.b = 0;

    SDL_SetRenderDrawColor(renderer, turtle.colour.r,
        turtle.colour.g,
        turtle.colour.b, 255);

    turtle.pendown = true;

}

void turtle_penUp()
{
    turtle.pendown = false;
}

void turtle_penDown()
{
    turtle.pendown = true;
}

void turtle_colour(SDL_Renderer* renderer, int r, int g, int b)
{
    turtle.colour.r = r;
    turtle.colour.g = g;
    turtle.colour.b = b;

    SDL_SetRenderDrawColor(renderer, turtle.colour.r,
        turtle.colour.g,
        turtle.colour.b, 255);

}

void turtle_save()
{
    turtle2 = turtle;
}

void turtle_load()
{
    turtle = turtle2;
}

double turtle_getX()
{
    return turtle.x0;
}

double turtle_getY()
{
    return turtle.y0;
}

void turtle_forward(SDL_Renderer* renderer, int pixels)
{
    double radians = turtle.heading * PI / 180.0;
    double x1 = cos(radians) * pixels;
    double y1 = sin(radians) * pixels;

    turtle_goto(renderer, turtle.x0 + x1, turtle.y0 + y1);
}

void turtle_backward(SDL_Renderer* renderer, int pixels)
{
    turtle_forward(renderer, -pixels);
}

void turtle_left(double angle)
{
    turtle.heading += angle;

    if (turtle.heading < 0.0)
    {
        turtle.heading += 360.0;
    }
    else if (turtle.heading >= 360.0)
    {
        turtle.heading -= 360.0;
    }
}

void turtle_right(double angle)
{
    turtle_left(-angle);
}

void turtle_heading(double angle)
{
    turtle.heading = angle;
}

void turtle_goto(SDL_Renderer* renderer, double x1, double y1)
{
    if (turtle.pendown)
    {
        turtle_line(renderer,
            (int)round(turtle.x0),
            (int)round(turtle.y0),
            (int)round(x1), (int)round(y1));
    }

    turtle.x0 = (double)x1;
    turtle.y0 = (double)y1;

}

/*
    Implementation of Bresenhams line algorithm based of code by Mike Lam starts here.
*/
void turtle_line(SDL_Renderer* renderer, int x0, int y0, int x1, int y1)
{
    // uses a variant of Bresenham's line algorithm:
    //   https://en.wikipedia.org/wiki/Talk:Bresenham%27s_line_algorithm

    int dx = ABS(x1 - x0);          // absolute value of coordinate distances
    int dy = ABS(y1 - y0);
    int offX = x0 < x1 ? 1 : -1;      // line-drawing direction offsets
    int offY = y0 < y1 ? 1 : -1;
    int x = x0;                     // incremental location
    int y = y0;
    int err;

    turtle_pixel(renderer, x, y);
    if (dx > dy)
    {
        err = dx / 2;
        while (x != x1)
        {
            err = err - dy;
            if (err < 0)
            {
                y += offY;
                err += dx;
            }
            x += offX;
            turtle_pixel(renderer, x, y);
        }
    }
    else
    {
        err = dy / 2;
        while (y != y1)
        {
            err = err - dx;
            if (err < 0)
            {
                x += offX;
                err += dy;
            }
            y += offY;
            turtle_pixel(renderer, x, y);
        }
    }
}
/*
    Implementation of Bresenhams line algorithm based of code by Mike Lam ends here.
*/

void turtle_pixel(SDL_Renderer* renderer, int x, int y)
{
    SDL_RenderDrawPoint(renderer, x, y);
}