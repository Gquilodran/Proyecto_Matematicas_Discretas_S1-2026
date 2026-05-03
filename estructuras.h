#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct{
	char nombreCalle[50];
	float x1, y1;
	float x2, y2;
	char sentido;
}calle;

typedef struct{
	char nombre[50];
	char ubicacion[50];
	float altura;
}punto;

typedef struct{
	calle calles[50];
	punto puntos[50];
	int nCalles;
    int nPuntos;
	int nX;
	int nY;
}Datos;

#endif