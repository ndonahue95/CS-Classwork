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
	// Step 2: Negate it
	// Step 3: Save to file
	// Step 4: Finalization

	IMAGE i = image_open(argv[1]);

	if (i == NULL)
		return -1;

	IMAGE i_neg = image_clone(i);

	int h = image_height(i);
	int w = image_width(i);

	int x, y;
	int* pixel_neg = image_pixels(i_neg);

	for (y = 0; y < h; ++y) {
		for (x = 0; x < w; ++x) {
			pixel_neg[x + y * w] = (0xFFFFFF - pixel_neg[x + y * w]) | 0xFF000000;
		}
	}


	char *copyName = malloc(strlen(argv[1]));
	strcpy(copyName, argv[1]);
	char *token, *prevToken, *lastt;

	token = strtok(copyName, ".");

	while (token != NULL) {
		lastt = prevToken;
		prevToken = token;
		token = strtok(NULL, ".");

		printf("%s  %s  %s\n", token, prevToken, lastt);
	}
	
	token = strtok(copyName, "/");

	while (token != NULL) {
		lastt = prevToken;
		prevToken = token;
		token = strtok(NULL, "/");

		printf("%s  %s  %s\n", token, prevToken, lastt);
	}

	char *negName = malloc(strlen(prevToken) + 14);
	strcpy(negName, prevToken);
	strcat(negName, "_negation.bmp");

	if (image_save(i_neg, negName))
		return -1;

	image_close(i);
	image_close(i_neg);

	return 0;
}
