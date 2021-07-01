#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 800
#define BG 200
#define SIDE 100

SDL_Window *win;
SDL_Renderer *rend;

SDL_Point mpos;
SDL_Rect obj = {
    0, 0, SIDE, SIDE
};
int dragging = 0;

SDL_Texture *boi;

struct {
    int lmb, rmb;
} mouse;

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
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    IMG_Init(IMG_INIT_PNG);

    boi = IMG_LoadTexture(rend, "res/boi.png");
}

// processing
int handleev() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) 
        switch (event.type) {
            case SDL_MOUSEMOTION:
                mpos.x = event.motion.x;
                mpos.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    mouse.lmb = 1;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    mouse.rmb = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    mouse.lmb = 0;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    mouse.rmb = 0;
                break;
            default:
                break;
        }
    return event.key.keysym.scancode == SDL_SCANCODE_Q;

}

void update() {
    if (mouse.lmb && SDL_PointInRect(&mpos, &obj)) {
        dragging = 1;
    } else {
        dragging = 0;
    }

    if (dragging) {
        obj.x = mpos.x-SIDE/2;
        obj.y = mpos.y-SIDE/2;
    }
}


// rendering
void render() {
    SDL_RenderCopy(rend, boi, NULL, &obj);
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
