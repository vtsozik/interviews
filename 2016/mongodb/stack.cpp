#include <stdio.h>

void print(long a) {
 printf("%u, %u\n", a, (sizeof(a) * a));
 print(++a);
}

int main() {
 print(1);
 return 0;
}
