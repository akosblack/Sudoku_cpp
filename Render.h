#ifndef RENDER_H_
#define RENDER_H_

#include "Consts.h"
#include <SDL.h>
#include "Text.h"
#include <string>
#include "Class_Sudoku.h"

const SDL_Color GRID_COLOR = { 0, 0, 0, 255 };
const SDL_Color PLAYER_WON_COLOR = { 50, 0, 255, 0 };
const SDL_Color BAD_TURN_COLOR = { 255, 0, 0, 0 };

//Nehezseg valaszto
void render_diff(SDL_Renderer *renderer);

//A Sudoku tablat letrehozo
void render_grid(SDL_Renderer *renderer, SDL_Color *color);
void render_only_grid(SDL_Renderer *renderer, SDL_Color *color);
void render_numbers(SDL_Renderer *renderer, Class_Sudoku*Game);

void renderGame(SDL_Renderer *renderer, Class_Sudoku*);

#endif