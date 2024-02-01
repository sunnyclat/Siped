#include "clientes.h"
#include "archivos.h"
///////////////////////////////////////////////////////////////////
//objetivo: carga de datos del cliente
//Recibe: un puntero estructura
//Retorna: nada
///////////////////////////////////////////////////////////////////
void carga_clientes(clientes *ctes)
{
	printf("\nNombre y Apellido:  ");
	fflush(stdin);
	gets(ctes->nya_cliente);
	if(strcmpi(ctes->nya_cliente,"Z")!=0)
	{
   	printf("Ingrese la direccion: ");
      fflush(stdin);
      gets (ctes->dir_cliente);
      printf("Ingrese el telefono: ");
      fflush(stdin);
      gets (ctes->tel_cliente);
	}
  //else
  //{
    //system("cls");
    //puts("\nFin de carga, presione una tecla para continuar");

   //}
}
///////////////////////////////////////////////////////////////////
//objetivo: graba datos del cliente
//Recibe: un puntero estructura
//Retorna: nada
///////////////////////////////////////////////////////////////////
void grabar_clientes(FILE **arch, clientes * ctes)
{
	int cli;
   int cant;
   time_t t;
   struct tm *tiempo;
   t=time(NULL);
   tiempo=localtime(&t);
   clientes aux;
/*   if((arch=fopen("clientes.dat","rb+"))==NULL)
   	if((arch=fopen("clientes.dat","wb+"))==NULL)
      	{printf("\n No hay memoria");
         getch();
         exit(1);
         }
*/
   fseek(*arch,0L,SEEK_END);
   cant=ftell(*arch)/sizeof(clientes);
   fseek(*arch,0L,SEEK_SET);
   if(cant==0)
   	{
//      	cant = ftell(arch)/sizeof(clientes);
   		ctes->id_cliente = 1000;
//   		ctes->id_cliente = cant+1;//cnt;
   		ctes->fa_cliente.d = tiempo->tm_mday;
   		ctes->fa_cliente.m = tiempo->tm_mon+1;
   		ctes->fa_cliente.a = tiempo->tm_year+1900;
      	fwrite(ctes,sizeof(clientes),1,*arch);
        //	fseek(arch,0L,SEEK_CUR);
      }
   else
		{
//		   fseek(arch,0L,SEEK_END);
		   fseek(*arch,-1L*sizeof(clientes),SEEK_END);
      //         cli=cant + 1;
//			cli=random(999)+1000;
//			fseek(arch,0L,SEEK_SET);
			fread(&aux,sizeof(clientes),1,*arch);
         cli=aux.id_cliente;
/*			while(!feof(arch))
  			{
            if (cli<ctes->id_cliente)
  	 				cli=ctes->id_cliente;
  		  		fread(&ctes,sizeof(clientes),1,arch);
//            randomize();
//				cli=random(999)+1000;
      //getch();
  			}
*/
        cli=cli+1;
//      	fseek(arch, 0L, SEEK_END);
//   		cant = ftell(arch)/sizeof(clientes);
   		ctes->id_cliente = cli;//cnt;
   		ctes->fa_cliente.d = tiempo->tm_mday;
   		ctes->fa_cliente.m = tiempo->tm_mon+1;
   		ctes->fa_cliente.a = tiempo->tm_year+1900;
         fseek(*arch,0L,SEEK_END);
   		fwrite(ctes, sizeof(clientes), 1, *arch);
      	fseek(*arch,0L,SEEK_CUR);
      }
//	fclose(arch);
}
///////////////////////////////////////////////////////////////////
//objetivo: mostrar los clientes
//Recibe: un puntero estructura
//Retorna: nada
///////////////////////////////////////////////////////////////////
void mostrar(FILE **arch)
{
	clientes ctes;
  	//rewind(arch);
/*	if((arch=fopen("clientes.dat","rb+"))==NULL)
	{
   	printf("\n El archivo no existe");
      getch();
      exit(1);
   }
*/
	fseek(*arch,0L,SEEK_SET);
	fread(&ctes,sizeof(clientes),1,*arch);
	system("cls");//   clrscr();
	printf("\n\n %57s","LISTADO DE CLIENTES REGISTRADOS EN 'SIPED 2013'");
	printf("\n-----------------------------------------------------------------------------");
   printf("\n| ID | Nombre y Apell.	| Direccion		| Telefono	| Fecha	    |");
   printf("\n-----------------------------------------------------------------------------");
	while(!feof(*arch))
	{
		printf("\n-----------------------------------------------------------------------------");
  		printf("\n| %d  | %s	| %s	| %s	| %d/%d/%d |",ctes.id_cliente,ctes.nya_cliente,ctes.dir_cliente,ctes.tel_cliente,ctes.fa_cliente.d,ctes.fa_cliente.m, ctes.fa_cliente.a);
      fseek(*arch,0L,SEEK_CUR);
  		fread(&ctes,sizeof(clientes),1,*arch);
      //getch();
  }
      printf("\n-----------------------------------------------------------------------------");
      printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar ");
 //	fclose(arch);
}
///////////////////////////////////////////////////////////////////
//objetivo: mostrar los clientes historicos
//Recibe: un puntero estructura
//Retorna: nada
///////////////////////////////////////////////////////////////////
//void mostrar_hist(FILE **arch)
void mostrar_hist(FILE **arch)
{
   clientes ctes;//e,i,o;
//	int cod_cli;
//   FILE *ctes_hist;//,*ctes_temp;
//   clientes e,i,o;
//   char** archivos;
//   leer_path (archivos);
//   abrir_archivo (&ctes_hist, archivos, 3, "rb+");


//	clientes ctes;
	fseek(*arch,0L,SEEK_SET);
	fread(&ctes,sizeof(clientes),1,*arch);


//	fseek(ctes_hist,0L,SEEK_SET);
//	fread(&ctes,sizeof(clientes),1,ctes_hist);
	system("cls");//   clrscr();
	printf("\n\n %57s","LISTADO DE CLIENTES BORRADOS EN 'SIPED 2013'");
	printf("\n-----------------------------------------------------------------------------");
   printf("\n| ID | Nombre y Apell.	| Direccion		| Telefono	| Fecha	    |");
   printf("\n-----------------------------------------------------------------------------");
	while(!feof(*arch))
	{
		printf("\n-----------------------------------------------------------------------------");
  		printf("\n| %d  | %s	| %s	| %s	| %d/%d/%d |",ctes.id_cliente,ctes.nya_cliente,ctes.dir_cliente,ctes.tel_cliente,ctes.fa_cliente.d,ctes.fa_cliente.m, ctes.fa_cliente.a);
      fseek(*arch,0L,SEEK_CUR);
  		fread(&ctes,sizeof(clientes),1,*arch);
      //getch();
  }
      printf("\n-----------------------------------------------------------------------------");
      printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar ");
//   	fclose(ctes_hist);

 //	fclose(arch);
}
///////////////////////////////////////////////////////////////////
//objetivo: busqueda binaria del cliente
//Recibe: un puntero estructura
//Retorna: un entero con el valor de la posicion del registro
///////////////////////////////////////////////////////////////////
int busquedaBinaria(indice_cliente *vec, int buscado, int tam)
{
	int medio, inicio, fin;
   inicio = 0;
  	fin = tam-1;
  	while(inicio <= fin)
   {
		medio = ((inicio + fin) / 2);
		if(buscado == (vec+medio)->id_cliente)
   	{
			//printf("El DNI '%d' se encuentra en la posicion REAL'%d'\n\n",(vec+medio)->id_cliente,(vec+medio)->posicion+1);
   		return (vec+medio)->posicion ;
   	}
   	else
   	{
   		if(buscado <(vec+medio)->id_cliente)
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
//objetivo: buscar el indice del cliente
//Recibe: un puntero estructura, tamaño, indice
//Retorna: indice del cliente
///////////////////////////////////////////////////////////////////
indice_cliente * generaIndice(FILE **arch, int *tam, indice_cliente *vec)
{
	clientes reg;
	int i;
/*	if((arch=fopen("clientes.dat","rb+"))==NULL)
	{
   	printf("\n El archivo no existe");
      getch();
      exit(1);
   }
*/
	fseek(*arch,0,SEEK_END);
	*tam=ftell(*arch)/sizeof(clientes);
	vec=(indice_cliente*)malloc(*tam*sizeof(indice_cliente));
	if(!vec)
	{
		printf("Error de memoria al intentar crear el indice");
   	exit(1);
	}
  	rewind(*arch);
  	for(i=0;i<*tam;i++){
		fread(&reg,sizeof(clientes),1,*arch);
   	(vec+i)->posicion=i;
      (vec+i)->id_cliente=reg.id_cliente;
	}
	return vec;
//   fclose(arch);
}
///////////////////////////////////////////////////////////////////
//objetivo: ordenar por el metodo quick sort
//Recibe: un puntero estructura, tamaño, indice
//Retorna: nada
///////////////////////////////////////////////////////////////////
void quicksort(indice_cliente *vec, int izq, int der){
 		int i=izq,j=der;
  		int x;
  		indice_cliente aux;
     	x=((vec + ((izq+der)/2))->id_cliente);
      do{
     			while(((*(vec+i)).id_cliente <x) )	i++;
    			while((x<(*(vec+j)).id_cliente ) )	j--;
    			if(i<=j){
        			aux=*(vec+i);
      			*(vec+i) = *(vec+j);
      			*(vec+j) = aux;
      			i++;
      			j--;
    			}
  		}
      while(i<=j);
      if(izq<j) quicksort(vec,izq,j);
  		if(i<der) quicksort(vec,i,der);
}
///////////////////////////////////////////////////////////////////
//objetivo: mostrar el registros del cliente
//Recibe: un puntero estructura, posicion del cliente
//Retorna: nada
///////////////////////////////////////////////////////////////////
void mostrarRegistro_cli(FILE **arch, int pos)
{
	clientes reg;
	fseek(*arch,(pos)*sizeof(clientes),SEEK_SET);
	fread(&reg,sizeof(clientes),1,*arch);
	printf("\n-----------------------------------------------------------------------------");
	printf("\n| %d  | %s	| %s	| %s	| %d/%d/%d |",reg.id_cliente,reg.nya_cliente,reg.dir_cliente,reg.tel_cliente,reg.fa_cliente.d,reg.fa_cliente.m, reg.fa_cliente.a);
   printf("\n-----------------------------------------------------------------------------");
//   fclose(arch);
}

///////////////////////////////////////////////////////////////////
//objetivo: modificar un cliente a eleccion
//Recibe: un puntero estructura, posicion del registro
//Retorna: nada
///////////////////////////////////////////////////////////////////
void modificar_cliente (FILE **arch, int pos)
{
//   int i;
   clientes a;
/*	if((arch=fopen("clientes.dat","rb+"))==NULL)
	{
   	printf("\n El archivo no existe");
      getch();
      exit(1);
   }
*/
   fseek(*arch,(pos)*sizeof(clientes),SEEK_SET);
   fread(&a,sizeof(clientes),1,*arch);
//   printf("\nNombre y Apellido:  ");
//	gets(a.nya_cliente);
   printf("Ingrese la nueva direccion de entrega: ");
   gets (a.dir_cliente);
   printf("Ingrese el nuevo telefono: ");
   gets (a.tel_cliente);

   fseek(*arch,(-1)*sizeof(clientes),SEEK_CUR);
   fwrite(&a,sizeof(clientes),1,*arch);
  	fseek(*arch,0,SEEK_CUR);
//   getch();
//   fclose(arch);
}
///////////////////////////////////////////////////////////////////
//objetivo: valida que la cadena ingresada no tenga caracteres
//Recibe: una cadena de caracteres
//Retorna: un valor entero
///////////////////////////////////////////////////////////////////
int valida(char cad[])
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
int valida_ingreso(void)
{
	void clrscr(void);
   int valida(char[]);
   char numero[20];
   int intnumero;
   do
   {
//      clrscr();
		printf("\nIngrese el numero de CLIENTE a consultar: ");
 		scanf ("%s",&numero);
      fflush (stdin);
   }while(!valida(numero));
   intnumero=atoi(numero);
   return intnumero;
}
///////////////////////////////////////////////////////////////////
//objetivo: impedir el ingreso de caracteres
//Recibe: una estructura
//Retorna: un entero valido sin caracteres
///////////////////////////////////////////////////////////////////
int valida_ingreso_baja(void)
{
	void clrscr(void);
   int valida(char[]);
   char numero[20];
   int intnumero;
   do
   {
//      clrscr();
		printf("\nIngrese el numero de CLIENTE que desea dar de baja: ");
 		scanf ("%s",&numero);
      fflush (stdin);
   }while(!valida(numero));
   intnumero=atoi(numero);
   return intnumero;
}

///////////////////////////////////////////////////////////////////
//objetivo: baja de un cliente a eleccion
//Recibe: un puntero estructura, posicion del registro
//Retorna: nada
///////////////////////////////////////////////////////////////////
void baja_cliente (FILE **arch, FILE **arch2, FILE **arch3,int pos)
{
   clientes e,i,o;
	int cod_cli;
//   FILE *ctes_temp;
//   clientes e,i,o;
//   char** archivos;


//	clientes reg;
	fseek(*arch,(pos)*sizeof(clientes),SEEK_SET);
	fread(&i,sizeof(clientes),1,*arch);
	cod_cli = i.id_cliente;
//	indice_cliente **index;
//	*index= generaIndice(&clientes, &tam, *index); //levanta el indice a memoria

   int val,nro;//,estado;//	int j,nro,res,val,ni,nj,estado;
	char modo[10],aux[50];
//	FILE *ped_pf,*pedhist_pf,*pedtemp_pf;  // declaro los punteros
//   FILE *prod_pf;
//   leer_path (archivos);


//   abrir_archivo (&ctes_hist, archivoss, 3, "rb+");
//   abrir_archivo (&ctes_temp, archivos, 5, "rb+");


       	fseek(*arch,0L,SEEK_SET);
         fseek(*arch2,0L,SEEK_END);
         fread(&e,sizeof(clientes),1,*arch);

         while(!feof(*arch))
         {
          	if(e.id_cliente==cod_cli)
            {

               fwrite(&e,sizeof(clientes),1,*arch2);

//  					printf("\n\t\t<<< Realizando baja... >>>\n\n");
//               system("cls");
//               printf("\nBaja realizada con exito\n");
//			      printf("\nPresione una tecla para continuar\n");
//      			getch();

//                fwrite(&e,sizeof(struct_pedido),1,pedtemp_pf);

            }
            else
            {
             	fwrite(&e,sizeof(clientes),1,*arch3);
            }
            fread(&e,sizeof(clientes),1,*arch);
			}
/*         cerrar_archivo(&prod_pf,direcciones,2);
         cerrar_archivo(&ped_pf,direcciones,3);
   		cerrar_archivo(&pedhist_pf,direcciones,6);
         cerrar_archivo(&pedtemp_pf,direcciones,7);
*/
   	fclose(*arch);
   	fclose(*arch3);
//   	fclose(ctes_hist);
//         remove(*(archivos+0));
//         rename(*(archivos+5),*(archivos+0));

//   abrir_archivo (&clientes, archivos, 0, "rb+");  //los abro
//	abrir_archivo (&ctes_temp,archivos,5,"wb+");
//   	abrir_archivo(&ctes_temp,archivos,5,"wb+");

//   abrir_archivo (&ctes_temp, archivos, 0, "ab+");  //
//   abrir_archivo (&ctes_temp, archivos, 0, "rb+");  //
}

