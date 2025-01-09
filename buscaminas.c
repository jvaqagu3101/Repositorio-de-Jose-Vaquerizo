#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main () {
	const int ANCHO=15;
	const int ALTO=10;
	const float PORC_MINAS=0.25;
	char terreno[ALTO][ANCHO];//contiene casillas en blanco o minas
	int mapa[ALTO][ANCHO];//contine en cada casilla (cuando la visites) el número de minas que la rodean
	int xmedio=ANCHO/2;
	int xjugador, yjugador;
	char direccion;//dirección en la que decide moverse el jugador
	int direccion_valida;//para no salirme del terreno
	int fin=0;//para controlar si se acabó ya
	
	/////////////////Tareas iniciales//////////////////////
	srand(time(NULL));
	
	//Inicializo el terreno
	for(int i=0;i<ALTO;i++){
		for(int j=0;j<ANCHO;j++){
			terreno[i][j]=' ';
		}
	}
	//Añado las minas: aprox 25% del terreno(alguna repetirá posición)
	for(int i=0;i<(ALTO*ANCHO)*PORC_MINAS;i++){
		int x=rand()%ANCHO;
		int y=rand()%ALTO;
		terreno[y][x]='*';
	}
	//Me aseguro de que en la posición final no haya
	terreno[0][xmedio]=' ';
	//Tampoco alrededor del inicio, para crear una zona segura
	terreno[ALTO-1][xmedio-1]=' ';
	terreno[ALTO-1][xmedio]=' ';
	terreno[ALTO-1][xmedio+1]=' ';
	terreno[ALTO-2][xmedio-1]=' ';
	terreno[ALTO-2][xmedio]=' ';
	terreno[ALTO-2][xmedio+1]=' ';
	//Inicializo mapa
	for(int i=0;i<ALTO;i++){
		for(int j=0;j<ANCHO;j++){
			mapa[i][j]=-1;//casilla no visitada -> -1, visitada con n minas -> n
		}
	}	
	
	
	
	/////////////////Empezamos el juego//////////////////////
	
	//Coloco al jugador en la parte inferior central
	xjugador=xmedio;
	yjugador=ALTO-1;
	
	while(1){//En principio, jugadas infinitas. Hasta que gane o muera.		
		// system("clear");
		
		//Dibujo el mapa, marcando en amarillo la posición del jugador
		for(int i=0;i<ALTO;i++){
			printf("\n");
			for(int j=0;j<ANCHO;j++){
				if(j==xmedio && i==0){
					printf("\033[42m");//fondo de celda verde
				}
				else if(xjugador==j && yjugador==i){
					printf("\033[43m");//fondo de celda naranja
					//Calculo las minas que rodean al jugador si no he estado ya en esa celda
					if(mapa[i][j]==-1){
						mapa[i][j]=0;
						for(int fila=i-1;fila<=i+1;fila++){
							for(int columna=j-1;columna<=j+1;columna++){
								if(fila>=0 && fila<ALTO && columna>=0 && columna<ANCHO && terreno[fila][columna]=='*') mapa[i][j]++;
							}
						}
					}
				}else if(mapa[i][j]>=0){
					printf("\033[44m");//fondo de celda azul: el camino que voy recorriendo
				}else{
					printf("\033[47m");//fondo de celda blanco
				}
				//Muestro el nº de minas que rodean cada tramo del camino recorrido
				if(fin && terreno[i][j]=='*'){//Sólo imprimo las minas si se ha terminado la partida
					printf("\033[31m");//tinta roja
					printf("*");
				}else{
					printf("\033[30m");//tinta negra
					(mapa[i][j]<=0)?printf(" "):printf("%d",mapa[i][j]);
				}
			}
			printf("\033[0m");//vuelve al color normal
		}
		
				
		//Si en el movimiento anterior llegué al fín, ya no sigo después de imprimir el mapa
		if(fin) break;
		
		
		//Si choco con mina o llego a la salida, muestro mensaje y marco la partida como finalizada para que pare trás presentar el escenario la próxima vez
		if((xjugador==xmedio && yjugador==0) || terreno[yjugador][xjugador]=='*'){
			if(terreno[yjugador][xjugador]=='*') printf("\n ¡Has perdido!");
			else printf("\n   ¡¡ ENHORABUENA !!");
			fin=1;
			continue;//Para que no pida movimiento
		}
				
		
		//Sólo llego hasta aquí si no he chocado con minas y no he llegado a la salida
		//Pido al jugador que se mueva y le obligo a que elija una dirección válida
		direccion_valida=0;
		while(!direccion_valida){
			printf("\nMueve: ");
			scanf("\n%c",&direccion);
			switch(direccion){
			case 'w':
				if(yjugador>0){
					yjugador--;
					direccion_valida=1;
				}
				break;
			case 's':
				if(yjugador<ALTO-1){
					yjugador++;
					direccion_valida=1;
				}
				break;
			case 'a':
				if(xjugador>0){
					xjugador--;
					direccion_valida=1;
				}
				break;
			case 'd':
				if(xjugador<ANCHO-1){
					xjugador++;
					direccion_valida=1;
				}
				break;
			}
		}
	
	
	}

	return 0;
}
