#include "parse_cmd_line.h"

int
parseCmdLine(int argc, char *argv[], pCallback p, void *userData)
{
	int ret = 0, i;
	for (i = 1; i < argc; i++)
	{
		if (*argv[i] == '-')
		{
			if (p((argv[i++]+1), argv[i], userData))
			{
				ret += 1;
			}
			else
			{
				return ERROR;
			}
		}
		else
		{
			if (p(NULL, argv[i], userData))
			{
				ret += 1;
			}
			else
			{
				return ERROR;
			}
		}
	}
	return ret;
}