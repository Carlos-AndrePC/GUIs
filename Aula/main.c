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
    int i =1;
    while(i){
        SDL_SetRenderDrawColor(ren, 255,255,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_Event evt;
        SDL_WaitEvent(&evt);
        switch (evt.type)
        {
            case SDL_QUIT:
                SDL_Quit();
                i=0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                int x,y;
                Uint32 Buttons = SDL_GetMouseState(&x, &y);
                SDL_SetRenderDrawColor(ren, 0,0,0,0x00);
                SDL_Rect r = {x,y,100,100}; 
                SDL_RenderFillRect(ren, &r);
                break;
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym)
                {
                case 's':
                    i = 0;
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        SDL_RenderPresent(ren);
    }
}
