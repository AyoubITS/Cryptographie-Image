#include <stdio.h>
#include <stdlib.h>
#include "fileConverter.h"
#include "messageEncoder.h"

#define INPUT_IMAGE_PATH "images\\galaxy.bmp"
#define OUTPUT_IMAGE_PATH "images\\img_out.bmp"

int main() {
	unsigned char *imgData;
	unsigned int fileSize = fileToByteArray(OUTPUT_IMAGE_PATH, &imgData);
	if (fileSize != -1) {
		//encodeMessage("salutations etranger", imgData, fileSize);
		char *msg = decodeMessage(imgData, fileSize);
		printf("message : %s\n", msg);
		//byteArrayToFile(OUTPUT_IMAGE_PATH, imgData, fileSize);
		free(imgData);
	}
	return 0;
}