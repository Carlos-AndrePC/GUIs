#include <SDL2/SDL.h>
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
  SDL_SetRenderDrawColor(ren, 255,255,255,0x00);
  SDL_RenderDrawLine(ren,300,500,300,400);
  SDL_RenderDrawLine(ren,300,500,400,575);
  SDL_RenderDrawLine(ren,300,500,200,575);
  SDL_RenderPresent(ren);
  SDL_Delay(5000);


  /* FINALIZACAO */
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
