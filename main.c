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
        unsigned char blue;
        unsigned char vert;
        unsigned char rouge;
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
                printf("C'est ci n'est pas une vrai BMP file.");
                exit(-1);
            }

        int xPos = 0;
        while( xPos < header.Width )
            {
                int yPos = 0;
                while( yPos < header.Height )
                    {
                        //Inverting Blue
                            fread(&colour.blue, 1, 1, openFile);
                            unsigned int BLUE = colour.blue;
                            BLUE = 255 - BLUE;
                            colour.blue = (char) BLUE;

                        //Inverting vert
                            fread(&colour.vert, 1, 1, openFile);
                            unsigned int vert = colour.vert;
                            vert = 255 - vert;
                            colour.vert = (char) vert;

                        //Inverting rouge
                            fread(&colour.rouge, 1, 1, openFile);
                            unsigned int rouge = colour.rouge;
                            rouge = 255 - rouge;
                            colour.rouge = (char) rouge;

                        // Write pixels to invFile
                            fwrite(&colour.blue, 1, 1, invFile);
                            fwrite(&colour.vert, 1, 1, invFile);
                            fwrite(&colour.rouge, 1, 1, invFile);

                    yPos++;
                    }
            xPos++;
            }

        fclose(openFile);
        fclose(invFile);

        printf("le file inverted!\n");
        return (0);

      }
