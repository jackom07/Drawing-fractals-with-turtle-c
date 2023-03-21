#pragma once
#ifndef TURTLE_H

#include <SDL.h> 

/*
    Reset turtle to default values for location (400, 300), heading (0), colour (red) and pen status (down).
*/
void turtle_reset(SDL_Renderer* renderer);

/*
    Set the pen status to "up" (do not draw).
*/
void turtle_penUp();

/*
    Set the pen status to "down" (draw).
*/
void turtle_penDown();

/*
    Set colour of the line the turtle will draw. Alpha is default 255.
*/
void turtle_colour(SDL_Renderer* renderer, int r, int g, int b);

/*
    Saves current state of turtle. Position, heading, colour and pen status.
*/
void turtle_save();

/*
    Loads the instance of the turtle created with the save turtle function.
 */
void turtle_load();

/*
    Returns the x coordinate.
*/
double turtle_getX();

/*
    Returns the y coordinate.
*/
double turtle_getY();
/*
    Move the turtle forward by integer amount of pixels.
*/
void turtle_forward(SDL_Renderer* renderer, int pixels);

/*
    Move the turtle negative forwards.
*/
void turtle_backward(SDL_Renderer* renderer, int pixels);

/*
    Turn the turtle to the left by the specified number of degrees.
*/
void turtle_left(double angle);

/*
    Turn the turtle to the right by the specified number of degrees.
*/
void turtle_right(double angle);

/*
    Point turtle at specified heading.
*/
void turtle_heading(double angle);
/*
    Move the turtle to the specified coordinates.
*/
void turtle_goto(SDL_Renderer* renderer, double x, double y);

/*
    Draw a straight line between the given coordinates.
*/
void turtle_line(SDL_Renderer* renderer, int x0, int y0, int x1, int y1);

/*
    Puts a pixel at the specified coordinates.
*/
void turtle_pixel(SDL_Renderer* renderer, int x, int y);


#endif