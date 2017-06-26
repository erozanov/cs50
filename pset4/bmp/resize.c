/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize need 4 arguments\n");
        return 0;
    }
    
    //resize n times
    int n = atoi(argv[1]);
    
    if (n < 1 || n > 100) {
        printf("n < 2 or > 100\n");
        return 1;
    }
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inpointer = fopen(infile, "r");
    if (inpointer == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outpointer = fopen(outfile, "w");
    if (outpointer == NULL)
    {
        fclose(inpointer);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inpointer);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inpointer);
    int originalWidth = bi.biWidth;
    int originalHeight = bi.biHeight;
    bi.biSizeImage*=n;
    bi.biWidth*=n;
    bi.biHeight*=n;
    

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outpointer);
        fclose(inpointer);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding for scanlines
    int paddingOriginal =  (4 - (originalWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);
    bf.bfSize = (bi.biSizeImage) + 54;
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outpointer);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outpointer);

    

    // iterate over infile's scanlines
    for (int i = 0, orHeight = abs(originalHeight); i < orHeight; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fseek(inpointer, (54 + ((originalWidth * sizeof(RGBTRIPLE) + paddingOriginal) * i)), SEEK_SET);
            // iterate over pixels in scanline
            for (int h = 0; h < originalWidth; h++) 
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inpointer);
                
                for (int k = 0; k < n; k++) 
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outpointer);
                }
            }
            
           // then add it back (to demonstrate how)
            for (int l = 0; l < padding; l++)
            {
                fputc(0x00, outpointer);
            }
            
        }
    }

    // close infile
    fclose(inpointer);

    // close outfile
    fclose(outpointer);

    // that's all folks
    return 0;
}
