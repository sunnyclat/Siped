#include "usuarios.h"
#include "archivos.h"
///////////////////////////////////////////////////////////////////
//objetivo: carga de datos del cliente
//Recibe: un puntero estructura
//Retorna: nada
///////////////////////////////////////////////////////////////////
void carga_usuarios(usuarios *usu)
{
//   usuarios usua;
	printf("\nNombre y Apellido: ");
	fflush(stdin);
   char usuario[100],usr[100],pass1[100], pass2[100],nomusuario[100];
   int cod,flag2,contador;

	gets(usu->nya_usuario);
	if(strcmpi(usu->nya_usuario,"Z")!=0)
	{
//      printf("Ingrese la password: ");
//      fflush(stdin);
//      gets (usu->pass_usuario);

	   do
   	{
	   	contador=0;
	      printf("\nIngrese nombre del usuario para el sistema: ");
   		fflush(stdin);
	      gets (nomusuario);
	      contador=fun_contar(nomusuario);
 			if(contador>20)
      	{
   	   	printf("\n\t");
	     	 	cprintf(" <<< Tiene que tener menos de 20 caracteres >>>");
   			printf("\n");
      	}
	   }while(contador>20);
		strcpy(usu->sis_usuario,nomusuario);

		do
   	{
      	fflush(stdin);
      	printf("\tIngrese la password del usuario:");
      	gets(pass1);
      	fflush(stdin);
      	printf("\tRepita password ingresado:");
      	gets(pass2);
         if(!(strcmp(pass1,pass2)==0))
      	{
         	printf("\n\t");
      		cprintf("<<< Existen diferencias en los passwords ingresados >>> ");
      		printf("\n");
         }
      }while(!(strcmp(pass1,pass2)==0));
      strcpy(usu->pass_usuario,pass1);


	   flag2=0;
   	do
   	{
	  		if(flag2!=0)
      	{
      		printf("\n\t");
	        	cprintf(" <<< Categoria incorrecta >>> ");
   	      printf("\n");
      	}
         else
         {
         	flag2=1;
	      }
   	   fflush(stdin);
      	printf("\n Categoria del usuario: \n\t1 -\tAdministrador\n\t2 -\tUsuario Operador\n\t3 -\tDelivery");
	      printf("\nIngrese categoria del usuario:");
   	   scanf("%d",&usu->usu_categoria);

//   	   scanf("%d",&usu.usu_categoria);
	   }while(usu->usu_categoria<1 || usu->usu_categoria>3 );

	   usu->usu_estado=1;
//   	usu.usu_codigo=cod;




	}
  //else
  //{
    //system("cls");
    //puts("\nFin de carga, presione una tecla para continuar");

   //}
}
///////////////////////////////////////////////////////////////////
//objetivo: graba datos del usuario
//Recibe: un puntero estructura
//Retorna: nada
///////////////////////////////////////////////////////////////////
void grabar_usuarios(FILE **arch, usuarios * usu)
{
	int usua;
   int cant;
   time_t t;
   struct tm *tiempo;
   t=time(NULL);
   tiempo=localtime(&t);
   usuarios aux;
/*   if((arch=fopen("clientes.dat","rb+"))==NULL)
   	if((arch=fopen("clientes.dat","wb+"))==NULL)
      	{printf("\n No hay memoria");
         getch();
         exit(1);
         }
*/
   fseek(*arch,0L,SEEK_END);
   cant=ftell(*arch)/sizeof(usuarios);
   fseek(*arch,0L,SEEK_SET);
   if(cant==0)
   	{
//      	cant = ftell(arch)/sizeof(clientes);
   		usu->id_usuario = 1;


//   		ctes->id_cliente = cant+1;//cnt;
   		usu->fa_usuario.d = tiempo->tm_mday;
   		usu->fa_usuario.m = tiempo->tm_mon+1;
   		usu->fa_usuario.a = tiempo->tm_year+1900;
      	fwrite(usu,sizeof(usuarios),1,*arch);
        //	fseek(arch,0L,SEEK_CUR);
      }
   else
		{
//		   fseek(arch,0L,SEEK_END);
		   fseek(*arch,-1L*sizeof(usuarios),SEEK_END);
      //         cli=cant + 1;
//			cli=random(999)+1000;
//			fseek(arch,0L,SEEK_SET);
			fread(&aux,sizeof(usuarios),1,*arch);
         usua=aux.id_usuario;
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
        usua=usua+1;
//      	fseek(arch, 0L, SEEK_END);
//   		cant = ftell(arch)/sizeof(clientes);
   		usu->id_usuario = usua;//cnt;
   		usu->fa_usuario.d = tiempo->tm_mday;
   		usu->fa_usuario.m = tiempo->tm_mon+1;
   		usu->fa_usuario.a = tiempo->tm_year+1900;
         fseek(*arch,0L,SEEK_END);
   		fwrite(usu, sizeof(usuarios), 1, *arch);
      	fseek(*arch,0L,SEEK_CUR);
      }
//	fclose(arch);
}
///////////////////////////////////////////////////////////////////
//objetivo: mostrar los clientes
//Recibe: un puntero estructura
//Retorna: nada
///////////////////////////////////////////////////////////////////
void mostrar_usuarios(FILE **arch)
{
	usuarios usu;
   int flag, flag2,contador,categoria,estado;
   char usr[15], yesno[4], pass1[50], pass2[50],cat[10],est[10],nomusuario[50];

  	//rewind(arch);
/*	if((arch=fopen("clientes.dat","rb+"))==NULL)
	{
   	printf("\n El archivo no existe");
      getch();
      exit(1);
   }
*/
	fseek(*arch,0L,SEEK_SET);
	fread(&usu,sizeof(usuarios),1,*arch);
	system("cls");//   clrscr();
	printf("\n\n %57s","LISTADO DE USUARIOS REGISTRADOS EN 'SIPED 2013'");
	printf("\n-----------------------------------------------------------------------------");
   printf("\n| ID | Nombre y Apell.	| Usuario | Categoria | Estado	| Fecha	    |");
   printf("\n-----------------------------------------------------------------------------");
	while(!feof(*arch))
	{

	switch(usu.usu_categoria)
  	{
	  	case 1:
	  		strcpy(cat,"Administrador");
   	   break;
      case 2:
         strcpy(cat,"Operador");
         break;
      case 3:
        	strcpy(cat,"Delivery");
         break;
	}
	switch(usu.usu_estado)
	{
     	case 0:
     		strcpy(est,"Inactivo");
         break;
   	case 1:
         strcpy(est,"Activo");
	      break;
   }
	printf("\n-----------------------------------------------------------------------------");
	printf("\n| %d  | %s	| %s | %s  | %s | %d/%d/%d |",usu.id_usuario,usu.nya_usuario,usu.sis_usuario,cat,est,usu.fa_usuario.d,usu.fa_usuario.m, usu.fa_usuario.a);
   fseek(*arch,0L,SEEK_CUR);
	fread(&usu,sizeof(usuarios),1,*arch);
      //getch();
  }
  printf("\n-----------------------------------------------------------------------------");
  printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar ");
 //	fclose(arch);
}
///////////////////////////////////////////////////////////////////
//objetivo: busqueda binaria del cliente
//Recibe: un puntero estructura
//Retorna: un entero con el valor de la posicion del registro
///////////////////////////////////////////////////////////////////
int busquedaBinariausu(indice_usu *vec, int buscado, int tam)
{
	int medio, inicio, fin;
   inicio = 0;
  	fin = tam-1;
  	while(inicio <= fin)
   {
		medio = ((inicio + fin) / 2);
		if(buscado == (vec+medio)->id_usuario)
   	{
			//printf("El DNI '%d' se encuentra en la posicion REAL'%d'\n\n",(vec+medio)->id_cliente,(vec+medio)->posicion+1);
   		return (vec+medio)->posicion ;
   	}
   	else
   	{
   		if(buscado <(vec+medio)->id_usuario)
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
//Recibe: un puntero estructura, tama�o, indice
//Retorna: indice del cliente
///////////////////////////////////////////////////////////////////
indice_usu * generaIndiceusu(FILE **arch, int *tam, indice_usu *vec)
{
	usuarios reg;
	int i;
/*	if((arch=fopen("clientes.dat","rb+"))==NULL)
	{
   	printf("\n El archivo no existe");
      getch();
      exit(1);
   }
*/
	fseek(*arch,0,SEEK_END);
	*tam=ftell(*arch)/sizeof(usuarios);
	vec=(indice_usu*)malloc(*tam*sizeof(indice_usu));
	if(!vec)
	{
		printf("Error de memoria al intentar crear el indice");
   	exit(1);
	}
  	rewind(*arch);
  	for(i=0;i<*tam;i++){
		fread(&reg,sizeof(usuarios),1,*arch);
   	(vec+i)->posicion=i;
      (vec+i)->id_usuario=reg.id_usuario;
	}
	return vec;
//   fclose(arch);
}
///////////////////////////////////////////////////////////////////
//objetivo: ordenar por el metodo quick sort
//Recibe: un puntero estructura, tama�o, indice
//Retorna: nada
///////////////////////////////////////////////////////////////////
void quicksortusu(indice_usu *vec, int izq, int der){
 		int i=izq,j=der;
  		int x;
  		indice_usu aux;
     	x=((vec + ((izq+der)/2))->id_usuario);
      do{
     			while(((*(vec+i)).id_usuario <x) )	i++;
    			while((x<(*(vec+j)).id_usuario ) )	j--;
    			if(i<=j){
        			aux=*(vec+i);
      			*(vec+i) = *(vec+j);
      			*(vec+j) = aux;
      			i++;
      			j--;
    			}
  		}
      while(i<=j);
      if(izq<j) quicksortusu(vec,izq,j);
  		if(i<der) quicksortusu(vec,i,der);
}
///////////////////////////////////////////////////////////////////
//objetivo: mostrar el registros del cliente
//Recibe: un puntero estructura, posicion del cliente
//Retorna: nada
///////////////////////////////////////////////////////////////////
void mostrarRegistro_usu(FILE **arch, int pos)
{
	usuarios reg;
   int flag, flag2,contador,categoria,estado;
   char usr[15], yesno[4], pass1[50], pass2[50],cat[10],est[10],nomusuario[50];


	fseek(*arch,(pos)*sizeof(usuarios),SEEK_SET);
	fread(&reg,sizeof(usuarios),1,*arch);

	switch(reg.usu_categoria)
  	{
	  	case 1:
	  		strcpy(cat,"Administrador");
   	   break;
      case 2:
         strcpy(cat,"Operador");
         break;
      case 3:
        	strcpy(cat,"Delivery");
         break;
	}
	switch(reg.usu_estado)
	{
     	case 0:
     		strcpy(est,"Inactivo");
         break;
   	case 1:
         strcpy(est,"Activo");
	      break;
   }


	printf("\n-----------------------------------------------------------------------------");
	printf("\n| %d  | %s	| %s	| %s | %s	| %d/%d/%d |",reg.id_usuario,reg.nya_usuario,reg.sis_usuario,cat,est,reg.fa_usuario.d,reg.fa_usuario.m, reg.fa_usuario.a);
   printf("\n-----------------------------------------------------------------------------");
//   fclose(arch);
}

///////////////////////////////////////////////////////////////////
//objetivo: modificar un cliente a eleccion
//Recibe: un puntero estructura, posicion del registro
//Retorna: nada
///////////////////////////////////////////////////////////////////
void modificar_usuario (FILE **arch, int pos)
{
//   int i;
   int flag, flag2,contador,categoria,estado;
   char usr[15], yesno[4], pass1[50], pass2[50],cat[10],est[10],nomusuario[50];

   usuarios usu;
/*	if((arch=fopen("clientes.dat","rb+"))==NULL)
	{
   	printf("\n El archivo no existe");
      getch();
      exit(1);
   }
*/
   fseek(*arch,(pos)*sizeof(usuarios),SEEK_SET);
   fread(&usu,sizeof(usuarios),1,*arch);
//   printf("\nNombre y Apellido:  ");
//	gets(a.nya_cliente);


	   flag2=0;
   	do
   	{
	  		if(flag2!=0)
      	{
      		printf("\n\t");
	        	cprintf(" <<< Categoria incorrecta >>> ");
   	      printf("\n");
      	}
         else
         {
         	flag2=1;
	      }
   	   fflush(stdin);
      	printf("\n Categoria del usuario: \n\t1 -\tAdministrador\n\t2 -\tOperador\n\t3 -\tDelivery");
	      printf("\nIngrese la nueva categoria del usuario:");
   	   scanf("%d",&usu.usu_categoria);

//   	   scanf("%d",&usu.usu_categoria);
	   }while(usu.usu_categoria<1 || usu.usu_categoria>3 );

	   usu.usu_estado=1;
//   	usu.usu_codigo=cod;

            printf("\nEstado:");
            switch(usu.usu_estado)
		   		{
            	case 0:
            		printf(" %d - Inactivo",usu.usu_estado);
               break;
               case 1:
                  printf(" %d - Activo",usu.usu_estado);
               break;
            	}
            do
	         {
   	 			fflush(stdin);
         		printf("\n\nDesea modificar el estado del usuario? Y/N:");
					gets(yesno);
 		 	 	}while(!((strcmp(yesno,"y")==0)||(strcmp(yesno,"Y")==0)||(strcmp(yesno,"n")==0)||(strcmp(yesno,"N")==0)));
            if((strcmp(yesno,"y")==0)||(strcmp(yesno,"Y")==0))
            {
   				flag2=0;
				   do
				   {
				 	if(flag2!=0)
               {
				    	printf("\n");
				      cprintf(" <<< Estado incorrecto >>>");
				  		printf("\n");
				   }else{
				   	flag2=1;
					}
			      printf("\n Estados del usuario: \n\t0 -\tInactivo\n\t1 -\tActivo");
			    	printf("\nIngrese estado del usuario: ");
			      scanf("%d",&estado);
			      }while(estado<0 || estado>1 );
               usu.usu_estado=estado;
 				}

/*   printf("Ingrese la nueva direccion de entrega: ");
   gets (a.dir_usuario);
   printf("Ingrese el nuevo telefono: ");
   gets (a.tel_usuario);
*/

   fseek(*arch,(-1)*sizeof(usuarios),SEEK_CUR);
   fwrite(&usu,sizeof(usuarios),1,*arch);
  	fseek(*arch,0,SEEK_CUR);
//   getch();
//   fclose(arch);
}
///////////////////////////////////////////////////////////////////
//objetivo: valida que la cadena ingresada no tenga caracteres
//Recibe: una cadena de caracteres
//Retorna: un valor entero
///////////////////////////////////////////////////////////////////
int validausu(char cad[])
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
int valida_ingresousu(void)
{
	void clrscr(void);
   int valida(char[]);
   char numero[20];
   int intnumero;
   do
   {
//      clrscr();
		printf("\nIngrese el numero de USUARIO a consultar: ");
 		scanf ("%s",&numero);
      fflush (stdin);
   }while(!valida(numero));
   intnumero=atoi(numero);
   return intnumero;
}



//	Funci�n: fun_contar, se encarga de contar un char
//	Par�metros: direcciones: doble puntero que contiene las direcciones del path.
//	Retorno: devuelve la cantidad del string (int).
int fun_contar(char*c)
{
	int contar=0;
	while(*c)
		{
		contar++;
	   c++;
		}
	return(contar);
}
//	Funci�n: usu_validauser, se encarga de validar el usuario y loguear
//	Par�metros: direcciones: doble puntero que contiene las direcciones del path.
//	Retorno: jerarquia del usuario.
int usu_validauser(char **archivos,char*usuario,char*password)
{
	usuarios usu;
   int priv;
	FILE *usu_pf, *log;
	char mensaje[100];
   priv=10;

	if((usu_pf=fopen(*(archivos+7),"r"))==NULL)
   {
   	printf("\n");
   	printf("No se puede leer el archivo usuarios.dat o el mismo no existe.");
  		printf("\n");
      printf("\nPresione una tecla para continuar\n");
      getch();
      exit(1);
   }

   if((log=fopen(*(archivos),"a+"))==NULL)
//   if((log=fopen(*(direcciones),"a+"))==NULL)
   {
      printf("\nERROR EN EL ACCESO AL ARCHIVO DE LOGIN");
      printf("\nPresione una tecla para continuar\n");
      getch();
      exit(1);
   }

   fseek(usu_pf,0L,SEEK_SET);
   fread(&usu,sizeof(usuarios),1,usu_pf);
	while(!feof(usu_pf))
   	{
      if (strcmp(usu.sis_usuario,usuario)==0)
      	{

         if(usu.usu_estado==1)
            {
         		if(strcmp(usu.pass_usuario,password)==0)
            	{
	               strcpy(mensaje," <<< Usuario Logueado Correctamente >>> ");
              		priv=usu.usu_categoria;
               }else{
               	printf("\n");
                  strcpy(mensaje," <<< Password Incorrecto >>> ");
					   printf(" <<< Password Incorrecto >>> ");
 						printf("\n");
				      printf("\nPresione una tecla para continuar\n");
      				getch();
               	priv=0;
                  exit(1);
            	}
            }else{
					printf("\n");
               strcpy(mensaje," <<< Usuario Inactivo >>> ");
				   printf(" <<< Usuario Inactivo >>>");
 					printf("\n");
			      printf("\nPresione una tecla para continuar\n");
      			getch();
               priv=0;
               exit(1);
            }
         }
		fread(&usu,sizeof(usuarios),1,usu_pf);
		}
   if(priv==10)
   {
   	printf("\n");
      strcpy(mensaje," <<< Usuario incorrecto o no pertenece al sistema >>> ");
		printf(" <<< Usuario incorrecto o no pertenece al sistema >>> ");
 		printf("\n");
      printf("\nPresione una tecla para continuar\n");
      getch();

      priv=0;
      exit(1);
   }
//   dd_loguser(log,*(archivos+4),"LOGIN",usuario,mensaje);
   return priv;
	fclose(usu_pf);
   fclose(log);
}

