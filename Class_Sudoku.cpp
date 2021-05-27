#include "Class_Sudoku.h"
#include <fstream>
#include <iostream>

Class_Sudoku::Class_Sudoku()
{
	this->start_null = 0;
	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			this->board[i][j] = ' ';
		}
	}
	this->state = NOT_IN_GAME;
}

Class_Sudoku::Class_Sudoku(const char * filename)
{
	this->start_null = 0;
	setBoard(filename);
	this->state = NOT_IN_GAME;
}

Class_Sudoku::~Class_Sudoku()
{
	this->start_null = 0;
	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			this->board[i][j] = ' ';
		}
	}
	this->state = QUIT_STATE;
}

void Class_Sudoku::copyClass(const Class_Sudoku that)
{
	this->start_null = that.getNull();
	
	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			this->board[i][j] = that.getBoardElement(i,j);
		}
	}
	this->state = that.getState();
}

void Class_Sudoku::copyClass(const Class_Sudoku *that)
{
	this->start_null = that->getNull();

	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			this->board[i][j] = that->getBoardElement(i, j);
		}
	}
	this->state = NOT_IN_GAME;
}

void Class_Sudoku::setDefault()
{
	setNull(0);
	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			this->board[i][j] = ' ';
		}
	}
	setState(NOT_IN_GAME);

}

void Class_Sudoku::setBoard(const char * filename)
{
	ifstream fin;
	fin.open(filename);
	if (fin.fail()) {
		std::cerr << "Input file not included in " << filename << " !" << std::endl;
		exit(1);
	}
	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			fin >> this->board[i][j];
			if (this->board[i][j] == '0')
			{
				this->setNullPlus();
				this->board[i][j] = ' ';
			}
		}
	}
	fin.close();
}

void Class_Sudoku::setBoardElement(int i, int j, char that)
{
	this->board[i][j] = that;
}

void Class_Sudoku::setState(int STATE)
{
	this->state = STATE;
}

void Class_Sudoku::setNull(int x)
{
	this->start_null = x;
}

void Class_Sudoku::setNullPlus()
{
	this->start_null++;
}

void Class_Sudoku::setNullMinus()
{
	this->start_null--;
}

void Class_Sudoku::copyBoard(const Class_Sudoku that)
{
	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			this->board[i][j] = that.getBoardElement(i, j);
		}
	}
}

void Class_Sudoku::copyBoard(const Class_Sudoku *that)
{
	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			this->board[i][j] = that->getBoardElement(i, j);
		}
	}
}

char Class_Sudoku::getBoardElement(int x, int y) const
{
	return this->board[x][y];
}

int Class_Sudoku::getState() const
{
	return this->state;
}

int Class_Sudoku::getNull() const
{
	return this->start_null;
}

void Class_Sudoku::swapROW(int x, int y)
{
	char temp[9];
	for (int i = 0; i < 9; i++)
		temp[i] = ' ';

	for (int j = 0; j < 9; j++)
	{
		temp[j] = getBoardElement(x, j);
		setBoardElement(x, j, getBoardElement(y, j));
		setBoardElement(y, j, temp[j]);
	}

}


void Class_Sudoku::swapCOL(int x, int y)
{
	char temp[9];
	for (int i = 0; i < 9; i++)
		temp[i] = ' ';

	for (int j = 0; j < 9; j++)
	{
		temp[j] = getBoardElement(j, x);
		setBoardElement(j, x, getBoardElement(j, y));
		setBoardElement(j, y, temp[j]);
	}

}



