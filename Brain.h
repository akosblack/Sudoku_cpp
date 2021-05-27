#ifndef THEBRAIN_H_
#define THEBRAIN_H_

#include "Consts.h"
#include "Render.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <SDL_ttf.h>
#include "Class_Sudoku.h"

using namespace std;

//A kattintatas kezelo fuggveny
bool click_cell(SDL_Event event, int x, int y, int w, int h);

//Ellenorzi a megoldast
bool isValidSudoku(const Class_Sudoku*Game);

//Palyagenerator
void BoardGenerator(int null, Class_Sudoku *diffGame);


#endif