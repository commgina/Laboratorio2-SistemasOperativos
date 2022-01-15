#include <stdio.h>  //archivo de cabecera de la biblioteca estandar de proposito general de C, define macros, tipos de variables, entrada y salida de funciones
#include <stdlib.h> //libreria para usar el exit
#include <string.h>
#include <ctype.h>

float const conversionMB = 0.0009766;
long retornarValor(char[]);

int main()
{
    
    FILE *memInfo = fopen("/proc/meminfo", "r");
    FILE *cpuInfo = fopen("/proc/cpuinfo", "r");
    char linea[50] = "";
    long valor = 0;
    long mb = 0;
    long total,libre,ocupada;
    int exit,cores,hilos;


//----------------------------------------------------------------------APARTADO 1.I------------------------------------------------------------------------// 
//*  Obtener la memoria ram total, libre y disponible en Megabytes. A partir del archivo /proc/meminfo.
 
   
    printf("----Información de la memoria----\n");

    while (fgets(linea, sizeof(linea), memInfo) && exit < 5)
    {

        if (strstr(linea, "MemTotal") != NULL)
        {
            valor = retornarValor(linea);
            mb = valor * conversionMB;
            printf("La memoria RAM total es: %ld mB\n", mb);
            exit++;

        }else if(strstr(linea, "MemFree") != NULL){
            
            valor = retornarValor(linea);
            mb = valor * conversionMB;
            printf("La memoria RAM libre es: %ld mB\n", mb);
            exit++;
            
        }else if(strstr(linea, "MemAvailable") != NULL){

            valor = retornarValor(linea);
            mb = valor * conversionMB;
            printf("La memoria RAM disponible es: %ld mB\n", mb);
            exit++;

        }else if(strstr(linea, "SwapTotal") != NULL){
            valor = retornarValor(linea);
            total = valor;
            exit++;

        }
        //----------------------------------------------------------------------APARTADO 1.II-----------------------------------------------------------------------//   
        //Obtener la memoria swap Ocupada. A partir del archivo /proc/meminfo.
        else if(strstr(linea, "SwapFree") != NULL){
            valor = retornarValor(linea);
            libre = valor;
            ocupada = total - libre;
            mb = ocupada * conversionMB;
            printf("La memoria Swap ocupada es: %ld mB\n", mb);
            exit++;
        }
   
    }

    exit = 0;
    fclose(memInfo);

//----------------------------------------------------------------------APARTADO 1.III-----------------------------------------------------------------------//   
/*Obtener la memoria swap Ocupada. A partir del archivo /proc/meminfo.
*Crear un programa en C que imprima información referida al CPU, a partir del archivo /proc/cpuinfo:
*Modelo de CPU.
*Cantidad de cores
*Cantidad de thread por cores.
*/

    printf("----Información del CPU----\n");

    while (fgets(linea, sizeof(linea), cpuInfo) && exit < 3){

        if (strstr(linea, "model name") != NULL)
        {
            printf("%s\n",linea);
            exit++;

        }else if(strstr(linea, "siblings") != NULL){
            
            hilos = retornarValor(linea);
            exit++;
            
        }else if(strstr(linea, "cpu cores") != NULL){

            printf("%s",linea);
            cores = retornarValor(linea);
            printf("thread por cores: %d\n", cores/hilos);
            exit++;

        }




    }







    return 0;
}



long retornarValor(char linea[])
{
    long val;
    char *p = linea;
    while(*p){

        if(isdigit(*p) && isdigit(*p+1)){
            val = strtol(p,&p,10);         
        }else{
            p++;
        }

    }

    return val;
}