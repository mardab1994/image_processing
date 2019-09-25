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

typedef enum {
	WHITE = 0,
	BLACK
} color_tresholding_t;
int tresholding(image_t *image, int treshold);

#endif /* SRC_FILTERS_FILTERS_H_ */
