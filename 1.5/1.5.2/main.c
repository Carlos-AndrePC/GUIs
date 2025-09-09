#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
SDL_Rect retangulos[3];
int nRetangulos = 0;
int esperaRetangulotTempo = 100;

int dirTempo[] = {1, 1};

void CriarRetanguloMouse(SDL_Renderer *ren, int i)
{
    int x, y;
    Uint32 Buttons = SDL_GetMouseState(&x, &y);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0x00);
    retangulos[i].x = x;
    retangulos[i].y = y;
    retangulos[i].w = 10;
    retangulos[i].h = 10;
    SDL_RenderFillRect(ren, &retangulos[i]);
    nRetangulos++;
}

void MoverRetanguloMouse()
{
    int x, y;
    Uint32 Buttons = SDL_GetMouseState(&x, &y);
    retangulos[0].x = x;
    retangulos[0].y = y;
}

void MoverRetanguloTempo()
{
    int x, y;
    Uint32 Buttons = SDL_GetMouseState(&x, &y);
    retangulos[1].x += 5 * dirTempo[0];
    retangulos[1].y += 5 * dirTempo[1];
    if (retangulos[1].x >= 200)
    {
        dirTempo[0] = -1;
    }
    if (retangulos[1].x <= 0)
    {
        dirTempo[0] = 1;
    }
    if (retangulos[1].y >= 100)
    {
        dirTempo[1] = -1;
    }
    if (retangulos[1].y <= 0)
    {
        dirTempo[1] = 1;
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
    SDL_Rect r = {40, 20, 10, 10};
    SDL_Event evt;
    CriarRetanguloMouse(ren, 0);
    CriarRetanguloMouse(ren, 1);
    Uint32 ms = esperaRetangulotTempo;
    while (1)
    {
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
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
                case SDLK_UP:
                    if (r.y > 0)
                        r.y -= 5;
                    break;
                case SDLK_DOWN:
                    if (r.y < 90)
                        r.y += 5;
                    break;
                case SDLK_LEFT:
                    if (r.x > 0)
                        r.x -= 5;
                    break;
                case SDLK_RIGHT:
                    if (r.x < 190)
                        r.x += 5;
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
