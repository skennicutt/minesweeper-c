#ifndef BORDER_H
#define BORDER_H

#include "main.h"

struct Border {
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  SDL_FRect *rect;
  unsigned rows;
  unsigned columns;
  float piece_height;
  float piece_weight;
  float left_offset;
};

bool border_new(struct Border **border, SDL_Renderer, unsigned rows,
                unsigned columns);
void border_free(struct Border **border);
void border_draw(const struct Border *b);

#endif
