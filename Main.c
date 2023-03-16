#include "turtle.h"
#include "fractal.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2>

#define winWid 800
#define winHei 800
#define winLocx 1100
#define winLocy 200

int iterations();

void saveImage(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char* args[])
{
    int go;
    int length = 100;
    int depth = 1;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        perror("SDL Error:\n");
    }

    SDL_Window* window = SDL_CreateWindow("Fractal window", winLocx, winLocy, winWid, winHei, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    printf("Welcome to the fractal drawing program!\n\n");
    printf("Please use the keyboard to choose a colour you wish to use; press 'r' for red, 'g' for green, and 'b' for blue.\n\n");
    printf("Once a colour is chosen use key inputs for choosing a shape; press '1' for sierpinski triangle, '2' for a tree and '3' for a Koch curve.\n\n");
    printf("Press 'e' at any time to clear the window of drawings.\n");
    printf("Press 's' at any time to save a snapshot of the window.\n");

    go = 1;
    while (go)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {

            case SDL_QUIT:
                go = 0;
                break;
                //User presses a key
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {

                case SDLK_r:
                    turtle_colour(renderer, 255, 0, 0);
                    printf("Red is chosen.\nNow please choose a shape.\n");
                    break;

                case SDLK_g:

                    turtle_colour(renderer, 0, 255, 0);
                    printf("Green is chosen.\nNow please choose a shape.\n");
                    break;

                case SDLK_b:
                    turtle_colour(renderer, 0, 0, 255);
                    printf("Blue is chosen.\nNow please choose a shape.\n");
                    break;

                case SDLK_1:
                    printf("Sierpinski is chosen. Now please enter an integer value between 1 and 25 corrosponding to how many iterations of the recursion you want in the terminal, followed by enter.\n\n");
                    printf("Once you have pressed enter please remember to click back onto the drawing window to continue drawing!\n");

                    depth = iterations();

                    sierpinski(renderer, 400, 400, 200, depth);
                    printf("Now please click back onto the drawing window and select a colour or shape to draw next.\n\n");
                    break;

                case SDLK_2:
                    printf("Tree is chosen. Now please enter an integer value between 1 and 25 corrosponding to how many iterations of the recursion you want in the terminal, followed by enter.\n\n");
                    printf("Once you have pressed enter please remember to click back onto the drawing window to continue drawing!\n");

                    depth = iterations();

                    turtle_goto(renderer, 200, 400);
                    drawTree(renderer, 75, depth);
                    printf("Now please click back onto the drawing window and select a colour or shape to draw next.\n\n");
                    break;

                case SDLK_3:
                    printf("Koch curve is chosen. Now please enter an integer value between 1 and 25 corrosponding to how many iterations of the recursion you want in the terminal, followed by enter.\n\n");
                    printf("Once you have pressed enter please remember to click back onto the drawing window to continue drawing!\n");

                    depth = iterations();

                    turtle_goto(renderer, 400, 600);
                    drawKoch(renderer, 100, depth);
                    printf("Now please click back onto the drawing window and select a colour or shape to draw next.\n\n");
                    break;

                case SDLK_e:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                    SDL_RenderClear(renderer);
                    printf("Window cleared!\n\n");
                    turtle_colour(renderer, 255, 0, 0);
                    break;


                case SDLK_s:

                    saveImage(window, renderer);

                    printf("Image saved!\n\n");

                    break;

                default: break;
                }
            }
            }
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int iterations()
{
    int iterate;

    scanf_s("%d", &iterate);

    return iterate;

}

void saveImage(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_Surface* image = SDL_CreateRGBSurface(0, winWid, winHei, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(renderer, NULL, 0, image->pixels, image->pitch);

    SDL_SaveBMP(image, "Fractal_Drawing.bmp");

    SDL_FreeSurface(image);
}
//            ___
//　　　 　　／＞　　フ
//　　　 　　| 　_　 _l
//　 　　 　／` ミ＿xノ
//　　 　 /　　　 　 |
//　　　 /　 ヽ　　 ﾉ
//　 　 │　　|　|　|
//　／￣|　　 |　|　|
//　| (￣ヽ＿_ヽ_)__)
//　二つ 