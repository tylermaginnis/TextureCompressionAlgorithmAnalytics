#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"

// Forward declaration of the DXT1 and DXT2 compression and decompression functions
void compressWithDXT1(const std::vector<uint8_t>& textureData, int width, int height, std::vector<uint8_t>& compressedData);
void decompressWithDXT1(const std::vector<uint8_t>& compressedData, int width, int height, std::vector<uint8_t>& textureData);
void compressWithDXT2(const std::vector<uint8_t>& textureData, int width, int height, std::vector<uint8_t>& compressedData);
void decompressWithDXT2(const std::vector<uint8_t>& compressedData, int width, int height, std::vector<uint8_t>& textureData);

// Enum for different compression algorithms
enum class CompressionAlgorithm {
    DXT1, DXT2, DXT3, DXT4, DXT5,
    ASTC_LDR, ASTC_HDR,
    ETC1, ETC2,
    PVRTC1, PVRTC2,
    BC1, BC2, BC3, BC4, BC5, BC6H, BC7
};

// Function to read PNG file and extract pixel data
std::vector<uint8_t> readPNG(const std::string& filePath, int& width, int& height, int& channels) {
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    if (!data) {
        std::cerr << "Failed to load PNG file: " << filePath << std::endl;
        return {};
    }

    channels = 4; // Ensure we have 4 channels (RGBA)
    std::vector<uint8_t> pixelData(data, data + (width * height * channels));
    stbi_image_free(data);
    return pixelData;
}

// Function to compress texture using the specified algorithm
bool compressTexture(const std::vector<uint8_t>& textureData, int width, int height, CompressionAlgorithm algorithm, std::vector<uint8_t>& compressedData) {
    switch (algorithm) {
        case CompressionAlgorithm::DXT1:
            std::cout << "Compressing using DXT1..." << std::endl;
            compressWithDXT1(textureData, width, height, compressedData);
            return true;
        case CompressionAlgorithm::DXT2:
            std::cout << "Compressing using DXT2..." << std::endl;
            compressWithDXT2(textureData, width, height, compressedData);
            return true;
        // Other cases...
        default:
            return false;
    }
}

// Function to uncompress texture using the specified algorithm
bool decompressTexture(const std::vector<uint8_t>& compressedData, int width, int height, CompressionAlgorithm algorithm, std::vector<uint8_t>& textureData) {
    switch (algorithm) {
        case CompressionAlgorithm::DXT1:
            std::cout << "Uncompressing using DXT1..." << std::endl;
            decompressWithDXT1(compressedData, width, height, textureData);
            return true;
        case CompressionAlgorithm::DXT2:
            std::cout << "Uncompressing using DXT2..." << std::endl;
            decompressWithDXT2(compressedData, width, height, textureData);
            return true;
        // Other cases...
        default:
            return false;
    }
}

// Function to write compressed data to a file
void writeToFile(const std::string& filePath, const std::vector<uint8_t>& data) {
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filePath << std::endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(data.data()), data.size());
    outFile.close();
}

// Function to read compressed data from a file
std::vector<uint8_t> readFromFile(const std::string& filePath) {
    std::ifstream inFile(filePath, std::ios::binary | std::ios::ate);
    if (!inFile) {
        std::cerr << "Failed to open file for reading: " << filePath << std::endl;
        return {};
    }
    std::streamsize size = inFile.tellg();
    inFile.seekg(0, std::ios::beg);
    std::vector<uint8_t> buffer(size);
    if (!inFile.read(reinterpret_cast<char*>(buffer.data()), size)) {
        std::cerr << "Failed to read file: " << filePath << std::endl;
        return {};
    }
    return buffer;
}

void printStatistics(const std::string& inputFilePath, const std::string& outputFilePath, int width, int height, int channels, const std::vector<uint8_t>& compressedData) {
    std::ifstream inputFile(inputFilePath, std::ios::binary | std::ios::ate);
    std::ifstream outputFile(outputFilePath, std::ios::binary | std::ios::ate);

    if (!inputFile || !outputFile) {
        std::cerr << "Failed to open input or output file for statistics." << std::endl;
        return;
    }

    auto inputFileSize = inputFile.tellg();
    auto outputFileSize = outputFile.tellg();

    std::cout << "Input File: " << inputFilePath << std::endl;
    std::cout << "Input File Size: " << inputFileSize << " bytes" << std::endl;
    std::cout << "Image Dimensions: " << width << "x" << height << std::endl;
    std::cout << "Number of Channels: " << channels << std::endl;

    std::cout << "Output File: " << outputFilePath << std::endl;
    std::cout << "Output File Size: " << outputFileSize << " bytes" << std::endl;
    std::cout << "Compression Ratio: " << static_cast<double>(inputFileSize) / outputFileSize << std::endl;
}

void saveAsPNG(const std::string& filePath, const std::vector<uint8_t>& data, int width, int height) {
    if (!stbi_write_png(filePath.c_str(), width, height, 4, data.data(), width * 4)) {
        std::cerr << "Failed to write PNG file: " << filePath << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <path/to/sample/directory> <path/to/output/directory>" << std::endl;
        return 1;
    }

    std::string sampleDirectory = argv[1];
    std::string outputDirectory = argv[2];

    for (const auto& entry : std::filesystem::directory_iterator(sampleDirectory)) {
        if (entry.path().extension() == ".png") {
            std::string inputFilePath = entry.path().string();
            int width, height, channels;
            std::vector<uint8_t> textureData = readPNG(inputFilePath, width, height, channels);

            if (textureData.empty()) {
                std::cerr << "Failed to read texture data from PNG file: " << inputFilePath << std::endl;
                continue;
            }

            for (int i = static_cast<int>(CompressionAlgorithm::DXT1); i <= static_cast<int>(CompressionAlgorithm::BC7); ++i) {
                CompressionAlgorithm algorithm = static_cast<CompressionAlgorithm>(i);
                std::vector<uint8_t> compressedData;
                if (compressTexture(textureData, width, height, algorithm, compressedData)) {
                    std::string algorithmName;
                    switch (algorithm) {
                        case CompressionAlgorithm::DXT1:
                            algorithmName = "DXT1";
                            break;
                        case CompressionAlgorithm::DXT2:
                            algorithmName = "DXT2";
                            break;
                        // Add other cases as needed
                        default:
                            algorithmName = "Unknown";
                            break;
                    }
                    std::string outputFilePath = outputDirectory + "/" + entry.path().filename().string() + "." + algorithmName + ".compressed";
                    writeToFile(outputFilePath, compressedData);
                    printStatistics(inputFilePath, outputFilePath, width, height, channels, compressedData);

                    // Uncompress the data to verify correctness
                    std::vector<uint8_t> uncompressedData;
                    if (decompressTexture(compressedData, width, height, algorithm, uncompressedData)) {
                        std::string uncompressedFilePath = outputDirectory + "/" + entry.path().filename().string() + "." + algorithmName + ".uncompressed.png";

                        // Save the uncompressed data as a PNG file
                        saveAsPNG(uncompressedFilePath, uncompressedData, width, height);
                    }
                }
            }
        }
    }

    return 0;
}