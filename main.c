/*
Made By Rein van der Linden / Sam Knoors - 2019
based on https://stackoverflow.com/questions/39823509/inverting-colors-of-pixels-in-a-bmp-file-in-c?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INPUT "Image.BMP"
#define OUTPUTINV "ImageInverted.BMP"

int main()
{
    struct BMP {
        char FileType[2];
        unsigned int FileSize;
        short Reserved1;
        short Reserved2;
        unsigned int DataOffset;
    };
    struct HEADER {
        unsigned int FileHeader;
        unsigned int HeaderSize;
        int Width;
        int Height;
        short Planes;
        short BitsPerPixel;
        unsigned int Compression;
        unsigned int BitmapSize;
        int HorizontalRes;
        int VerticalRes;
        unsigned int NumberColors;
        unsigned int ImportantColors;
    };
    struct COLOURS {
        unsigned char BLUE;
        unsigned char GREEN;
        unsigned char RED;
    };
    struct BMP bmp;
    struct HEADER header;
    struct COLOURS colour;

        FILE *openFile = fopen(INPUT, "rb+");
        FILE *invFile = fopen(OUTPUTINV, "wb+");

        fread(bmp.FileType, 1, 2, openFile);
        fread(&bmp.FileSize, 4, 1, openFile);
        fseek(openFile, 4, SEEK_CUR);
        fread(&bmp.DataOffset, 4, 1, openFile);
        fread(&header.FileHeader, 4, 1, openFile);
        fread(&header.Width, 4, 1, openFile);
        fread(&header.Height, 4, 1, openFile);
        fread(&header.Planes, 2, 1, openFile);
        fread(&header.BitsPerPixel, 2, 1, openFile);
        fread(&header.Compression, 4, 1, openFile);
        fread(&header.BitmapSize, 4, 1, openFile);
        fread(&header.HorizontalRes, 4, 1, openFile);
        fread(&header.VerticalRes, 4, 1, openFile);
        fread(&header.NumberColors, 4, 1, openFile);
        fread(&header.ImportantColors, 4, 1, openFile);

        fwrite(bmp.FileType, 1, 2, invFile);
        fwrite(&bmp.FileSize, 4, 1, invFile);
        fseek(invFile, 4, SEEK_CUR);
        fwrite(&bmp.DataOffset, 4, 1, invFile);
        fwrite(&header.FileHeader, 4, 1, invFile);
        fwrite(&header.Width, 4, 1, invFile);
        fwrite(&header.Height, 4, 1, invFile);
        fwrite(&header.Planes, 2, 1, invFile);
        fwrite(&header.BitsPerPixel, 2, 1, invFile);
        fwrite(&header.Compression, 4, 1, invFile);
        fwrite(&header.BitmapSize, 4, 1, invFile);
        fwrite(&header.HorizontalRes, 4, 1, invFile);
        fwrite(&header.VerticalRes, 4, 1, invFile);
        fwrite(&header.NumberColors, 4, 1, invFile);
        fwrite(&header.ImportantColors, 4, 1, invFile);

       if (bmp.FileType[0] != 'B' && bmp.FileType[1] != 'M')
            {
                printf("The file might not have the correct name or it might not be a BMP file. Please Check this!");
                return (0);
            }

        int xPos = 0;
        while( xPos < header.Width )
            {
                int yPos = 0;
                while( yPos < header.Height )
                    {
                        //Inverting BLUE
                            fread(&colour.BLUE, 1, 1, openFile);
                            unsigned int BLUE = colour.BLUE;
                            BLUE = 255 - BLUE;
                            colour.BLUE = (char) BLUE;

                        //Inverting GREEN
                            fread(&colour.GREEN, 1, 1, openFile);
                            unsigned int GREEN = colour.GREEN;
                            GREEN = 255 - GREEN;
                            colour.GREEN = (char) GREEN;

                        //Inverting RED
                            fread(&colour.RED, 1, 1, openFile);
                            unsigned int RED = colour.RED;
                            RED = 255 - RED;
                            colour.RED = (char) RED;

                        // Write pixels to invFile
                            fwrite(&colour.BLUE, 1, 1, invFile);
                            fwrite(&colour.GREEN, 1, 1, invFile);
                            fwrite(&colour.RED, 1, 1, invFile);

                    yPos++;
                    }
            xPos++;
            }

        fclose(openFile);
        fclose(invFile);

        printf("The BMP file has been inverted!\n");
        return (0);

      }
