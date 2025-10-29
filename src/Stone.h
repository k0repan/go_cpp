#pragma once
#include "raylib.h"

#define filenameBSTONE "../textures/bstone.png"
#define filenameWSTONE "../textures/wstone.png"


class Stone {
    public:
        int x, y;
        bool isBlack { true };
        bool isStand { false };
        Texture2D texture;
        Stone(const bool isB, const int x, const int y): x(x), y(y), isBlack(isB) {
            if (isB) {
                texture = LoadTexture(filenameBSTONE);
            }else {
                texture = LoadTexture(filenameWSTONE);
            }
        }
        void dragAtCursor(int, int) const;
};
