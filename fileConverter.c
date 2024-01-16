#include "fileConverter.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int getFileLength(FILE *file) {
	// Go to the end, check the offset size and return to the begining of the file 
	fseek(file, 0, SEEK_END);
	unsigned int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	return size;
}

unsigned int fileToByteArray(char *filename, char **destinationArray) {
	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Cannot open \"%s\"", filename);
		perror("");
		return -1;
	}
	else {
		// Get the total length of the file
		unsigned int nBytes = getFileLength(file);
		*destinationArray = (char *)malloc(nBytes * sizeof(char));
		if (*destinationArray == NULL) {
			perror("Cannot allocate byte array");
			return -1;
		}
		// Copy all content in 
		if (fread(*destinationArray, nBytes, 1, file) != 1) {
			fclose(file);
			free(*destinationArray);
			perror("Cannot put file content in byte array");
			return -1;
		}
		// We have read the entire file
		return nBytes;
	}
}

void byteArrayToFile(char *filename, char *byteArray, unsigned int size) {
	FILE *outputFile = fopen(filename, "wb");
	if (outputFile == NULL) {
		printf("Cannot open \"%s\"", filename);
		perror("");
	}
	else {
		fwrite(byteArray, size, 1, outputFile);
		fclose(outputFile);
	}
}