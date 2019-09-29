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

    if (tresholding(image_get(), 50) != 0) {
    	printf("ERROR\n");
    }

    if (half_tresholding(image_get(),55 , BLACK) != 0) {
    	printf("ERROR\n");
    }

    if (gamma_correction(image_get(), 25) != 0) {
    	printf("ERROR\n");
    }

    if (change_levels(image_get(), 20, 30) != 0) {
    	printf("ERROR\n");
    }

    if (contouring(image_get()) != 0) {
    	printf("ERROR\n");
    }

    if (blurr(image_get(), BLURR_ORBITAL, 1) != 0) {
    	printf("ERROR\n");
    }

    if (hstogram_stretching(image_get()) != 0) {
    	printf("ERROR\n");
    }

    if (histgram_alignment(image_get()) != 0) {
    	printf("ERROR\n");
    }

	return 0;
}
