#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING 1000

void SetStringLog(char* str)
{
	FILE* fptr;

	fptr = fopen("./program.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	fprintf(fptr, "Log strign: %s\n", str);
	fclose(fptr);
}

void SetStringLogDouble(char *name, double value)
{
	FILE* fptr;

	fptr = fopen("./program.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	fprintf(fptr, "Log %s: %f\n", name, value);
	fclose(fptr);
}
void ClearFile()
{
	FILE* fptr;

	fptr = fopen("./program.txt", "w");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	fprintf(fptr, " ");
	fclose(fptr);
}
