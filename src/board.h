#pragma once
#include <array>
#include <iostream>
#include <memory>

#include "raylib.h"
#include "Tile.h"
#include "Vector2Int.h"

// Cells data
inline constexpr int CELLS_QUANT { 13 };
inline constexpr int CELL_SPACE { 40 };
inline constexpr int NUMBERS_CELL_WIDTH { 20 };
inline constexpr int NUMBERS_CELL_HEIGHT { CELL_SPACE };
inline constexpr int LETTERS_CELL_WIDTH { CELL_SPACE };
inline constexpr int LETTERS_CELL_HEIGHT { NUMBERS_CELL_WIDTH };
inline constexpr int WHITE_TILES_QUANT { 180 };
inline constexpr int BLACK_TILES_QUANT { WHITE_TILES_QUANT + 1 };
// Screen data
inline constexpr int BOARD_WIDTH { CELL_SPACE * CELLS_QUANT };
inline constexpr int BOARD_HEIGHT { CELL_SPACE * CELLS_QUANT };
inline constexpr int ADD_SCREEN_HEIGHT { 150 };
inline constexpr int FPS { 60 };

class Board {
    public:
        void drawBoard() const;
        void drawTiles() const;
        std::array<std::unique_ptr<Tile>, WHITE_TILES_QUANT> whiteTiles;
        std::array<std::unique_ptr<Tile>, BLACK_TILES_QUANT> blackTiles;
};
