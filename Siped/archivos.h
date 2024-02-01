#ifndef archivos_h
#define archivos_h
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include <time.h>
///////////////////////////////////////////////////////////////////
int Ver_Cant_Archivos(void);
void leer_path(char**);
void abrir_archivo(FILE **, char**, int ,char *);
int cerrar_archivo(FILE **, char**, int);
void login(FILE *,char*,char*,int); //funcion que escribe el login de los archivos
///////////////////////////////////////////////////////////////////
#endif
