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

int main (int argc, char **argv) {
	if (argc != 2) {
		printf("Bledna liczba argumentow\n");
		return 1;
	}

	read_image(argv);
	printf_image_info();
    print_image_matrix();
    save_image("kopia", 5);

	return 0;
}
