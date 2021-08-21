#include <iostream>
#include <cstring>

union val_u {
 int i;
 char *s;
};


/* BONUS QUESTION (MACRO enabled implementation provided)
   There are 2 portability issues related to:
   a) Little (Intel) vs Big (Sparc) Endianess
   b) 32 vs 64 bit addressing
   But portable implementation:
   a) Negatively impacts performance
   b) Uses more buffer space
*/

//#define PORTABLE

#ifdef PORTABLE
#include <stdio.h>
#else
static const int ITCS(sizeof(int) / sizeof(char));
#endif

void serialize(void *buffer, const char *format, const
 union val_u src[]) {
 int itcs(sizeof(int) / sizeof(char));
 for(int i(0), j(0);; ++i) {
  char type = format[i];
  if(type == 'i') {
#ifndef PORTABLE
   char *pca = (char *) &(src[i].i);
   for(int k(0); k < ITCS; ++k, ++j) {
    ((char *) buffer)[j] = pca[k];
   } 
#else
   /* could really use stringstream, but sprintf performs better */
   j += sprintf(&((char *) buffer)[j], "%d", src[i].i);
   ((char *) buffer)[j++] = '\0';
#endif
  } else if(type == 's') {
   /* We could use strcpy to copy and strlen to advance j,
      but this assumes double iteration through s char array */
   for(int k(0);; ++k, ++j) {
    if((((char *) buffer)[j] = src[i].s[k]) == '\0') {
     ++j;
     break; 
    }
   } 
  } else {
   //Assume '\0' - null termination of format string
   break;
  }
 }
}

void deserialize(union val_u dst[], const char *format,
 const void *buffer) {
 for(int i(0), j(0);; ++i) {
  char type = format[i];
  if(type == 'i') {
#ifndef PORTABLE
   char *pca = (char *) &(dst[i].i);
   for(int k(0); k < ITCS; ++k, ++j) {
    pca[k] = ((char *) buffer)[j];
   }
#else
   /* could really use stringstream, but sscanf performs better */
   j += (sscanf(&((char *) buffer)[j], "%i", &dst[i].i) + 1);
#endif
  } else if(type == 's') {
   /* We could use strcpy to copy and strlen to advance j,
      but this assumes double iteration through s char array */
   for(int k(0);; ++k, ++j) {
    if(((dst[i].s[k]) = ((char *) buffer)[j]) == '\0') {
     ++j;
     break;
    }
   }
  } else {
   //Assume '\0' - null termination of format string
   break;
  }
 }
}

int main() {
 union val_u input[3];
 
 input[0].i = 3;
 input[1].s = new char[30];
 strcpy(input[1].s, " test string ");
 input[2].i = 5;
 
 char buffer[256];
 serialize(buffer, "isi", input);
 
 std::cout << input[0].i << input[1].s << input[2].i << " = ";
 
 union val_u output[3];
 output[1].s = new char[30];
 
 deserialize(output, "isi", buffer);
 
 std::cout << output[0].i << output[1].s << output[2].i <<
 std::endl;
 return 0;
}
