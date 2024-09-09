#ifndef COLOR_UTILS_H
#define COLOR_UTILS_H

#include <cstdint>

// Helper function to convert RGB to 565 format
inline uint16_t rgbTo565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

// Helper function to convert 565 format to RGB
inline void rgbFrom565(uint16_t color, uint8_t& r, uint8_t& g, uint8_t& b) {
    r = (color >> 11) & 0x1F;
    g = (color >> 5) & 0x3F;
    b = color & 0x1F;

    r = (r << 3) | (r >> 2);
    g = (g << 2) | (g >> 4);
    b = (b << 3) | (b >> 2);
}

#endif // COLOR_UTILS_H