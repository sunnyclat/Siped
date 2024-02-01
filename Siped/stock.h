#ifndef STOCK_H
#define STOCK_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream.h>
#include <ctype.h>
typedef struct
{
	int posicion;
   int id_stk;
}indice_stock;

typedef struct {
 			      int d,m,a;
               }fecha_stock;

typedef struct
{
	int id_stk;
   char desc_stk[100];
   float precio;
   int cant_stock;
   fecha_stock fa_stk;
}stock;

void carga_stock(stock*);
void grabar_stock(FILE **, stock*);
void mostrar_stock (FILE **);
int busquedaBinaria(indice_stock *, int, int);
void quicksort(indice_stock *, int , int);
indice_stock * generaIndicestock(FILE**, int *, indice_stock *);
void mostrarRegistro(FILE**, int);
void modificar_stock(FILE **, int);
int valida(char []);
int valida_ingresocbo( void);

#endif