#include <SDL2/SDL.h>

#define W_WIDTH     800
#define W_HEIGHT    600

#define BLACK       0, 0, 0, 255
#define WHITE       255, 255, 255, 255

SDL_bool        game_runs = SDL_TRUE;

SDL_Window      *p_Window = NULL;
SDL_Renderer    *p_Render = NULL;
SDL_Event       event;

void game_init(void);
void game_inputs(void);
void game_clean(void);

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    game_init();

    while(game_runs)
    {
        game_inputs();

        SDL_SetRenderDrawColor(p_Render, BLACK);
        SDL_RenderClear(p_Render);

        SDL_RenderPresent(p_Render);

        SDL_Delay(16);
    }

    game_clean();
    return 0;
}

void game_init(void)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Error SDL Init: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    p_Window = SDL_CreateWindow("Test_Pong", 
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                W_WIDTH, W_HEIGHT,
                                SDL_WINDOW_SHOWN);
    p_Render = SDL_CreateRenderer(p_Window, -1, SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);

    if(!p_Window && !p_Render) {
        SDL_Log("Error SDL window and renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void game_inputs(void)
{
    while(SDL_PollEvent(&event)) {
        if(SDL_QUIT == event.type) game_runs = SDL_FALSE;
        if(SDL_KEYDOWN == event.type) {
            switch(event.key.keysym.sym) {
                case SDLK_ESCAPE: game_runs = SDL_FALSE;
                    break;
            }
        }
    }
}

void game_clean(void)
{
    SDL_DestroyRenderer(p_Render);
    SDL_DestroyWindow(p_Window);
    SDL_Quit();
}