#include "callback.h"

int
cmd_line_interpreter(char *key, char *value, void *data)
{
	int ret = 1;
	fractalData_n *fracData = data;
	if (key != NULL)
	{
		if (!str_case_cmp(key, "type"))
		{
			if (valid_type(value))
			{
				fracData->type = value;
			}
			else
			{
				fracData->errorType = ERR_WRONG_TYPE;
				ret = 0;
			}
		}
		else if (!str_case_cmp(key, "lstart"))
		{
			if (strisalpha(value))
			{
				fracData->errorType = ERR_ALPHA_LSTART;
				ret = 0;
			}
			else
			{
				double lStart = strtod(value, NULL);
				if (valid_lStart(lStart))
				{
					fracData->lStart = lStart;
				}
				else
				{
					fracData->errorType = ERR_WRONG_LSTART;
					ret = 0;
				}
			}
		}
		else if (!str_case_cmp(key, "lend"))
		{
			if (strisalpha(value))
			{
				fracData->errorType = ERR_ALPHA_LEND;
				ret = 0;
			}
			else
			{
				double lEnd = strtod(value, NULL);
				if (valid_lEnd(lEnd))
				{
					fracData->lEnd = lEnd;
				}
				else
				{
					fracData->errorType = ERR_WRONG_LEND;
					ret = 0;
				}
			}
		}
		else if (!str_case_cmp(key, "lconstant"))
		{
			if (strisalpha(value))
			{
				fracData->errorType = ERR_ALPHA_LCONSTANT;
				ret = 0;
			}
			else
			{
				double lConstant = strtod(value, NULL);
				if (valid_lConstant(lConstant))
				{
					fracData->lConstant = lConstant;
				}
				else
				{
					fracData->errorType = ERR_WRONG_LCONSTANT;
					ret = 0;
				}
			}
		}
		else if (!str_case_cmp(key, "leftangle"))
		{
			if (strisalpha(value))
			{
				fracData->errorType = ERR_ALPHA_LEFT_ANGLE;
				ret = 0;
			}
			else
			{
				double angle = strtod(value, NULL);
				if (valid_angle(angle))
				{
					fracData->leftAngle = angle;
				}
				else
				{
					fracData->errorType = ERR_WRONG_LEFT_ANGLE;
					ret = 0;
				}
			}
		}
		else if (!str_case_cmp(key, "rightangle"))
		{
			if (strisalpha(value))
			{
				fracData->errorType = ERR_ALPHA_RIGHT_ANGLE;
				ret = 0;
			}
			else
			{
				double angle = strtod(value, NULL);
				if (valid_angle(angle))
				{
					fracData->rightAngle = angle;
				}
				else
				{
					fracData->errorType = ERR_WRONG_RIGHT_ANGLE;
					ret = 0;
				}
			}
		}
		else if (!str_case_cmp(key, "x0"))
		{
			if (strisalpha(value))
			{
				fracData->errorType = ERR_ALPHA_COORDINATE;
				ret = 0;
			}
			else
			{
				fracData->x0 = strtod(value, NULL);
			}
		}
		else if (!str_case_cmp(key, "xf"))
		{
			if (strisalpha(value))
			{
				fracData->errorType = ERR_ALPHA_COORDINATE;
				ret = 0;
			}
			else
			{
				fracData->xf = strtod(value, NULL);
			}
		}
		else if (!str_case_cmp(key, "y0"))
		{
			if (strisalpha(value))
			{
				fracData->errorType = ERR_ALPHA_COORDINATE;
				ret = 0;
			}
			else
			{
				fracData->y0 = strtod(value, NULL);
			}
		}
		else if (!str_case_cmp(key, "yf"))
		{
			if (strisalpha(value))
			{
				fracData->errorType = ERR_ALPHA_COORDINATE;
				ret = 0;
			}
			else
			{
				fracData->yf = strtod(value, NULL);
			}
		}
		else
		{
			printf("%s\n", key);
			fracData->errorType = ERR_UNKNOWN_KEY;
			ret = 0;
		}
	}
	else
	{
		fracData->errorType = ERR_NO_KEY;
		ret = 0;
	}

	return ret;
}

int str_case_cmp(char * str1, char * str2)
{
	char auxStr1[100];
	char auxStr2[100];
	strcpy_s(auxStr1, 100, str1);
	str_to_lwr(auxStr1);
	strcpy_s(auxStr2, 100, str2);	// Uso strcpy_s porque usando strcpy Visual me hacia saltar un error.
	str_to_lwr(auxStr2);

	return strcmp(auxStr1, auxStr2);
}

void str_to_lwr(char * str)
{
	int i = 0;
	while (*(str + i) != '\0')
	{
		if (isupper(*(str + i)))
		{
			*(str + i) = tolower(*(str + i));
		}
		i++;
	}
}

int valid_type(char * value)
{
	return (!str_case_cmp(value, "uniforme") || !str_case_cmp(value, "octogono") || !str_case_cmp(value, "	mandelbrot"));
}

int valid_lStart(double lStart)
{
	return (lStart > 0 && lStart <= 100);
}

int valid_lEnd(double lEnd)
{
	return (lEnd > 0 && lEnd < 100);
}

int valid_lConstant(double lConstant)
{
	return (lConstant > 0 && lConstant < 1);
}

int valid_angle(double angle)
{
	return (angle >= -90 && angle <= 90);
}

int valid_data(fractalData_n * data)
{
	int ret = 1;
	if (!str_case_cmp(data->type, "mandelbrot"))
	{
		if (!valid_mandelbrot(data))
		{
			printf("%d %d %d %d\n", data->x0, data->y0, data->xf, data->yf);
			fprintf(stderr, "Los parametros ingresados son incorrectos.\n El Mandelbrot recibe x0, y0, xf, e yf.\n");
			ret = 0;
		}
	}
	else if (!str_case_cmp(data->type, "octogono"))
	{
		if (!valid_octogono(data))
		{
			fprintf(stderr, "Los parametros ingresados son incorrectos.\n El Octogono recibe lStart, lEnd, lConstant, x0, y0, xf, e yf.\n");
			ret = 0;
		}
	}
	else if (!str_case_cmp(data->type, "uniforme"))
	{
		if (!valid_uniforme(data))
		{
			fprintf(stderr, "Los parametros ingresados son incorrectos.\n El Uniforme recibe lStart, lEnd, lConstant, leftAngle, rightAngle, x0, y0, xf, e yf.\n");
			ret = 0;
		}
	}
	else
	{
		fprintf(stderr, "Se ingreso un tipo de fractal no esperado.\n Se espera recibir UNIFORME, OCTOGONO o MANDELBROT.\n");
		ret = 0;
	}
	
	return ret;
}

void how_to(int error)
{
	switch (error)
	{
	case ERR_NO_KEY: fprintf(stderr, "Se recibio un argumento sin un key.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_WRONG_TYPE: fprintf(stderr, "Se recibio un tipo de fractal invalido.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_WRONG_LSTART: fprintf(stderr, "Parametro lStart fuera de rango.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_WRONG_LEND: fprintf(stderr, "Parametro lEnd fuera de rango.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_WRONG_LCONSTANT: fprintf(stderr, "Parametro lConstant fuera de rango.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_WRONG_LEFT_ANGLE: fprintf(stderr, "Parametro leftAngle fuera de rango.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_WRONG_RIGHT_ANGLE: fprintf(stderr, "Parametro rightAngle fuera de rango.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_UNKNOWN_KEY: fprintf(stderr, "Se ingreso una key no reconocida.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_ALPHA_LSTART: fprintf(stderr, "Se ingresaron caracteres invalidos en lStart.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_ALPHA_LEND: fprintf(stderr, "Se ingresaron caracteres invalidos en lEnd.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_ALPHA_LCONSTANT: fprintf(stderr, "Se ingresaron caracteres invalidos en lConstant.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_ALPHA_LEFT_ANGLE: fprintf(stderr, "Se ingresaron caracteres invalidos en leftAngle.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_ALPHA_RIGHT_ANGLE: fprintf(stderr, "Se ingresaron caracteres invalidos en rightAngle.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	case ERR_ALPHA_COORDINATE: fprintf(stderr, "Se ingresaron caracteres invalidos en alguna de las coordenadas.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
	}
}

int strisalpha(char * str)
{
	int i = 0;
	while (*(str + i) != '\0')
	{
		if (isalpha(*(str + i)))
		{
			return 1;
		}
		i++;
	}
	return 0;
}

int valid_mandelbrot(fractalData_n * data)
{
	return (isnan(data->lStart) && isnan(data->lEnd) && isnan(data->lConstant) && isnan(data->leftAngle) && isnan(data->rightAngle) && !isnan(data->x0) && !isnan(data->y0) && !isnan(data->xf) && !isnan(data->yf));
}

int valid_octogono(fractalData_n * data)
{
	return (!isnan(data->lStart) && !isnan(data->lEnd) && !isnan(data->lConstant) && isnan(data->leftAngle) && isnan(data->rightAngle) && !isnan(data->x0) && !isnan(data->y0) && isnan(data->xf) && isnan(data->yf));
}

int valid_uniforme(fractalData_n * data)
{
	return (!isnan(data->lStart) && !isnan(data->lEnd) && !isnan(data->lConstant) && !isnan(data->leftAngle) && !isnan(data->rightAngle) && !isnan(data->x0) && !isnan(data->y0) && !isnan(data->xf) && !isnan(data->yf));
}
