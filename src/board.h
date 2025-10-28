#pragma once
#include <iostream>
#include "raylib.h"
#include "Vector2Int.h"

// Cells data
inline constexpr int CELLS_QUANT { 19 };
inline constexpr int CELL_SIZE { 40 };
inline constexpr int NUMBERS_CELL_WIDTH { 20 };
inline constexpr int NUMBERS_CELL_HEIGHT { CELL_SIZE };
inline constexpr int LETTERS_CELL_WIDTH { CELL_SIZE };
inline constexpr int LETTERS_CELL_HEIGHT { NUMBERS_CELL_WIDTH };
// Screen data
inline constexpr int SCREEN_WIDTH { CELL_SIZE * CELLS_QUANT};
inline constexpr int SCREEN_HEIGHT { CELL_SIZE * CELLS_QUANT};
inline constexpr int ADD_SCREEN_HEIGHT { 150 };
inline constexpr int FPS { 60 };

class Board {
    public:
        void drawBoard() const;
};
