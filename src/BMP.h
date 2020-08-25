#pragma once
#ifndef _BMP_H
#define _BMP_H

#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <memory>
#include "CMatrix.h"

#define SIZE_OF_BYTE 8
#define BIT_PER_PIXEL_8 8

#pragma pack(push, 1)
struct Header {
    uint16_t file_type = 0x4D42;          // File type always BM which is 0x4D42 (stored as hex uint16_t in little endian)
    uint32_t file_size = 0;               // Size of the file (in bytes)
    uint16_t reserved1 = 0;               // Reserved, always 0
    uint16_t reserved2 = 0;               // Reserved, always 0
    uint32_t offset_pixel_array = 0;      // Start position of pixel data (bytes from the beginning of the file)
};

struct DIBHeader {
    uint32_t size = 40;                     // Size of this header (BITMAPINFOHEADER's size is 40)
    int32_t width = 0;                      // width of bitmap in pixels
    int32_t height = 0;                     // width of bitmap in pixels
    uint16_t constant = 1;                  // this is always 1
    uint16_t bit_per_pixel = 0;             // number of bits per pixel (8 / 24)
    uint32_t compression = 0;               // 0
    uint32_t size_image = 0;                // probably 0
    int32_t x_pixels_per_meter = 0;
    int32_t y_pixels_per_meter = 0;
    uint32_t colors_used = 0;               // number color indexes in the color table. Use 0 for the max number of colors allowed by bit_per_pixel
    uint32_t colors_important = 0;          // number of colors used for displaying the bitmap. If 0 all colors are required
};

struct Color {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t padding;
    
    void toGray() {
        red = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
        blue = red;
        green = red;
    }
};
#pragma pack(pop)

struct BMP {
    Header bmp_header;
    DIBHeader bmp_dib_header;
    Color bmp_color_palette[256];

    BMP(const std::string& fname);

    void readFile(const std::string& fname);
    void writeToFile(const std::string& fname);

    std::unique_ptr<CMatrix> getBitMapMatrix() const;
    void setBitMapMatrix(std::unique_ptr<CMatrix>& bitMapMatrix);

private:
    uint32_t row_stride = 0;
    std::vector<uint8_t> bmp_bitMapArray;

    void writeHeader(std::ofstream &of);
    void writeBitMap(std::ofstream &of);

    // Add 1 to the row_stride until it is divisible with align_stride (for paddings)
    uint32_t make_stride_aligned(uint32_t align_stride);
};

#endif