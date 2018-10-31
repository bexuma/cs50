#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 512

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    uint8_t buf[512];

    int counter = 0;
    FILE *outptr = NULL;

    // Iterate over file contents
    while (fread(buf, BLOCK_SIZE, 1, inptr))
    {
        // Check if the first four bytes are a JPEG signature
        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff
            && (buf[3] & 0xf0) == 0xe0)
        {
            // Close the file, if it is opened
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            char filename[8];
            sprintf(filename, "%03d.jpg", counter);

            printf("%s\n", filename);

            // Open a new JPEG file for writing
            outptr = fopen(filename, "w");

            counter++;
        }

        if (outptr != NULL)
        {
            fwrite(buf, BLOCK_SIZE, 1, outptr);
        }
    }

    if (outptr != NULL)
    {
        fclose(outptr);
    }

    fclose(inptr);

    return 0;

}