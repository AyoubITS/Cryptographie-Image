#ifndef MESSAGE_ENCODER_H
#define MESSAGE_ENCODER_H

void encodeMessage(char *message, unsigned char *byteArray, unsigned int arraySize);
unsigned char *decodeMessage(unsigned char *byteArray, unsigned int arraySize);

#endif // !MESSAGE_ENCODER_H
