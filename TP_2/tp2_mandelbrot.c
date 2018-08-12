#include "tp2_mandelbrot.h"

int draw_mandelbrot(complexPlane_n plane, int maxIterations)
{
	double dx = fabs(creal(plane.Zf) - creal(plane.Z0)) / DIS_WIDTH;
	double dy = fabs(cimag(plane.Zf) - cimag(plane.Z0)) / DIS_HEIGHT;
	mandelbrotData_n data = { { plane.Z0._Val[0],plane.Z0._Val[1] }, 0, 256, plane};
	_Dcomplex start = { 0, 0 };

	ALLEGRO_DISPLAY *display = NULL;
	int i, j;

	if (al_init())
	{
		if (display = al_create_display(DIS_WIDTH, DIS_HEIGHT))
		{
			if (!al_init_image_addon())
			{
				fprintf(stderr, "Could not load image addon.\n");
				al_destroy_display(display);
				al_uninstall_system();
				return -1;
			}
		}
		else
		{
			fprintf(stderr, "Could not create display.\n");
			al_uninstall_system();
			return -1;
		}
	}
	else
	{
		fprintf(stderr, "Could not initialize Allegro.\n");
		return -1;
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_set_target_backbuffer(display);
	for (i = 0; i < DIS_WIDTH; i++)
	{
		for (j = 0; j < DIS_HEIGHT; j++)
		{
			data.iterations = 0;
			data.Zi._Val[1] += dy;
			if (is_mandelbrot(start, &data))
			{
				al_put_pixel(i, j, al_map_rgb(0, 0, 0));
			}
			else if (data.iterations >= (data.maxIterations - 235))
			{
				al_put_pixel(i, j, al_map_rgb(255, 255, 255));
			}
			else
			{
				al_put_pixel(i, j, al_map_rgb(50, 50, 255/data.iterations));
			}
		}
		data.Zi._Val[1] = plane.Z0._Val[1];
		data.Zi._Val[0] += dx;
	}
	al_flip_display();

	printf("Para salir del programa presione 'q' y luego ENTER.\n");

	while (getchar() != 'q')
	{
		printf("Ingreso una tecla erronea. Para salir del programa presione 'q' y luego ENTER.\n");
	}

	al_shutdown_image_addon();
	al_destroy_display(display);
	al_uninstall_system();
	return 0;
}

int
is_mandelbrot(_Dcomplex Zn, mandelbrotData_n *data)
{
	if (mand_diverges(Zn, max(fabs(creal(data->plane.Zf) - creal(data->plane.Z0)), fabs(cimag(data->plane.Zf) - cimag(data->plane.Z0)))))
	{
		return 0;
	}
	else if (data->iterations >= data->maxIterations)
	{
		return 1;
	}
	else
	{
		data->iterations++;
		is_mandelbrot(fn(Zn, data->Zi), data);
	}
}

int 
mand_diverges(_Dcomplex Zn, double divergent)
{
	double mod = cabs(Zn);
	return mod > divergent;
}

_Dcomplex 
fn(_Dcomplex Zn, _Dcomplex Zi)
{
	_Dcomplex square = { 2, 0 };
	_Dcomplex aux = cpow(Zn, square);
	_Dcomplex ret = { creal(aux) + creal(Zi), cimag(aux) + cimag(Zi) };
	return ret;
}

