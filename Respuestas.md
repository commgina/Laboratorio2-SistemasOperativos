# Apartado 3

## I. ¿Cómo utilizar typedef junto a struct? ¿Para qué sirve? Ejemplo.
    
Typedef es una keyword que nos provee el lenguaje C para cambiarle el nombre a un tipo de dato. Por lo tanto si usamos typedef con un struct podemos definir un nuevo tipo de dato y usar ese tipo de dato para definir las variables del struct. Podemos verlo en un ejemplo:

```c
//STRUCT SIN USAR TYDEF
#include<stdio.h>

struct Libro{
  char titulo[20];
  char autor[20];
  char categoria[20];
};
int main() {
    struct Libro elTunel;
    elTunel.titulo = "El Tunel";
    elTunel.autor = "Ernesto Sabato";
    elTunel.categoria = "Novela psicologica y existencialista"
    
    return 0;
}
```

```c
//STRUCT CON TYDEF
#include<stdio.h>

typedef struct Libro{
  char titulo[20];
  char autor[20];
  char categoria[20];
} Libro;

int main() {
    Libro elTunel;
    elTunel.titulo = "El Tunel";
    elTunel.autor = "Ernesto Sabato";
    elTunel.categoria = "Novela psicologica y existencialista";
    
    return 0;
}
```

## ¿Qué es _packing and padding_ ?   
El alineamiento de estructuras de datos es la forma en que los datos son accedidos y organizados en la memoria de una computadora. Consta de dos partes: **data alignment y data structure padding**  

### **Data Alignment**

Data alignment consiste en en poner los datos en una direccion de memoria igual a un multiplo del tamaño de la **palabra**. Una palabra en un procesador de 32 bits es de 4 bytes y en uno de 64 bits es de 8 bytes Para eso es necesario insertar bytes entre el final de la ultima estructura de dato y el comienzo de la proxima, a esto le llamamos **data structure padding**. 

### **Structure padding**

Con el fin de alinear los datos en la memoria, uno o mas bytes vacios son insertados entre las direcciones de memoria. Por ejemplo: 


```c
#include<stdio.h>
struct student  
{ 

  char a; // 1 byte  
  char b; // 1 byte  
  int c; // 4 bytes   

} var;
int main(){

  printf("%d", sizeof(var));
  //output : 8 bytes
  return 0

}  
```
Supongamos un arquitectura de 32 bits donde el tamaño de palabra es de 4 bytes. Esto quiere decir que en un ciclo del CPU, podemos acceder a 1 byte del char *a*, 1 byte del char *b* y 2 bytes de *c*. Esto nos daria problemas ya que necesitariamos dos ciclos para acceder a *c* lo cual significa un desperdicio innecesario de ciclos. Lo que hara el padding sera insertar 2 bytes vacios despues de las variables tipo char y correr el int para que este se acceda en solo un ciclo, como se ve en la siguiente imagen:

![alt text](https://static.javatpoint.com/cpages/images/structure-padding-in-c2.png)

### **Structure packing**

Es una manera de evitar el padding escribiendo _attribute_((_packed_)) a una estructura. En Windows podemos usar #pragma pack(1). Pragma es una directiva utilizada para activar o desactivar algunas caracteristicas

```c
#include<stdio.h>
struct __attribute__((__packed__)) student  
{  

  char a; // 1 byte  
  char b; // 1 byte  
  int c; // 4 bytes   

} var;
int main(){

  printf("%d", sizeof(var));
  //output : 6 bytes
  return 0

}  
```
Por lo tanto, es decicion del programador decidir si prioriza los ciclos del CPU o si prioriza un mejor aprovechamiento de la memoria.

## II. Respuestas a preguntas del codigo lab2.c

### Explique a que se debe los tamanios de cada una de las estructuras
Para esta explicacion, tener en cuenta que los parentesis representan paquetes de 4 bytes a donde se agruparan las variables para respetar el padding

- sizeof(BaseData) -> (a,b)+(x)+(y+c)+(z)+(d) = 4+4+4+4+4 = 20

- sizeof(ReorderData) -> (a+b)+(x)+(y+z)+(c+d) = 4+4+4+4 = 16

- sizeof(ExtendedData)) -> (LL)+(a+b+y+x)+(z+w+c+d) = 8 + 8 + 8 = 24
Como el tipo de dato de mayor size es 8, empaqueta las variables en packs de 8 bytes

- sizeof(BaseDataPacked)) -> a+b+x+y+c+z+d = 1 + 1 + 4 + 2 + 1 + 2+ 3 = 14
El atributo unpacked evita el padding, por lo tanto tamaño del struct es la suma del tamaño de los datos

### Explique por que la expresion que calcula  limit y limit_aux generan el mismo resutado

- En el primer caso estoy sumandole 20 a al array que se forma con la direccion de memoria, como el array funciona como puntero a la primera posicion, si le sumamos 20, nos lleva a la posicion 20. Al castearlo a char* podemos apuntar a cualquier byte del struct
- En el segundo caso, al incrementarle 1 a la direccion del struct (&data) el cual tiene un tamaño de 20 bytes y como la aritmetica de punteros se hace en multiplos del tamaño del dato apuntado
    
### Explique los valores que se muestran en pantalla en cada iteracion del for

Lo que se hace en el for es recorrer byte a byte el struct e imprimir el contenido de cada byte en hexadecimal. Un ejemplo de ejecucion:

byte 00 : 0x01  //1 en hexa  
byte 01 : 0x03  //3 en hexa  
byte 02 : 0x00  // padding  
byte 03 : 0x00  // padding  
byte 04 : 0x0f  //1er byte del int. 15 en hexa  
byte 05 : 0x00  // 2do byte del int  
byte 06 : 0x00  // 3er byte del int  
byte 07 : 0x00  // 4to byte del int  
byte 08 : 0xff  // 1er byte del unsgined short int. 65535 en hexa es FFFF,ocupa 2 bytes  
byte 09 : 0xff  // 2do byte del unsgined short int  
byte 10 : 0x80  // char. 128 en hexa es 80  
byte 11 : 0xa2  // padding  
byte 12 : 0xff  // -1 en hexa es FFFF ya que 1 es 0000 0000 0000 0001, haciendole complemento es 1111 1111 1111 1110 y sumandole uno 1111 1111 1111 1111  
byte 13 : 0xff  // 2do byte de -1  
byte 14 : 0x01  // d[0] = 1  
byte 15 : 0x01  // d[1] = 1  
byte 16 : 0x01  // d[2] = 1  
byte 17 : 0xfb  // padding  
byte 18 : 0x26  // padding  
byte 19 : 0x9a  // padding  

### Correcciones a structs.h

Al compilar con gcc -Wall -Werror -pedantic, se obtiene un error con el char c al cual se le intenta asignar un valor int = 128. Si bien se pueden guardar un int de 8 bit en los char, el rango de los unsigned es de -128 a 127 y de los unsigned es 0 a 255, es por ello que lo cambie a unsigned  
Con respecto al unsigned short int que se le asigna -1, le quite el unsigned ya que si bien puedo asignarle un numero negativo a un unsigned, esto no me dara el valor esperado, si no el mayor valor que pueden alojar los short (65535).