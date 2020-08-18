#include <stdbool.h>
#include <string>
#include "bmp_tester.hpp"
#include "file_reading.h"

void testing::bmp::rotate_image(const std::string& imagePath, const std::string& outputPath) {

}


void testing::bmp::convert_to_grayscale(const std::string& imagePath, const std::string& outputPath) {

}

bool is_file_bmp(const std::string& path) {
    std::string file = readFileContent(path);
    if (file[0] == 'B' && file[1] == 'M')
        return true;
}