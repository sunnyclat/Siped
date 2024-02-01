#include "siped.h"
///////////////////////////////////////////////////////////////////
//objetivo: Mostrar principal el menu del sistema
//Recibe: nada
//Retorna: un entero con la eleccion seleccionada
///////////////////////////////////////////////////////////////////
int menu_gral (int menu)
{
   int op=0;
   while (op<1 || op>6)
   {
	  	clrscr();
		printf("///////////////////////////////////////////////////\n");
		printf("Materia: LENGUAJE DE PROGRAMACION III           \n");
		printf("Proyecto 1: SISTEMA DE PEDIDOS                  \n");
		printf("Profesora: ISABEL MARKO                         \n");
		printf("///////////////////////////////////////////////////\n");
		printf(" Integrantes:                                      \n");
		printf(" ------------                                      \n");
		printf(" SAMUEL LUDUENA                                    \n");
		printf(" RODRIGO CONDE                                     \n");
		printf(" IVAN ROSEMBLUN                                    \n");
		printf(" IVAN ALARCON                                      \n");
		printf("///////////////////////////////////////////////////\n");
   	printf("\n SISTEMA DE PEDIDOS (SIPED) \n");
		printf("---------------------------\n");
     	if(menu==1 || menu==2)
      {
		   printf ("1. CLIENTES\n");
   		printf ("2. PEDIDOS\n");
	   	printf ("3. COMBOS\n");
   		printf ("4. INFORMES\n");
	     	if(menu==1)
   	   {
		   	printf ("5. USUARIOS\n");
			}
			printf ("6. SALIR\n");
   	   printf("\n\n Elegir una opcion: ");
      	scanf("%d",&op);
		}

     	if(menu==3)
      {
   		printf ("2. PEDIDOS\n");
   		printf ("4. INFORMES\n");
			printf ("6. SALIR\n");
   	   printf("\n\n Elegir una opcion: ");
      	scanf("%d",&op);
		}
   }
	return(op);
}
///////////////////////////////////////////////////////////////////
//objetivo: Mostrar el menu de clientes del sistema
//Recibe: nada
//Retorna: un entero con la eleccion seleccionada
///////////////////////////////////////////////////////////////////
int menu_ctes (void)
{
   int op2=0;
   while (op2<1 || op2>6)
   {
	  	clrscr();
   	printf("\n SIPED - CLIENTES \n");
		printf("------------------- \n");
     	printf ("1-Alta de clientes\n");
      printf ("2-Listar Todos\n");
      printf ("3-Consulta y Modificacion de un Cliente\n");
      printf ("4-Baja de un cliente (fisica)\n");
      printf ("5-Listar Clientes Borrados (archivo historica)\n");
      printf ("6-Salir\n");
      printf("\n\n Elegir una opcion: ");
      scanf("%d",&op2);
   }
	return(op2);
}
///////////////////////////////////////////////////////////////////
//objetivo: Mostrar el menu de pedidos del sistema
//Recibe: nada
//Retorna: un entero con la eleccion seleccionada
///////////////////////////////////////////////////////////////////
int menu_pedi (int menu)
{
   int op3=0;
   while (op3<1 || op3>5)
   {
	  	clrscr();
   	printf("\n SIPED - PEDIDOS \n");
		printf("-------------------------\n");
     	if(menu==1 || menu==2)
      {
	     	printf ("1-Alta de Pedidos\n");
      }
      printf ("2-Listar todo\n");
     	if(menu==1 || menu==2)
      {
	      printf("3-Consulta y Modificacion de Servicios\n");
      }
      printf("4-Marcar pedido como entregado\n");
      printf("5-Volver\n");
      printf("\n\n Elegir una opcion: ");
      scanf("%d",&op3);
   }
	return(op3);
}
///////////////////////////////////////////////////////////////////
//objetivo: Mostrar el menu combos del sistema
//Recibe: nada
//Retorna: un entero con la eleccion seleccionada
///////////////////////////////////////////////////////////////////
int menu_stock (void)
{
	int op5=0;
   while (op5<1 || op5>4)
   {
   	clrscr();
   	printf("\n SIPED - COMBOS \n");
		printf("-------------------------\n");
     	printf ("1-Alta de Combos\n");
      printf ("2-Consulta de Combos\n");
      printf ("3-Consulta y Modificacion de Combos\n");
      printf ("4-Salir\n");
      printf("\n\n Elegir una opcion: ");
		scanf ("%d", &op5);
//   			fflush (stdin);
   }
   return (op5);
}
///////////////////////////////////////////////////////////////////
//objetivo: Mostrar el menu informes del sistema
//Recibe: nada
//Retorna: un entero con la eleccion seleccionada
///////////////////////////////////////////////////////////////////
int menu_informe (void)
{
	int op4=0;
   while (op4<1 || op4>5)
   	{
      	clrscr();
         printf("\n SIPED - INFORMES \n");
         printf("-------------------------\n");
         printf("1-Cantidad de clientes registrados\n");
         printf("2-Consulta de pedidos en curso\n");
         printf("3-Consulta de pedidos entregados\n");
         printf("4-Eventos\n");
         printf("5-Volver\n");
         printf("\n\n Elegir una opcion: ");
         scanf("%d",&op4);
      }
      return(op4);
}
///////////////////////////////////////////////////////////////////
//objetivo: Mostrar el menu de usuarios del sistema
//Recibe: nada
//Retorna: un entero con la eleccion seleccionada
///////////////////////////////////////////////////////////////////
int menu_usu (void)
{
   int op6=0;
   while (op6<1 || op6>4)
   {
	  	clrscr();
   	printf("\n SIPED - USUARIOS \n");
		printf("------------------- \n");
     	printf ("1-Alta de Usuarios\n");
      printf ("2-Listar Todos\n");
      printf ("3-Consulta y Modificacion de usuario\n");
      printf ("4-Salir\n");
      printf("\n\n Elegir una opcion: ");
      scanf("%d",&op6);
   }
	return(op6);
}

