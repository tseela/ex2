#include <stdbool.h>
#include <string>
#include "bmp_tester.hpp"
#include "BMP.h"

void testing::bmp::rotate_image(const std::string& imagePath, const std::string& outputPath) {
    auto image = BMP(imagePath);
    std::swap(image.bmp_dib_header.width, image.bmp_dib_header.height);
    std::swap(image.bmp_dib_header.x_pixels_per_meter, image.bmp_dib_header.y_pixels_per_meter);
    auto bitMap = image.BMP::getBitMapMatrix();
    auto bitMapCopy = CMatrix(bitMap);
    for(uint32_t i = 0; i < bitMap.getHeight(); ++i) {
        for(uint32_t j = 0; j < bitMap.getWidth(); ++j) {
            bitMap.setValue(i, j, bitMapCopy.getValue(j, bitMapCopy.getHeight() - i - 1));
        }
    }
    image.setBitMapMatrix(bitMap);
}


void testing::bmp::convert_to_grayscale(const std::string& imagePath, const std::string& outputPath) {

}
