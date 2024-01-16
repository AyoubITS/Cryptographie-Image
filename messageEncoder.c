#include "messageEncoder.h"
#include <stdio.h>
#include <stdlib.h>
#include "bmpConstants.h"

char getNthBit(char byte, char index) {
	return (byte >> index) & 1;
}

void codeCharacter(char character, unsigned int *index, char *byteArray) {
	for (char i = 0; i < 8; i++) {
		// pixels are in reverse position (B,G,R)
		*index = *index + 2;
		char bit = getNthBit(character, i);
		if (bit == 1) {
			//set the last bit of the pixel to 1
			byteArray[*index] |= 1; /// 1001 | 0001 == 1001
		}
		else {
			//set the last bit of the pixel to 0
			byteArray[*index] &= ~(1); /// 1001 & 1110 == 1000
		}
	}
}

void encodeMessage(char *message, unsigned char *byteArray, unsigned int arraySize) {
	// First bytes are the header are not used
	unsigned int arrayIndex = HEADER_BYTES_COUNT;
	unsigned int characterIndex = 0;
	char character;
	// code all characters into array until having the terminal character 
	do {
		character = message[characterIndex];
		codeCharacter(character, &arrayIndex, byteArray);
		characterIndex++;
	} while (character != '\0' && arrayIndex < arraySize);
}

char decodeCharacter(unsigned char *byteArray, unsigned int *index) {
	// Read the next 8 red characters bytes and put them in the resulting char
	unsigned char character = 0x00;
	for (int i = 0; i < 8; i++) {
		// red value is in the 3rd field of the array
		*index = *index + 2;
		char bit = byteArray[*index] & 1;
		character |= bit << i;
	}
	return character;
}

unsigned char *decodeMessage(unsigned char *byteArray, unsigned int arraySize) {
	// Don't touch at the first header bytes
	unsigned int arrayIndex = HEADER_BYTES_COUNT;
	// Each character take up to 8 pixels
	unsigned int maxNumberOfCharacters = arraySize / 8 + 1;
	char *decodedMessage = malloc(maxNumberOfCharacters * sizeof(char));
	if (decodedMessage == NULL) {
		perror("Cannot alocate memory for decoded message");
		return NULL;
	}
	unsigned int characterIndex = 0;
	while (characterIndex < maxNumberOfCharacters) {
		char decodedCharacter = decodeCharacter(byteArray, &arrayIndex);
		decodedMessage[characterIndex] = decodedCharacter;
		characterIndex++;
		if (decodedCharacter == '\0') {
			break;
		}
	}
	// Just in case, add aterminal character at the end in order to avoid reading garbage
	decodedMessage[maxNumberOfCharacters - 1] = '\0';
	return decodedMessage;
}
