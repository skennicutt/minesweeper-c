#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cassert>
#include <iostream>

#include "SDL3/SDL_events.h"
#include "utils.h"

#define WINDOW_X 0
#define WINDOW_Y 0
#define LOGICAL_HEIGHT 640
#define LOGICAL_WIDTH 800
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define GRID_SIZE 20
#define GRID_DIM 380

#define GRID_START_X ((LOGICAL_WIDTH / 2) - (GRID_DIM / 2))
#define GRID_START_Y ((LOGICAL_HEIGHT / 2) - (GRID_DIM / 2))

// Core structures
typedef struct game_state {
  bool quit;
  bool reset;
  bool game_over;
} GameState;

void handle_user_key_down(game_state *state, SDL_Event e) {
  switch (e.key.key) {
  case SDLK_ESCAPE:
    state->quit = true;
    break;
  default:
    break;
  }
}

void handle_user_key_input(game_state *state, SDL_Event e) {
  switch (e.type) {
  case SDL_EVENT_QUIT:
    state->quit = true;
    break;
  case SDL_EVENT_KEY_UP:
    break;
  case SDL_EVENT_KEY_DOWN:
    // handle_user_key_down(state, e);
    break;
  default:
    break;
  }
}

// Input Handling
void handle_user_input(game_state *state) {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    handle_user_key_input(state, e);
  }
}

// Render Loop
SDL_Window *initialize_window() {
  SDL_Window *window = SDL_CreateWindow("Minesweeper", WINDOW_WIDTH,
                                        WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);

  if (!window) {
    fprintf(stderr, "ERROR: SDL_CreateWindow");
  }
  return window;
}

SDL_Renderer *initialize_renderer(SDL_Window *window) {
  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  if (!renderer) {
    fprintf(stderr, "ERROR: SDL_CreateRenderer");
  }
  return renderer;
}

game_state initialize_game_state() {
  return game_state{
      false,
      false,
      false,
  };
}

bool is_game_over() { return false; }

void execute_main_gameplay_loop(SDL_Renderer *renderer, game_state &state) {
  if (state.reset) {
    state.reset = false;
  }

  if (is_game_over()) {
    state.game_over = true;
    state.quit = true;
    return;
  }

  handle_user_input(&state);

  SDL_RenderClear(renderer);
  // RENDER LOOP START

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderPresent(renderer);

  SDL_Delay(300); // This is a horrible way to delay, it interferes with input
                  // handling and causes delays
}

int main(int, char *[]) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "ERROR: Could not initialize SDL: %s\n", SDL_GetError());
  }

  srand((unsigned int)time(NULL));

  SDL_Window *window = initialize_window();
  SDL_Renderer *renderer = initialize_renderer(window);

  // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_SetRenderLogicalPresentation(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);

  // SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hello World", "This
  // is a test of the message box", window);

  game_state state = initialize_game_state();

  while (state.quit != true) {
    execute_main_gameplay_loop(renderer, state);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
