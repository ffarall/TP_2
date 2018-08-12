#ifndef _MANDELBROT_
#define _MANDELBROT_

/*****************************************
INCLUDES
*****************************************/
#include <stdio.h>
#include <minmax.h>
#include <complex.h>
#include <math.h>
#include <allegro5/allegro.h>

/*****************************************
DEFINES
*****************************************/
#define ERROR -1
#define DIS_WIDTH 600
#define DIS_HEIGHT 600

/*****************************************
TYPEDEFS
*****************************************/
typedef struct
{
	_Dcomplex Z0;
	_Dcomplex Zf;	// Vértices del plano complejo.
} complexPlane_n;

typedef struct
{
	_Dcomplex Zi;
	int iterations;						// Número de iteraciones.
	int maxIterations;
	complexPlane_n plane;
} mandelbrotData_n;

/*****************************************
FUN PROTOTIPES
*****************************************/
int
is_mandelbrot(_Dcomplex Zn, mandelbrotData_n *data);
int
mand_diverges(_Dcomplex Zn, double divergent);
_Dcomplex
fn(_Dcomplex Zn, _Dcomplex Zi);
int
draw_mandelbrot(complexPlane_n plane, int maxIterations);

#endif // _MANDELBROT_