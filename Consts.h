#ifndef SUDOKU_H_
#define SUDOKU_H_

//A jatek allapotai
#define NOT_IN_GAME 0
#define RUNNING_STATE 1
#define QUIT_STATE 2
#define PLAYER_WON 3
#define SOMETHING_WRONG 4
#define BTN_STATE 5

//A fix tabla meretei
#define COL 9
#define ROW 9

//Pixelbeli meret
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

//A Sudoku tabla meretei
#define INNER_SCREEN_WIDTH 300
#define INNER_SCREEN_HEIGHT 300

//Egy negyzet meretei
#define cell_width (INNER_SCREEN_WIDTH / ROW)
#define cell_height (INNER_SCREEN_HEIGHT/ COL)

typedef struct {
	int x, y;
}Selected;

#endif 