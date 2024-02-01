#include "archivos.h"
///////////////////////////////////////////////////////////////////
//objetivo: funcion para saber la cantidad de archivos
//Recibe: nada
//Retorna: un entero con el valor de la cantida de archivo de path.txt
///////////////////////////////////////////////////////////////////
int Ver_Cant_Archivos(void) //ESTA FUNCION VA A DEVOLVER LA CANTIDAD DE ARCHIVOS QUE TIENE EL PATH.
{
	char linea[80];
   int cont=0;
   FILE *arch;
   arch= fopen("path.txt","r");//el archivo de path esta en el dir donde se ejecuta el programa
   if (arch==NULL)
   {
	   printf("ERROR EN EL ACCESO AL ARCHIVO\n");
      getch();
      exit(1);
   }

   fgets(linea,80,arch); //lee 80 caracteres de la 1º linea del archivo
   while(!feof(arch))
   {
   	cont++;
      fgets(linea,80,arch);
	}
   fclose(arch);
   return (cont-1); //le resto 1 porque va del 0 al 4 -> 5 elementos
}
///////////////////////////////////////////////////////////////////
//objetivo: lee los archivos
//Recibe: un doble puntero de estructura
//Retorna: nada
///////////////////////////////////////////////////////////////////
void leer_path (char** archivos) //A ESTA FUNCION QUE LEE LOS ARCHIVOS, SE LE MANDA
{
	char aux[80]="\0"; //genera un vector de caracteres y lo pone en NULL
   int i=0,j;

   FILE *arch;
   arch= fopen("path.txt","r");//el archivo de path esta en el dir donde se ejecuta el programa
   if (arch==NULL)
   {
	   printf("ERROR EN EL ACCESO AL ARCHIVO\n");
      getch();
      exit(1);
   }

   fseek(arch,0,SEEK_SET);
   fscanf(arch,"%s", aux);//almacena el path en aux
   while (!feof(arch))
   {
   	//if(!(*(archivos+i)= (char *) calloc (1, strlen(aux)+1))){
      if(!(*(archivos+i)= (char *) malloc (strlen(aux)+1)))
      	{
      		printf("ERROR AL RESERVAR MEMORIA\n");
            getch();
            exit(1);
         }
      strcpy(*(archivos+i),aux); //copio en la memoria, lo que tengo en aux
      strcat(*(archivos+i),"\0"); //le agrego el /0
      //printf("%s\n",*(archivos+i));
      fscanf(arch,"%s", aux);//almacena el path en aux
      i++;
   }
}
///////////////////////////////////////////////////////////////////
//objetivo: Abrir Archivo, se encarga de abrir el archivo solicitado con su respectivo modo.
//Recibe: arch: estructura del archivo a abrir.
//					direcciones: doble puntero que contiene las direcciones del path.
//					dirnum: número de línea del archivo en el path.
//					modo: número de modo para abrir el archivo, valores posibles:WB+ RB+ A+ R+.
//Retorna: nada
///////////////////////////////////////////////////////////////////
void abrir_archivo(FILE **arch,char **archivos,int num,char *modo)
{
	FILE *log;

   if((log=fopen(*(archivos+4),"a"))==NULL)
   {
      printf("ERROR EN EL ACCESO AL ARCHIVO DE LOGIN");
      getch();
      exit(1);
   }
   if((*arch=fopen(*(archivos+num),modo))==NULL)
   {

//   if(abrir_archivo(&clientesvent_pf,direcciones,8,1)==0)  // 1 es abrir, 0 es crear
//   	abrir_archivo(&vent_pf,direcciones,8,0);

//      	printf("El archivo %s NO existe. Se crea nuevo archivo. \nFAVOR DE INGRESAR NUEVAMENTE A SIPED",*(archivos+num));
      	login(log,*(archivos+num),modo,0);
		   (*arch=fopen(*(archivos+num),+"ab+"));

      	fclose(log);
//      	getch();
//      	exit(1);
   }
   login(log,*(archivos+num),modo,1);
   fclose(log);
}
///////////////////////////////////////////////////////////////////
//objetivo: Abrir Archivo login
//Recibe: estructura del archivo
//Retorna: nada
///////////////////////////////////////////////////////////////////
void login(FILE *log, char *nom, char *mod,int res)
{
	time_t t; //llama a la libreria time.h
   struct tm *tiempo;
   t=time(NULL);
   tiempo=localtime(&t);
   fprintf(log,"Fecha %02d/%02d/%02d Hora %02d:%02d Archivo %s en modo %s ",
   tiempo->tm_mday,tiempo->tm_mon+1,tiempo->tm_year+1900,tiempo->tm_hour,tiempo->tm_min,nom,mod);
   if (res) fprintf(log,"correctamente abierto\n");
   else fprintf(log,"no se pudo abrir\n");
}
///////////////////////////////////////////////////////////////////
//	Parámetros: arch: estructura del archivo a cerrar.
//					direcciones: doble puntero que contiene las direcciones del path.
//					dirnum: número de línea del archivo en el path.
//	Retorno: Ninguno.
///////////////////////////////////////////////////////////////////
int cerrar_archivo(FILE **arch,char **archivos, int dirnum)
{
	char mensaje[99];
   FILE *log;

   if((log=fopen(*(archivos),"a+"))==NULL)
   {
      printf("\nERROR EN EL ACCESO AL ARCHIVO DE LOGIN");
      getch();
      exit(1);
   }

   if(fclose(*arch)==0) //	Bien Cerrado
   {
   	strcpy(mensaje,"Se cerro correctamente el archivo ");
      strcat(mensaje,*(archivos+dirnum));
//		dd_log(log,*(archivos+dirnum),"INFO",mensaje);
      //free(*arch);
      return 1;
   }
	else	// Mal Cerrado
   {
   	strcpy(mensaje,"No se puede cerrar el archivo ");
      strcat(mensaje,*(archivos+dirnum));
   	printf("\nNo se puede cerrar el archivo %s",*(archivos+dirnum));
 //     dd_log(log,*(archivos+dirnum),"INFO",mensaje);
      //free(*arch);
      return 0;
   }
}
