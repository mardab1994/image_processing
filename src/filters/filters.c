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
				image->computed_matrix[y * image->x_dim + x]  = 0;
			} else {
				image->computed_matrix[y * image->x_dim + x] = image->shades_of_grey;
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
					image->computed_matrix[y * image->x_dim + x]  = 0;
				}
			} else if (color_tresholding == WHITE) {
				if (image->matrix[y * image->x_dim + x] > treshold) {
					image->computed_matrix[y * image->x_dim + x]  = image->shades_of_grey;
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
			image->computed_matrix[y * image->x_dim + x]  = image->shades_of_grey *
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
				image->computed_matrix[y * image->x_dim + x] = 0;
			} else if (image->matrix[y * image->x_dim + x] >= white) {
				image->computed_matrix[y * image->x_dim + x] = image->shades_of_grey;
			} else {
				image->computed_matrix[y * image->x_dim + x] = (image->matrix[y * image->x_dim + x] - black) *
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
			image->computed_matrix[y * image->x_dim + x] = a + b;
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
				image->computed_matrix[y * image->x_dim + x] = (image->matrix[y * image->x_dim + x] + a + b) / 3;
			} else if (blurr_type == BLURR_VERTICALL) {
				image->computed_matrix[y * image->x_dim + x] = (image->matrix[y * image->x_dim + x] + c + d) / 3;
			} else if (blurr_type == BLURR_ORBITAL) {
				image->computed_matrix[y * image->x_dim + x] = (image->matrix[y * image->x_dim + x] + a + b + c + d) / 5;
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
			image->computed_matrix[y * image->x_dim + x] = (image->matrix[y * image->x_dim + x] - minimum_level) *
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

	int count_of_shades[256] = {0};
	float probability_of_shade_in_image[256] = {0};

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			count_of_shades[(image->matrix[y * image->x_dim + x])]++;

			if (image->matrix[y * image->x_dim + x] < minimum_level) {
				minimum_level = image->matrix[y * image->x_dim + x];
			}

			if (image->matrix[y * image->x_dim + x] > maximum_level) {
				maximum_level = image->matrix[y * image->x_dim + x];
			}
		}
	}

	float sum = 0;
	for (int i = 0; i < 256; i++) {
		probability_of_shade_in_image[i] = (float)(((float)count_of_shades[i]) / (image->x_dim*image->y_dim));
		sum += probability_of_shade_in_image[i];
	}
	if (sum < 1) {
		printf("sum prob = %f", sum);
	}


	float *cumulative_distribution;
	cumulative_distribution = malloc(image->x_dim * image->y_dim * sizeof(float));
	if (cumulative_distribution == NULL) {
		return ALOCATION_MEMORY;
	}

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			cumulative_distribution[y * image->x_dim + x] = 0;
		}
	}

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			for (int i = 0; i < image->matrix[y * image->x_dim + x]; i++) {
				cumulative_distribution[y * image->x_dim + x] += probability_of_shade_in_image[i];
			}
			cumulative_distribution[y * image->x_dim + x] = cumulative_distribution[y * image->x_dim + x] * (maximum_level - minimum_level) + minimum_level;
#if (DEBUG == 1)
			printf("%f\n",cumulative_distribution[y * image->x_dim + x] );
#endif
			}
	}

	for (int y = 0; y < image->y_dim; y++) {
		for (int x = 0; x < image->x_dim; x++) {
			image->computed_matrix[y * image->x_dim + x] = cumulative_distribution[y * image->x_dim + x];//round( 255 * ((cumulative_distribution[y * image->x_dim + x] - 1)/(image->x_dim * image->y_dim)) );
		}
	}

	return 0;
}





















