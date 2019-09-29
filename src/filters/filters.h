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

typedef enum {
	BLURR_HORIZONTALL = 0,
	BLURR_VERTICALL,
	BLURR_ORBITAL // orbitalne czyli do średniej brane są piksele z boku i od góry i od dołu
} blurr_type_t;

int tresholding(image_t *image, int treshold);
int half_tresholding(image_t *image, int treshold, color_tresholding_t color_tresholding);
int gamma_correction(image_t *image, double gamma_level);
int change_levels(image_t *image, int black, int white);

int contouring(image_t *image);
int blurr(image_t *image, blurr_type_t blurr_type, int radius);

int hstogram_stretching(image_t *image);
int histgram_alignment(image_t *image);

#endif /* SRC_FILTERS_FILTERS_H_ */
