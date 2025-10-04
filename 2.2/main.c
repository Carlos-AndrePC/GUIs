#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>


int esperaRetangulotTempo = 100;

int dirTempo[] = {1, 1};

int didDrag = 0;
int didHandlePointerDown = 0;
int dragOrigin[] = {0,0};
int origPos[] = {40,20};



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

void MoverQuadradro(SDL_Rect *r){
    int x, y;
    Uint32 Buttons = SDL_GetMouseState(&x, &y);
    r->x = x;
    r->y = y;
}

int Entre_Limite_Mouse(int x,int y,SDL_Rect r){
    if(x<=r.x+10 && x>=r.x && y<=r.y+10 && y>=r.y) return 1;
    else return 0;
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
    SDL_Rect r = {origPos[0], origPos[1], 10, 10};
    Uint32 ms = esperaRetangulotTempo;
    while (1)
    {
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);
        if(AUX_WaitEventTimeout(&evt, &ms))
        {
            if (evt.type == SDL_QUIT)
            {
                SDL_Quit();
                break;
            }
            else if (evt.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                Uint32 Buttons = SDL_GetMouseState(&x, &y);
                printf("%d\n",Entre_Limite_Mouse(x,y,r));
                if(evt.button.state == SDL_PRESSED && evt.button.button == SDL_BUTTON_LEFT && Entre_Limite_Mouse(x,y,r)){
                    dragOrigin[0] = x;
                    dragOrigin[1] = y;
                    didDrag = 1;
                }
            }
            else if (evt.type == SDL_MOUSEBUTTONUP)
            {
                if(evt.button.state == SDL_RELEASED && evt.button.button == SDL_BUTTON_LEFT)
                didDrag = 0;
            }
            else if (evt.type == SDL_MOUSEMOTION)
            {
                if(didDrag){
                    MoverQuadradro(&r);
                }
            }
        }
        else
        {
            ms = esperaRetangulotTempo;
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
