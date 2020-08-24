#include <stdbool.h>
#include <string>
#include <memory>
#include "bmp_tester.hpp"
#include "BMP.h"

void printMatrix(std::unique_ptr<CMatrix>& lalala) {
    std::cout << "matrix:" << std::endl;
    for (uint32_t i = 0; i < lalala->getHeight(); i++) {
        for (uint32_t j = 0; j < lalala->getWidth(); j++) {
            std::cout << lalala->getValue(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void testing::bmp::rotate_image(const std::string& imagePath, const std::string& outputPath) {
    auto image = std::make_unique<BMP>(imagePath);
    auto bitMapCopy = image->BMP::getBitMapMatrix();
    std::swap(image->bmp_dib_header.width, image->bmp_dib_header.height);
    std::swap(image->bmp_dib_header.x_pixels_per_meter, image->bmp_dib_header.y_pixels_per_meter);
    std::unique_ptr<CMatrix> new_bitMap;
    printMatrix(bitMapCopy);
    if (image->bmp_dib_header.bit_per_pixel == BIT_PER_PIXEL_8) {
        new_bitMap = std::make_unique<CMatrix>(bitMapCopy->getWidth(), bitMapCopy->getHeight());
        for(uint32_t i = 0; i < bitMapCopy->getHeight(); ++i) {
            for(uint32_t j = 0; j < bitMapCopy->getWidth(); ++j) {
                new_bitMap->setValue(j, i, bitMapCopy->getValue(i, bitMapCopy->getWidth() - j - 1));
            }
        }
        printMatrix(new_bitMap);
    } else {
        new_bitMap = std::make_unique<CMatrix>(bitMapCopy->getWidth() / 3, bitMapCopy->getHeight() * 3);
        for(uint32_t i = 0; i < bitMapCopy->getHeight(); ++i) {
            for(uint32_t j = 0; j < bitMapCopy->getWidth() - 2; j += 3) {
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
    auto image = BMP(imagePath);
    uint32_t blue = image.bmp_color_palette.blue_mas;
    uint32_t red = image.bmp_color_palette.red_mask;
    uint32_t green = image.bmp_color_palette.green_mask;
    uint32_t grayScale = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
    image.bmp_color_palette.red_mask = grayScale;
    image.bmp_color_palette.green_mask = grayScale;
    image.bmp_color_palette.blue_mas = grayScale;
    image.writeToFile(outputPath);
}
