#include "border.h"
#include "main.h"

bool border_new(struct Border **border, SDL_Renderer *renderer, unsigned rows,
                unsigned columns) {
  *border = (Border *)calloc(1, sizeof(struct Border));
  if (!*border) {
    fprintf("Could not allocate memory for border");
  }
}

void border_free(struct Border **border) {}

void border_draw(const struct Border *b) {}
