#include <stdlib.h>

int main() {
 char *p = (char *)malloc(1);
 free(p);
 free(p);
 return 0;
}
