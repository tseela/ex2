#include "BMP.h"

struct BMP
{
    void BMP::readFile(const char *fname) {
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
            if(bmp_dib_header.bit_per_pixel == 8) {
                inp.read((char*)&bmp_color_palette, sizeof(bmp_color_palette));
            }

            // Jump to the pixel data location
            inp.seekg(bmp_header.offset_pixel_array, inp.beg);
            bmp_bitMapArray.resize(bmp_dib_header.width * bmp_dib_header.height * bmp_dib_header.bit_per_pixel / SIZE_OF_BYTE);

            // Checking the different row paddings
            if (bmp_dib_header.width % 4 == 0) {
                inp.read((char*)bmp_bitMapArray.data(), bmp_bitMapArray.size());
                bmp_header.file_size += static_cast<uint32_t>(bmp_bitMapArray.size());
            }
            else {
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

    void BMP::writeToFile(const char *fname) {
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
        if(bmp_dib_header.bit_per_pixel == 8) {
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
};
