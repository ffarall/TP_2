#include <stdio.h>
#include "tp2_mandelbrot.h"
#include "parse_cmd_line.h"
#include "callback.h"
#include <math.h>
#include "fun_fractals.h"
#include "liballegro.h"
#include "uniforme.h"

int
main(int argc, char *argv[])
{
	fractalData_n data = { NULL, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, 0 }; // Se inicializa con valores que los datos no pueden tomar para luego hacer su comparación y validación
	if (parseCmdLine(argc, argv, cmd_line_interpreter, &data) == ERROR)
	{
		how_to(data.errorType);
		return -1;
	}
	else
	{
		if (valid_data(&data))
		{
			if (!str_case_cmp(data.type, "uniforme"))
			{
				allegroinit();
				ALLEGRO_DISPLAY * display = al_create_display(XMAX, YMAX);
				double delta = ALLEGRO_PI - data.leftAngle - data.rightAngle;
				double c = (180 - data.leftAngle + data.rightAngle)*ALLEGRO_PI / 180;
				data.leftAngle = data.leftAngle * ALLEGRO_PI / 180;
				data.rightAngle = -data.rightAngle * ALLEGRO_PI / 180;
				double b = (sin(data.rightAngle) / sin(delta)) * c;
				triangle(data.x0, data.y0, data.x0 + data.lStart * DISPLAY_CONST, data.y0, data.x0 + (data.lStart * DISPLAY_CONST *(sin(data.rightAngle)*cos(data.leftAngle)) / sin(c)), data.y0 - (data.lStart* DISPLAY_CONST *(sin(data.rightAngle)*sin(data.leftAngle)) / sin(c)), data.lEnd);
				
				printf("Para salir del programa presione 'q' y luego ENTER.\n");
				while (getchar() != 'q')
				{
					printf("Ingreso una tecla erronea. Para salir del programa presione 'q' y luego ENTER.\n");
				}

				al_destroy_display(display);
				return 0;
			}
			else if (!str_case_cmp(data.type, "octogono"))
			{
				if (init_allegro()) 
				{
					if (fun_octagon(data.x0, data.y0, data.lStart, data.lEnd, data.lConstant))
					{
						printf("Para salir del programa presione 'q' y luego ENTER.\n");
						while (getchar() != 'q')
						{
							printf("Ingreso una tecla erronea. Para salir del programa presione 'q' y luego ENTER.\n");
						}
						destroy_allegro();
					}
					else
					{
						return ERROR;
					}
				}
				else
				{
					return ERROR;
				}
			}
			else if (!str_case_cmp(data.type, "mandelbrot"))
			{
				complexPlane_n plane = { {data.x0, data.y0}, {data.xf, data.yf} };
				if (draw_mandelbrot(plane, MAX_ITERATIONS) == ERROR)
				{
					return ERROR;
				}
			}
		}
		else
		{
			return -1;
		}
	}


	return 0;
}