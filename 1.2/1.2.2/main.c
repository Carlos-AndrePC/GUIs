#include <SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Hello World!",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         600, 600, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
    circleRGBA(ren,0,300,30,0,0,255,255);
    circleRGBA(ren,80,300,30,0,0,255,255);
    SDL_SetRenderDrawColor(ren, 255,0,0,0x00);
    SDL_Rect r = {-45,270, 200,40 };
    SDL_RenderFillRect(ren, &r);
    SDL_Rect r1 = {80,250, 20,20 };
    SDL_RenderFillRect(ren, &r1);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);


    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
