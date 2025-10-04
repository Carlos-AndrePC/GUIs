#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <SDL2/SDL_events.h>
int espera = 250;


int AUX_WaitEventTimeout(SDL_Event *evt, Uint32 *ms)
{
    Uint32 inicio = SDL_GetTicks();  // Marca o tempo antes da chamada
    int ret = SDL_WaitEventTimeout(evt, *ms);
    Uint32 fim = SDL_GetTicks();     // Marca o tempo depois da chamada

    Uint32 decorrido = fim - inicio; // Calcula quanto tempo passou

    if (decorrido >= *ms)
    {
        *ms = 0;
    }
    else
    {
        *ms -= decorrido;
    }

    return ret; // 1 se evento chegou, 0 se timeout
}

void CriarEvento(int *n){
    SDL_Event eventocliques;
    eventocliques.type = SDL_USEREVENT;
    eventocliques.user.code = *n;
    *n = 0;
    SDL_PushEvent(&eventocliques);
}

int main(int argc, char *args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *win = SDL_CreateWindow("Movendo um Retângulo",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       200, 100, SDL_WINDOW_SHOWN);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    
    SDL_Event evt;
    Uint32 ms = espera;
    int contador_de_clique = 0;
    int x = -1;
    int y = -1;
    while (1)
    {

        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);
        if(AUX_WaitEventTimeout(&evt, &ms))
       {
            if(evt.type == SDL_QUIT){
                SDL_Quit();
                break;
            }
            else if(evt.type == SDL_MOUSEBUTTONDOWN){
                int x1,y1;
                Uint32 Buttons = SDL_GetMouseState(&x1, &y1);
                if( x == x1 && y == y1){
                    ms = espera;
                }
                else{
                    x = x1;
                    y = y1;
                    CriarEvento(&contador_de_clique);
                }
                contador_de_clique ++;
            }
            else if(evt.type == SDL_MOUSEMOTION){
                ms = espera;
                CriarEvento(&contador_de_clique);
            }
            else if(evt.type == SDL_USEREVENT){
                if (evt.user.code !=0 )printf(" %c",(char)(evt.user.code%26)+96);
            }
       }
       else
       {
            ms = espera;
            CriarEvento(&contador_de_clique);
       }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
