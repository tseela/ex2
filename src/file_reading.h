#pragma once
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>

#define SIZE_OF_BYTE 8

#pragma pack(push, 1)
struct Header {
    uint16_t file_type{ 0x4D42 };          // File type always BM which is 0x4D42 (stored as hex uint16_t in little endian)
    uint32_t file_size{ 0 };               // Size of the file (in bytes)
    uint16_t reserved1{ 0 };               // Reserved, always 0
    uint16_t reserved2{ 0 };               // Reserved, always 0
    uint32_t offset_data{ 0 };             // Start position of pixel data (bytes from the beginning of the file)
};

struct DIBHeader {
    uint32_t size{ 40 };                      // Size of this header (BITMAPINFOHEADER's size is 40)
    int32_t width{ 0 };                      // width of bitmap in pixels
    int32_t height{ 0 };                     // width of bitmap in pixels
    uint16_t constant{ 1 };                  // this is always 1
    uint16_t bit_per_pixel{ 0 };             // number of bits per pixel (8 / 24)
    uint32_t compression{ 0 };               // 0
    uint32_t size_image{ 0 };                // probably 0
    int32_t x_pixels_per_meter{ 0 };
    int32_t y_pixels_per_meter{ 0 };
    uint32_t colors_used{ 0 };               // number color indexes in the color table. Use 0 for the max number of colors allowed by bit_per_pixel
    uint32_t colors_important{ 0 };          // number of colors used for displaying the bitmap. If 0 all colors are required
};

// has usage only if bit_per_pixel = 8
struct ColorPalette {
    uint32_t red_mask{ 0x00ff0000 };         // Bit mask for the red channel
    uint32_t green_mask{ 0x0000ff00 };       // Bit mask for the green channel
    uint32_t blue_mask{ 0x000000ff };        // Bit mask for the blue channel
    uint32_t alpha_mask{ 0xff000000 };       // Bit mask for the alpha channel
    uint32_t color_space_type{ 0x73524742 }; // Default "sRGB" (0x73524742)
    uint32_t unused[16]{ 0 };                // Unused data for sRGB color space
};
#pragma pack(pop)

struct BMP {
    Header bmp_header;
    DIBHeader bmp_dib_header;
    ColorPalette bmp_color_palette;
    std::vector<uint8_t> data;

    BMP(const char *fname) {
        readFile(fname);
    }

    void readFile(const char *fname) {
        std::ifstream inp {fname, std::ios_base::binary};
        if (inp) {
            // reading the bmp_header
            inp.read((char*)&bmp_header, sizeof(bmp_header));
            if(bmp_header.file_type != 0x4D42) {
                throw std::runtime_error("Error! Unrecognized file format.");
            }

            // reading color palette
            inp.read((char*)&bmp_dib_header, sizeof(bmp_dib_header));
            // The ColorPalette is used only for 8-bit files
            if(bmp_dib_header.bit_per_pixel == 8) {
                inp.read((char*)&bmp_color_palette, sizeof(bmp_color_palette));
            }

            // Jump to the pixel data location
            inp.seekg(bmp_header.offset_data, inp.beg);

            // Color palette appears only on 8-bit files
            if(bmp_dib_header.bit_per_pixel == 8) {
                bmp_header.offset_data = sizeof(Header) + sizeof(DIBHeader) + sizeof(ColorPalette);
            } else {
                bmp_header.offset_data = sizeof(Header) + sizeof(DIBHeader);
            }
            bmp_header.file_size = bmp_header.offset_data;

            if (bmp_dib_header.height < 0 || bmp_dib_header.width < 0) {
                throw std::runtime_error("Image's height or width is smaller then 0 (WTF?!?)");
            }

            data.resize(bmp_dib_header.width * bmp_dib_header.height * bmp_dib_header.bit_per_pixel / SIZE_OF_BYTE);

            // Checking the different row paddings
            if (bmp_dib_header.width % 4 == 0) {
                inp.read((char*)data.data(), data.size());
                bmp_header.file_size += static_cast<uint32_t>(data.size());
            }
            else {
                row_stride = bmp_dib_header.width * bmp_dib_header.bit_per_pixel / SIZE_OF_BYTE;
                uint32_t new_stride = make_stride_aligned(4);
                std::vector<uint8_t> padding_row(new_stride - row_stride); // vector of zero at the size of the padding row

                // reading the array data pixels into the data (and the padding_row)
                for (int i = 0; i < bmp_dib_header.height; ++i) {
                    inp.read((char*)(data.data() + row_stride * i), row_stride);
                    inp.read((char*)padding_row.data(), padding_row.size());
                }
                // Adding the bits that we read to the file's size
                bmp_header.file_size += static_cast<uint32_t>(data.size()) + bmp_dib_header.height * static_cast<uint32_t>(padding_row.size());
            }
        }
        else {
            throw std::runtime_error("Unable to open the input image file.");
        }
    }

private:
    uint32_t row_stride{ 0 };

    void write_headers(std::ofstream &of) {
        of.write((const char*)&bmp_header, sizeof(bmp_header));
        of.write((const char*)&bmp_dib_header, sizeof(bmp_dib_header));
        if(bmp_dib_header.bit_per_pixel == 32) {
            of.write((const char*)&bmp_color_palette, sizeof(bmp_color_palette));
        }
    }

    void write_headers_and_data(std::ofstream &of) {
        write_headers(of);
        of.write((const char*)data.data(), data.size());
    }

    // Add 1 to the row_stride until it is divisible with align_stride (for paddings)
    uint32_t make_stride_aligned(uint32_t align_stride) {
        uint32_t new_stride = row_stride;
        while (new_stride % align_stride != 0) {
            new_stride++;
        }
        return new_stride;
    }
};