#pragma once
#include "Consts.h"

class Class_Sudoku
{
	char board[COL][ROW];
	int state;
	int start_null;
public:
	Class_Sudoku();
	Class_Sudoku(const char * file);	
	~Class_Sudoku();
	

	void copyClass(const Class_Sudoku);
	void copyClass(const Class_Sudoku*);

	void setDefault();
	void setBoard(const char*);
	void setBoardElement(int,int,char);
	void setState(int STATE);
	void setNull(int);
	void setNullPlus();
	void setNullMinus();

	void copyBoard(const Class_Sudoku);
	void copyBoard(const Class_Sudoku*);

	char getBoardElement(int,int) const;
	int getState() const;
	int getNull() const;

	void swapROW(int, int);
	void swapCOL(int, int);

	
};

