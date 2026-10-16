#pragma once
#include "raylib.h"

#define filenameBSTONE "../textures/bstone32.png"
#define filenameWSTONE "../textures/wstone32.png"

inline constexpr int textureWidth { 32 };
inline constexpr int CELL_SPACE { 40 };

class Stone {
    public:
        float x, y;
        bool isBlack { true };
        bool isStand { false };
        Texture2D texture;
        Stone(const bool isB, const float x, const float y): x(x), y(y), isBlack(isB) {
            if (isB) {
                texture = LoadTexture(filenameBSTONE);
            }else {
                texture = LoadTexture(filenameWSTONE);
            }
        }
        // ~Stone(){ UnloadTexture(texture); }
        void dragAtCursor(float, float) const;
        void drawStone() const;
};
