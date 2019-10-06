/*
 * menu.h
 *
 *  Created on: 5 paź 2019
 *      Author: marcinsith
 */

#ifndef SRC_MENU_MENU_H_
#define SRC_MENU_MENU_H_

typedef enum {
	START = 0,
	READ_IMAGE,
	SAVE_IMAGE,
	IMAGE_INFO,
	TRESHOLDING,
	HALF_TRESHOLDING,
	GAMMA,
	COUNTOURING,
	BLURR,
	HISTOGRAM_STRETCHING,
	HISTOGRAM_ALIGMENT,
	CHANGE_LEVELS,
	EXIT
} menu_t ;

void main_menu(void);




#endif /* SRC_MENU_MENU_H_ */
