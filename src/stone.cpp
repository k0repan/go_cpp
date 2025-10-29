#include "stone.h"


void Stone::dragAtCursor(const int x, const int y) const {
    const float centerX = static_cast<float>(texture.width) / 2.0f,
        centerY = static_cast<float>(texture.height) / 2.0f;
    DrawTextureV(texture, {x - centerX, y - centerY}, WHITE);
}
