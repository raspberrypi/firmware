//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
// Additional contributions copyright (c) 2011 Research In Motion Limited

// esUtil_TGA.c
//
//    This file contains the QNX implementation of a TGA image loader

#include <stdio.h>
#include <stdlib.h>

#include "esUtil.h"

////////////////////////////////////////////////////////////////////////////////////
//
//  Public Functions
//
//

///
//  LoadTGA()
//
int LoadTGA(const char *fileName, char **buffer, int *width, int *height)
{
    char path[255];
    strcpy(path, "./app/native/");
    strcat(path, fileName);

    FILE* file = fopen(path, "rb");
    if (!file)
    {
        return FALSE;
    }

    // Read the image header
    unsigned char header[12];
    fread(header, sizeof(unsigned char), 12, file);

    // Make sure this is a type 2 image
    if (header[2] != 2)
    {
        // Unsupported tga image type in file
        fclose(file);
        return FALSE;
    }

    // Make sure there is no color map in this image
    if (header[1] != 0)
    {
        // Unsupported color map
        fclose(file);
        return FALSE;
    }

    // Read width and height fields for the image
    short s;
    fread(&s, sizeof(short), 1, file);
    *width = s;
    fread(&s, sizeof(short), 1, file);
    *height = s;

    // Read in the bits per pixel format for this image (only support 24 and 32)
    unsigned char bpp;
    fread(&bpp, sizeof(unsigned char), 1, file);
    if (bpp != 24 && bpp != 32)
    {
        fclose(file);
        return FALSE;
    }

    // Calculate the actual number of color components and the texture data size
    int colorComponents = bpp / 8;
    int size = (*width) * (*height) * colorComponents;

    // Read past the image descriptor byte
    fseek(file, 1, SEEK_CUR);

    // Read past the image identification field, in case it exists
    if (header[0] > 0)
    {
        fseek(file, header[0], SEEK_CUR);
    }

    // Allocate space for the pixels in this image
    char* data = malloc(size);

    // Read in the texture data
    fread(data, 1, size, file);

    // Done reading in TGA file
    fclose(file);

    // Swap the first and third bytes - R (red) and B (blue) - to convert the image to RGB(A) format
    unsigned char temp;
    int i;
    for (i = 0; i < size; i += colorComponents)
    {
        temp = data[i];
        data[i] = data[i+2];
        data[i+2] = temp;
    }

    if (colorComponents == 3)
    {
        *buffer = data;
    }
    else if (colorComponents == 4)
    {
        // Convert RGBA to RGB
        int pixelCount = (*width) * (*height);
        *buffer = malloc(pixelCount * 3);
        for (i = 0; i < pixelCount; ++i)
        {
            (*buffer)[i * 3] = data[i * 4];
            (*buffer)[i * 3 + 1] = data[i * 4 + 1];
            (*buffer)[i * 3 + 2] = data[i * 4 + 2];
        }
        free(data);
    }

    return TRUE;
}
