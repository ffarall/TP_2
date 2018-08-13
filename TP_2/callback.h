#ifndef _CALLBACK_
#define _CALLBACK_

/*****************************************
INCLUDES
*****************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/*****************************************
DEFINES
*****************************************/
#define ERR_NO_KEY 256
#define ERR_WRONG_TYPE 257
#define ERR_WRONG_LSTART 258
#define ERR_WRONG_LEND 259
#define ERR_WRONG_LCONSTANT 260
#define ERR_WRONG_LEFT_ANGLE 261
#define ERR_WRONG_RIGHT_ANGLE 262
#define ERR_UNKNOWN_KEY 263
#define ERR_ALPHA_LSTART 265
#define ERR_ALPHA_LEND 266
#define ERR_ALPHA_LCONSTANT 267
#define ERR_ALPHA_LEFT_ANGLE 268
#define ERR_ALPHA_RIGHT_ANGLE 269
#define ERR_ALPHA_COORDINATE 270
#define ERR_OVERWRITE 271
#define OCTOGON_DISP_WIDTH 800
#define OCTOGON_DISP_HEIGHT 800


/*****************************************
TYPEDEFS
*****************************************/
typedef struct
{
	char *type;
	double lStart;
	double lEnd;
	double lConstant;
	double leftAngle;
	double rightAngle;
	double x0;
	double y0;
	double xf;
	double yf;
	int errorType;
}fractalData_n;

/*****************************************
FUN PROTOTIPES
*****************************************/
int
cmd_line_interpreter(char *key, char *value, void *data);
int
str_case_cmp(char *str1, char *str2);					// Max 100 characters per string.
void
str_to_lwr(char *str);
int
valid_type(char *value);
int
valid_lStart(double lStart);
int
valid_lEnd(double lEnd);
int
valid_lConstant(double lConstant);
int
valid_angle(double angle);
int
valid_data(fractalData_n *data);
void
how_to(int error);
int
strisalpha(char *str);
int
valid_mandelbrot(fractalData_n *data);
int
valid_octogono(fractalData_n *data);
int
valid_uniforme(fractalData_n *data);

#endif // _CALLBACK_
