/*
 * filters.h
 *
 *  Created on: 24 wrz 2019
 *      Author: marcinsith
 */

#ifndef SRC_FILTERS_FILTERS_H_
#define SRC_FILTERS_FILTERS_H_

#include "../config.h"
#include "../image/image.h"

#include <stdbool.h>

typedef enum {
	WHITE = 0,
	BLACK
} color_tresholding_t;



int tresholding(image_t *image, int treshold);
int half_tresholding(image_t *image, int treshold, color_tresholding_t color_tresholding);
int gamma_correction(image_t *image, double gamma_level);
int change_levels(image_t *image, int black, int white);



#endif /* SRC_FILTERS_FILTERS_H_ */
