#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

void StairCase(const int n) {
    //char *str = (char *)malloc(n); 
    char str[n];
    memset(str, '#', n);
    for(int i = 1; i <= n; ++i) {
        printf("%*.*s\n", n, i, str);
    }
    //free(str);
}

int main() {
    int _n = 6;
    //scanf("%d", &_n);
    
    StairCase(_n);
    
    return 0;
}
