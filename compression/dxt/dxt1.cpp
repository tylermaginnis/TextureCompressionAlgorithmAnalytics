#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cmath>
#include "../../include/dxt/color_utils.h"

// Function to compress texture using DXT1 algorithm
void compressWithDXT1(const std::vector<uint8_t>& textureData, int width, int height, std::vector<uint8_t>& compressedData) {
    std::cout << "Starting DXT1 compression..." << std::endl;

    // Ensure the compressed data vector is empty
    compressedData.clear();

    // DXT1 compression logic
    for (int y = 0; y < height; y += 4) {
        for (int x = 0; x < width; x += 4) {
            // Extract 4x4 block
            std::vector<uint8_t> block(64, 0); // 16 pixels * 4 bytes per pixel
            for (int j = 0; j < 4; ++j) {
                for (int i = 0; i < 4; ++i) {
                    int srcX = x + i;
                    int srcY = y + j;
                    if (srcX < width && srcY < height) {
                        int index = (srcY * width + srcX) * 4;
                        if (index + 3 < textureData.size()) {
                            block[(j * 4 + i) * 4 + 0] = textureData[index + 0];
                            block[(j * 4 + i) * 4 + 1] = textureData[index + 1];
                            block[(j * 4 + i) * 4 + 2] = textureData[index + 2];
                            block[(j * 4 + i) * 4 + 3] = textureData[index + 3];
                        }
                    }
                }
            }

            // Determine a 4-color palette
            uint8_t minR = 255, minG = 255, minB = 255;
            uint8_t maxR = 0, maxG = 0, maxB = 0;

            for (size_t j = 0; j < block.size(); j += 4) {
                uint8_t r = block[j];
                uint8_t g = block[j + 1];
                uint8_t b = block[j + 2];

                minR = std::min(minR, r);
                minG = std::min(minG, g);
                minB = std::min(minB, b);

                maxR = std::max(maxR, r);
                maxG = std::max(maxG, g);
                maxB = std::max(maxB, b);
            }

            uint16_t color1 = rgbTo565(minR, minG, minB);
            uint16_t color2 = rgbTo565(maxR, maxG, maxB);

            // Interpolate the other two colors in the palette
            uint8_t r1, g1, b1, r2, g2, b2;
            rgbFrom565(color1, r1, g1, b1);
            rgbFrom565(color2, r2, g2, b2);

            uint8_t r3 = (2 * r1 + r2) / 3;
            uint8_t g3 = (2 * g1 + g2) / 3;
            uint8_t b3 = (2 * b1 + b2) / 3;

            uint8_t r4 = (r1 + 2 * r2) / 3;
            uint8_t g4 = (g1 + 2 * g2) / 3;
            uint8_t b4 = (b1 + 2 * b2) / 3;

            uint16_t color3 = rgbTo565(r3, g3, b3);
            uint16_t color4 = rgbTo565(r4, g4, b4);

            // Assign each pixel an index into the palette
            std::vector<uint8_t> indices(16, 0);
            for (size_t j = 0; j < block.size(); j += 4) {
                uint8_t r = block[j];
                uint8_t g = block[j + 1];
                uint8_t b = block[j + 2];

                uint32_t dist1 = (r - r1) * (r - r1) + (g - g1) * (g - g1) + (b - b1) * (b - b1);
                uint32_t dist2 = (r - r2) * (r - r2) + (g - g2) * (g - g2) + (b - b2) * (b - b2);
                uint32_t dist3 = (r - r3) * (r - r3) + (g - g3) * (g - g3) + (b - b3) * (b - b3);
                uint32_t dist4 = (r - r4) * (r - r4) + (g - g4) * (g - g4) + (b - b4) * (b - b4);

                uint8_t index = 0;
                if (dist1 <= dist2 && dist1 <= dist3 && dist1 <= dist4) {
                    index = 0;
                } else if (dist2 <= dist1 && dist2 <= dist3 && dist2 <= dist4) {
                    index = 1;
                } else if (dist3 <= dist1 && dist3 <= dist2 && dist3 <= dist4) {
                    index = 2;
                } else {
                    index = 3;
                }

                indices[j / 4] = index;
            }

            // Pack the indices
            uint32_t packedIndices = 0;
            for (size_t k = 0; k < indices.size(); ++k) {
                packedIndices |= (indices[k] & 0x03) << (2 * k);
            }

            // Append the compressed block to the output data
            compressedData.push_back(static_cast<uint8_t>(color1 & 0xFF));
            compressedData.push_back(static_cast<uint8_t>((color1 >> 8) & 0xFF));
            compressedData.push_back(static_cast<uint8_t>(color2 & 0xFF));
            compressedData.push_back(static_cast<uint8_t>((color2 >> 8) & 0xFF));
            compressedData.push_back(static_cast<uint8_t>(packedIndices & 0xFF));
            compressedData.push_back(static_cast<uint8_t>((packedIndices >> 8) & 0xFF));
            compressedData.push_back(static_cast<uint8_t>((packedIndices >> 16) & 0xFF));
            compressedData.push_back(static_cast<uint8_t>((packedIndices >> 24) & 0xFF));
        }
    }

    std::cout << "DXT1 compression completed." << std::endl;
}

// Function to decompress texture using DXT1 algorithm
void decompressWithDXT1(const std::vector<uint8_t>& compressedData, int width, int height, std::vector<uint8_t>& textureData) {
    std::cout << "Starting DXT1 decompression..." << std::endl;

    textureData.resize(width * height * 4); // Resize the output vector to hold the decompressed data

    int blockIndex = 0;
    for (int y = 0; y < height; y += 4) {
        for (int x = 0; x < width; x += 4) {
            if (blockIndex + 7 >= compressedData.size()) {
                std::cerr << "Compressed data is too small for the given dimensions." << std::endl;
                return;
            }

            uint16_t color1 = compressedData[blockIndex] | (compressedData[blockIndex + 1] << 8);
            uint16_t color2 = compressedData[blockIndex + 2] | (compressedData[blockIndex + 3] << 8);
            uint32_t indices = compressedData[blockIndex + 4] | (compressedData[blockIndex + 5] << 8) | (compressedData[blockIndex + 6] << 16) | (compressedData[blockIndex + 7] << 24);

            uint8_t r1, g1, b1, r2, g2, b2;
            rgbFrom565(color1, r1, g1, b1);
            rgbFrom565(color2, r2, g2, b2);

            uint8_t r3 = (2 * r1 + r2) / 3;
            uint8_t g3 = (2 * g1 + g2) / 3;
            uint8_t b3 = (2 * b1 + b2) / 3;

            uint8_t r4 = (r1 + 2 * r2) / 3;
            uint8_t g4 = (g1 + 2 * g2) / 3;
            uint8_t b4 = (b1 + 2 * b2) / 3;

            for (int j = 0; j < 4; ++j) {
                for (int i = 0; i < 4; ++i) {
                    int dstX = x + i;
                    int dstY = y + j;
                    if (dstX < width && dstY < height) {
                        int index = (indices >> (2 * (j * 4 + i))) & 0x03;
                        int dstIndex = (dstY * width + dstX) * 4;

                        if (dstIndex + 3 < textureData.size()) { // Ensure index is within bounds
                            switch (index) {
                                case 0:
                                    textureData[dstIndex] = r1;
                                    textureData[dstIndex + 1] = g1;
                                    textureData[dstIndex + 2] = b1;
                                    textureData[dstIndex + 3] = 255;
                                    break;
                                case 1:
                                    textureData[dstIndex] = r2;
                                    textureData[dstIndex + 1] = g2;
                                    textureData[dstIndex + 2] = b2;
                                    textureData[dstIndex + 3] = 255;
                                    break;
                                case 2:
                                    textureData[dstIndex] = r3;
                                    textureData[dstIndex + 1] = g3;
                                    textureData[dstIndex + 2] = b3;
                                    textureData[dstIndex + 3] = 255;
                                    break;
                                case 3:
                                    textureData[dstIndex] = r4;
                                    textureData[dstIndex + 1] = g4;
                                    textureData[dstIndex + 2] = b4;
                                    textureData[dstIndex + 3] = 255;
                                    break;
                            }
                        } else {
                            std::cerr << "Index out of bounds in decompressWithDXT1: " << dstIndex << std::endl;
                        }
                    }
                }
            }

            blockIndex += 8;
        }
    }

    std::cout << "DXT1 decompression completed." << std::endl;
}