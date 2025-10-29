#pragma once
#include <array>
#include <iostream>
#include <memory>

#include "raylib.h"
#include "stone.h"
#include "Vector2Int.h"

#define BACKGROUND_COLOR Color{0xE6, 0xDA, 0xC0, 0xFF}

// Cells data
inline constexpr int CELLS_QUANT { 13 };
inline constexpr int CELL_SPACE { 40 };
inline constexpr int NUMBERS_CELL_WIDTH { 20 };
inline constexpr int NUMBERS_CELL_HEIGHT { CELL_SPACE };
inline constexpr int LETTERS_CELL_WIDTH { CELL_SPACE };
inline constexpr int LETTERS_CELL_HEIGHT { NUMBERS_CELL_WIDTH };
inline constexpr int WHITE_STONES_QUANT { CELLS_QUANT * CELLS_QUANT / 2 };
inline constexpr int BLACK_STONES_QUANT { WHITE_STONES_QUANT + 1 };
inline constexpr int textureWidth { 1024 };
inline constexpr float coefCompression { 1.2f };
// Screen data
inline constexpr int BOARD_WIDTH { CELL_SPACE * CELLS_QUANT };
inline constexpr int BOARD_HEIGHT { CELL_SPACE * CELLS_QUANT };
inline constexpr int ADD_SCREEN_HEIGHT { 150 };
inline constexpr int FPS { 60 };

inline Texture2D bowlBStone;
inline Texture2D bowlWStone;

class Board {
    public:
        bool isStoneDragging { false };
        Vector2Int dragStonePos;
        void drawBoard() const;
        void drawBowls() const;
        void setStoneOnBoard(Stone&, const Vector2Int&);
        std::array<std::array<std::unique_ptr<Stone>, CELLS_QUANT>, CELLS_QUANT> board;
        std::array<std::unique_ptr<Stone>, WHITE_STONES_QUANT> whiteStones;
        std::array<std::unique_ptr<Stone>, BLACK_STONES_QUANT> blackStones;
        Board() {
            bowlBStone = LoadTexture(filenameBSTONE);
            bowlWStone = LoadTexture(filenameWSTONE);
        }
};

Vector2Int getPosXYFloatToInt(float, float);