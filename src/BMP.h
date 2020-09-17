#pragma once
#ifndef _BMP_H
#define _BMP_H

#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <memory>
#include <stdint.h>
#include "CMatrix.h"

static constexpr int const& SIZE_OF_BYTE = 8;
static constexpr int const& BIT_PER_PIXEL_8 = 8;
static constexpr int const& DEFAULT_COLOR_PALETTE_SIZE = 256;

#pragma pack(push, 1)
/**
 * @brief Struct for the header of the bmp file.
 * 
 */
struct Header {
    uint16_t file_type = 0x4D42;          // File type always BM which is 0x4D42 (stored as hex uint16_t in little endian)
    uint32_t file_size = 0;               // Size of the file (in bytes)
    uint16_t reserved1 = 0;               // Reserved, always 0
    uint16_t reserved2 = 0;               // Reserved, always 0
    uint32_t offset_pixel_array = 0;      // Start position of pixel data (bytes from the beginning of the file)
};

/**
 * @brief Struct for the DIB header of the bmp file.
 * 
 */
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

/**
 * @brief Struct for every color in the color palette of the file.
 *        Note that we have a color palette only in 8-bit files.
 * 
 */
struct Color {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t padding;
    
    /**
     * @brief Converts this color to grayscale.
     * 
     */
    void toGray() {
        red = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
        blue = red;
        green = red;
    }
};
#pragma pack(pop)

/**
 * @brief Struct for bmp file (24-bit or 8-bit).
 * 
 */
class BMP {
public:
    Header bmp_header;
    DIBHeader bmp_dib_header;
    Color bmp_color_palette[DEFAULT_COLOR_PALETTE_SIZE];

    /**
     * @brief Construct a new BMP object.
     * 
     * @param fname - the name (path) of the bmp file.
     */
    explicit BMP(const std::string& fname);

    /**
     * @brief Reading a bmp file into the struct.
     * 
     * @param fname - the name of the file.
     */
    void readFile(const std::string& fname);
    /**
     * @brief Writing the bmp image into the given file.
     * 
     * @param fname - the name of the file we need to write to.
     */
    void writeToFile(const std::string& fname);

    /**
     * @brief Get the Bit Map of the bmp in CMatrix form.
     * 
     * @return std::unique_ptr<CMatrix> 
     */
    std::unique_ptr<CMatrix> getBitMapMatrix() const;
    /**
     * @brief Set the Bit Map of the bmp using a CMatrix form.
     * 
     * @param bitMapMatrix 
     */
    void setBitMapMatrix(std::unique_ptr<CMatrix>& bitMapMatrix);

private:
    uint32_t m_row_stride = 0;
    std::vector<uint8_t> m_bmp_bitMapArray;

    /**
     * @brief Writes to the file the header, dib header and the color palette (only in 8-bit).
     * 
     * @param of - the stream we use to write with.
     */
    void writeHeader(std::ofstream &of);
    /**
     * @brief Writes to the file the bit map of the bmp.
     * 
     * @param of - the stream we use to write with.
     */
    void writeBitMap(std::ofstream &of);

    /**
     * @brief Gives the smallest number that is bigger then row_stride and divides by align_stride.
     * 
     * @param align_stride 
     * @return uint32_t 
     */
    uint32_t make_stride_aligned(uint32_t align_stride);
};

#endif