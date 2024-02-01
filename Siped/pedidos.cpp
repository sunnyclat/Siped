#include "pedidos.h"
#include "clientes.h"
#include "stock.h"
#include "informe.h"
///////////////////////////////////////////////////////////////////
//objetivo: carga de datos del pedido
//Recibe: un puntero estructura
//Retorna: nada
///////////////////////////////////////////////////////////////////
void carga_pedidos(FILE **arch,FILE **arch1,pedidos *ped)
{
  char listado, listadocbo;
  int existe_cli,existe_cbo,cod_cbo;
  printf("\nIngrese Numero del cliente (Finaliza con 0):  ");
  fflush(stdin);
  scanf("%d",&ped->cliente_ped);

  if(ped->cliente_ped!=0)
  {
		if((existe_cli=valida_cliente(ped->cliente_ped))==0)
      {
      	printf("El cliente %d no existe, desea ver listado de clientes (S/N)?",ped->cliente_ped);
         fflush(stdin);
         scanf("%c",&listado);
         switch(listado)
         {
         	case 'S':
            mostrar(arch);
            break;
            case 's':
            mostrar(arch);
            break;
            case 'N':
            break;
            case 'n':
            break;
            default:
            printf("opcion no valida");
            break;
         }
         ped->cliente_ped=1;
         getch();
      }
      else
      {
			printf("\nIngrese Combo:  ");
  			fflush(stdin);
     		scanf ("%d",&ped->ped_cbo);

			if((existe_cbo=valida_combo(ped->ped_cbo))==0)
	      {
   	   	printf("El COMBO %d no existe, desea ver listado de combos (S/N)?",ped->ped_cbo);
      	   fflush(stdin);
         	scanf("%c",&listadocbo);
	         switch(listadocbo)
   	      {
      	   	case 'S':
         	   mostrar_stock(arch1);
	            break;
   	         case 's':
      	      mostrar_stock(arch1);
         	   break;
	            case 'N':
   	         break;
      	      case 'n':
         	   break;
            	default:
	            printf("opcion no valida");
   	         break;
      	   }
	         ped->cliente_ped=1;
         	getch();
         }
         else
         {
				printf("Ingrese Cantidad de combos: ");
   	   	fflush(stdin);
      		scanf ("%d",&ped->ped_cant);
			}
      }

  }
}
///////////////////////////////////////////////////////////////////
//objetivo: graba datos del pedido
//Recibe: un puntero estructura
//Retorna: nada
///////////////////////////////////////////////////////////////////
void grabar_pedidos(FILE **arch, pedidos * ped,FILE ** arch_eventos)
{

	if(ped->cliente_ped!=1)
	{
		int cant=0;
	   time_t t;
   	struct tm *tiempo;
	   t=time(NULL);
   	tiempo=localtime(&t);

  	FILE* arch1=NULL;
   stock stk1;
   eventos eve;
   if((arch1=fopen("stock.dat","rb+"))==NULL)
   {
   	printf("\n No se puede acceder al archivo stock.dat");
      getch();
      exit(1);
   }
   fseek(arch1, 0L, SEEK_SET);
	fread(&stk1,sizeof(stock),1,arch1);
   while(stk1.id_stk!=(ped->ped_cbo))
   	fread(&stk1,sizeof(stock),1,arch1);
   stk1.cant_stock=stk1.cant_stock-(ped->ped_cant);

   	//EVENTOS
   	if(stk1.cant_stock<=10)
      	{printf("\n ¡Stock minimo alcanzado! Mensaje agregado a archivo eventos.txt.");

         fseek(*arch_eventos,0L,SEEK_END);
         eve.fecha_eve.d = tiempo->tm_mday;
	   	eve.fecha_eve.m = tiempo->tm_mon+1;
   		eve.fecha_eve.a = tiempo->tm_year+1900;

	   	eve.hora_eve.h = tiempo->tm_hour;
   		eve.hora_eve.m = tiempo->tm_min;

         strcpy(eve.desc_eve,stk1.desc_stk);

         strcpy(eve.message,"Stock minimo alcanzado, reponer combo.");

         fwrite(&eve,sizeof(eventos),1,*arch_eventos);
         fseek(*arch_eventos,0L,SEEK_CUR);
         }


   ped->impo_serv=stk1.precio*(ped->ped_cant);
   fseek(arch1,-1L*sizeof(stock),SEEK_CUR);
   fwrite(&stk1,sizeof(stock),1,arch1);

	   fseek(*arch, 0L, SEEK_END);
   	cant = ftell (*arch)/sizeof(pedidos);
	   ped->id_ped = cant+1;
   	ped->fecha_ped.d = tiempo->tm_mday;
	   ped->fecha_ped.m = tiempo->tm_mon+1;
   	ped->fecha_ped.a = tiempo->tm_year+1900;

	   ped->hora_ped.h = tiempo->tm_hour;
   	ped->hora_ped.m = tiempo->tm_min;

	   strcpy (ped->est_ped, "EN CURSO");
   	fwrite(ped, sizeof(pedidos), 1, *arch);

	}
}
///////////////////////////////////////////////////////////////////
//objetivo: mostrar los pedidos
//Recibe: un puntero estructura
//Retorna: nada
///////////////////////////////////////////////////////////////////
void mostrar_pedidos(FILE **arch)
{
	pedidos ped;
	fseek(*arch,0L,SEEK_SET);
	fread(&ped,sizeof(pedidos),1,*arch);
	system("cls");//   clrscr();
	printf("\n\n %57s","LISTADO DE PEDIDOS REGISTRADOS EN 'SIPED 2013'");
	printf("\n-----------------------------------------------------------------------------");
   printf("\n| Id | Fecha | Hora | Cli | Cbo | Cant | Estado | Importe |");
   printf("\n-----------------------------------------------------------------------------");

  	while (!feof(*arch))
  	{
		printf("\n-----------------------------------------------------------------------------");
  		printf("\n| %d  | %02d/%02d | %02d:%02d | %d  | %d | %d	| %s	| %.2f |",ped.id_ped,ped.fecha_ped.d,ped.fecha_ped.m, ped.hora_ped.h, ped.hora_ped.m,ped.cliente_ped,ped.ped_cbo,ped.ped_cant,ped.est_ped,ped.impo_serv);
      fseek(*arch,0L,SEEK_CUR);
	  fread(&ped,sizeof(pedidos),1,*arch);
	}
	printf("\n-----------------------------------------------------------------------------");
   printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar ");

}
///////////////////////////////////////////////////////////////////
//objetivo: valida el numero del cliente
//Recibe: numero del cliente
//Retorna: un entero valido
///////////////////////////////////////////////////////////////////
int valida_cliente (int nro_cli)
{
	FILE* arch=NULL;
	clientes cli;
   if((arch=fopen("clientes.dat","rb+"))==NULL)
   {
   	printf("\n No se puede acceder al archivo clientes.dat");
      getch();
      exit(1);
   }
   fseek(arch, 0L, SEEK_SET);
   while(!feof(arch))
   {
		if(cli.id_cliente==nro_cli) return(1);
		fread(&cli,sizeof(clientes),1,arch);
   }
   return(0);
   fclose(arch);
}
///////////////////////////////////////////////////////////////////
//objetivo: valida el numero del combo
//Recibe: numero del combo
//Retorna: un entero valido
///////////////////////////////////////////////////////////////////
int valida_combo (int nro_stk)
{
	FILE* arch=NULL;
   stock stk;
   //	clientes cli;
   if((arch=fopen("stock.dat","rb+"))==NULL)
   {
   	printf("\n No se puede acceder al archivo stock.dat");
      getch();
      exit(1);
   }
   fseek(arch, 0L, SEEK_SET);
   while(!feof(arch))
   {
		if(stk.id_stk==nro_stk) return(1);
		fread(&stk,sizeof(stock),1,arch);
   }
   return(0);
}

///////////////////////////////////////////////////////////////////
//objetivo: busqueda binaria del pedidos
//Recibe: un puntero estructura
//Retorna: un entero con el valor de la posicion del registro
///////////////////////////////////////////////////////////////////
int busquedaBinariaped(indice_ped *vec, int buscado, int tam)
{
	int medio, inicio, fin;
   inicio = 0;
  	fin = tam-1;
  	while(inicio <= fin)
   {
		medio = ((inicio + fin) / 2);
		if(buscado == (vec+medio)->id_ped)
   	{
			//printf("El DNI '%d' se encuentra en la posicion REAL'%d'\n\n",(vec+medio)->id_cliente,(vec+medio)->posicion+1);
   		return (vec+medio)->posicion ;
   	}
   	else
   	{
   		if(buscado <(vec+medio)->id_ped)
      	{
      		fin = medio - 1;
      	}
      	else
      	{
      		inicio = medio + 1;
      	}
   	}
	}
   return -1;
}
///////////////////////////////////////////////////////////////////
//objetivo: buscar el indice del pedido
//Recibe: un puntero estructura, tamaño, indice
//Retorna: indice del pedido
///////////////////////////////////////////////////////////////////
indice_ped * generaIndiceped(FILE **arch, int *tam, indice_ped *vec)
{
	pedidos reg;
	int i;
	fseek(*arch,0,SEEK_END);
	*tam=ftell(*arch)/sizeof(pedidos);
	vec=(indice_ped*)malloc(*tam*sizeof(indice_ped));
	if(!vec)
	{
		printf("Error de memoria al intentar crear el indice");
   	exit(1);
	}
  	rewind(*arch);
  	for(i=0;i<*tam;i++){
		fread(&reg,sizeof(pedidos),1,*arch);
   	(vec+i)->posicion=i;
      (vec+i)->id_ped=reg.id_ped;
	}
	return vec;
//   fclose(arch);
}
///////////////////////////////////////////////////////////////////
//objetivo: ordenar por el metodo quick sort
//Recibe: un puntero estructura, tamaño, indice
//Retorna: nada
///////////////////////////////////////////////////////////////////
void quicksortped(indice_ped *vec, int izq, int der){
 		int i=izq,j=der;
  		int x;
  		indice_ped aux;
     	x=((vec + ((izq+der)/2))->id_ped);
      do{
     			while(((*(vec+i)).id_ped <x) )	i++;
    			while((x<(*(vec+j)).id_ped ) )	j--;
    			if(i<=j){
        			aux=*(vec+i);
      			*(vec+i) = *(vec+j);
      			*(vec+j) = aux;
      			i++;
      			j--;
    			}
  		}
      while(i<=j);
      if(izq<j) quicksortped(vec,izq,j);
  		if(i<der) quicksortped(vec,i,der);
}
///////////////////////////////////////////////////////////////////
//objetivo: mostrar el registros del pedido
//Recibe: un puntero estructura, posicion del pedido
//Retorna: nada
///////////////////////////////////////////////////////////////////
void mostrarRegistroped(FILE **arch, int pos)
{
	pedidos ped;
	fseek(*arch,(pos)*sizeof(pedidos),SEEK_SET);
	fread(&ped,sizeof(pedidos),1,*arch);
	printf("\n-----------------------------------------------------------------------------");
  		printf("\n| %d  | %02d/%02d | %02d:%02d | %d  | %d | %d	| %s	| %.2f |",ped.id_ped,ped.fecha_ped.d,ped.fecha_ped.m, ped.hora_ped.h, ped.hora_ped.m,ped.cliente_ped,ped.ped_cbo,ped.ped_cant,ped.est_ped,ped.impo_serv);
   printf("\n-----------------------------------------------------------------------------");
//   fclose(arch);
}

///////////////////////////////////////////////////////////////////
//objetivo: modificar un pedido a eleccion
//Recibe: un puntero estructura, posicion del registro
//Retorna: nada
///////////////////////////////////////////////////////////////////
void modificar_ped (FILE **arch, int pos)
{

   pedidos ped;
   fseek(*arch,(pos)*sizeof(pedidos),SEEK_SET);
   fread(&ped,sizeof(pedidos),1,*arch);

     	printf("Ingrese Combo: ");
     	fflush(stdin);
     	scanf ("%d",&ped.ped_cbo);
		printf("Ingrese Cantidad de combos: ");
     	fflush(stdin);
     	scanf ("%d",&ped.ped_cant);

   fseek(*arch,(-1)*sizeof(pedidos),SEEK_CUR);
   fwrite(&ped,sizeof(pedidos),1,*arch);
   fseek(*arch,0,SEEK_CUR);
//   getch();
//   fclose(arch);
}
///////////////////////////////////////////////////////////////////
//objetivo: valida que la cadena ingresada no tenga caracteres
//Recibe: una cadena de caracteres
//Retorna: un valor entero
///////////////////////////////////////////////////////////////////
int validaped(char cad[])
{
    int i;
    int c=0;
    for(i=0;i<strlen(cad);i++)
        if (!isdigit(cad[i]))
            c++;

    if (c>0)
        return 0; //tiene caracteres
    else
       return 1; //no tiene caracteres
}
///////////////////////////////////////////////////////////////////
//objetivo: impedir el ingreso de caracteres
//Recibe: una estructura
//Retorna: un entero valido sin caracteres
///////////////////////////////////////////////////////////////////
int valida_ingresoped( void)
{
	void clrscr(void);
   int valida(char[]);
   char numero[20];
   int intnumero;
   do
   {
		printf("\nIngrese el numero de PEDIDO a consultar: ");
 		scanf ("%s",&numero);
      fflush (stdin);
   }while(!valida(numero));
   intnumero=atoi(numero);
   return intnumero;
}
////////////////////////////////////////////////////////////////////
//objetivo: baja logica de un pedido
//Recibe: estructura, posicion del pedido
//Retorna: nada
////////////////////////////////////////////////////////////////////
void baja_logica(FILE **arch,int pos)
{

   pedidos ped;
   fseek(*arch,(pos)*sizeof(pedidos),SEEK_SET);
   fread(&ped,sizeof(pedidos),1,*arch);
     strcpy (ped.est_ped,"ENTREGADO");

   fseek(*arch,(-1)*sizeof(pedidos),SEEK_CUR);
   fwrite(&ped,sizeof(pedidos),1,*arch);
   fseek(*arch,0,SEEK_CUR);
//   getch();
//   fclose(arch);
}

