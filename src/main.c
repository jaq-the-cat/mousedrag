#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 800
#define BG 200

SDL_Window *win;
SDL_Renderer *rend;

// initialization
void init() {
    // Window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    win = SDL_CreateWindow(
        "jaq-the-cat/mousedrag",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        0);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    IMG_Init(IMG_INIT_PNG);
}

// rendering
void render() {
}

// processing
int handleev() {
    SDL_Event event;
    SDL_PollEvent(&event);
    return event.key.keysym.scancode == SDL_SCANCODE_Q;
}

void update() {
}

int main() {
    init();

    int close = 0;
    while (!close) {
        close = handleev();
        update();
        SDL_SetRenderDrawColor(rend, BG, BG, BG, 255);
        SDL_RenderClear(rend);
        render();
        SDL_RenderPresent(rend);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    return 0;
}
