#ifndef UTILS_H
#define UTILS_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cstdio>
#include <cstdlib>

inline int uniform_random(int lower, int upper) {
  int range = upper - lower + 1;
  int limit = RAND_MAX - (RAND_MAX % range);
  int r;
  do {
    r = rand();
  } while (r >= limit);
  return (r % range) + lower;
}

inline bool load_sprite_sheet(SDL_Renderer *renderer, SDL_Texture **image,
                              const char *file_path, int width, int height,
                              SDL_FRect **rects) {

  if (*image) {
    SDL_DestroyTexture(*image);
    *image = NULL;
  }

  if (*rects) {
    free(*rects);
    *rects = NULL;
  }

  *image = IMG_LoadTexture(renderer, file_path);
  if (!*image) {
    fprintf(stderr, "Error loading sprite sheet: %s\n", SDL_GetError());
    return false;
  }

  int rows = (*image)->h / height;
  int columns = (*image)->w / width;

  if (!SDL_SetTextureScaleMode(*image, SDL_SCALEMODE_PIXELART)) {
    fprintf(stderr, "Error setting texture scale mode: %s\n", SDL_GetError());
    return false;
  }

  *rects = (SDL_FRect *)calloc(1, sizeof(SDL_FRect) * rows * columns);

  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      int index = row * columns + column;
      (*rects)[index].x = (float)(column * width);
      (*rects)[index].y = (float)(row * height);
      (*rects)[index].w = (float)width;
      (*rects)[index].h = (float)height;
    }
  }

  return true;
}

#endif
