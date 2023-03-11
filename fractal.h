#pragma once
#ifndef FRACTALS_H

#include <SDL.h>

/*
    All the fractal functions will take the same variables, the sierpinski function bieng the only outlier with a couple of
    extra parameters. The common variables are; The renderer, the intial size of the fractal shape and the depth of the recursion.
    In the case of the sierpinski, the extra parameters are the starting x and y coordinates.
*/

void sierpinski(SDL_Renderer* renderer, float x, float y, float size, int depth);

void drawTree(SDL_Renderer* renderer, float size, int depth);

void drawKoch(SDL_Renderer* renderer, float size, int depth);

#endif
