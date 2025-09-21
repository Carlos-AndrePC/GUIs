#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>

SDL_Rect retangulos[3];
int nRetangulos = 0;
int esperaRetangulotTempo = 100;
int vencendor = -1;
int terminaram[] = {0,0,0};
int dirTempo[] = {1, 0};

void CriarRetanguloMouse(SDL_Renderer *ren, int i)
{
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0x00);
    retangulos[i].x = 0;
    retangulos[i].y = 0+(i*30);
    retangulos[i].w = 10;
    retangulos[i].h = 10;
    SDL_RenderFillRect(ren, &retangulos[i]);
    nRetangulos++;
}

void MoverRetanguloMouse()
{
    int x, y;
    Uint32 Buttons = SDL_GetMouseState(&x, &y);
    if(x>=180){
        x = 180;
        if(vencendor == -1){
            vencendor = 0;
            printf("O vencedor é o 0\n");
        }
        terminaram[0] = 1;
    }
    retangulos[0].x = x;
    retangulos[0].y = 0;
}

void MoverRetanguloTempo()
{
    retangulos[1].x += 5 * dirTempo[0];
    retangulos[1].y += 5 * dirTempo[1];
    if (retangulos[1].x >= 180)
    {
        dirTempo[0] = 0;
        if(vencendor == -1){
            vencendor = 1;
            printf("O vencedor é o 1\n");
        }
        terminaram[1] = 1;
    }
    if (retangulos[1].x <= 0)
    {
        dirTempo[0] = 0;
    }
}

void RenderRetangulos(SDL_Renderer *ren)
{
    int i = 0;
    while (i < nRetangulos)
    {
        SDL_SetRenderDrawColor(ren, i * 25, i * 25, i * 25, 0x00);
        SDL_RenderFillRect(ren, &retangulos[i]);
        i++;
    }
}

void ReiniciarPosição(){
    for(int i =0;i<3;i++){
        retangulos[i].x = 0;    
        terminaram[i] = 0;
    }
    vencendor = -1;
    dirTempo[0] = 1;
}

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
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0x00);
    SDL_Rect r = {180, 0, 20, 200};
    CriarRetanguloMouse(ren, 0);
    CriarRetanguloMouse(ren, 1);
    CriarRetanguloMouse(ren, 2);
    Uint32 ms = esperaRetangulotTempo;
    while (1)
    {
        if(terminaram[0] == 1 && terminaram[1] == 1 && terminaram[2] == 1){
            ReiniciarPosição();
        }
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 255, 0, 0, 0x00);
        SDL_RenderFillRect(ren, &r);
        RenderRetangulos(ren);
        SDL_RenderPresent(ren);
        if(AUX_WaitEventTimeout(&evt, &ms))
        {
            if (evt.type == SDL_QUIT)
            {
                SDL_Quit();
                break;
            }
            else if (evt.type == SDL_KEYDOWN)
            {
                switch (evt.key.keysym.sym)
                {
                    break;
                case SDLK_LEFT:
                    if (retangulos[2].x > 0)
                        retangulos[2].x -= 5;
                    break;
                case SDLK_RIGHT:
                    if (retangulos[2].x < 180) retangulos[2].x += 5;
                    else{
                        if(vencendor == -1) {
                            vencendor = 2;
                            printf("O vencedor é o 2\n");
                        }
                        terminaram[2] = 1;;
                    }
                    break;
                }
            }
            else if (evt.type == SDL_MOUSEMOTION)
            {
                MoverRetanguloMouse(ren);
            }
        }
        else
        {
            MoverRetanguloTempo();
            ms = esperaRetangulotTempo;
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
