#include <stdio.h>
#include "leecturaMapa.c"

int main(){
	int eleccion;
	printf("Hola usuario, que desea realizar:\n");
	printf("1.-Subir mapa 	2.-Consultar opciones	3.-Cerrar\n");
	scanf("%d",&eleccion);
	if(eleccion==1){
		FILE *archivo = recive_archivo();
		Datos mapaTuristico = lee_archivo(archivo);
		return 0;
	}else if(eleccion==2){
		printf("Hasta pronto");
		return 0;
	}
}

