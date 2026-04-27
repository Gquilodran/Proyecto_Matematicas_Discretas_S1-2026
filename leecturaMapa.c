#include <stdio.h>
#include <math.h>
#import "estructuras.h"


//Funcion que abrira el archivo txt con el mapa en caso de que exista
FILE recive_archivo(){
	char Narchivo[100];
	FILE *archivo;
	printf("Ingrese el nombre o ruta del arhivo con el mapa a probar:");
	scanf("%s", &Narchivo);

	archivo = fopen(Narchivo, "r"); //Lo abrimos en modo lectura

	if(archivo == NULL){
		printf("El archivo  %s no se pudo abrir o no existe.", Narchivo);
		return 1;
	}
	return archivo;
}


int cuenta_direcciones(calle calles[50]){
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
	return nX, nY;
}

//En esta función, desglosamos el archivo para trabajar con las calles y todo lo que contenga
void lee_archivo(FILE archivo){
	calle* calles[50]; //Arreglo de calles
	punto* puntos[50]; //Arreglo de puntos de interes

	int nPuntos=0;
	int nCalles=0;
	fscanf(archivo, "%d", &nCalle);

	for(int i=0; i<nCalle; i++){
		fscanf(archivo, "%s,%f,%f,%f,%f,%c", 
			calles[i].nombreCalle, 
			&calles[i].x1
			&calles[i].y1
			&calles[i].x2
			&calles[i].y1
			&calles[i].sentido
			);
	}

	for(int i=0; i<nPuntos;í++){
		fscanf(archivo, "%s,%s,%f",
			puntos[i].nombre,
			puntos[i].ubicacion,
			&puntos[i].altura
			);
	}
	printf(cuenta_direcciones(nCalles));
}