#include <stdio.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "liballegro.h"

#define WIDTH 640
#define HEIGHT 640

ALLEGRO_DISPLAY * display;

int init_allegro(void)
{
	int answer = 1;
	if (!al_init())
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		answer = -1;
	}

	display = al_create_display(WIDTH, HEIGHT);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		answer = -1;
	}

	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "failed to initialize primitives addon!\n");
		answer = -1;
	}

	return answer;
}

void destroy_allegro(void)
{
	al_destroy_display(display);
}