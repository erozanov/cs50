/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
/opt/sandbox50/bin/run.sh * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define CARD_NAME "card.raw"
#define BUFFER_SIZE 512

typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
    BYTE buffer[BUFFER_SIZE];
    char fileTitle[8];
    FILE* out = NULL;

    FILE* in = fopen(CARD_NAME, "r");
    
    if (in == NULL)
    {
        printf("Could not open file");
        fclose(in);
        return 1;
    }
    int fileCount = 0;
    int writing = 0;
    while (fread(&buffer, BUFFER_SIZE , 1, in) == 1) 
    {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && 
               (buffer[3] == 0xe0 || buffer[3] == 0xe1))
            {
                if (out != NULL) {
                    fclose(out);
                }
                sprintf(fileTitle, "%.3d.jpg", fileCount);
                out = fopen(fileTitle, "w");
                
                if (out == NULL)
                {
                    printf("couldn't open the new out file\n");
                    return 2;
                }
                fileCount++;
                writing = 1;
            }
            
            if (writing == 1 && out != NULL)
            {
               fwrite(&buffer, BUFFER_SIZE, 1, out); 
            }
    }
    fclose(in);
    fclose(out);
    return 0;
}
