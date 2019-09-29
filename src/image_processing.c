/*
 ============================================================================
 Name        : image_processing.c
 Author      : Marcin Dabioch
 Version     :
 Copyright   : Your copyright notice
 Description : image_processing in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "image/image.h"
#include "filters/filters.h"

int main (int argc, char **argv) {
	if (argc != 2) {
		printf("Bledna liczba argumentow\n");
		return 1;
	}

	printf("%s\n", argv[1]);

	read_image(argv);

	printf_image_info();

#if (DEBUG == 1)
    print_image_matrix();
#endif

    	printf("ERROR\n");
    }
    save_image("progowanie_", 11);

	return 0;
}
