/*
 * image.h
 *
 *  Created on: 23 wrz 2019
 *      Author: marcinsith
 */

#ifndef IMAGE_IMAGE_H_
#define IMAGE_IMAGE_H_

#include <stdio.h>
#include <stdlib.h>

#include "../config.h"


typedef struct {
	int magic_number;
	int x_dim;
	int y_dim;
	int shades_of_grey;
	int *matrix;
	int *computed_matrix;
	char image_name[IMAGE_NAME_LEN];
} image_t;

void read_image(char **argv);
void printf_image_info(void);
void print_image_matrix(void);
void save_image(char *name, int name_len);
image_t *image_get(void);

#endif /* IMAGE_IMAGE_H_ */
