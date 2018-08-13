#ifndef FUN_FRACTALS_H
#define FUN_FRACTALS_H

#define N_LADOS 8
#define _USE_MATH_DEFINES  

#include <stdio.h>
#include <stdlib.h>
#include <math.h>  
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

int fun_octagon(double x, double y, double l, double lEnd, double lConstant);
void draw_octagon(double l, double x, double y);

#endif
