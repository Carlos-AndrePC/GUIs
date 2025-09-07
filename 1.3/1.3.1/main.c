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
    int i =0;
    while(i<650){
        SDL_SetRenderDrawColor(ren, 0,0,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0,0,0,0x00);
        SDL_RenderDrawPoint(ren,150,150);
        SDL_SetRenderDrawColor(ren, 0,0,0,0x00);
        SDL_Rect r = {0,400, 600,200};
        SDL_RenderFillRect(ren, &r);
        SDL_SetRenderDrawColor(ren, 255,255,0,0x00);
        SDL_Rect r1 = {0,475, 600,50};
        SDL_RenderFillRect(ren, &r1);
        circleRGBA(ren,i,425,30,0,0,255,255);
        circleRGBA(ren,i+80,425,30,0,0,255,255);
        SDL_SetRenderDrawColor(ren, 255,0,0,0x00);
        SDL_Rect r2 = {i-45,390, 200,40 };
        SDL_RenderFillRect(ren, &r2);
        SDL_Rect r3 = {i+80,375, 20,20 };
        SDL_RenderFillRect(ren, &r3);
        SDL_RenderPresent(ren);
        SDL_Delay(100);
        i++;
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
