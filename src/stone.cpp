#include "stone.h"


void Stone::dragAtCursor(const float x, const float y) const {
    constexpr float center = static_cast<float>(textureWidth) / 2.0f;
    DrawTextureV(texture, {x - center, y - center}, WHITE);
}

void Stone::drawStone() const {
    const float scaleFigureToCell = static_cast<float>(CELL_SPACE) / static_cast<float>(textureWidth);
    DrawTextureEx(texture, {x, y}, 0, scaleFigureToCell, WHITE);
}