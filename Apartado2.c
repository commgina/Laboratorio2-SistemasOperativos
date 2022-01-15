#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    char str[80];
    int cantidadPalabras = 0;
    int contadorPalabras = 0;
    char **strArray;

    FILE *file;
    file = fopen("/proc/version", "r");

    // Allocate memory to the array of strings (char arrays)
    cantidadPalabras = 17;        
    strArray = (char **) malloc(sizeof(char*) * cantidadPalabras); //alojo la cantiad de palabras en el archivo por el tamanio de los strings

    while (fscanf(file, "%s", str) != EOF) {  //fscanf lee datos de un archivo, en el formato que le indique, y la variable donde se guardaran los datos
        
        strArray[contadorPalabras] = (char *) malloc(sizeof(char) * (strlen(str)));  //alojo en memoria una cantidad igual al tama;o que requiere un char
        strcpy(strArray[contadorPalabras], str); //copio el valor de str en el str array en la posicion indicada
        ++contadorPalabras; //incremento la posicion
    }


    int i = 0;
    int j = 0;
    for (; i<contadorPalabras; i++) {
        for(;j< strlen(strArray[i]); j++) {
            strArray[i][j] = toupper(strArray[i][j]);
        }
        j=0;
        
    }

    i=0;
    for (; i<contadorPalabras; i++) {
        
        puts(strArray[i]); //imprimo las palabras
    }

    i = 0;
    for (; i<contadorPalabras; i++) {
        free(strArray[i]); //libero el espacio que ocupaba cada stirng
    }
    free(strArray); //libero el espacio que habia inicial (linea 16)
    fclose(file);   //cierro el archivo

    return 0;
}
