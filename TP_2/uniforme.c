#include "uniforme.h"



int triangle(float x1, float y1, float x2, float y2, float x3, float y3, float lfinal)
{
	srand(time(NULL));
	al_draw_triangle(x1, y1, x2, y2, x3, y3, al_map_rgb(rand()%256, rand()%256, rand()%256), 1); // cambiar color aca	
	al_flip_display();
	al_rest(0.05);
	int tempx = (x1 + x2 + x3) / 3.0, tempy = ((y1 + y2 + y3) / 3.0);

	if (!validarlargos(tempx, tempy, x1, y1, x2, y2, x3, y3, lfinal))																	// reviso area del triangulo a crear para que no sea demasiado chico
	{
		triangle(tempx, tempy, x1, y1, x2, y2, lfinal);
		triangle(tempx, tempy, x1, y1, x3, y3, lfinal);
		triangle(tempx, tempy, x2, y2, x3, y3, lfinal);
	}
	else
	{
		return 0;
	}
}


int validarlargos(float centrox, float centroy, float x1, float y1, float x2, float y2, float x3, float y3, float lend)
{
	int rta = 0;
	float aux1 = x1 - centrox;
	float aux2 = y1 - centroy;
	if (((aux1*aux1) + (pow(aux2, 2))) <= pow(lend, 2))
	{
		rta = 1;
	}
	aux1 = x2 - centrox;
	aux2 = y2 - centroy;
	if (((aux1*aux1) + (pow(aux2, 2))) <= (pow(lend, 2)))
	{
		rta = 1;
	}
	aux1 = x3 - centrox;
	aux2 = y3 - centroy;
	if (((aux1*aux1) + (pow(aux2, 2))) <= (pow(lend, 2)))
	{
		rta = 1;
	}
	return rta;


}

void allegroinit(void)
{
	al_init();
	al_init_primitives_addon();

}