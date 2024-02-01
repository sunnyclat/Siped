#ifndef INFORME_H
#define INFORME_H
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdlib.h>
int cantcli_informe(FILE **);
void pedencurso_informe(FILE **);
void pedentregados_informe (FILE **);
void mostrar_eventos(FILE **);

typedef struct
{
	int d,m,a;
}fecha_eventos;

typedef struct
{
	int h,m;
}hora_eventos;

typedef struct
{
fecha_eventos fecha_eve;
hora_eventos hora_eve;
char desc_eve[100];
char message[100];
} eventos;

#endif


