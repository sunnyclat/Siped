#include "informe.h"
#include "pedidos.h"
#include "clientes.h"
#include "stock.h"
////////////////////////////////////////////////////////////////////////
int cantcli_informe(FILE **arch)
{
int cant;
	fseek(*arch,0L,SEEK_END);
   cant=ftell(*arch)/sizeof(clientes);
return(cant);
fclose(*arch);
}

/////////////////////////////////////////////////////////////////////

void pedencurso_informe(FILE **arch)
{
  	pedidos ped;

   clrscr();
	fseek(*arch,0L,SEEK_SET);
	fread(&ped,sizeof(pedidos),1,*arch);
	system("cls");//   clrscr();
	printf("\n\n %57s","LISTADO DE PEDIDOS REGISTRADOS EN 'SIPED 2013'");
	printf("\n-----------------------------------------------------------------------------");
   printf("\n| Id | Fecha | Hora | Cli | Cbo | Cant | Estado | Importe |");
   printf("\n-----------------------------------------------------------------------------");

  	while (!feof(*arch))
  	{
   	if(strcmp(ped.est_ped,"EN CURSO")==0)
			{printf("\n-----------------------------------------------------------------------------");
  			printf("\n| %d  | %02d/%02d | %02d:%02d | %d  | %d | %d	| %s	| %.2f |",ped.id_ped,ped.fecha_ped.d,ped.fecha_ped.m, ped.hora_ped.h, ped.hora_ped.m,ped.cliente_ped,ped.ped_cbo,ped.ped_cant,ped.est_ped,ped.impo_serv);
      	fseek(*arch,0L,SEEK_CUR);
         }
	  fread(&ped,sizeof(pedidos),1,*arch);
	}
	printf("\n-----------------------------------------------------------------------------");
   printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar ");

}

/////////////////////////////////////////////////////////////////////

void pedentregados_informe(FILE **arch)

{
  	pedidos ped;

   clrscr();
	fseek(*arch,0L,SEEK_SET);
//	rewind(arch);
	fread(&ped,sizeof(pedidos),1,*arch);
	system("cls");//   clrscr();
	printf("\n\n %57s","LISTADO DE PEDIDOS REGISTRADOS EN 'SIPED 2013'");
	printf("\n-----------------------------------------------------------------------------");
   printf("\n| Id | Fecha | Hora | Cli | Cbo | Cant | Estado | Importe |");
   printf("\n-----------------------------------------------------------------------------");

  	while (!feof(*arch))
  	{
   	if(strcmp(ped.est_ped,"ENTREGADO")==0)
			{printf("\n-----------------------------------------------------------------------------");
  			printf("\n| %d  | %02d/%02d | %02d:%02d | %d  | %d | %d	| %s	| %.2f |",ped.id_ped,ped.fecha_ped.d,ped.fecha_ped.m, ped.hora_ped.h, ped.hora_ped.m,ped.cliente_ped,ped.ped_cbo,ped.ped_cant,ped.est_ped,ped.impo_serv);
      	fseek(*arch,0L,SEEK_CUR);
         }
	  fread(&ped,sizeof(pedidos),1,*arch);
	}
	printf("\n-----------------------------------------------------------------------------");
   printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar ");

}

/////////////////////////////////////////////////////////////////////

void mostrar_eventos(FILE ** arch1_eventos)
{
clrscr();
eventos eve1;

fseek(*arch1_eventos,0L,SEEK_SET);

	printf("\n\n %57s","EVENTOS 'SIPED 2013'");
	printf("\n-----------------------------------------------------------------------------");
   printf("\n| Fecha | Hora | Cbo | Mensaje |");
   printf("\n-----------------------------------------------------------------------------");
   fread(&eve1,sizeof(eventos),1,*arch1_eventos);
   //printf("\n| %02d/%02d | %02d:%02d | %s	 | %s	|",eve1.fecha_eve.d,eve1.fecha_eve.m,eve1.hora_eve.h,eve1.hora_eve.m,eve1.desc_eve,eve1.message);
   while(!feof(*arch1_eventos))
   	{printf("\n| %02d/%02d | %02d:%02d | %s	 | %s	|",eve1.fecha_eve.d,eve1.fecha_eve.m,eve1.hora_eve.h,eve1.hora_eve.m,eve1.desc_eve,eve1.message);
      fread(&eve1,sizeof(eventos),1,*arch1_eventos);
   	}
   printf("\n-----------------------------------------------------------------------------");
   printf("\n\n\n\n%57s"," Presione cualquier tecla para continuar ");
}


