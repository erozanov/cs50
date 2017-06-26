#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do {
        printf("Height: ");
        n = GetInt();
    } while( n < 0 || n > 23 );
    
    for(int i = 0; i < n; i++) 
    {
        for(int k = n - (i + 1); k > 0; k--){
                printf(" ");
            }
        for(int j = 0; j < i + 2; j++) 
        {
           printf("#"); 
        }
        printf("\n");
    }

}