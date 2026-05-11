#include <stdio.h>
#include "leecturaMapa.c"
#include "construyeMapa.c"
#include "rutaTuristica.c"

int main(){
	while(1)
	{
		printf("Hola usuario\n");
		FILE *archivo = recive_archivo();
		Datos mapaTuristico = lee_archivo(archivo);
		if (mapaTuristico.nCalles == 0 || mapaTuristico.nPuntos == 0) {
			printf("No hay nada que procesar. Se solicitara que ingrese otro archivo\n");
			continue;
		}
		fclose(archivo);
		Grafo g;

		calcular_coordenadas_puntos(&mapaTuristico);
		construir_grafo(&mapaTuristico, &g);
		recorrer_puntos(&g, &mapaTuristico);

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

