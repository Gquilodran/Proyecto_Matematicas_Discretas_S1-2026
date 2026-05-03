#include <stdio.h>
#include "leecturaMapa.c"

int main(){
	printf("Aqui esta el main");
	FILE *archivo = recive_archivo();
	Datos mapaTuristico = lee_archivo(archivo);
	return 0;
}
