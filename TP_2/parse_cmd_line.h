#ifndef _PARSE_CMD_LINE_
#define _PARSE_CMD_LINE_

/*****************************************
				INCLUDES
*****************************************/
#include <stdio.h>

/*****************************************
				DEFINES
*****************************************/
#define ERROR -1

/*****************************************
				TYPEDEFS
*****************************************/
typedef int(*pCallback) (char *, char*, void *);

/*****************************************
			FUN PROTOTIPES
*****************************************/
int 
parseCmdLine(int argc, char *argv[], pCallback p, void *userData);

#endif // _PARSE_CMD_LINE_