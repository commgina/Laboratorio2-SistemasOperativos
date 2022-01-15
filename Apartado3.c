#include <stdio.h>
#include <stdlib.h>


typedef struct nodo{

    char *nombre;
    struct nodo *sig;

}Libro;



//defino la estructura de forma recursiva de manera que pueda autoreferenciarse
//tiene un puntero que apunta a estructuras nodo
//se puede pensar como que cada nodo es un libro con un nombre y una flecha que apunta hacia el siguiente libro de una Lista

int main(){ 
    

    Libro * cabeza = NULL; //variable local que apunta al primer elemento de la lista

    cabeza = (Libro*)malloc(sizeof(Libro)); //alojamos memoria que sea del tama;o del struct 
    
    if( cabeza == NULL){ //siempre debemos checkear si malloc nos retorna null

        return 1;
    }

    cabeza->nombre = "El Tunel";
    cabeza->sig = NULL;


}

void push(Libro * cabeza, char *nombre){

    Libro * actual = cabeza;

    while (actual->sig != NULL){ //itero por toda la lista enlazada hasta que no hay mas libros

        actual = actual->sig;
    }

    actual->sig = (Libro *)malloc(sizeof(Libro));
    actual->sig->nombre= nombre;
    actual->sig->sig = NULL;
}