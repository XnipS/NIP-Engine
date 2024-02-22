#pragma once

#include "core.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <bits/types/FILE.h>
#include <cstdio>

static inline void LoadBMPFromFile(const char* path)
{
    unsigned char* data;
    unsigned char header[54]; // Typical bmp header size
    unsigned int dataPos; // Start of data stream
    unsigned int imageSize; // width * height * 3
    unsigned int width, height;

    // Load file
    FILE* file = fopen(path, "rb");
    if (!file) {
        NE_LOG_ERROR("Image could not be loaded at %s\n", path);
    }

    // Check header contents
    if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
        NE_LOG_ERROR("Incorrect BMP file header size at %s\n", path);
    }
    if (header[0] != 'B' || header[1] != 'M') { // Check typical BMP header contents
        NE_LOG_ERROR("Incorrect BMP file header at %s\n", path);
    }

    // Read ints from the byte array
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    // Guess missing information
    if (imageSize == 0) {
        imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    }
    if (dataPos == 0) {
        dataPos = 54; // Typical BMP header
    }

    // Generate buffer
    data = new unsigned char[imageSize];

    // Read image into memory
    fread(data, 1, imageSize, file);

    // Cleanup
    fclose(file);

    // Create new GL Texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // Bind texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Pass texture to GL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    // Texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
