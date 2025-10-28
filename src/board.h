#pragma once
#include <iostream>
#include "raylib.h"

inline constexpr int CELLS_QUANT { 8 };
inline constexpr int CELL_SIZE { 80 };
inline constexpr int SCREEN_WIDTH { CELL_SIZE * CELLS_QUANT};
inline constexpr int SCREEN_HEIGHT { CELL_SIZE * CELLS_QUANT};
inline constexpr int ADD_SCREEN_HEIGHT { 150 };
inline constexpr int FPS { 60 };

class Board {
    public:
        void drawBoard() const;
};
