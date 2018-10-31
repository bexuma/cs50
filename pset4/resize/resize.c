#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

void bitmapFile(BITMAPFILEHEADER);
void bitmapInfo(BITMAPINFOHEADER);

int main(int argc, char **argv)
{
    // command line accepts program name and three arguments
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // convert factor to int data type
    int n = atoi(argv[1]);
    if (n < 1 || n > 100)
    {
        fprintf(stderr, "Factor should be more than 0 and less than 101\n");
        return 1;
    }

    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
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
        return 4;
    }

    bitmapFile(bf);
    bitmapInfo(bi);

    int inptWidth = bi.biWidth;
    int inptHeight = abs(bi.biHeight);

    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding for scanlines
    int padding1 = (4 - (inptWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding2 = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = abs(bi.biHeight) * (sizeof(RGBTRIPLE) * bi.biWidth + padding2);

    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    bitmapFile(bf);
    bitmapInfo(bi);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < inptHeight; i++)
    {
        RGBTRIPLE *triples = malloc(inptWidth * sizeof(RGBTRIPLE));

        // populate the array with pixels from the scanline
        for (int j = 0; j < inptWidth; j++)
        {
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            triples[j] = triple;
        }

        // repeat the process below n times (new height)
        for (int h = 0; h < n; h++)
        {
            // repeat the process below for each original pixel
            for (int p = 0; p < inptWidth; p++)
            {
                // write the same pixel n times
                for (int x = 0; x < n; x++)
                {
                    fwrite(&triples[p], sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Add a new padding
            for (int l = 0; l < padding2; l++)
            {
                fputc(0x00, outptr);
            }

        }

        fseek(inptr, padding1, SEEK_CUR);

        free(triples);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

void bitmapFile(BITMAPFILEHEADER bf)
{
    printf("BITMAPFILEHEADER\n");
    printf("bfType: %i\n", bf.bfType);
    printf("bfSize: %i\n", bf.bfSize);
    printf("bfReserved1: %i\n", bf.bfReserved1);
    printf("bfReserved2: %i\n", bf.bfReserved2);
    printf("bfOffBits: %i\n\n", bf.bfOffBits);
}

void bitmapInfo(BITMAPINFOHEADER bi)
{
    printf("BITMAPINFOHEADER\n");
    printf("biSize: %i\n", bi.biSize);
    printf("biWidth: %i\n", bi.biWidth);
    printf("biHeight: %i\n", bi.biHeight);
    printf("biPlanes: %i\n", bi.biPlanes);
    printf("BitCount: %i\n", bi.biBitCount);
    printf("biCompression: %i\n", bi.biCompression);
    printf("biSizeImage: %i\n", bi.biSizeImage);
    printf("biXPelsPerMeter: %i\n", bi.biXPelsPerMeter);
    printf("biYPelsPerMeter: %i\n", bi.biYPelsPerMeter);
    printf("biClrUsed: %i\n", bi.biClrUsed);
    printf("biClrImportant: %i\n\n", bi.biClrImportant);
}