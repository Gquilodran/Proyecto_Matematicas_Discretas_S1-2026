#import <stdio.h>


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


int lee_archivo(FILE archivo){
	calle calles[50]; //Arreglo de calles
	punto puntos[50]; //Arreglo de puntos de interes

	int nPuntos=0;
	int nCalles=0;
	fscanf(archivo, "%d", &nCalle);

	for(int i=0; i<nCalle; i++){
		fscanf(archivo, "%s,%f,%f,%f,%f,%f,")
	}
}