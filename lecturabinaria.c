#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define LONG_MAX 50

typedef struct{
    int id;
    char nombre[LONG_MAX];
    int notas[3];
}Alumno;

FILE* inicio();
void procesamiento();

int main(){
    FILE* archivo=inicio();
    procesamiento(archivo); 
    fclose(archivo);
    return 0;
}

FILE* inicio(){
    char nombre_archivo[]="pruebabinaria.dat";
    FILE** archivo=fopen(nombre_archivo,"rb");
    if(archivo==NULL){
        printf("\nError al abrir archivo");
        exit(-1);
    }
    return archivo;
}

// void procesamiento(FILE*f){
//     Alumno nuevo;
//     while(true){
//         if(fread(&nuevo,sizeof(Alumno),1,f)!=1) break;
//         printf("\n%d - %s: %d %d %d", nuevo.id, nuevo.nombre,nuevo.notas[0], nuevo.notas[1], nuevo.notas[2]);
//     }
// }

void procesamiento(FILE*f){
    fseek(f,0,SEEK_END);
    int cantidad_alumnos = ftell(f)/sizeof(Alumno);
    Alumno lista[cantidad_alumnos];
    fseek(f,0,SEEK_SET);
    fread(lista,sizeof(Alumno),cantidad_alumnos,f);

    for(int i=0;i<cantidad_alumnos;i++){
        printf("\n%d - %s:", lista[i].id,lista[i].nombre);
        for(int j=0; j<=2; j++){
            printf(" %d",lista[i].notas[j]);
        }
    }
}