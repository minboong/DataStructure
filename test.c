#include <stdio.h>

typedef enum color {red,black} color;

int main(){
    color clr = red;
    clr++;
    clr= !clr;

    printf("hello world\n");

    return 0;
}