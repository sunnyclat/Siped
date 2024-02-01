// EJERCICIO QUE MUESTRA EL USO DE ESTRUCTURAS Y ARCHIVOS BINARIOS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <time.h>
typedef struct {
 			      int d,m,a;
               }fecha;

typedef struct  {
 			      char ayn[31];
               int leg;
               fecha fnac;
               float suel;
               }dato;

typedef struct  {
 			      int posicion;
               int leg;
               }indice;

/////////////////////////   DECLARACION DE FUNCIONES //////////////////////////
int Ver_Cant_Archivos(void);
void mostrar(FILE*);
void carga_datos(dato*);
void abrir_archivo(FILE **, char**, int ,char *) ;
void grabar(FILE *, dato *);
void eliminacion(int  );
void actualizacion(FILE*);
void login(FILE *,char*,char*,int); //funcion que escribe el login de los archivos
int menu();
void path(char**); //funcion que lee los path desde un text file
////////////////////////////////////////////////////////////////////////////////
int busquedaBinaria(indice *, int , int);
void quicksort(indice *, int , int);
indice * generaIndice(FILE*, int *, indice *);
void mostrarRegistro(FILE*, int);
////////////////////////////////////////////////////////////////////////////////

int main()
{
 dato reg;
 indice **index=NULL;
 FILE *arch1, *archh,*archn, *archlpt;
 int cant_archivos,leg,tam,pos;
 char **archivos=NULL; //vector de cadenas que contendra los paths
 cant_archivos = Ver_Cant_Archivos();
 if(!(archivos=(char **) malloc(cant_archivos*sizeof(char*))))
 {
       printf("ERROR AL RESERVAR MEMORIA\n");
       getch();
       exit(1);
 }
 path(archivos); //carga los paths
 /**************************
 Posicion 0: Corresponde a archivos.dat
 Posicion 1: Corresponde a arch_nuevo.dat
 Posicion 2: Corresponde a historicos.dat
 Posicion 3: Corresponde a login.txt

 ***************************/
 abrir_archivo(&arch1,archivos,0,"w+"); //archivos.dat
 printf("%45s","Ingreso de Datos\n\n");
 printf("para terminar la carga escribir como nombre fin\n\n");fflush(stdin);
  carga_datos(&reg);
 while (strcmpi(reg.ayn,"fin"))
 {
  grabar(arch1,&reg) ;
  carga_datos(&reg);
 }
 getch();
 system("cls");     //clrscr();


 printf("%52s ","***Datos Ingresados***\n");
 printf("%52s" ,"**********************\n\n");
 mostrar(arch1);
 getch();

 /////////////////////////////////////////////////////////////////////////////
 printf("\n\n\n%45s","Consulta aleatoria\n\n");
 if(!(index=(indice **) malloc(sizeof(indice*))))
 {
       printf("ERROR AL RESERVAR MEMORIA\n");
       getch();
       exit(1);
 }
 *index= generaIndice(arch1, &tam, *index); //levanta el indice a memoria
 quicksort(*index, 0, tam); //ordena el indice en memoria
 printf("\ningrese Numero de legajo a consultar: \n"); fflush(stdin);
 scanf ("%d",&leg);
 printf("\neste es: %d ",leg );
 getch();
 pos=busquedaBinaria(*index, leg, tam);
 if(pos==-1) printf("\nEl legajo no existe\n");
 else mostrarRegistro(arch1, pos);
//////////////////////////////////////////////////////////////////////////////
 getch();
 system("cls");
 rewind(arch1);


  printf("\n%45s","Creacion de archivo historico y nuevo\n\n");
  abrir_archivo(&archn,archivos,1,"w+"); //arch_nuevo.dat
  abrir_archivo(&archh,archivos,2,"w+"); //historicos.dat
  printf("\ningrese Numero de legajo a eliminar: \n"); fflush(stdin);
  scanf ("%d",&leg);
  printf("\neste es: %d ",leg );
  getch();
  while(leg!=0)
  {
  fread(&reg,sizeof(dato),1,arch1);
   while(!feof(arch1))
   {
  		if(leg!=reg.leg )
      	 grabar(archn,&reg);
       else
          grabar(archh,&reg);

 	 fread(&reg,sizeof(dato),1,arch1);
    }
   printf("\ningrese Otro Nro. de legajo a eliminar \n");
   printf("Si desea terminar ingrese 0\n"); fflush(stdin);
   scanf ("%d",&leg);
   }
   fclose( archh);
   fclose(arch1);
   remove("archivos.dat");
   fclose(archn);
   rename("arch_nuevo.dat","archivos.dat");
   system("cls");
   printf("\n%45s","ARCHIVO HISTORICO\n\n"); fflush(stdin);
   abrir_archivo(&archh,archivos,2,"r+"); //historicos.dat
   mostrar(archh);
   fclose(archh);
   getch();
   system("cls");
   printf("\n%45s","ARCHIVO NUEVO\n\n"); fflush(stdin);
   abrir_archivo(&arch1,archivos,0,"r+"); //archivos.dat
   mostrar(arch1);
   getch();
   system("cls");
   printf("\n%45s"," Actualizacion\n\n");
   actualizacion(arch1);
   rewind(arch1);
   system ("cls");
   printf("\n%45s","Archivo con Datos Actualizados\n\n");fflush(stdin);
   mostrar(arch1);
   free(archivos);
   free(index);
   getch();
 }
 /*...............Funciones
 -----------------------------------------*/
 // ********** determina la cantidad de archivos a trabajar ***************
 int  Ver_Cant_Archivos(void)
 {    char linea[80];
      int cont=0;
      FILE *arch;
      if((arch=fopen("path.txt","r"))==NULL)//el archivo de path esta en el dir
      //donde se ejecuta el programa
      {
   	      printf("ERROR EN EL ACCESO AL ARCHIVO\n");
            getch();
            exit(1);
      }
        fgets(linea,80,arch);
        while(!feof(arch))
          {cont++;
          fgets(linea,80,arch);
          }
      fclose(arch);
      return (cont-1);
 }
  //*******almacena los path*********//
 void path(char **archivos){
      char aux[80]="\0";
      int i=0,j;
      FILE *arch;
      if((arch=fopen("path.txt","r"))==NULL)//el archivo de path esta en el dir
      //donde se ejecuta el programa
      {
   	      printf("ERROR EN EL ACCESO AL ARCHIVO\n");
            getch();
            exit(1);
      }
      fseek(arch,0,SEEK_SET);
	  fscanf(arch,"%s", aux);//almacena el path en aux
       while (!feof(arch)){
           //if(!(*(archivos+i)= (char *) calloc (1, strlen(aux)+1))){
           if(!(*(archivos+i)= (char *) malloc (strlen(aux)+1))){
                printf("ERROR AL RESERVAR MEMORIA\n");
                getch();
                exit(1);
           }
	       strcpy(*(archivos+i),aux);
           strcat(*(archivos+i),"\0");
           //printf("%s\n",*(archivos+i));
           fscanf(arch,"%s", aux);//almacena el path en aux
           i++;
      }
 }
 //********apertura archivos******//
 void abrir_archivo(FILE **arch,char **archivos,int num,char *modo)
{
	FILE *log;

   	if((log=fopen(*(archivos+3),"a"))==NULL)
   {
      printf("ERROR EN EL ACCESO AL ARCHIVO DE LOGIN");
      getch();
      exit(1);
   }
    if((*arch=fopen(*(archivos+num),modo))==NULL)
   {
      printf("ERROR EN EL ACCESO AL ARCHIVO %s",*(archivos+num));
      login(log,*(archivos+num),modo,0);
      fclose(log);
      getch();
      exit(1);
   }
   login(log,*(archivos+num),modo,1);
   fclose(log);
}
//*******escritura en archivo de login********//
void login(FILE *log, char *nom, char *mod,int res){
     time_t t;
     struct tm *tiempo;
     t=time(NULL);
     tiempo=localtime(&t);
     fprintf(log,"Fecha %02d/%02d/%02d Hora %02d:%02d Archivo %s en modo %s ",
     tiempo->tm_mday,tiempo->tm_mon+1,tiempo->tm_year+1900,tiempo->tm_hour,tiempo->tm_min,nom,mod);
     if (res) fprintf(log,"correctamente abierto\n");
     else fprintf(log,"no se pudo abrir\n");
}
//********ESCRIBIR ARCHIVO*********//
void grabar(FILE *arch, dato *reg)
{
   fseek(arch, 0L, SEEK_END);
   fwrite(reg, sizeof(dato), 1, arch);
}
//*******CARGA DE DATOS*****//
void carga_datos(dato *reg)
{
  printf("\nApellido y Nombres         :  "); fflush(stdin);
  gets(reg->ayn);
  if(strcmpi(reg->ayn,"fin")!=0)
  {
      printf("Ingrese Numero de Legajo   :  ");fflush(stdin);
      scanf("%d",&reg->leg);
      printf("Ingrese fecha de nacimiento\n");
      printf("con el formato, dd/mm/aaaa :  ");fflush(stdin);
      scanf("%d/%d/%d",&reg->fnac.d,&reg->fnac.m,&reg->fnac.a);
      printf("%s","Ingrese Sueldo             :  $");fflush(stdin);
      scanf("%f",&reg->suel);
   }
   else
   {
    system("cls");
    puts("\n carga terminada, presione una tecla para continuar");
   }
}

void mostrar(FILE*arch)
{
  dato reg;
  rewind(arch);
  fread(&reg,sizeof(dato),1,arch);
  printf("Nombre ") ;
  printf("Nro. de Legajo ");
  printf("Fecha de nacimiento ");
  printf("Sueldo\n\n");
  while (!feof(arch))
  {
  printf("\n%s ",reg.ayn);
  printf("%d ",reg.leg);
  printf("%2d/%2d/%2d ",reg.fnac.d,reg.fnac.m,reg.fnac.a);
  printf("%7.2f ",reg.suel);
  fread(&reg,sizeof(dato),1,arch);
  }
 }

//******MENU DE OPCIONES************//
int menu()
 { int op1;
      do
      /*3*/{
      system("cls");
      printf("\n Opciones de Actualizacion \n");
      puts("\n1: Nombre\n");
      puts("\n2: Nro. de Legajo\n");
      puts("\n3: Sueldo\n");
      puts("\n4: Fecha de Nacimiento\n");
      puts("\n5: Salir\n\n");
      printf("\n elija el campo a actualizar\n"); fflush(stdin);
      scanf("%d",&op1);
      if(op1 < 1 || op1 > 5)
         {
         	printf("OPCION INCORRECTA, presione una tecla");fflush(stdin);
            getch();
         }

        /*3*/}
        while(op1 < 1 || op1 > 5);
        return   op1;
  }
//*********ACTUALIZACION*************//
 void  actualizacion(FILE*arch)

 {  int leg,op;
 	  dato rauxn;
  rewind(arch);

 printf("\nIngrese Nro. de legajo a actualizar \n"); fflush(stdin);
  scanf ("%d",&leg);
  printf("\neste es %d\n",leg );
     getch();
    while(leg!=0)
   /*1*/ {
  fread(&rauxn,sizeof(dato),1,arch);
  while(!feof(arch))
  /*2*/{
     if(leg==rauxn.leg)
      op= menu();
        while(op!=5)
         {
      	 switch(op)
          /*5*/{
       	case 1: printf("\nEscriba el nombre correcto\n"); fflush(stdin);
              gets(rauxn.ayn);
              break;
       	case 2: printf("\nEscriba el nuevo numero de legajo\n"); fflush(stdin);
              scanf("%d",&rauxn.leg);
              break;
       	case 3: printf("\nEscriba el nuevo Sueldo\n");fflush(stdin);
              scanf("%f",&rauxn.suel);
              break;
         case 4: printf("\nEscriba la nueva fecha de nacimiento\n");
                 printf("con el formato, dd/mm/aaaa   \n   ");fflush(stdin);
              scanf("%d/%d/%d",&rauxn.fnac.d,&rauxn.fnac.m,&rauxn.fnac.a);
              break;
       	 /*5*/}
         op= menu();
         }
      fseek(arch,ftell(arch)- sizeof(dato),SEEK_SET);
      fwrite(&rauxn,sizeof(dato),1,arch);
      fseek(arch, 0L, SEEK_CUR);
      fread(&rauxn,sizeof(dato),1,arch);
   }
   printf("\nIngrese otro Nro. de legajo a actualizar, \n"); fflush(stdin);
   printf("\n si desea terminar ingrese un 0 (cero)\n");
   scanf ("%d",&leg);
 }
}


indice * generaIndice(FILE*arch, int *tam, indice *vec)
{
  dato reg;
  int i;
  fseek(arch,0,SEEK_END);
  *tam=ftell(arch)/sizeof(dato);
  vec=(indice *) malloc (*tam*sizeof(indice));
  if(!vec){
  		printf("Error de memoria al intentar crear el indice");
   	exit(1);
  }
  rewind(arch);
  for(i=0;i<*tam;i++){
  		fread(&reg,sizeof(dato),1,arch);
   	(vec+i)->posicion=i;
      (vec+i)->leg=reg.leg;
  }
  return vec;
}


void quicksort(indice *vec, int izq, int der){
 		int i=izq,j=der;
  		int x;
  		indice aux;
     	x=((vec + ((izq+der)/2))->leg);
      do{
     			while(((*(vec+i)).leg <x) )	i++;
    			while((x<(*(vec+j)).leg ) )	j--;
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


int busquedaBinaria(indice *vec, int buscado, int tam){

		int medio, inicio, fin;
      inicio = 0;
    	fin = tam-1;
    	while(inicio <= fin){
      		medio = ((inicio + fin) / 2);
      		if(buscado == (vec+medio)->leg){
	        			printf("El leg '%d' se encuentra en la posicion '%d'\n\n",(vec+medio)->leg,(vec+medio)->posicion);
        				return (vec+medio)->posicion ;
            }
            else{
          			if(buscado <(vec+medio)->leg){
            				fin = medio - 1;
          			}
          			else{
            				inicio = medio + 1;
          			}
      		}
    	}
    	return -1;
}

void mostrarRegistro(FILE* arch, int pos){

	  	dato reg;
  		fseek(arch,pos*sizeof(dato),SEEK_SET);
  		fread(&reg,sizeof(dato),1,arch);
  		printf("Nombre ") ;
  		printf("Nro. de Legajo ");
  		printf("Fecha de nacimiento ");
  		printf("Sueldo\n\n");
  		printf("\n%s ",reg.ayn);
  		printf("%d ",reg.leg);
 		printf("%2d/%2d/%2d ",reg.fnac.d,reg.fnac.m,reg.fnac.a);
  		printf("%7.2f ",reg.suel);
}
