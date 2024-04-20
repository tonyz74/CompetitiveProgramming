#include <stdio.h>
#include <limits.h>

int main(void) {
    long x = 1e10;
    printf("%lu %llu\n", sizeof(long long), LONG_LONG_MAX);
    printf("x: %ld", x);
}
