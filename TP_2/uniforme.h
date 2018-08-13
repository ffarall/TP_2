#ifndef _UNIFORME_
#define _UNIFORME_

/*****************************************
INCLUDES
*****************************************/
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include <math.h>

/*****************************************
DEFINES
*****************************************/
#define XMAX 800
#define YMAX 800

/*****************************************
TYPEDEFS
*****************************************/

/*****************************************
FUN PROTOTIPES
*****************************************/
void allegroinit(void);
int triangle(float x1, float y1, float x2, float y2, float x3, float y3, float);
bool validarlargos(float centrox, float centroy, float x1, float y1, float x2, float y2, float x3, float y3, float lend);

#endif // _UNIFORME_