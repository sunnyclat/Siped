#ifndef PEDIDOS_H
#define PEDIDOS_H
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdlib.h>
////////////////////////////////////////////////////////////////////////
typedef struct
{
	int posicion;
   int id_ped;
}indice_ped;

typedef struct
{
	int d,m,a;
}fecha_pedidos;

typedef struct
{
	int h,m;
}hora_pedidos;

/*
typedef struct
{
	int cod_prod;

}productos
*/
typedef struct
{
	int id_ped;
   fecha_pedidos fecha_ped; //FECHA DE HOY
   hora_pedidos hora_ped;
   int cliente_ped;
   int ped_cbo;
   int ped_cant;
   //   char obs_serv[101];
   char est_ped[21];
   float impo_serv;
   //fecha_servicios ff_serv; //FECHA EN QUE EL ESTADO SE PUSO EN CUMPLIDO
   char gtia_serv[11];
}pedidos;
////////////////////////////////////////////////////////////////////////
void carga_pedidos(FILE **,FILE **,pedidos*);
void grabar_pedidos(FILE **, pedidos*,FILE **);
void mostrar_pedidos(FILE **);
int  valida_cliente(int);
int valida_combo(int);

int busquedaBinariaped(indice_ped *, int, int);
void quicksortped(indice_ped *, int , int);
indice_ped * generaIndiceped(FILE **, int *, indice_ped *);
void mostrarRegistroped(FILE **, int);
void modificar_ped(FILE **, int);
int validaped(char []);
int valida_ingresoped( void);
//void des_cbo_cal_pre (int*,int*,float*);
void baja_logica (FILE **,int);
#endif