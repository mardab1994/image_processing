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

#include "menu/menu.h"

int main (int argc, char **argv) {
	if (argc != 2) {
		printf("Bledna liczba argumentow\n");
		return 1;
	}

	read_image(argv);
	main_menu();

	return 0;
}
