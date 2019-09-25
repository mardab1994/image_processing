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




