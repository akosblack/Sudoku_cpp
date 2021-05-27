#ifndef TEXT_H_
#define TEXT_H_

#include "Render.h"

//SDL_Rect tipusu hely tarolo
void DestPosition(int x, int y, int w, int h);

//*char altal kapott szoveg megjelenitese
void text_render(char *szoveg, SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color TextColor);

#endif 