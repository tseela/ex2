
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <stdint.h>
#include "CMatrix.h"
#include "BMP.h"

BMP::BMP(const std::string& fname) {
    readFile(fname);
}

void BMP::readFile(const std::string& fname) {
    std::ifstream inp {fname, std::ios_base::binary};
    if (inp) {
        // reading the bmp_header
        inp.read((char*)&bmp_header, sizeof(bmp_header));
        if(bmp_header.file_type != 0x4D42) {
            throw std::runtime_error("Error! Unrecognized file format.");
        }

        // reading the DIB Header
        inp.read((char*)&bmp_dib_header, sizeof(bmp_dib_header));

        // reading color palette
        if(bmp_dib_header.bit_per_pixel == BIT_PER_PIXEL_8) {
            inp.read((char*)&bmp_color_palette, sizeof(bmp_color_palette));
        }

        // Jump to the pixel data location
        // inp.seekg(bmp_header.offset_pixel_array, inp.beg);
        bmp_bitMapArray.resize(bmp_dib_header.width * bmp_dib_header.height * bmp_dib_header.bit_per_pixel / SIZE_OF_BYTE);

        // Checking the different row paddings
        if (bmp_dib_header.width % 4 == 0) {
            inp.read((char*)bmp_bitMapArray.data(), bmp_bitMapArray.size());
            bmp_header.file_size += static_cast<uint32_t>(bmp_bitMapArray.size());
        } else {
            row_stride = bmp_dib_header.width * bmp_dib_header.bit_per_pixel / SIZE_OF_BYTE;
            uint32_t new_stride = make_stride_aligned(4);
            std::vector<uint8_t> padding_row(new_stride - row_stride); // vector of zero at the size of the padding row

            // reading the array data pixels into the data (and the padding_row)
            for (int i = 0; i < bmp_dib_header.height; ++i) {
                inp.read((char*)(bmp_bitMapArray.data() + row_stride * i), row_stride);
                inp.read((char*)padding_row.data(), padding_row.size());
            }
            // Adding the bits that we read to the file's size
            bmp_header.file_size += static_cast<uint32_t>(bmp_bitMapArray.size()) + bmp_dib_header.height * static_cast<uint32_t>(padding_row.size());
        }
    }
    else {
        throw std::runtime_error("Unable to open the input image file.");
    }
}

void BMP::writeToFile(const std::string& fname) {
    std::ofstream of {fname, std::ios_base::binary};
    if (of) {
        // Check for paddings
        if (bmp_dib_header.width % 4 == 0) {
            writeHeader(of);
            writeBitMap(of);
        } else {
            writeHeader(of);

            // Need paddings (just like in readFile)
            uint32_t new_stride = make_stride_aligned(4);
            std::vector<uint8_t> padding_row(new_stride - row_stride);

            // reading the array data pixels into the data (and the padding_row)
            for (int i = 0; i < bmp_dib_header.height; ++i) {
                of.write((const char*)(bmp_bitMapArray.data() + row_stride * i), row_stride);
                of.write((const char*)padding_row.data(), padding_row.size());
            }
        }
    }
    else {
        throw std::runtime_error("Unable to open the output image file.");
    }
}

void BMP::writeHeader(std::ofstream &of) {
    of.write((const char*)&bmp_header, sizeof(bmp_header));
    of.write((const char*)&bmp_dib_header, sizeof(bmp_dib_header));
    if(bmp_dib_header.bit_per_pixel == BIT_PER_PIXEL_8) {
        of.write((const char*)&bmp_color_palette, sizeof(bmp_color_palette));
    }
}

void BMP::writeBitMap(std::ofstream &of) {
    of.write((const char*)bmp_bitMapArray.data(), bmp_bitMapArray.size());
}

// Add 1 to the row_stride until it is divisible with align_stride (for paddings)
uint32_t BMP::make_stride_aligned(uint32_t align_stride) {
    uint32_t new_stride = row_stride;
    while (new_stride % align_stride != 0) {
        new_stride++;
    }
    return new_stride;
}

std::unique_ptr<CMatrix> BMP::getBitMapMatrix() const {
    if (bmp_dib_header.bit_per_pixel == BIT_PER_PIXEL_8) {
        auto matrix = std::make_unique<CMatrix>(bmp_dib_header.height, bmp_dib_header.width * 3);
        uint32_t k = 0;
        for (uint32_t i = 0; i < bmp_dib_header.height; ++i) {
            for (uint32_t j = 0; j < matrixWidth; ++j, ++k) {
                matrix->setValue(i, j, bmp_bitMapArray.at(k));
                matrix->setValue(i, j + 1, bmp_bitMapArray.at(k));
                matrix->setValue(i, j + 2, bmp_bitMapArray.at(k));
            }
        }
        return matrix;
    } else {
        uint32_t matrixWidth = bmp_dib_header.width * 3;
        auto matrix = std::make_unique<CMatrix>(bmp_dib_header.height, matrixWidth);
        uint32_t k = 0;
        for (uint32_t i = 0; i < bmp_dib_header.height; ++i) {
            for (uint32_t j = 0; j < matrixWidth; ++j, ++k) {
                matrix->setValue(i, j, bmp_bitMapArray.at(k));
            }
        }
        return matrix;
    }
}

void BMP::setBitMapMatrix(std::unique_ptr<CMatrix>& bitMapMatrix) {
    bmp_bitMapArray.resize(bitMapMatrix->getHeight() * bitMapMatrix->getWidth());
    uint32_t k = 0;
    for (uint32_t i = 0; i < bitMapMatrix->getHeight(); ++i) {
        for (uint32_t j = 0; j < bitMapMatrix->getWidth(); ++j, ++k) {
            bmp_bitMapArray.at(k) = static_cast<uint8_t>(bitMapMatrix->getValue(i, j));
        }
    }
}
Color::Color(uint32_t red, uint32_t green, uint32_t blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}
Color Color::toGray(Color& a) {
    uint32_t grayScale = 0.2126 * a.red + 0.7152 * a.green + 0.0722 * a.blue;
    return Color(grayScale,grayScale,grayScale);
}