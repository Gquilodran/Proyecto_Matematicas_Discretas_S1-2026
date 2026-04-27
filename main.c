#include <stdio.h>
#import "leecturaMapa.c"

int main(){
	printf("Aqui esta el main");
	FILE archivo = recive_archivo();
	lee_archivo(archivo);
	return 0;
}
