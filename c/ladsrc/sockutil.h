/* sockutil.h - Prototypes for utility functions used in socket examples */

void die(char * message);
void copyData(int from, int to);
#ifndef CMSG_DATA
#define CMSG_DATA(cmsg) ((cmsg)->cmsg_data)
#endif
