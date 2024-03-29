/*
 * image.c
 *
 *  Created on: 23 wrz 2019
 *      Author: marcinsith
 */

#include "image.h"
#include <string.h>

static image_t image;

void
read_image(char **argv)
{
	FILE *fp;
	char ch;
	char *im_name = image.image_name;
	char *file_name = image.file_name;
	int cntr = 0;
	int *ptr;

	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("Blad otawrcia pliku");
		exit(1);
	}

    do {
		ch = fgetc(fp);

		if (ch == 'P') {
			fscanf(fp, "%d", &image.magic_number);
#if (DEBUG == 1)
			printf("Magic number = %d \n", image.magic_number);
#endif
			continue;
		}

		if (ch == '#') {
			while (ch != '\n') {
				ch = fgetc(fp);
				if (ch == ' ') {
					cntr++;
					continue;
				}
				*im_name++ = ch;
				if (cntr < 2) {
					*file_name++ = ch;
				}
			}
			fscanf(fp, "%d", &image.x_dim);
			fscanf(fp, "%d", &image.y_dim);
#if (DEBUG == 1)
			printf("x = %d \ny = %d\n", image.x_dim, image.y_dim);
#endif
			image.matrix = malloc(image.y_dim * image.x_dim * sizeof(int));
			if (image.matrix == NULL) {
				printf("Blad alokacji pamiec\n");
				exit(2);
			}

			image.computed_matrix = malloc(image.y_dim * image.x_dim * sizeof(int));
			if (image.computed_matrix == NULL) {
				printf("Blad alokacji pamiec\n");
				exit(2);
			}

			ptr = &image.matrix[0];
			ch = fgetc(fp);
			fscanf(fp, "%d", &image.shades_of_grey);
			continue;
		}

		if ((ch == ' ') || (ch == '\n')) {
			fscanf(fp, "%d", ptr++);
		}

    } while(ch != EOF);
#if (DEBUG == 1)
    printf("%s\n", image.file_name);
    printf("%s\n", image.image_name);
#endif
    fclose(fp);
}

void
printf_image_info(void)
{
	printf("Image name: %s", image.image_name);
	printf("Magic number: %d\n", image.magic_number);
	printf("X = %d\nY = %d\n", image.x_dim, image.y_dim);
	printf("Shades of grey: %d\n", image.shades_of_grey);
}

void
print_image_matrix(void)
{
    for (int y = 0; y < image.y_dim; y++) {
		for (int x = 0; x < image.x_dim; x++) {
			printf("%02d ", image.matrix[y*image.x_dim + x]);
		}
		printf("\n");
	}
}

void
save_image(char *name, int name_len)
{
	FILE *fp;
	char self_name[IMAGE_NAME_LEN];
	int j = 0;

	for (int i = 0; i < IMAGE_NAME_LEN; i++) {
		if (i < name_len) {
			self_name[i] = name[i];
		} else {
			self_name[i] = image.file_name[j];
			j++;
		}
	}

	if ((fp = fopen(self_name, "w")) == NULL) {
		printf("Blad otawrcia pliku");
		exit(1);
	}

	fprintf(fp, "P%d\n", image.magic_number);
	fprintf(fp, "# %s", image.image_name);
	fprintf(fp, "%d %d\n%d\n", image.x_dim, image.y_dim, image.shades_of_grey);

    for (int y = 0; y < image.y_dim; y++) {
		for (int x = 0; x < image.x_dim; x++) {
			fprintf(fp, "%d ", image.computed_matrix[y*image.x_dim + x]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);

	char show_up_image_name[IMAGE_NAME_LEN +10] = {"eog "};
	strcat(show_up_image_name ,self_name);

	system(show_up_image_name);
}

image_t
*image_get(void)
{
	return &image;
}
