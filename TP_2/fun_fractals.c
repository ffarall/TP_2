#include "fun_fractals.h"

int fun_octagon(double x, double y, double l, double lEnd, double lConstant)
{
	int answer = 0;
	int contador = 0;
	
	//En las variables add_y, add_x se almacena cuanto hay que moverse para llegar hacia el proximo vertice
	double add_y;
	double add_x;
	
	
	double alpha = M_PI/4.0;   //pi/4 = 45° ----> Angulo interno alpha de un octogono

	//Las coordenadas xi, yi, xf, yf son coordenadas que se utilizaran para moverme por los vertices del octogono "principal"
	double xi = x + (l/2);						
	double yi = y - (l/2) - (l*(cos(alpha)));
	double xf = xi;
	double yf = yi;

	draw_octagon(l, x, y);	//Dibujo el octogono "principal"

	if ((l*lConstant) >= lEnd) //Mientras el largo de los lados del octogono no sea menor al largo final, se ejecuta lo siguiente
	{
		//Recorro todos los vertices	
		for (contador=1 ; contador<= N_LADOS; contador++)
		{
			add_y = l * (sin(contador * (M_PI / 4))); //Se calcula cuanto hay que moverse en el eje y
			add_x = l * (cos(contador *(M_PI / 4)));  //Se calcula cuanto hay que moverse en el eje x
		
			//Actualizo las nuevas coordenadas
			xf += add_x;							 
			yf += add_y;

			answer = fun_octagon(xf, yf, (l*lConstant), lEnd, lConstant);
		}	
	}
	else
	{
		answer = 1;
	}

	return answer;	
}

void draw_octagon(double l, double x, double y)
{
	int contador = 0;
	ALLEGRO_COLOR color = al_map_rgb(255, 255, 0); //Color AMARILLO

	double alpha = M_PI/4.0f;   //pi/4 = 45° ----> Angulo interno alpha de un octogono

	//Las coordenadas xi, yi, xf, yf son coordenadas que se utilizaran para moverme por los vertices del octogono "principal"
	//Las coordenadas xi, yi se utilizan para el punto inicial de la linea y las coordenadas xf, yf se utilizan para el punto final
	double xi = x + (l / 2.0f);
	double yi = y - (l / 2.0f) - (l*(cos(alpha)));
	double xf;
	double yf;

	//En las variables add_y, add_x se almacena cuanto hay que moverse para llegar hacia el proximo vertice
	double add_y;
	double add_x;

	//Recorro todos los vertices
	for (contador=1; contador<= N_LADOS; contador++, xi = xf, yi = yf)
	{
		add_y = l*(sin(contador * (M_PI / 4)));
		add_x = l*(cos(contador * (M_PI / 4)));
		xf = xi + add_x;
		yf = yi + add_y;
		al_draw_line(xi, yi, xf, yf, color, 3);
		al_flip_display();
	}
}