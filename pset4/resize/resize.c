/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize factor infile outfile\n");
        return 1;
    }
    // remember inputs
    float f= atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];
    
    if (f<=0.0 || f>100.0)
    {
        fprintf(stderr, "Factor has to be a Float between 0 and 100\n");
        return 2;
    }
    
    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    //New headers
    int Old_Width = bi.biWidth;
    int Old_Width_bytes = bi.biWidth * sizeof(RGBTRIPLE);
    int Old_Height = abs(bi.biHeight);
    int Old_padding = ((4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4); 
    bi.biWidth *= f;
    bi.biHeight *= f;
    bi.biSizeImage = (((sizeof(RGBTRIPLE) * bi.biWidth)+ ((4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4)) * abs(bi.biHeight));
    bf.bfSize= bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);


    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int New_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0; i < Old_Height; i++)
    {
        //For f times
        for (int l = 0; l < f; l++)
            {
            // iterate over pixels in scanline of infile
            for (int j = 0; j < Old_Width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // Write f times in the horizontal row in outfile
                for (int k = 0; k < f; k++)
                {
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add new padding in outfile
            for (int k = 0; k < New_padding; k++)
                {
                fputc(0x00, outptr);
                }
            // Move Current In Pointer back to the start
            fseek(inptr, -Old_Width_bytes, SEEK_CUR); 
            }
        // Move Current Pointer to the end of the scanline of infile
        fseek(inptr, Old_Width_bytes + Old_padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}