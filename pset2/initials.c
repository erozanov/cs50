#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char* concat(char s1, char s2)
{
    return strcat(&s1, &s2);;
}

int main(void)
{
    
    string s = GetString();
    printf("%c",toupper(s[0]));
    for(int i = 0, n = strlen(s); i < n; i++) 
    {
        if (s[i] == ' ') 
        {
         printf("%c",toupper(s[i + 1]));
        }
    }
     printf("\n");
  
}

