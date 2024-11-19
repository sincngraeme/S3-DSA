#include "Huffman.h"
#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>

//#define _CRT_NONSTDC_NO_WARNINGS

void printMainMenu();

int main()
{
    int Flag = 0; // Flag to control the program loop
    int c;
    char inname[256], outname[256];
    FILE* f;
    unsigned char* in = nullptr;
    unsigned char* out = nullptr;
    long insize = 0, outsize = 0;
    int algo = 2; // Default to Huffman compression (algorithm 2)
    Huff huff;
    char* waste = NULL;

    while (!Flag)
    {
        // Render the menu
        printMainMenu();

        // Wait for keypress and read input
        while (!_kbhit()); // Wait for a key to be available
        c = _getch();      // Read the key

        switch (c)
        {
        case '1': // Compress File
            
            printf("Enter input file name: ");
            scanf("%255s", inname);
            printf("Enter output file name: ");
            scanf("%255s", outname);

            // Open input file
            f = fopen(inname, "rb");

            if (!f)
            {
                printf("Unable to open input file \"%s\".\n", inname);
                perror;
                break;
            }

            // Get input file size
            fseek(f, 0, SEEK_END);                          //go to the end of the file.
            insize = ftell(f);                              //Say how many bytes there were.
            fseek(f, 0, SEEK_SET);                          //go back to the start of the file.
            printf("Input file: %d bytes\n", insize);       //report.

            // Allocate memory for input buffer.
            in = (unsigned char*)malloc(insize*sizeof(unsigned char*));
            if (!in)
            {
                printf("Not enough memory\n");
                fclose(f);
                free(f);

                break;
            }

            // Read input file
            fread(in, 1, (size_t)insize, f);
            fclose(f);
            free(f);
        
            // Calculate worst-case buffer size for output
            outsize = (insize * (104 + 50)) / (100 + 384);
            out = (unsigned char*)malloc(outsize *sizeof(unsigned char*));

            if (!out)
            {
                printf("Not enough memory\n");
                free(in);
                break;
            }

            // Compress
            outsize = huff.Huffman_Compress(in, out, (unsigned int)insize);

            // Output file statistics
            printf("Output file: %d bytes (%.1f%%)\n", outsize, 100.0f * (float)outsize / (float)insize);

            // Write to output file
            f = fopen(outname, "wb");

            if (!f)
            {
                printf("Unable to open output file \"%s\".\n", outname);
                free(in);
                free(out);
                break;
            }

            fwrite(out, outsize, 1, f);
            fclose(f);
        
            // Free memory
            free(f);
            free(in);
            free(out);

            printf("File compressed successfully!\n");
            break;

        case '2': // Decompress File

            printf("Enter input file name: ");
            scanf("%255s", inname);
            printf("Enter output file name: ");
            scanf("%255s", outname);

            // Open input file
            f = fopen(inname, "rb");

            if (!f)
            {
                printf("Unable to open input file \"%s\".\n", inname);
                break;
            }

            // Get input file size
            fseek(f, 0, SEEK_END);
            insize = ftell(f);
            fseek(f, 0, SEEK_SET);
            printf("Input file: %d bytes\n", insize);

            // Allocate memory for input
            in = (unsigned char*)malloc(insize*(sizeof(unsigned char*)));

            if (!in)
            {
                printf("Not enough memory\n");
                fclose(f);
                free(f);
                break;
            }

            // Read input file
            fread(in, insize, 1, f);
            fclose(f);
            free(f);

            // Allocate memory for output (example size, adjust as needed)
            outsize = insize * 2; // Adjust based on expected decompressed size
            out = (unsigned char*)calloc(outsize , sizeof(unsigned char*));
            printf("Size of output buffer is: %d\n", sizeof(out));

            if (!out)
            {
                printf("Not enough memory\n");
                free(in);
                break;
            }

            // Decompress
            huff.Huffman_Uncompress(in, out, (unsigned int)insize, (unsigned int)outsize);
            printf("Decompression complete.\n");

            printf("the message contained in the file is: %s\n", out);

            // Write to output file
            f = fopen(outname, "wb");
            if (!f)
            {
                printf("Unable to open output file \"%s\".\n", outname);
                free(in);
                free(out);
                break;
            }

            fwrite(out, sizeof(char), outsize, f);       
            fclose(f);

            // Free memory
            free(f);           
            free(in);
            free(out);

            printf("File decompressed successfully!\n");
            break;

        case '3':
            printf("Exiting program.\n");
            Flag = 1; // Exit the loop
            break;

        default:
            printf("\nInvalid option. Please try again.\n");
            break;
        }
    }

    return 0;
}

// Renders main menu
void printMainMenu()
{
  //  printf("\033[H\033[J"); // Clear the screen using ANSI escape codes
    printf("--------------- Welcome ---------------\n\n");
    printf("\tCompress File\t\t(1)\n");
    printf("\tDecompress File\t\t(2)\n");
    printf("\tExit Program\t\t(3)\n");
    printf("\n----------------------------------------------\n");
}
