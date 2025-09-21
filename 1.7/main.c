#include <SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
int espera = 25;


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
    IMG_Init(0);
    SDL_Texture * img = IMG_LoadTexture(ren, "Carro.png");
    assert(img != NULL);
    /* EXECUÇÃO */
    int i =0;
    int corFundo = 0;
    SDL_Event evt;
    Uint32 antes = SDL_GetTicks();
    Uint32 ms = espera;
    while(1){
        if (AUX_WaitEventTimeout(&evt, &ms)){
            if(evt.type == SDL_QUIT){
                SDL_Quit();
                break;
            }
            else if(evt.type == SDL_MOUSEBUTTONDOWN){
                if(corFundo == 0) corFundo = 1;
                else corFundo = 0;
            }
        }
        else{
            ms = espera;
            if(i==650) i = 0;
            SDL_SetRenderDrawColor(ren,0,0,255*corFundo,0x00);
            SDL_RenderClear(ren);
            SDL_SetRenderDrawColor(ren, 0,0,0,0x00);
            SDL_RenderDrawPoint(ren,150,150);
            SDL_SetRenderDrawColor(ren, 0,0,0,0x00);
            SDL_Rect r = {0,400, 600,200};
            SDL_RenderFillRect(ren, &r);
            SDL_SetRenderDrawColor(ren, 255,255,0,0x00);
            SDL_Rect r1 = {0,475, 600,50};
            SDL_RenderFillRect(ren, &r1);
            SDL_Rect Carro = {i,400, 249,72};
            SDL_RenderCopy(ren,img,NULL,&Carro);
            SDL_RenderPresent(ren);
            i++;
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
