#include "board.h"

#include <vector>


// Convert coords to cell position
Vector2Int getPosXYFloatToInt(const float x, const float y) {
    return {(x - NUMBERS_CELL_WIDTH) / CELL_SPACE, (y - LETTERS_CELL_HEIGHT) / CELL_SPACE};
}


void Board::setStoneOnBoard(Stone &t, const Vector2Int &toXY) {
    t.x = toXY.first;
    t.y = toXY.second;
    board[toXY.second][toXY.first] = std::make_unique<Stone>(t);
    // Make check for liberties
}


void Board::drawBowls() const {
    constexpr int indent { 100 };
    constexpr int spaceDownTheBoard { CELL_SPACE * 2 };

    constexpr float scaleFigureToCell = CELL_SPACE / coefCompression / static_cast<float>(textureWidth);
    // White bowl
    DrawTextureEx(bowlWStone,
        {indent - 7, BOARD_HEIGHT + spaceDownTheBoard - 9},
        0, scaleFigureToCell, WHITE);
    DrawText(std::to_string(whiteStones.size()).c_str(),
        indent, BOARD_HEIGHT + spaceDownTheBoard, 16, BLACK);

    // Black bowl
    DrawTextureEx(bowlBStone,
        {BOARD_WIDTH - indent - 7, BOARD_HEIGHT + spaceDownTheBoard - 9},
        0, scaleFigureToCell, WHITE);
    DrawText(std::to_string(blackStones.size()).c_str(),
        BOARD_WIDTH - indent, BOARD_HEIGHT + spaceDownTheBoard, 16, WHITE);
}


void Board::drawBoard() const {
    // Background
    DrawRectangle(0, 0, BOARD_WIDTH, BOARD_HEIGHT + ADD_SCREEN_HEIGHT, BACKGROUND_COLOR);

    int x = 0;
    int startPos = 0;
    bool first = true;

    // Vertical numbers
    while (x < CELLS_QUANT) {
        DrawText(std::to_string(CELLS_QUANT - x).c_str(),
            startPos + NUMBERS_CELL_WIDTH / 2 - 7,
            x * NUMBERS_CELL_HEIGHT + NUMBERS_CELL_HEIGHT / 2 + 3,
            16, BLACK);
        ++x;

        if (x == CELLS_QUANT && first) {
            startPos = BOARD_WIDTH + NUMBERS_CELL_WIDTH - CELL_SPACE + 3;
            first = false;
            x = 0;
        }
    }

    x = 0;
    startPos = 10;
    first = true;

    // Horizontal letters
    while (x < CELLS_QUANT) {
        const Vector2 textPos = {
            static_cast<float>(x * LETTERS_CELL_WIDTH + LETTERS_CELL_HEIGHT / 2 + NUMBERS_CELL_WIDTH - 12),
            static_cast<float>(startPos + LETTERS_CELL_WIDTH / 2 - LETTERS_CELL_HEIGHT - 2)
        };

        DrawTextCodepoint(GetFontDefault(), 'A' + x, textPos, 16, BLACK);
        ++x;

        if (x == CELLS_QUANT && first) {
            startPos = CELL_SPACE * CELLS_QUANT + LETTERS_CELL_HEIGHT - 20;
            first = false;
            x = 0;
        }
    }

    // Board itself
    // Horizontal lines
    for (int i = 0; i < CELLS_QUANT; i++) {
        const Vector2 startH = {
            NUMBERS_CELL_WIDTH,
            static_cast<float>(LETTERS_CELL_HEIGHT + i * CELL_SPACE + 10)
        }, endH = {
            NUMBERS_CELL_WIDTH + (CELLS_QUANT - 1) * CELL_SPACE,
            static_cast<float>(LETTERS_CELL_HEIGHT + i * CELL_SPACE + 10)
        };
        DrawLineEx(startH, endH, 1.5f, BLACK);
    }

    // Vertical lines
    for (int j = 0; j < CELLS_QUANT; j++) {
        const Vector2 startV = {
            static_cast<float>(NUMBERS_CELL_WIDTH + j * CELL_SPACE),
            LETTERS_CELL_HEIGHT + 10
        }, endV = {
            static_cast<float>(NUMBERS_CELL_WIDTH + j * CELL_SPACE),
            LETTERS_CELL_HEIGHT + (CELLS_QUANT - 1) * CELL_SPACE + 10
        };
        DrawLineEx(startV, endV, 1.5f, BLACK);
    }

    // Hoshi points
    constexpr float hoshiRadius { CELL_SPACE * 0.15f };
    constexpr int step = (CELLS_QUANT - 1) / 4;
    const std::vector hoshiPoints = {step, CELLS_QUANT / 2, CELLS_QUANT - 1 - step};

    for (const int i : hoshiPoints) {
        for (const int j : hoshiPoints) {
            const Vector2Int circlePos = {
                NUMBERS_CELL_WIDTH + j * CELL_SPACE,
                 LETTERS_CELL_HEIGHT + i * CELL_SPACE + 10};
            DrawCircle(circlePos.first, circlePos.second, hoshiRadius, BLACK);
        }
    }
}
