#include "SimpleTexture.h"

namespace cc {

uint32_t getMipLevel (uint32_t width, uint32_t height) {
    uint32_t size = std::max(width, height);
    uint32_t level = 0;
    while (size) { size >>= 1; level++; }
    return level;
}

bool isPOT (uint32_t n) { return n && (n & (n - 1)) == 0; }

bool canGenerateMipmap (uint32_t w, uint32_t h) {
    return isPOT(w) && isPOT(h);
}

} // namespace cc {
