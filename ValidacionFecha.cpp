#include <stdio.h>
#include <conio.h>
int Bisiesto ( int );
int CantidadDiasDelMes(int,int);
int EsFechaValida(int,int,int);
//////////////////////////////////////////////////////////////////////////
void main(void)
{
 int OK=0,dia, mes,anio;
 do{
    if(OK==0)
    {printf("\n INGRESAR DIA  MES  ANIO: ");
    OK=1;
    }
    else
     printf("\n\n INGRESAR NUEVAMENTE ");
    scanf("%d%d%d",&dia,&mes,&anio);
  } while (EsFechaValida(dia,mes,anio) == 0);

 printf("FECHA CORRECTAMENTE INGRESADA");
 getch();
}

////////////////////////////////////////////////////////////////////
int Bisiesto ( int a)
{ int r;
  if (( a%4 == 0 && a%100 != 0 ) || (a%400 == 0) )
   r=1;
  else
   r=0;
  return (r);
}

/////////////////////////////////////////////////////////////////////////
int CantidadDiasDelMes(int m,int a)
{
  int cdm;
  if(m==4 || m==6 || m==9 || m==11)
     cdm = 30;
  else
     if ( m== 2)
        cdm = 28 +Bisiesto(a);
     else
        cdm = 31;
   return (cdm);
}

/////////////////////////////////////////////////////////////////////////
int EsFechaValida(int d,int m ,int a)
{
  int r=0;
  if( a>=1950 && a<=2020)
    if ( m>= 1 && m <= 12 )
        if( d >=1 && d <= CantidadDiasDelMes(m,a))
           r=1;
   return (r);
}
