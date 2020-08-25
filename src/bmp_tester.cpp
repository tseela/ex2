#include <stdbool.h>
#include <string>
#include <memory>
#include "bmp_tester.hpp"
#include "BMP.h"

void testing::bmp::rotate_image(const std::string& imagePath, const std::string& outputPath) {
    auto image = std::make_unique<BMP>(imagePath);
    auto bitMapCopy = image->BMP::getBitMapMatrix();
    std::swap(image->bmp_dib_header.width, image->bmp_dib_header.height);
    std::swap(image->bmp_dib_header.x_pixels_per_meter, image->bmp_dib_header.y_pixels_per_meter);
    std::unique_ptr<CMatrix> new_bitMap;
    if (image->bmp_dib_header.bit_per_pixel == BIT_PER_PIXEL_8) {
        new_bitMap = std::make_unique<CMatrix>(image->bmp_dib_header.height, image->bmp_dib_header.width);
        for (uint32_t i = 0; i < bitMapCopy->getHeight(); ++i) {
            for (uint32_t j = 0; j < bitMapCopy->getWidth(); ++j) {
                new_bitMap->setValue(j, i, bitMapCopy->getValue(i, bitMapCopy->getWidth() - j - 1));
            }
        }
    } else {
        new_bitMap = std::make_unique<CMatrix>(bitMapCopy->getWidth() / 3, bitMapCopy->getHeight() * 3);
        for (uint32_t i = 0; i < bitMapCopy->getHeight(); ++i) {
            for (uint32_t j = 0; j < bitMapCopy->getWidth() - 2; j += 3) {
                for (uint32_t k = 0; k < 3; ++k) {
                    new_bitMap->setValue(j / 3, 3 * i + k, bitMapCopy->getValue(i, bitMapCopy->getWidth() - j - 3 + k));
                }
            }
        }
    }
    image->setBitMapMatrix(new_bitMap);
    image->writeToFile(outputPath);
}


void testing::bmp::convert_to_grayscale(const std::string& imagePath, const std::string& outputPath) {
    auto image = std::make_unique<BMP>(imagePath);
    auto matrix = image->BMP::getBitMapMatrix();
    if (image->bmp_dib_header.bit_per_pixel == BIT_PER_PIXEL_8) {
        uint32_t numOfColorsUsed = 256;
        if (image->bmp_dib_header.colors_used != 0) {
            numOfColorsUsed = image->bmp_dib_header.colors_used;
        }
        for (uint32_t i = 0; i < numOfColorsUsed; ++i) {
            image->bmp_color_palette[i].toGray();
        }
    } else {
        auto new_bitMap = std::make_unique<CMatrix>(matrix->getHeight(), matrix->getWidth());
        for ( uint32_t i = 0; i < matrix->getHeight(); ++i ) {
            for ( uint32_t j = 0; j < matrix->getWidth(); j += 3 ) {
                uint32_t red = matrix->getValue(i, j);
                uint32_t green = matrix->getValue(i, j + 1);
                uint32_t blue = matrix->getValue(i, j + 2);
                double grayScale = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
                new_bitMap->setValue(i, j, grayScale);
                new_bitMap->setValue(i, j + 1, grayScale);
                new_bitMap->setValue(i, j + 2, grayScale);
            }
        }
        image->setBitMapMatrix(new_bitMap);
    }
    image->writeToFile(outputPath);
}
