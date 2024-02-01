#include "usuarios.h"
#include "pedidos.h"
#include "stock.h"
#include "siped.h"
#include "archivos.h"
#include "clientes.h"
#include "informe.h"
///////////////////////////////////////////////////////////////////
void main (void)
{
   int opcion,cantarchivos,menu,contador,contador2,nro,i;
   int inten=0;
   char **archivos,usuario[200],*password,pedcod[200];
//   char** archivos;
	clientes ctes;
   stock stk;
   pedidos ped;
   usuarios usu;
	int cant_archivos, id, pos, tam, repetir;
   int op, op2, op3, op4, op5, op6;

   char cad[25];
   indice_cliente **index;
   indice_stock **indexstk;
   indice_ped **indexped;
   indice_usu **indexusu;
   FILE *clientes;
   FILE *usuarios;
   FILE *stock;
   FILE *pedidos;
   FILE *eventos;
   FILE *ctes_hist,*ctes_temp;
//   FILE *eventos;
   system("Color 30");
   textbackground(3);
   char sino;
   cant_archivos = Ver_Cant_Archivos();
   archivos = (char**) malloc (cant_archivos*sizeof(char*));
   if (archivos==NULL)
   	{
      	printf ("No se pudo asignar memoria!!!");
         getch();
         exit(1);
      }
   if(!(index=(indice_cliente **) malloc(sizeof(indice_cliente*))))
 	{
   	printf("ERROR AL RESERVAR MEMORIA\n");
      getch();
      exit(1);
 	}
   if(!(indexstk=(indice_stock **) malloc(sizeof(indice_stock*))))
 	{
   	printf("ERROR AL RESERVAR MEMORIA\n");
      getch();
      exit(1);
 	}
   if(!(indexped=(indice_ped **) malloc(sizeof(indice_ped*))))
 	{
   	printf("ERROR AL RESERVAR MEMORIA\n");
      getch();
      exit(1);
 	}
   if(!(indexusu=(indice_usu **) malloc(sizeof(indice_usu*))))
 	{
   	printf("ERROR AL RESERVAR MEMORIA\n");
      getch();
      exit(1);
 	}
   leer_path (archivos);
   abrir_archivo (&clientes, archivos, 0, "rb+");
   abrir_archivo (&ctes_hist, archivos, 3, "rb+");
   abrir_archivo (&ctes_temp, archivos, 5, "rb+");
   abrir_archivo (&pedidos, archivos, 1, "rb+");
   abrir_archivo (&stock, archivos, 2, "rb+");
   abrir_archivo (&eventos,archivos,6,"rb+");
   abrir_archivo (&usuarios,archivos,7,"rb+");
   do
   {
   system("CLS");
	   do
	   {
			contador=0;
         printf("\nIngrese el nombre del usuario: ");
			fflush(stdin);
			gets(usuario);
			contador=fun_contar(usuario);
			if(contador>20)
				{
				printf("\n\t");
				cprintf(" <<< Tiene que tener menos de 20 caracteres >>>");
				printf("\n");
				}
		}while(contador>20);
      do
		  {
		  	contador=0;
		  	fflush(stdin);
        	printf("\t");
         password = getpass("Ingrese el password del usuario: ");
			contador2=fun_contar(password);
			if(contador2>10)
				{
					printf("\n\t");
      			cprintf(" <<< Tiene que tener menos de 10 caracteres >>>");
				   printf("\n");
			   }
         }while(contador2>10);
   	menu=usu_validauser(archivos,usuario,password);
      inten++;
      if(inten==3)
      	menu=11;
   }while(menu<=0);
	repetir = 1;
	do
	{
   	op=menu_gral(menu);
		switch(op)
		{
			case 1:
	     	if(menu==1 || menu==2)
   	   {

      		op2=menu_ctes();
	   		switch(op2)
   			{
		   		case 1:
						clrscr();
         			printf ("%57s","ALTA DE CLIENTES (termina con Z)\n\n");
						carga_clientes(&ctes);
   					while (strcmpi(ctes.nya_cliente,"Z"))
 						{
  							grabar_clientes(&clientes,&ctes);
  							carga_clientes(&ctes);
      				}
         			clrscr();
      				break;
   			  	case 2:
						mostrar (&clientes);
						getch();
            		clrscr();
   					break;
   				case 3:
            		*index= generaIndice(&clientes, &tam, *index);
            		quicksort(*index, 0, tam-1);
						id = valida_ingreso();
            		pos=busquedaBinaria(*index, id, tam);
            		if(pos==-1)
               	{
							printf("\n ESE CLIENTE NO EXISTE !\n");
               		getch();
               		clrscr();
						}
 						else
    					{
                     clrscr();
                     printf("\n\n %57s","CONSULTA POR CLIENTE REGISTRADOS EN 'SIPED 2013'");
							printf("\n-----------------------------------------------------------------------------");
   						printf("\n| Id | Nombre y Apel.	| Direccion		| Telefono	| Fecha	    |");
	   					printf("\n-----------------------------------------------------------------------------");
               		mostrarRegistro_cli(&clientes, pos);
               		printf ("\n\n DESEA MODIFICAR ESTE CLIENTE (s/n): ");
                     fflush (stdin);
               		scanf ("%c", &sino);
               		fflush (stdin);
               		switch (sino)
               		{
                  		case 's':
                  			modificar_cliente (&clientes, pos);
							      printf("\n REGISTRO MODIFICADO");
							      printf("\n-----------------------------------------------------------------------------");
                     		printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar\n\n");
                           getch();
                  			break;
                  		case 'n':
                     		clrscr();
                     		break;
								default:
                    			printf ("Opcion no valida... Ingrese s o n !!!\n");
              					getch();
                     		clrscr();
                     		break;
                  	}
               	}
   					break;
            	case 4:
            		*index= generaIndice(&clientes, &tam, *index);
            		quicksort(*index, 0, tam-1);
						id = valida_ingreso_baja();
            		pos=busquedaBinaria(*index, id, tam);
            		if(pos==-1)
               	{
							printf("\n ESE CLIENTE NO EXISTE !\n");
               		getch();
               		clrscr();
						}
 						else
    					{
                     clrscr();
                     printf("\n\n %57s","CONSULTA DE CLIENTE A BORRAR EN 'SIPED 2013'");
							printf("\n-----------------------------------------------------------------------------");
   						printf("\n| Id | Nombre y Apel.	| Direccion		| Telefono	| Fecha	    |");
	   					printf("\n-----------------------------------------------------------------------------");

               		mostrarRegistro_cli(&clientes, pos);

               		printf ("\n\n ESTA SEGURO QUE DESEA DAR DE BAJA ESTE CLIENTE (s/n): ");
                     fflush (stdin);
               		scanf ("%c", &sino);
               		fflush (stdin);
               		switch (sino)
               		{
                  		case 's':

                  			baja_cliente (&clientes,&ctes_hist,&ctes_temp, pos);

							      printf("\n REGISTRO BORRADO");
							      printf("\n-----------------------------------------------------------------------------");
                     		printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar\n\n");
                           getch();

                           fclose (clientes);
                           fclose (ctes_temp);
           //                cerrar_archivo(&clientes,archivos,0);
			  //					   cerrar_archivo(&ctes_temp,archivos,5);


				               remove(*(archivos+0));
         						rename(*(archivos+5),*(archivos+0));

								   abrir_archivo (&clientes, archivos, 0, "rb+");
								   abrir_archivo (&ctes_temp, archivos, 5, "rb+");

                  			break;
                  		case 'n':
                     		clrscr();
                     		break;
								default:
                    			printf ("Opcion no valida... Ingrese s o n !!!\n");
              					getch();
                     		clrscr();
                     		break;
                  	}
               	}
   					break;
            	case 5:
//						mostrar (&clientes);
						mostrar_hist(&ctes_hist);
						getch();
            		clrscr();
   					break;
            	case 6:
         			break;
    			}  //fin switch menu
				break;
   		case 2:
   			op3=menu_pedi(menu);
   			switch (op3)
   			{
	   			case 1:
        			if(menu==1 || menu==2)
               {
                      clrscr();
                     printf ("%57s","ALTA DE PEDIDOS \n\n");
                     carga_pedidos(&clientes, &stock, &ped);
   						while (ped.cliente_ped!=0)
 								{
  									grabar_pedidos(&pedidos,&ped,&eventos);
  									carga_pedidos(&clientes, &stock, &ped);
         					}
                      clrscr();
                }
	      			break;
   				case 2:
                     mostrar_pedidos (&pedidos);
							getch();
	            		clrscr();
                     break;
                  default:
                  	printf ("Ese valor no existe en el menu !!!\n");
					case 3:
        			if(menu==1 || menu==2)
               {
            		*indexped= generaIndiceped(&pedidos, &tam, *indexped);
            		quicksortped(*indexped, 0, tam-1);
						id = valida_ingresoped();
            		pos=busquedaBinariaped(*indexped, id, tam);
            		if(pos==-1)
               	{
							printf("\n ESE REGISTRO ES INEXISTENTE !\n");
               		getch();
               		clrscr();
						}
 						else
    					{
                     clrscr();
                     printf("\n\n %57s","CONSULTA POR PEDIDOS REGISTRADOS EN 'SIPED 2013'");
							printf("\n-----------------------------------------------------------------------------");
						   printf("\n| Id | Fecha | Hora | Cli | Cbo | Cant | Estado | Importe |");
						   printf("\n-----------------------------------------------------------------------------");
               		mostrarRegistroped(&pedidos, pos);
               		printf ("\n\n DESEA MODIFICAR ESTE PEDIDO (s/n): ");
                     fflush (stdin);
               		scanf ("%c", &sino);
               		fflush (stdin);
               		switch (sino)
               		{
                  		case 's':
                  			modificar_ped (&pedidos, pos);
							      printf("\n REGISTRO MODIFICADO");
							      printf("\n-----------------------------------------------------------------------------");
                     		printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar\n\n");
                           getch();
                  			break;
                  		case 'n':
                     		clrscr();
                     		break;
								default:
                    			printf ("Opcion no valida... Ingrese s o n !!!\n");
              					getch();
                     		clrscr();
                     		break;
                  	}
               	}
               }
   				break;
  					case 4:
            		*indexped= generaIndiceped(&pedidos, &tam, *indexped);
            		quicksortped(*indexped, 0, tam-1);
						id = valida_ingresoped();
            		pos=busquedaBinariaped(*indexped, id, tam);
            		if(pos==-1)
               	{
							printf("\n ESE REGISTRO ES INEXISTENTE !\n");
               		getch();
               		clrscr();
						}
 						else
    					{
                     clrscr();
                     printf("\n\n %57s","CONSULTA POR PEDIDOS REGISTRADOS EN 'SIPED 2013'");
							printf("\n-----------------------------------------------------------------------------");
						   printf("\n| Id | Fecha | Hora | Cli | Cbo | Cant | Estado | Importe |");
						   printf("\n-----------------------------------------------------------------------------");
               		mostrarRegistroped(&pedidos, pos);
               		printf ("\n\n DESEA MARCAR ESTE PEDIDO COMO 'ENTREGADO'? (s/n): ");
                     fflush (stdin);
               		scanf ("%c", &sino);
               		fflush (stdin);
               		switch (sino)
               		{
                  		case 's':
                  			baja_logica (&pedidos, pos);
							      printf("\n REGISTRO ACTUALIZADO");
							      printf("\n-----------------------------------------------------------------------------");
                     		printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar\n\n");
                           getch();
                  			break;
                  		case 'n':
                     		clrscr();
                     		break;
								default:
                    			printf ("Opcion no valida... Ingrese s o n !!!\n");
              					getch();
                     		clrscr();
                  }
					}
         			break;
  					case 5:
         			break;
				}//fin switch
            break;
   		case 3:   //COMBOS
   			op5=menu_stock();
   			switch (op5)
   			{
	   			case 1:
                  clrscr();
                  printf ("%57s","ALTA DE COMBOS (termina con Z)\n\n");
  						carga_stock(&stk);
   					while (strcmpi(stk.desc_stk,"Z"))
 						{
  							grabar_stock(&stock,&stk) ;
  							carga_stock(&stk);
         			}
                  break;
   				case 2:
                  mostrar_stock(&stock);
						getch();
            		clrscr();
                  break;
					case 3:
            		*indexstk= generaIndicestock(&stock, &tam, *indexstk);
            		quicksort(*indexstk, 0, tam-1);
						id = valida_ingresocbo();
            		pos=busquedaBinaria(*indexstk, id, tam);
            		if(pos==-1)
               	{
							printf("\n ESE REGISTRO ES INEXISTENTE !\n");
               		getch();
               		clrscr();
						}
 						else
    					{
                     clrscr();
                     printf("\n\n %57s","CONSULTA POR COMBOS REGISTRADOS EN 'SIPED 2013'");
							printf("\n-----------------------------------------------------------------------------");
   						printf("\n|Cbo | Descripcion			    	 | Precio | Stk | Fecha C/M |");
   						printf("\n-----------------------------------------------------------------------------");
               		mostrarRegistro(&stock, pos);
               		printf ("\n\n DESEA MODIFICAR ESTE COMBO (s/n): ");
                     fflush (stdin);
               		scanf ("%c", &sino);
               		fflush (stdin);
               		switch (sino)
               		{
                  		case 's':
                  			modificar_stock (&stock, pos);
							      printf("\n REGISTRO MODIFICADO");
							      printf("\n-----------------------------------------------------------------------------");
                     		printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar\n\n");
                           getch();
                  			break;
                  		case 'n':
                     		clrscr();
                     		break;
								default:
                    			printf ("Opcion no valida... Ingrese s o n !!!\n");
              					getch();
                     		clrscr();
                     		break;
                  	}
               	}
   					break;
            }
            break;
   		case 4:
            op4=menu_informe();
            switch(op4)
             {
            	case 1:
               	clrscr();
                  printf("\n\n %57s","CONSULTA POR CLIENTE REGISTRADOS EN 'SIPED 2013'");
                  printf("\n --------------------------------------------------------------");
                  printf("\n Hay %d cliente/s registrado/s al dia de la fecha.",cantcli_informe(&clientes));
                  printf("\n --------------------------------------------------------------");
                  getch();
                  break;
               case 2:
                  pedencurso_informe(&pedidos);
                  getch();
               	clrscr();
               	break;
               case 3:
               	pedentregados_informe(&pedidos);
                  getch();
               	clrscr();
                  break;
               case 4:
               	mostrar_eventos(&eventos);
                  getch();
                  clrscr();
               	break;
               case 5:
						break;
               default:
                  printf ("Ese valor no existe en el menu !!!\n");
              break;
			  	}//fin switch
			break;

   		case 5:
        	if(menu==1)
         {
				op6=menu_usu();
	   		switch(op6)
   			{
		   		case 1:
		        	if(menu==1 || menu==2)
               {
						clrscr();
         			printf ("%57s","ALTA DE USUARIOS (termina con Z)\n\n");
						carga_usuarios(&usu);
   					while (strcmpi(usu.nya_usuario,"Z"))
 						{
  							grabar_usuarios(&usuarios,&usu);
  							carga_usuarios(&usu);
      				}
         			clrscr();
               }
      				break;
   			  	case 2:
						mostrar_usuarios (&usuarios);
						getch();
            		clrscr();
   					break;
   				case 3:
            		*indexusu= generaIndiceusu(&usuarios, &tam, *indexusu);
            		quicksortusu(*indexusu, 0, tam-1);
						id = valida_ingresousu();
            		pos=busquedaBinariausu(*indexusu, id, tam);
            		if(pos==-1)
               	{
							printf("\n ESE USUARIO NO EXISTE !\n");
               		getch();
               		clrscr();
						}
 						else
    					{
                     clrscr();
                     printf("\n\n %57s","CONSULTA POR USUARIOS REGISTRADOS EN 'SIPED 2013'");
							printf("\n-----------------------------------------------------------------------------");
   						printf("\n| Id | Nombre y Apel.	| Usuario  | Categoria | Estado	| Fecha	    |");
	   					printf("\n-----------------------------------------------------------------------------");
               		mostrarRegistro_usu(&usuarios, pos);
               		printf ("\n\n DESEA MODIFICAR ESTE USUARIO (s/n): ");
                     fflush (stdin);
               		scanf ("%c", &sino);
               		fflush (stdin);
               		switch (sino)
               		{
                  		case 's':
                  			modificar_usuario (&usuarios, pos);
							      printf("\n REGISTRO MODIFICADO");
							      printf("\n-----------------------------------------------------------------------------");
                     		printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar\n\n");
                           getch();
                  			break;
                  		case 'n':
                     		clrscr();
                     		break;
								default:
                    			printf ("Opcion no valida... Ingrese s o n !!!\n");
              					getch();
                     		clrscr();
                     		break;
                  	}
               	}
   					break;
            	case 4:
   					break;
    			}  //fin switch menu
			}
			break;
   		case 6:
				repetir = 0;
         }
      		break;
  		}//fin switch externo (switch principal)
	}while (repetir == 1);
}
///////////////////////////////////////////////////////////////////

