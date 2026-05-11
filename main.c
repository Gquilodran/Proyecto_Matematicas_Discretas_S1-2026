#include <stdio.h>
#include "leecturaMapa.c"
#include "construyeMapa.c"

int main(){
	while(1)
	{
		printf("Hola usuario\n");
		FILE *archivo = recive_archivo();
		Datos mapaTuristico = lee_archivo(archivo);

		printf("Mapa leido exitosamente, que desea hacer ahora?\nIngrese 1 para leer otro mapa, o 2 para salir del programa\n");
		int eleccion=0;
		while(eleccion!=1 && eleccion!=2)
		{
			scanf("%d",&eleccion);
			if(eleccion==1){
				break;
			}else if(eleccion==2){
				printf("Hasta pronto");
				return 0;
			}else
			{
				printf("Accion invalida.\nIngrese 1 para leer otro mapa, o 2 para salir del programa\n");
			}
		}
	}
}

