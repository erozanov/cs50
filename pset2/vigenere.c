#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

char getfirstletter(int value);

int main(int argc, string argv[])
{
        if (argc != 2) 
        {
            printf("You need a argument\n");  
            return 1;
        }
        
        string key = (argv[1]);
    
        int keylen = strlen(key);
        
        for(int i= 0; i < keylen; i++)
        {
          if (!isalpha(key[i]))
          {
            printf("Keyword must only contain letters A-Z and a-z");  
            return 1; 
          }
            
        }
        
        string text = GetString();
        
        for(int i = 0, keycount = 0, n = strlen(text); i < n; i++)
        {
            int letter = text[i];
            
            if(isalpha(letter))
            {
                char keyj = key[keycount % keylen];

                char incrementLetter = keyj - getfirstletter(keyj);
                
                letter = (letter + incrementLetter - getfirstletter(letter)) % ALPHABET_SIZE + getfirstletter(letter);
                keycount++;
            }
            printf("%c", letter);  
        }
        printf("\n");  
    return 0;   
}

char getfirstletter(int value)
{
    return islower(value) ? 'a' : 'A';
}



