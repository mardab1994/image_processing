/*
 * menu.c
 *
 *  Created on: 5 paź 2019
 *      Author: marcinsith
 */

#include "menu.h"

#include "../image/image.h"
#include "../filters/filters.h"

#include <stdio.h>
#include <stdlib.h>

static void print_menu(void);
static void select_menu(menu_t menu);
static int scan_input(int range_down, int range_up);

void
main_menu(void)
{

	menu_t menu = START;
	int tmp;

	do {
		print_menu();

		while((scanf("%d", &tmp) == 0) || (tmp < READ_IMAGE || tmp > EXIT)) {
			getchar();
			printf("Podaj Liczbe !!! \n");
		}

		menu = (menu_t)tmp;

		if (menu == EXIT) {
			exit(EXIT_SUCCESS);
		}

		select_menu(menu);
	} while(menu != EXIT);

}


static void
print_menu(void)
{

	printf("IMAGE PROCESSING\n\n");
	printf("[1]\tRead image\n");
	printf("[2]\tSave image\n");
	printf("[3]\tPrint image info\n");
	printf("[4]\tTresholding\n");
	printf("[5]\tHalf tresholding\n");
	printf("[6]\tGamma correction\n");
	printf("[7]\tCountouing\n");
	printf("[8]\tBlurr\n");
	printf("[9]\tHistogram stretching\n");
	printf("[10]\tHistogram aligment\n");
	printf("[11]\tChange levels\n");
	printf("[12]\tExit\n");
}

static void
select_menu(menu_t menu)
{

	switch(menu) {
	case READ_IMAGE:
		printf("READ_IMAGE\n");
		break;

	case SAVE_IMAGE:
		printf("SAVE_IMAGE\n");
		break;

	case IMAGE_INFO:
		printf("IMAGE_INFO\n");
		printf_image_info();
		break;

	case TRESHOLDING:
		printf("TRESHOLDING\n");
		printf("Set treshold in range <0, 100>\n ");
		int treshold = scan_input(0, 100);

		if (tresholding(image_get(), treshold) != 0) {
			printf("ERROR\n");
		}

		break;

	case HALF_TRESHOLDING:
		printf("HALF_TRESHOLDING\n");
		printf("Set treshold in range <0, 100>\n ");
		int half_treshold = scan_input(0, 100);

		printf("Set type tresholding (0 - WHITE, 1 - BLACK))");
		color_tresholding_t type = (color_tresholding_t)scan_input(0, 1);

	    if (half_tresholding(image_get(),half_treshold , type) != 0) {
	    	printf("ERROR\n");
	    }

		break;

	case GAMMA:
		printf("GAMMA\n");
		printf("Set gamma level\n");
		int gamma_level = scan_input(0, 255);
	    if (gamma_correction(image_get(), gamma_level) != 0) {
	    	printf("ERROR\n");
	    }

		break;

	case COUNTOURING:
		printf("COUNTOURING\n");
	    if (contouring(image_get()) != 0) {
	    	printf("ERROR\n");
	    }

		break;

	case BLURR:
		printf("BLURR\n");
		printf("Set blurr type [0 - HORIZONTAL, 1 - VERTICAL, 2 - ORBITAL]");

		blurr_type_t blurr_type = (blurr_type_t)scan_input(0, 3);

	    if (blurr(image_get(), blurr_type, 1) != 0) {
	    	printf("ERROR\n");
	    }

		break;

	case HISTOGRAM_STRETCHING:
		printf("HISTOGRAM_STRETCHING\n");
	    if (hstogram_stretching(image_get()) != 0) {
	    	printf("ERROR\n");
	    }

		break;

	case HISTOGRAM_ALIGMENT:
		printf("HISTOGRAM_ALIGMENT\n");
	    if (histgram_alignment(image_get()) != 0) {
	    	printf("ERROR\n");
	    }

		break;

	case CHANGE_LEVELS:
		printf("CHANGE_LEVELS\n");
		printf("Set white level\n");
		int white_level = scan_input(0, 255);
		printf("Set white level\n");
		int black_level = scan_input(0, 255);

	    if (change_levels(image_get(), black_level, white_level) != 0) {
	    	printf("ERROR\n");
	    }

		break;

	default:
		break;
	}

}

static int
scan_input(int range_down, int range_up)
{
	int input;

	while ((scanf("%d", &input) == 0) || (input < range_down || input > range_up)) {
		getchar();
		printf("Give a number in range: <%d, %d >!!! \n", range_down, range_up);
	}

	return input;
}





