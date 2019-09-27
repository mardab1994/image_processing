/*
 * filters.c
 *
 *  Created on: 24 wrz 2019
 *      Author: marcinsith
 */

#include "filters.h"
#include "../errors.h"

#include <math.h>

int
tresholding(image_t *image, int treshold)
{
	if (image == NULL) {
		return NO_IMAGE_PTR;
	}

	treshold = (treshold * image->shades_of_grey) / 100;

    for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			if (image->matrix[y * image->x_dim + x] <= treshold) {
				image->matrix[y * image->x_dim + x]  = 0;
			} else {
				image->matrix[y * image->x_dim + x] = image->shades_of_grey;
			}
		}
	}

    return 0;
}

int
half_tresholding(image_t *image, int treshold, color_tresholding_t color_tresholding)
{
	if (image == NULL) {
		return NO_IMAGE_PTR;
	}

	treshold = (treshold * image->shades_of_grey) / 100;

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			if (color_tresholding == BLACK) {
				if (image->matrix[y * image->x_dim + x] <= treshold) {
					image->matrix[y * image->x_dim + x]  = 0;
				}
			} else if (color_tresholding == WHITE) {
				if (image->matrix[y * image->x_dim + x] > treshold) {
					image->matrix[y * image->x_dim + x]  = image->shades_of_grey;
				}
			}
		}
	}

	return 0;
}

int
gamma_correction(image_t *image, double gamma_level)
{
	if (image == NULL) {
		return NO_IMAGE_PTR;
	}

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			image->matrix[y * image->x_dim + x]  = image->shades_of_grey *
					pow(((image->matrix[y * image->x_dim + x])/image->shades_of_grey), (1 / gamma_level));
		}
	}

	return 0;
}

int
change_levels(image_t *image, int black, int white)
{
	if (image == NULL) {
		return NO_IMAGE_PTR;
	}

	if (black > 255 || white > 255) {
		return COLOR_LEVEL_OVERFLOW;
	}

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			if (image->matrix[y * image->x_dim + x] <= black) {
				image->matrix[y * image->x_dim + x] = 0;
			} else if (image->matrix[y * image->x_dim + x] >= white) {
				image->matrix[y * image->x_dim + x] = image->shades_of_grey;
			} else {
				image->matrix[y * image->x_dim + x] = (image->matrix[y * image->x_dim + x] - black) *
						(image->shades_of_grey / (white - black));
			}
		}
	}

	return 0;
}


//-------------------------------------------------------------
// L O C A L     O P E R A T I O N S

int
contouring(image_t *image)
{
	if (image == NULL) {
		return NO_IMAGE_PTR;
	}

	int a, b;

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			if (x < image->x_dim - 1) {
				a = abs(image->matrix[y * image->x_dim + x + 1] - image->matrix[y * image->x_dim + x]);
			} else {
				a = 0;
			}

			if (y < image->y_dim - 1) {
				b = abs(image->matrix[(y + 1) * image->x_dim + x] - image->matrix[y * image->x_dim + x]);
			} else {
				b = 0;
			}
			image->matrix[y * image->x_dim + x] = a + b;
		}
	}

	return 0;
}


int
blurr(image_t *image, blurr_type_t blurr_type, int radius)
{
	if (image == NULL) {
		return NO_IMAGE_PTR;
	}

	if ((blurr_type > BLURR_ORBITAL) || (blurr_type < BLURR_HORIZONTALL)) {
		return BLURR_TYPE_OVERFLOW;
	}

	int a, b, c, d;

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			if (blurr_type != BLURR_VERTICALL) {	// dla horizontal i orbital
				if (x > 0) {
					a = image->matrix[y * image->x_dim + x - 1];
				} else {
					a = image->matrix[y * image->x_dim + x];
				}

				if (x < image->x_dim -1) {
					b = image->matrix[y * image->x_dim + x + 1];
				} else {
					b = image->matrix[y * image->x_dim + x];
				}
			}

			if (blurr_type != BLURR_HORIZONTALL) {	// dla vertical i orbital
				if (y > 0) {
					c = image->matrix[(y - 1) * image->x_dim + x];
				} else {
					c = image->matrix[y * image->x_dim + x];
				}

				if (y < image->y_dim - 1) {
					d = image->matrix[(y + 1) * image->x_dim + x];
				} else {
					d = image->matrix[y * image->x_dim + x ];
				}
			}

			if (blurr_type == BLURR_HORIZONTALL) {
				image->matrix[y * image->x_dim + x] = (image->matrix[y * image->x_dim + x] + a + b) / 3;
			} else if (blurr_type == BLURR_VERTICALL) {
				image->matrix[y * image->x_dim + x] = (image->matrix[y * image->x_dim + x] + c + d) / 3;
			} else if (blurr_type == BLURR_ORBITAL) {
				image->matrix[y * image->x_dim + x] = (image->matrix[y * image->x_dim + x] + a + b + c + d) / 5;
			}
		}
	}

	return 0;
}

//-------------------------------------------------------------
// G L O B A L     O P E R A T I O N S

int
hstogram_stretching(image_t *image)
{
	if (image == NULL) {
		return NO_IMAGE_PTR;
	}

	int minimum_level = 255;
	int maximum_level = 0;

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			if (image->matrix[y * image->x_dim + x] > maximum_level) {
				maximum_level = image->matrix[y * image->x_dim + x];
			} else if (image->matrix[y * image->x_dim + x]  < minimum_level) {
				minimum_level = image->matrix[y * image->x_dim + x];
			}
		}
	}

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			image->matrix[y * image->x_dim + x] = (image->matrix[y * image->x_dim + x] - minimum_level) *
					(maximum_level / (maximum_level - minimum_level));
		}
	}

	return 0;
}

int
histgram_alignment(image_t *image)
{
	if (image == NULL) {
		return NO_IMAGE_PTR;
	}

	int minimum_level = 256;
	int maximum_level = 0;

	int count_of_shades[256]; // tablica zawierajaca liczebnosc danego odcienia koloru

	int *count_of_shades_in_image;
	count_of_shades_in_image = malloc(image->shades_of_grey* sizeof(int));

	if (count_of_shades_in_image == NULL) {
		return ALOCATION_MEMORY;
	}
	for (int shades = 0; shades < 256; shades++) {

			count_of_shades[shades] = 0;

	}
	float *H;

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			if (image->matrix[y * image->x_dim + x] > maximum_level) {
				maximum_level = image->matrix[y * image->x_dim + x];
			} else if (image->matrix[y * image->x_dim + x]  < minimum_level) {
				minimum_level = image->matrix[y * image->x_dim + x];
			}

			for (int shades = 0; shades < 256; shades++) {
				if (shades == image->matrix[y * image->x_dim + x]) {
					count_of_shades[shades]++;
					break;
				}
			}
		}
	}

	H = malloc(image->x_dim * image->y_dim * sizeof(float));

	if (H == NULL) {
		return ALOCATION_MEMORY;
	}

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			H[y * image->x_dim + x] = (count_of_shades[image->matrix[y * image->x_dim + x]]) / (image->x_dim * image->y_dim);
		}
	}

//	for (int y = 0; y < image->y_dim; y++) {
//		for (int x = 0; x < image->x_dim; x++) {
//			image->matrix[y * image->x_dim + x] = (int) (((H[y * image->x_dim + x] - 1) / ((image->x_dim * image->y_dim) - 1)))*(image->shades_of_grey - 1);
//		}
//	}

	return 0;
}





















