#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

int main(int argc, string argv[])
{
        if(argc != 2) 
        {
            printf("You need a argument\n");  
            return 1;
        }
        int key = atoi(argv[1]) % 26;
        string text = GetString();
        
        for(int i = 0, n = strlen(text); i < n; i++)
        {
            int letter = text[i];
            
            if(isalpha(letter))
            {
                char firstLetter = islower(letter) ? 'a' : 'A';
                letter = (letter + key - firstLetter) % ALPHABET_SIZE + firstLetter;

            }
            printf("%c", letter);  
        }
        printf("\n");  
    return 0;   
}
