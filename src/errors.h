/*
 * errors.h
 *
 *  Created on: 24 wrz 2019
 *      Author: marcinsith
 */

#ifndef SRC_ERRORS_H_
#define SRC_ERRORS_H_

typedef enum {
	INPUT_FILE = 1,
	NO_IMAGE_PTR,
	COLOR_LEVEL_OVERFLOW,
	BLURR_TYPE_OVERFLOW,
	ALOCATION_MEMORY,
	LAST_ERROR
} errors_t;

#endif /* SRC_ERRORS_H_ */
