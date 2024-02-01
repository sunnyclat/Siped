#ifndef CLIENTES_H
#define CLIENTES_H
#include <conio.h>
#include <iostream.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
///////////////////////////////////////////////////////////////////
typedef struct
{
	int posicion;
   int id_cliente;
}indice_cliente;

typedef struct
{
 	int d,m,a;
}fecha_clientes;

typedef struct
{
	int id_cliente;
   char nya_cliente[61];
   char dir_cliente[61];
   char tel_cliente[21];
   fecha_clientes fa_cliente;
}clientes;
///////////////////////////////////////////////////////////////////
void carga_clientes(clientes*);
void grabar_clientes(FILE **, clientes*);
void mostrar (FILE **);
void mostrar_hist (FILE **);
//void mostrar_hist (void);
int busquedaBinaria(indice_cliente *, int, int);
void quicksort(indice_cliente *, int , int);
indice_cliente * generaIndice(FILE **, int *, indice_cliente *);
void mostrarRegistro_cli(FILE **, int);
void modificar_cliente(FILE **, int);
int valida(char []);
int valida_ingreso( void);
int valida_ingreso_baja( void);
void baja_cliente(FILE **,FILE **,FILE **, int);
//void baja_clientes(FILE **, clientes*);
///////////////////////////////////////////////////////////////////
#endif