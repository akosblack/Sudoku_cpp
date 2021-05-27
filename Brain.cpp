#include "Consts.h"
#include "Render.h"
#include "Brain.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <SDL_ttf.h>
#include "Class_Sudoku.h"
#include <unordered_set>
#include <ctime>
#include <conio.h>
#include <cstdio>

bool click_cell(SDL_Event event, int x, int y, int w, int h)
{
	int x2 = event.button.x;
	int y2 = event.button.y;
	if ((x2 > x) && (x2 < w) && (y2 > y) && (y2 < h)) return true;
	else return false;
}

bool isValidSudoku(const Class_Sudoku * Game)
{
	unordered_set<int> has;

	for (int i = 0; i < 9; i++) {
		has.clear();
		// rows
		for (int j = 0; j < 9; j++) {
			if (Game->getBoardElement(i, j) != ' ') {
				if (has.count(Game->getBoardElement(i, j))) {
					return false;
				}
				has.insert(Game->getBoardElement(i, j));
			}
		}
		has.clear();
		// columns
		for (int j = 0; j < 9; j++) {
			if (Game->getBoardElement(j,i) != ' ') {
				if (has.count(Game->getBoardElement(j, i))) {
					return false;
				}
				has.insert(Game->getBoardElement(j,i));
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// 3x3as negyzet ellenorzo
			has.clear();
			for (int x = i * 3; x < i * 3 + 3; x++) {
				for (int y = j * 3; y < j * 3 + 3; y++) {
					if (Game->getBoardElement(x, y) != ' ') {
						if (has.count(Game->getBoardElement(x, y))) {
							return false;
						}
						has.insert(Game->getBoardElement(x, y));
					}
				}
			}
		}
	}
	return true;
}


int null, Class_Sudoku*diffGame)
{
	
	diffGame->setDefault();
	diffGame->setBoard("baseTemplate.txt");

	//Random megcserél az minden 3as groupban egy oszlopot, majd sort

	int randrow1 = rand() % 3;
	int randrow2 = rand() % 3;
	int randcol1 = rand() % 3;
	int randcol2 = rand() % 3;

	//Ugyel arra hogy ugyanazt a kettot ne cserelje meg, mert az ertelmetlen
	while (randrow1 == randrow2)
		randrow2 = rand() % 3;
	while (randcol1 == randcol2)
		randcol2 = rand() % 3;

	diffGame->swapROW(randrow1, randrow2);
	diffGame->swapROW(randrow1 + 3, randrow2 + 3);
	diffGame->swapROW(randrow1 + 6, randrow2 + 6);

	diffGame->swapCOL(randcol1, randcol2);
	diffGame->swapCOL(randcol1 + 3, randcol2 + 3);
	diffGame->swapCOL(randcol1 + 6, randcol2 + 6);


	//Megcsereli a palyan az ugyanolyan elemeket egy masikra 2x
	int wasChanched = 0;

	while (wasChanched != 2)
	{
		char randX = (rand() % 9) + 1 + 48;
		char randY = (rand() % 9) + 1 + 48;

		while (randX == randY)
			randY = (rand() % 9) + 1 + 48;

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (diffGame->getBoardElement(i, j) == randX)
				{
					diffGame->setBoardElement(i, j, randY);
					j++;
				}

				if (diffGame->getBoardElement(i, j) == randY)
				{
					diffGame->setBoardElement(i, j, randX);
					j++;
				}
			}
		}
		wasChanched++;
	}

	//Elvesz a palyabol annyi elemet, amennyit a nehezsegiszint megkovetel
	int nullNum = 0;
	int randI = 0;
	int randK = 0;

	while (nullNum != null)
	{
		randI = rand() % 9;
		randK = rand() % 9;

		if (diffGame->getBoardElement(randI, randK) != ' ')
		{
			diffGame->setBoardElement(randI, randK, ' ');
			nullNum++;
		}

	}

	if (!isValidSudoku(diffGame))
	{
		std::cout << std::endl << "Grid generating problem, retry" << std::endl;
		BoardGenerator(null, diffGame);
	}
	else
	{
		diffGame->setNull(null);
		diffGame->setState(RUNNING_STATE);
		std::cout << "Succesfully generated the grid" << std::endl;
		std::cout << "The number of the nulls: " << diffGame->getNull() << std::endl;		
	}

}
