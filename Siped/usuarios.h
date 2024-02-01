#ifndef USUARIOS_H
#define USUARIOS_H
#include <conio.h>
#include <iostream.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
///////////////////////////////////////////////////////////////////
/*
typedef struct
{
	int usu_codigo;
   char usu_nombre[30];
   char usu_usu[10];
   char usu_password[10];
   int usu_estado;
   int usu_categoria;
}usuarios;
*/

typedef struct
{
	int posicion;
   int id_usuario;
}indice_usu;

typedef struct
{
 	int d,m,a;
}fecha_usuario;

typedef struct
{
	int id_usuario;
   char nya_usuario[30];
   char sis_usuario[10];
   char pass_usuario[10];
   int usu_estado;
   int usu_categoria;
   fecha_usuario fa_usuario;
}usuarios;

///////////////////////////////////////////////////////////////////
int fun_contar(char*);
void carga_usuarios(usuarios*);
void grabar_usuarios(FILE **, usuarios*);
void mostrar_usuarios (FILE **);

int usu_validauser(char **,char*,char*);

//void mostrar_hist (FILE **);
//void mostrar_hist (void);
int busquedaBinariausu(indice_usu *, int, int);
void quicksortusu(indice_usu *, int , int);
indice_usu * generaIndiceusu(FILE **, int *, indice_usu *);
void mostrarRegistro_usu(FILE **, int);
void modificar_usuario(FILE **, int);
int validausu(char []);
int valida_ingresousu( void);
//void baja_cliente(FILE **, int);
//void baja_clientes(FILE **, clientes*);
///////////////////////////////////////////////////////////////////
#endif


