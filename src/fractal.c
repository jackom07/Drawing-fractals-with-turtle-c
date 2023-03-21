#include "turtle.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#include <math.h>

#define PI 3.141

#define MAXCOUNT 30

//sierp start

/*
    Make turtle draw a triangle between points calculated by "triangle" function.
*/
void drawtriangle(SDL_Renderer* renderer, float x0, float y0, float x1, float y1, float x2, float y2)
{
    turtle_penDown();
    turtle_line(renderer, x0, y0, x1, y1);
    turtle_line(renderer, x1, y1, x2, y2);
    turtle_line(renderer, x2, y2, x0, y0);

}

/*
    Calculate points of the triangle according to length provided by user.
*/
void triangle(SDL_Renderer* renderer, float x, float y, float l)
{
    drawtriangle(renderer, x, y, x + l / 2, y - sin(PI / 3) * l, x + l, y);
}

/*
    Recursive function to draw the initial triangle, and then three smaller triangles with origins at the points of the traingle before.
*/
void triRec(SDL_Renderer* renderer, float x, float y, float l, int depth, int max)
{
    if (depth == max)
    {
        triangle(renderer, x, y, l);
    }
    else
    {
        triRec(renderer, x, y, l / 2, depth + 1, max);
        triRec(renderer, x + l / 2, y, l / 2, depth + 1, max);
        triRec(renderer, x + l / 4, y - sin(PI / 3) * l / 2, l / 2, depth + 1, max);
    }
}

/*
    Final sierpinski function that passes the depth and initial side length specified by user.
*/
void sierpinski(SDL_Renderer* renderer, float x, float y, float size, int depth)
{
    turtle_penDown();
    triRec(renderer, x, y, size, 1, depth);
    turtle_penUp();
}
//sierp end

//tree start

void tree(SDL_Renderer* renderer, float size, float max)
{
    if (size <= max)
    {
        return;
    }
    else
    {
        //algorithm to draw tree based on source code from
        //https://pythonguides.com/fractal-python-turtle/
        turtle_forward(renderer, size);
        turtle_left(30);
        tree(renderer, size * 0.75, max);
        turtle_right(60);
        tree(renderer, size * 0.75, max);
        turtle_left(30);
        turtle_backward(renderer, size);
    }
}

/*
    'drawTree' function sets the turtles orientation to upwards and puts the pen down. It then creates the variable max which
    is initial size / the specified depth - 1. This max value is what is passed back to the 'tree' function and becomes the
    terminating condition. Finally, raises pen.
*/

void drawTree(SDL_Renderer* renderer, float size, int depth)
{
    turtle_heading(270);
    turtle_penDown();
    float max;
    max = size / depth - 1;

    tree(renderer, size, max);
    turtle_penUp();
}

//tree end

//koch curve snowflake start

void koch(SDL_Renderer* renderer, float size, int depth, int max)
{
    if (depth == max)
    {
        turtle_forward(renderer, size);
    }
    else
    {
        koch(renderer, size / 3, depth + 1, max);
        turtle_left(-60);
        koch(renderer, size / 3, depth + 1, max);
        turtle_right(-120);
        koch(renderer, size / 3, depth + 1, max);
        turtle_left(-60);
        koch(renderer, size / 3, depth + 1, max);
    }
}

/*
    'drawKoch' function sets the turtles orientation to right and puts the pen down. Starting from the first iteration,
    the depth the user enters is the terminating condition. It also uses a four loop to then draw another koch curve at
    the end of the each one at a different orientation to create the 'snowflake'.
*/

void drawKoch(SDL_Renderer* renderer, float size, int depth)
{
    turtle_heading(180);
    turtle_penDown();


    for (int i = 0; i <= 6; i++)
    {
        koch(renderer, size, 1, depth);
        turtle_left(60);
    }
    turtle_penUp();
}

//koch curve snowflake end