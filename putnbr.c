#include <unistd.h>

void putnbr(int n) {
    long long int x = n;
    if (x < 0) x = -x;
    if (n < 0) write(1, "-", 1);
    if (n < 10)
    {
         char c = x + '0';
         write(1, &c, 1): 
