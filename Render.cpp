#include "Consts.h"
#include <SDL.h>
#include "Text.h"
#include "Render.h"
#include "Consts.h"
#include <fstream>
#include <iostream>
#include <string>

SDL_Rect DestPos2;

void DestPosition2(int x, int y, int w, int h)
{
	DestPos2.x = x;
	DestPos2.y = y;
	DestPos2.w = w;
	DestPos2.h = h;
}

void render_diff(SDL_Renderer *renderer)
{
	SDL_Surface* Diff= NULL;
	SDL_Texture* DiffTex = NULL;

	//kep betoltese
	Diff = SDL_LoadBMP("diff.bmp");
	DiffTex = SDL_CreateTextureFromSurface(renderer, Diff);
	SDL_FreeSurface(Diff);

	//Megjelenites
	DestPosition2(0, 0, 600, 600);
	SDL_RenderCopy(renderer, DiffTex, NULL, &DestPos2);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(DiffTex);

}

void render_grid(SDL_Renderer *renderer, const SDL_Color *color)
{
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

	//Hatter letrehozasa
	SDL_Surface* WP = NULL;
	SDL_Texture* WPTex = NULL;

	//kep betoltese
	WP = SDL_LoadBMP("wp.bmp");
	WPTex = SDL_CreateTextureFromSurface(renderer, WP);
	SDL_FreeSurface(WP);

	//Megjelenites
	DestPosition2(0, 0, 600, 600);
	SDL_RenderCopy(renderer, WPTex, NULL, &DestPos2);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(WPTex);

	//Grid rajzolasa
	
	for (int i = 0; i < COL + 1; ++i)
	{
		if ((i == 0) || (i == 3) || (i == 6) || (i == 9))
		{
			SDL_RenderDrawLine(renderer, i*cell_width + 149, 150, i*cell_width + 149, INNER_SCREEN_HEIGHT + 147.5); //colums oszlop
			SDL_RenderDrawLine(renderer, i*cell_width + 150, 150, i*cell_width + 150, INNER_SCREEN_HEIGHT + 147.5);
			SDL_RenderDrawLine(renderer, i*cell_width + 151, 150, i*cell_width + 151, INNER_SCREEN_HEIGHT + 147.5);

			SDL_RenderDrawLine(renderer, 150, i*cell_height + 149, INNER_SCREEN_WIDTH + 147.5, i*cell_height + 149); //rows sor
			SDL_RenderDrawLine(renderer, 150, i*cell_height + 150, INNER_SCREEN_WIDTH + 147.5, i*cell_height + 150);
			SDL_RenderDrawLine(renderer, 150, i*cell_height + 151, INNER_SCREEN_WIDTH + 147.5, i*cell_height + 151);
		}
		else
		SDL_RenderDrawLine(renderer, i*cell_width + 150, 150, i*cell_width + 150, INNER_SCREEN_HEIGHT + 147.5); //colums oszlop
		SDL_RenderDrawLine(renderer, 150, i*cell_height + 150, INNER_SCREEN_WIDTH + 147.5, i*cell_height + 150); //rows sor
	}
}

void render_only_grid(SDL_Renderer *renderer, const SDL_Color *color)
{
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

	//Grid rajzolasa

	for (int i = 0; i < COL + 1; ++i)
	{
		if ((i == 0) || (i == 3) || (i == 6) || (i == 9))
		{
			SDL_RenderDrawLine(renderer, i*cell_width + 149, 150, i*cell_width + 149, INNER_SCREEN_HEIGHT + 147.5); //colums oszlop
			SDL_RenderDrawLine(renderer, i*cell_width + 150, 150, i*cell_width + 150, INNER_SCREEN_HEIGHT + 147.5);
			SDL_RenderDrawLine(renderer, i*cell_width + 151, 150, i*cell_width + 151, INNER_SCREEN_HEIGHT + 147.5);

			SDL_RenderDrawLine(renderer, 150, i*cell_height + 149, INNER_SCREEN_WIDTH + 147.5, i*cell_height + 149); //rows sor
			SDL_RenderDrawLine(renderer, 150, i*cell_height + 150, INNER_SCREEN_WIDTH + 147.5, i*cell_height + 150);
			SDL_RenderDrawLine(renderer, 150, i*cell_height + 151, INNER_SCREEN_WIDTH + 147.5, i*cell_height + 151);
		}
		else
			SDL_RenderDrawLine(renderer, i*cell_width + 150, 150, i*cell_width + 150, INNER_SCREEN_HEIGHT + 147.5); //colums oszlop
		SDL_RenderDrawLine(renderer, 150, i*cell_height + 150, INNER_SCREEN_WIDTH + 147.5, i*cell_height + 150); //rows sor
	}
}

void render_numbers(SDL_Renderer *renderer, Class_Sudoku*Game)
{
	SDL_Color TextColor = { 0, 0, 0 , 255 };
	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			char c = Game->getBoardElement(i, j);

			char *text = new char[2];
			text[0] = c;
			text[1] = '\0';

			text_render(text, renderer, j*cell_width + 155, i*cell_height + 155, 25, 25, TextColor);
		}
	}
}

void renderGame(SDL_Renderer *renderer, Class_Sudoku*Game)
{
	switch (Game->getState())
	{
	case RUNNING_STATE:
		render_grid(renderer, &GRID_COLOR);
		render_numbers(renderer, Game);
		std::cout << "The Render: Done" << std::endl;
		break;
	case PLAYER_WON:
		std::cout << "The player won!" << std::endl;
		render_grid(renderer, &PLAYER_WON_COLOR);
		render_numbers(renderer, Game);
		break;
	case SOMETHING_WRONG:
		render_only_grid(renderer, &BAD_TURN_COLOR);		
		std::cerr << "Something is wrong" << std::endl;
		std::cerr << "Please, delete the previous number that you have wrote in!" << std::endl;	
		break;
	case BTN_STATE:
		render_only_grid(renderer, &GRID_COLOR);
		break;
	}
}