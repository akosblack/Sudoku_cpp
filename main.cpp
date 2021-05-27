#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "Consts.h"
#include "Render.h"
#include "Brain.h"
#include "Text.h"
#include "Class_Sudoku.h"



int main(int argc, char*argv[])
{
	SDL_Surface *windowSurface = NULL;
	SDL_Renderer*renderer = NULL;
	SDL_Surface *logo = NULL;


	/////////////////	
	//Window creation
	/////////////////
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cerr << "SDL coit not initialise! SDL error: " << SDL_GetError() << std::endl;

	if (TTF_Init() == -1)
		std::cerr << "Failed to initalize SDL_ttf. \n" << std::endl;

	SDL_Window *window = SDL_CreateWindow("Sudoku",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_ALLOW_HIGHDPI);
	windowSurface = SDL_GetWindowSurface(window);
	
	//Logo betoltese
	logo = SDL_LoadBMP("logo_1.bmp");
	if (logo == NULL)
		std::cerr << "SDL could not open the logo! " << SDL_GetError() << std::endl;
	SDL_SetWindowIcon(window, logo);
	SDL_FreeSurface(logo);

	if (window == NULL)
	{
		std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	//////////
	//Renderer
	//////////
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
	{
		ofstream fout;
		fout.open("Errors.txt");
		if (fout.fail())
		{
			std::cerr << "Output file opening failed."<<std::endl;
			exit(1);
		}
		else
		{
			std::cout << "Output file written successfully"<<std::endl;
		}
		SDL_DestroyWindow(window);
		"SDL_CreateRenderer Error: %s\n", SDL_GetError();
		fout.close();
		return EXIT_FAILURE;
	}

	
	////////////
	//Event loop
	////////////

//Nehezseg valaszto
	srand(time(nullptr));
	Class_Sudoku Game;

	render_diff(renderer);
	SDL_Event MouseEvent;
	bool choosed = false;
	int choosedNULL = 0;
	while (!choosed)
	{

		while (SDL_PollEvent(&MouseEvent))
		{
			switch (MouseEvent.type)
			{

			case SDL_QUIT:
				exit(1);
				break;
			case SDL_KEYUP:
				//Kilepeshez ESC
				switch (MouseEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					exit(1);
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
			
				switch (MouseEvent.button.button)
				{
				case SDL_BUTTON_LEFT:

					//Easy					
					if (click_cell(MouseEvent, 175, 115, 425, 215))
					{
						choosedNULL = 30;
						std::cout << "Easy" << std::endl;
						auto t1 = std::chrono::high_resolution_clock::now();
						BoardGenerator(choosedNULL, &Game);
						auto t2 = std::chrono::high_resolution_clock::now();
						std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
						std::cout << "The grid gen was: " << fp_ms.count() << "ms" << std::endl;
						choosed = true;

					}

					//Medimum
					if (click_cell(MouseEvent, 175, 238, 425, 338))
					{						
						choosedNULL = 40;
						std::cout << "Medium" << std::endl;
						auto t1 = std::chrono::high_resolution_clock::now();
						BoardGenerator(choosedNULL, &Game);
						auto t2 = std::chrono::high_resolution_clock::now();
						std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
						std::cout << "The grid gen was: " << fp_ms.count() << "ms" << std::endl;
						choosed = true;
					}

					//BME aka Hard
					if (click_cell(MouseEvent, 175, 361, 425, 461))
					{
						choosedNULL = 50;
						std::cout << "Hard" << std::endl;
						auto t1 = std::chrono::high_resolution_clock::now();
						BoardGenerator(choosedNULL, &Game);
						auto t2 = std::chrono::high_resolution_clock::now();
						std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
						std::cout << "The grid gen was: " << fp_ms.count() << "ms" << std::endl;

						choosed = true;
					}
				}
			}
				
		}

	}

	
	//Bevitel miatt kotelezo
	SDL_StartTextInput();

	Class_Sudoku Origin;
	Origin.copyBoard(Game);
	Origin.setState(NOT_IN_GAME);	

	Selected Selected;
	Selected.x = 10;
	Selected.y = 0;

	SDL_Event windowEvent;	

//Kirajzolas
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
	renderGame(renderer, &Game);
	bool canDelete = false;
	bool mustDelete = false;

//Mainloop
	while (Game.getState() != QUIT_STATE)
	{

		while (SDL_PollEvent(&windowEvent))
		{

			switch (windowEvent.type)
			{
			case SDL_QUIT:
				Game.setState(QUIT_STATE);
				break;

			case SDL_MOUSEBUTTONDOWN:
				//Melyik mezöbe kattintott
				switch (windowEvent.button.button)
				{
				case SDL_BUTTON_LEFT:
					
					//New grid
					if (click_cell(windowEvent, 54, 150, 96, 192))
					{
						auto t1 = std::chrono::high_resolution_clock::now();
						BoardGenerator(choosedNULL, &Game);						
						auto t2 = std::chrono::high_resolution_clock::now();
						std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
						std::cout << "The grid gen was: " << fp_ms.count() << "ms" << std::endl;
						Origin.copyBoard(Game);
						renderGame(renderer, &Game);
						break;
					}
					//A kilepteto gomb
					else if (click_cell(windowEvent, 54, 408, 96, 450))
					{
						Game.setState(QUIT_STATE);
						break;
					}
					else
					{
						for (int i = 0; i < 9; i++)
						{
							for (int j = 0; j < 9; j++)
							{
								//Mezo kivalasztasa
								//click_cell(event,x,y,x+w,y+h)
								if (click_cell(windowEvent, 152 + i * cell_width, 152 + j * cell_height, 152 + i * cell_width + cell_width, 152 + j * cell_height + cell_height))
								{

									if (Game.getBoardElement(j, i) == ' ')
									{
										
										Selected.x = i;
										Selected.y = j;
										std::cout << "Selected tile: " << Selected.y  << "," << Selected.x << std::endl;
										break;
									}
									
									else
									{
										Selected.x = 10;
										break;
									}
								}

							}
						}
						break;
					}
					break;
				case SDL_BUTTON_RIGHT:
					//Mezo atjatvitasa
					if (canDelete)
					{
						
						for (int i = 0; i < COL; i++)
						{
							for (int j = 0; j < ROW; j++)
							{
								if (click_cell(windowEvent, 153 + i * cell_width, 153 + j * cell_height, 153 + i * cell_width + cell_width, 153 + j * cell_height + cell_height))
								{
									
									if (Game.getBoardElement(j, i) != Origin.getBoardElement(j, i))
									{
										if (mustDelete)
										{
											Game.setNull(0);
											mustDelete = false;
											
											Game.setState(BTN_STATE);
											renderGame(renderer, &Game);
											
										}
										Game.setBoardElement(j, i, ' ');
										SDL_Rect rect;
										rect.x = 152.5 + i * cell_width;
										rect.y = 152.5 + j * cell_height;
										rect.w = cell_width - 5;
										rect.h = cell_height - 5;
										SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
										SDL_RenderFillRect(renderer, &rect);
										std::cout << "The deletion has been made on " << j << "," << i << std::endl;
										Game.setNullPlus();
										std::cout << "The number of the nulls: " << Game.getNull() << std::endl;
										break;
									}
									else
										break;

								}


							}


						}

						break;

					}//if(canDelete) vége
					
				}

			//Billentyu lenyomas
			case SDL_KEYUP:
				//Kilepeshez ESC
				switch (windowEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					Game.setState(QUIT_STATE);
					break;
				}
				default: 
					break;

			//Begepeles mezobe (csak szam)
			case SDL_TEXTINPUT:
				{
				if (Selected.x != 10)
				{
					
					if (!(windowEvent.text.text[0] >= 49 && windowEvent.text.text[0] <= 58 ))
					{
						std::cerr << "Wrong input! Only numbers! " << std::endl;
						break;
					}
					else
					{
						SDL_Color EnteredTextColor = { 0, 200, 200 , 0 };
						text_render(windowEvent.text.text, renderer, 155.5 + Selected.x * cell_width, 155.5 + Selected.y * cell_height, 25, 25, EnteredTextColor);
						Game.setBoardElement(Selected.y, Selected.x,windowEvent.text.text[0]);
						std::cout << "The input is valid: " << Game.getBoardElement(Selected.y, Selected.x) << std::endl;
						Game.setNullMinus();
						std::cout << "The number of the nulls: " << Game.getNull() << std::endl;
						Selected.x = 10;
						canDelete = true;
						break;
					}
				}
				
				}
			}
		}
		//Ellenorzes arra, hogy vege van e a jateknak
		if(Game.getNull() == 0) 
		{
			if (isValidSudoku(&Game))
			{
				
				Game.setState(PLAYER_WON);
				renderGame(renderer, &Game);
				Game.setNullPlus();
				canDelete = false;
					
			}
			else if(!isValidSudoku(&Game))
			{			
				Game.setState(SOMETHING_WRONG);
				renderGame(renderer, &Game);
				Game.setNull(1); //Azert van ra szukseg, hogy ki tudjon lepni ebbol a ciklusbol	
				canDelete = true;
				mustDelete = true; //Kell, hogy visszaállítsa a nullák szamat a normalisra, 0-ra, torles elott
				
			}
			
			
		}
	
		SDL_RenderPresent(renderer);

	}
	
//End of Mainloop

	SDL_StopTextInput();

	SDL_FreeSurface(windowSurface);
	windowSurface = NULL;
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();

	std::cout << std::endl << "Succesfully closed!" << std::endl;

	return EXIT_SUCCESS;
}