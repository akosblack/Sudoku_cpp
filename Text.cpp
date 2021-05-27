#include "Text.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Consts.h"

SDL_Rect DestPos;

void DestPosition(int x, int y, int w, int h)
{
	DestPos.x = x;
	DestPos.y = y;
	DestPos.w = w;
	DestPos.h = h;
}

void text_render(char *szoveg, SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color TextColor)
{
	TTF_Font *Font = NULL;
	Font = TTF_OpenFont("Rubik-Light.ttf", 24);
	

	SDL_Surface *text = NULL;

	text = TTF_RenderText_Solid(Font, szoveg, TextColor);

	SDL_Texture *SzovegTex = NULL;
	SzovegTex = SDL_CreateTextureFromSurface(renderer, text);

	SDL_FreeSurface(text);

	DestPosition(x, y, w, h);

	SDL_RenderCopy(renderer, SzovegTex, NULL, &DestPos);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(SzovegTex);
	TTF_CloseFont(Font);
}
