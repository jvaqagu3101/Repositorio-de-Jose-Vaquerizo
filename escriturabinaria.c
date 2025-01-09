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
    FILE* archivo=fopen(nombre_archivo,"ab");
    if(archivo==NULL){
        printf("\nError al abrir archivo");
        exit(-1);
    }
    return archivo;
}

void procesamiento(FILE* f){
    //int id=0;
    //char nombre[LONG_MAX+1];
    //int trim1,trim2,trim3;

    int contador=0;
    do{
        Alumno nuevo;
        printf("\n Dame el id (0 para salir)");
        scanf("%d",&nuevo.id);
        while(getchar()!='\n');
        if(nuevo.id==0) break;
        
        printf("\nDame el nombre: ");
        char formato[12]="";
        sprintf(formato,"%%%d[^\n]",LONG_MAX);
        scanf(formato,nuevo.nombre);
        while(getchar()!='\n');

        printf("\nDime las notas de los tres trimestres: ");
        scanf("%d",&nuevo.notas[0]);
        scanf("%d",&nuevo.notas[1]);
        scanf("%d",&nuevo.notas[2]);
        while(getchar()!='\n');

        fwrite(&nuevo,sizeof(Alumno),1,f);
        contador++;
    }while(true);
}