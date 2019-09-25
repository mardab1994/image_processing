/*
 * filters.c
 *
 *  Created on: 24 wrz 2019
 *      Author: marcinsith
 */

#include "filters.h"
#include "../errors.h"

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



