#ifndef _UNIFORME_
#define _UNIFORME_

/*****************************************
INCLUDES
*****************************************/
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include <math.h>
#include <time.h>

/*****************************************
DEFINES
*****************************************/
#define XMAX 800
#define YMAX 800
#define DISPLAY_CONST 6

/*****************************************
TYPEDEFS
*****************************************/

/*****************************************
FUN PROTOTIPES
*****************************************/
void allegroinit(void);
int triangle(float x1, float y1, float x2, float y2, float x3, float y3, float);
int validarlargos(float centrox, float centroy, float x1, float y1, float x2, float y2, float x3, float y3, float lend);

#endif // _UNIFORME_