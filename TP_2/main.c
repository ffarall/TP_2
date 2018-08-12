#include <stdio.h>
#include "tp2_mandelbrot.h"

int
main(int argc, char *argv[])
{
	complexPlane_n plane = { {-2, -2}, {2, 2} };
	if (draw_mandelbrot(plane, 256))
	{
		return -1;
	}

	return 0;
}