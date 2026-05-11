#include <stdio.h>
#include <math.h>
#include "estructuras.h"


//Funcion que abrira el archivo txt con el mapa en caso de que exista
FILE *recive_archivo(){
	char Narchivo[100];
	printf("Ingrese el nombre o ruta del archivo con el mapa a probar:\n");
	scanf("%s", Narchivo);

	FILE *archivo = fopen(Narchivo, "r"); //Lo abrimos en modo lectura

	if(archivo == NULL){
		printf("El archivo  %s no se pudo abrir o no existe.\n", Narchivo);
		return recive_archivo();
	}
	return archivo;
}


void cuenta_direcciones(calle calles[50]){
	int nX = 0;
	int nY = 0;
	for(int i = 0; i<50; i++){
		if(calles[i].sentido == 'X'){
			nX++;
		}else if(calles[i].sentido == 'Y'){
			nY++;
		}else{
			continue;
		}
	}
	printf("Sentidos X: %d, Sentidos Y: %d\n", nX, nY);
}

//En esta función, desglosamos el archivo para trabajar con las calles y todo lo que contenga
Datos lee_archivo(FILE *archivo){
	Datos mapaTuristico;
	mapaTuristico.nPuntos = 0;
	mapaTuristico.nCalles = 0;
	mapaTuristico.nX = 0;
	mapaTuristico.nY = 0;

	if(archivo==NULL) return mapaTuristico;

	fscanf(archivo, "%d", &mapaTuristico.nCalles);

	for(int i=0; i<mapaTuristico.nCalles; i++){
		fscanf(archivo, "%s %f %f %f %f %c", 
			mapaTuristico.calles[i].nombreCalle, 
			&mapaTuristico.calles[i].x1,
			&mapaTuristico.calles[i].y1,
			&mapaTuristico.calles[i].x2,
			&mapaTuristico.calles[i].y2,
			&mapaTuristico.calles[i].sentido
			);
		if(mapaTuristico.calles[i].sentido == 'X') mapaTuristico.nX++;
		if(mapaTuristico.calles[i].sentido == 'Y') mapaTuristico.nY++;
	}

	fscanf(archivo, "%d", &mapaTuristico.nPuntos);
	for(int i=0; i<mapaTuristico.nPuntos;i++){
		fscanf(archivo, "%s %s %lf",
			mapaTuristico.puntos[i].nombre,
			&mapaTuristico.puntos[i].ubicacion,
			&mapaTuristico.puntos[i].altura
			);
	}
	printf("Sentidos X: %d, Sentidos Y: %d\n", mapaTuristico.nX, mapaTuristico.nY);
	return mapaTuristico;
}

void ocupado(){
	printf("Aqui deberia ir una funcion que calcule un punto");
}