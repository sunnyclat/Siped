#include "stock.h"
////////////////////////////////////////////////////////////////////////
void carga_stock(stock *stk)
{
	printf("\n Ingrese Detalle del Combo: ");
   fflush(stdin);
	gets (stk->desc_stk);
	if(strcmpi(stk->desc_stk,"Z")!=0)
	{
		printf("Ingrese la precio del Combo: ");
      fflush(stdin);
      scanf ("%f", &stk->precio);
		printf("Ingrese la cantidad disponible para este Combo: ");
      fflush(stdin);
      scanf ("%d", &stk->cant_stock);
	}
  	else
  //{
    //system("cls");
    puts("\nFin de carga, presione una tecla para continuar");
   //}
}
////////////////////////////////////////////////////////////////////////
void grabar_stock(FILE **arch, stock * stk)
{
   int cant=0;
   time_t t;
   struct tm *tiempo;
   t=time(NULL);
   tiempo=localtime(&t);
/*
   if((arch=fopen("stock.dat","rb+"))==NULL)
   	if((arch=fopen("stock.dat","wb+"))==NULL)
      	{printf("\n No hay memoria");
         getch();
         exit(1);
         }
*/
   fseek(*arch, 0L, SEEK_END);
   cant = ftell (*arch)/sizeof(stock);
   stk->id_stk = cant+1;
   stk->fa_stk.d = tiempo->tm_mday;
   stk->fa_stk.m = tiempo->tm_mon+1;
   stk->fa_stk.a = tiempo->tm_year+1900;
   fwrite(stk, sizeof(stock), 1, *arch);
//	fclose(arch);
}
////////////////////////////////////////////////////////////////////////
void mostrar_stock(FILE**arch)
{
	stock stk;
	rewind(*arch);
/*	if((arch=fopen("stock.dat","rb+"))==NULL)
  	{
   	printf("\n El archivo no existe");
      getch();
      exit(1);
   }
*/
	fread(&stk,sizeof(stock),1,*arch);
	system("cls");//   clrscr();
	printf("\n\n %57s","LISTADO DE COMBOS EN 'SIPED 2013'");
	printf("\n-----------------------------------------------------------------------------");
   printf("\n|Cbo | Descripcion			    	 | Precio | Stk | Fecha C/M |");
   printf("\n-----------------------------------------------------------------------------");
	while (!feof(*arch))
	{
		printf("\n-----------------------------------------------------------------------------");
  		printf("\n| %d  | %s		  | %.2f | %d | %d/%d/%d |",stk.id_stk,stk.desc_stk,stk.precio,stk.cant_stock,stk.fa_stk.d,stk.fa_stk.m, stk.fa_stk.a);
		fread(&stk,sizeof(stock),1,*arch);
	}
   printf("\n-----------------------------------------------------------------------------");
   printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar ");
//	fclose(arch);
}
////////////////////////////////////////////////////////////////////////
int busquedaBinaria(indice_stock *vec, int buscado, int tam)
{
	int medio, inicio, fin;
   inicio = 0;
  	fin = tam-1;
  	while(inicio <= fin)
   {
		medio = ((inicio + fin) / 2);
		if(buscado == (vec+medio)->id_stk)
   	{
			//printf("El DNI '%d' se encuentra en la posicion REAL'%d'\n\n",(vec+medio)->id_cliente,(vec+medio)->posicion+1);
   		return (vec+medio)->posicion ;
   	}
   	else
   	{
   		if(buscado <(vec+medio)->id_stk)
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
indice_stock * generaIndicestock(FILE**arch, int *tam, indice_stock *vec)
{
	stock reg;
	int i;
/*	if((arch=fopen("stock.dat","rb+"))==NULL)
	{
   	printf("\n El archivo no existe");
      getch();
      exit(1);
   }
*/
	fseek(*arch,0,SEEK_END);
	*tam=ftell(*arch)/sizeof(stock);
	vec=(indice_stock*)malloc(*tam*sizeof(indice_stock));
	if(!vec)
	{
		printf("Error de memoria al intentar crear el indice");
   	exit(1);
	}
  	rewind(*arch);
  	for(i=0;i<*tam;i++){
		fread(&reg,sizeof(stock),1,*arch);
   	(vec+i)->posicion=i;
      (vec+i)->id_stk=reg.id_stk;
	}
	return vec;
//   fclose(arch);
}
///////////////////////////////////////////////////////////////////
void quicksort(indice_stock *vec, int izq, int der){
 		int i=izq,j=der;
  		int x;
  		indice_stock aux;
     	x=((vec + ((izq+der)/2))->id_stk);
      do{
     			while(((*(vec+i)).id_stk <x) )	i++;
    			while((x<(*(vec+j)).id_stk ) )	j--;
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
void mostrarRegistro(FILE** arch, int pos)
{
	stock stk;//reg;
/*	if((arch=fopen("stock.dat","rb+"))==NULL)
	{
   	printf("\n El archivo no existe");
      getch();
      exit(1);
   }
*/
	fseek(*arch,(pos)*sizeof(stock),SEEK_SET);
	fread(&stk,sizeof(stock),1,*arch);
	printf("\n-----------------------------------------------------------------------------");
  		printf("\n| %d  | %s		  | %.2f | %d | %d/%d/%d |",stk.id_stk,stk.desc_stk,stk.precio,stk.cant_stock,stk.fa_stk.d,stk.fa_stk.m, stk.fa_stk.a);
   printf("\n-----------------------------------------------------------------------------");
//   fclose(arch);
}

///////////////////////////////////////////////////////////////////
void modificar_stock (FILE **arch, int pos)
{
   int i;
   stock stk;
   char aux[100];
/*	if((arch=fopen("stock.dat","rb+"))==NULL)
	{
   	printf("\n El archivo no existe");
      getch();
      exit(1);
   }
*/
   fseek(*arch,(pos)*sizeof(stock),SEEK_SET);
   fread(&stk,sizeof(stock),1,*arch);
//   printf("\nNombre y Apellido:  ");
//	gets(a.nya_cliente);
   printf("Detalle el combo a modificar: ");
   fflush(stdin);
   gets(aux);
   strcpy(stk.desc_stk,aux);

//   gets (stk.desc_stk);
   printf("Ingrese el precio: ");
   fflush(stdin);
   scanf ("%f", &stk.precio);
	printf("Ingrese la cantidad disponible para este Combo: ");
   fflush(stdin);
   scanf ("%d", &stk.cant_stock);

   fseek(*arch,-1L*sizeof(stock),SEEK_CUR);
   fwrite(&stk,sizeof(stock),1,*arch);
//   getch();
//   fclose(arch);
}
///////////////////////////////////////////////////////////////////
int valida(char cad[])  //funcion valida que la cadena ingresada no tenga caracteres
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
int valida_ingresocbo( void) //aqui se hace el trabajo de impedir el ingreso de caracteres y retorna un integer que es el
                           // numero ingresado valido, sin caracteres
{
	void clrscr(void);
   int valida(char[]);
   char numero[20];
   int intnumero;
   do
   {
//      clrscr();
		printf("\nIngrese el numero de COMBO a consultar: ");
 		scanf ("%s",&numero);
      fflush (stdin);
   }while(!valida(numero));
   intnumero=atoi(numero);
   return intnumero;
}

