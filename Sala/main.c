#include <SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>

SDL_Rect retangulos[10];
int direcaoRetangulos[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int velocidade = 10;
int nRetangulos = 0;

void CriarRetangulo(SDL_Renderer* ren,int i){
    int x,y;
    Uint32 Buttons = SDL_GetMouseState(&x, &y);
    SDL_SetRenderDrawColor(ren, 0,0,0,0x00);
    retangulos[i].x = x;
    retangulos[i].y = y;
    retangulos[i].w = 100;
    retangulos[i].h = 100; 
    SDL_RenderFillRect(ren, &retangulos[i]);
}

void MoverRetangulos(SDL_Renderer* ren){
    int i =0;
    while(i<nRetangulos){
        SDL_SetRenderDrawColor(ren, i*25,i*25,i*25,0x00);
        int inicio = i*2;
        retangulos[i].x =  retangulos[i].x + (velocidade* direcaoRetangulos[inicio]);
        retangulos[i].y =  retangulos[i].y + (velocidade* direcaoRetangulos[inicio+1]);
        if(retangulos[i].x >= 500 ||retangulos[i].x <= 100 ){
            direcaoRetangulos[inicio] = direcaoRetangulos[inicio] * (-1);
        }
        if(retangulos[i].y >= 500 || retangulos[i].y <= 100){
            direcaoRetangulos[inicio+1] = direcaoRetangulos[inicio+1] * (-1);
        }
        SDL_RenderFillRect(ren, &retangulos[i]);
        i++;
    }
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

    /* EXECUÇÃO */
    int i =1;
    SDL_SetRenderDrawColor(ren, 255,255,0xFF,0x00);
    SDL_RenderClear(ren);
    while(i){
           
        SDL_Event evt;
        SDL_WaitEvent(&evt);
        switch (evt.type)
        {
            case SDL_QUIT:
                SDL_Quit();
                i=0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (nRetangulos <10) {
                    CriarRetangulo(ren,nRetangulos);
                    nRetangulos++;
                }
                break;
            default:
                break;
            } 
        SDL_SetRenderDrawColor(ren, 255,255,0xFF,0x00);
        SDL_RenderClear(ren);
        MoverRetangulos(ren);
        SDL_RenderPresent(ren);
    }
}
