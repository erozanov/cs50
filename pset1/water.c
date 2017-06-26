#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int m;
    do {
        printf("I need a minutes\n");
        m = GetInt();
    
    } while(m < 1);
    
    int b = m * 12;
    printf("minutes: %i\n", m);
    printf("bottles: %i\n", b);

}