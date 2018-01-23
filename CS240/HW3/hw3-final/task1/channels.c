// do not modify the line after the line after next
// do not modify the line after next
// do not modify the next line
#include "../lib/imageio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[])
{
	// TODO
	// Step 1: Load original image
	// Step 2: Separate channels
	// Step 3: Save each channels to three files
	// Step 4: Finalization

	IMAGE i = image_open(argv[1]);

	if (i == NULL)
		return -1;

	IMAGE i_red = image_clone(i);
	IMAGE i_gre = image_clone(i);
	IMAGE i_blu = image_clone(i);

	int h = image_height(i);
	int w = image_width(i);

	int x, y;
	int* pixel_r = image_pixels(i_red);
	int* pixel_g = image_pixels(i_gre);
	int* pixel_b = image_pixels(i_blu);

	for (y = 0; y < h; ++y) {
		for (x = 0; x < w; ++x) {
			int redMask = 0xFF0000FF;
			int greenMask = 0xFF00FF00;
			int blueMask = 0xFFFF0000;

			pixel_r[x + y * w] = pixel_r[x + y * w] & redMask;
			pixel_g[x + y * w] = pixel_g[x + y * w] & greenMask;
			pixel_b[x + y * w] = pixel_b[x + y * w] & blueMask;
		}
	}

	char *copyName = malloc(strlen(argv[1]));
	strcpy(copyName, argv[1]);
	char *lastt, *prevToken, *token;

	lastt = "o";
	token = strtok(copyName, ".");

	while (token != NULL) {
		lastt = prevToken;
		prevToken = token;
		token = strtok(NULL, ".");

		printf("%s  %s  %s\n", lastt, prevToken, token);
	}
	
	token = strtok(copyName, "/");

	while (token != NULL) {
		lastt = prevToken;
		prevToken = token;
		token = strtok(NULL, "/");

		printf("    %s   %s   %s\n", lastt, prevToken, token);
	}


	char *rName = malloc(strlen(prevToken) + 9);
	strcpy(rName, prevToken);
	strcat(rName, "_red.jpg");

	if (image_save(i_red, rName))
		return -1;

	char *gName = malloc(strlen(prevToken) + 11);
	strcpy(gName, prevToken);
	strcat(gName, "_green.tif");

	if (image_save(i_gre, gName))
		return -1;

	char *bName = malloc(strlen(prevToken) + 10);
	strcpy(bName, prevToken);
	strcat(bName, "_blue.bmp");

	if (image_save(i_blu, bName))
		return -1;


	image_close(i);
	image_close(i_red);
	image_close(i_gre);
	image_close(i_blu);

	return 0;
}
