/*
 * menu.c
 *
 *  Created on: 5 paź 2019
 *      Author: marcinsith
 */

#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

static void print_menu(void);
static void select_menu(menu_t menu);


void
main_menu(void)
{

	menu_t menu = START;
	int tmp;

	do {
		print_menu();
		while((scanf("%d", &tmp) == 0) || (tmp < 1 || tmp > 10)) {
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
	case TRESHOLDING:
		printf("TRESHOLDING\n");
		break;
	case HALF_TRESHOLDING:
		printf("HALF_TRESHOLDING\n");
		break;
	case GAMMA:
		printf("GAMMA\n");
		break;
	case COUNTOURING:
		printf("COUNTOURING\n");
		break;
	case BLURR:
		printf("BLURR\n");
		break;
	case HISTOGRAM_STRETCHING:
		printf("HISTOGRAM_STRETCHING\n");
		break;
	case HISTOGRAM_ALIGMENT:
		printf("HISTOGRAM_ALIGMENT\n");
		break;
	default:
		break;
	}
}









