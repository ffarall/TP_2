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
				if (fracData->type == NULL)
				{
					fracData->type = value;
				}
				else
				{
					fracData->errorType = ERR_OVERWRITE;
					ret = 0;
				}
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
					if (isnan(fracData->lStart))
					{
						fracData->lStart = lStart;
					}
					else
					{
						fracData->errorType = ERR_OVERWRITE;
						ret = 0;
					}
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
					if (valid_lStart(lEnd))
					{
						if (isnan(fracData->lEnd))
						{
							fracData->lEnd = lEnd;
						}
						else
						{
							fracData->errorType = ERR_OVERWRITE;
							ret = 0;
						}
					}
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
					if (isnan(fracData->lConstant))
					{
						fracData->lConstant = lConstant;
					}
					else
					{
						fracData->errorType = ERR_OVERWRITE;
						ret = 0;
					}
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
					if (isnan(fracData->leftAngle))
					{
						fracData->leftAngle = angle;
					}
					else
					{
						fracData->errorType = ERR_OVERWRITE;
						ret = 0;
					}
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
					if (isnan(fracData->rightAngle))
					{
						fracData->rightAngle = angle;
					}
					else
					{
						fracData->errorType = ERR_OVERWRITE;
						ret = 0;
					}
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
				if (isnan(fracData->x0))
				{
					fracData->x0 = strtod(value, NULL);
				}
				else
				{
					fracData->errorType = ERR_OVERWRITE;
					ret = 0;
				}
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
				if (isnan(fracData->xf))
				{
					fracData->xf = strtod(value, NULL);
				}
				else
				{
					fracData->errorType = ERR_OVERWRITE;
					ret = 0;
				}
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
				if (isnan(fracData->y0))
				{
					fracData->y0 = strtod(value, NULL);
				}
				else
				{
					fracData->errorType = ERR_OVERWRITE;
					ret = 0;
				}
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
				if (isnan(fracData->yf))
				{
					fracData->yf = strtod(value, NULL);
				}
				else
				{
					fracData->errorType = ERR_OVERWRITE;
					ret = 0;
				}
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
	return (!str_case_cmp(value, "uniforme") || !str_case_cmp(value, "octogono") || !str_case_cmp(value, "mandelbrot"));
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
			fprintf(stderr, "Los parametros ingresados son incorrectos.\n El Mandelbrot recibe x0, y0, xf, e yf, teniendo en cuenta que el punto final debe ser distinto del inicial en ambas coordenadas.\n");
			ret = 0;
		}
	}
	else if (!str_case_cmp(data->type, "octogono"))
	{
		if (!valid_octogono(data))
		{
			fprintf(stderr, "Los parametros ingresados son incorrectos.\n El Octogono recibe lStart, lEnd, lConstant, x0 e y0, teniendo en cuenta que las coordenadas deben estar en el rango [%d,%d]x[%d,%d].\n", 0, OCTOGON_DISP_WIDTH, 0, OCTOGON_DISP_HEIGHT);
			ret = 0;
		}
	}
	else if (!str_case_cmp(data->type, "uniforme"))
	{
		if (!valid_uniforme(data))
		{
			fprintf(stderr, "Los parametros ingresados son incorrectos.\n El Uniforme recibe lStart, lEnd, leftAngle, rightAngle, x0 e y0.\n");
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
	case ERR_OVERWRITE: fprintf(stderr, "Se ingresaron parametros por duplicado.\nEl programa recibe los siguientes parametros por linea de comandos:\n-type {UNIFORME, OCTOGONO, MANDELBROT}\n-lStart (0...100]\n-lEnd (0...100).\n-lConstant (0...1).\n-leftAngle [-90...90].\n-rightAngle [-90...90].\n-x0, y0, xf, yf (pueden tomar valores flotantes).\n"); break;
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
	int areArgsValid = (isnan(data->lStart) && isnan(data->lEnd) && isnan(data->lConstant) && isnan(data->leftAngle) && isnan(data->rightAngle) && !isnan(data->x0) && !isnan(data->y0) && !isnan(data->xf) && !isnan(data->yf));
	int areCoordenatesSame = (data->x0 == data->xf || data->y0 == data->yf);
	return (areArgsValid && !areCoordenatesSame);
}

int valid_octogono(fractalData_n * data)
{
	int areArgsValid = (!isnan(data->lStart) && !isnan(data->lEnd) && !isnan(data->lConstant) && isnan(data->leftAngle) && isnan(data->rightAngle) && !isnan(data->x0) && !isnan(data->y0) && isnan(data->xf) && isnan(data->yf));
	int areCoordenatesInRange = (data->x0 >= 0 && data->x0 <= OCTOGON_DISP_WIDTH && data->y0 >= 0 && data->y0 <= OCTOGON_DISP_HEIGHT);
	return (areArgsValid && areCoordenatesInRange);
}

int valid_uniforme(fractalData_n * data)
{
	return (!isnan(data->lStart) && !isnan(data->lEnd) && isnan(data->lConstant) && !isnan(data->leftAngle) && !isnan(data->rightAngle) && !isnan(data->x0) && !isnan(data->y0) && isnan(data->xf) && isnan(data->yf));
}
