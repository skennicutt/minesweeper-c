#ifndef MAIN_H
#define MAIN_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <cassert>
#include <cstdio>
#include <iostream>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_surface.h"
#include "utils.h"
#include "vendored/SDL/include/SDL3/SDL_render.h"
#include "vendored/SDL/include/SDL3/SDL_video.h"

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

#endif
