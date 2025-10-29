#include "board.h"

#include <vector>


void Board::setTileOnBoard(Stone &t, const Vector2Int &xy) {
    t.x = xy.first;
    t.y = xy.second;
    if (t.isBlack) {
        whiteStones[0] = std::make_unique<Stone>(t);
    }else {
        blackStones[0] = std::make_unique<Stone>(t);
    }
}


void Board::drawTiles() const {
    DrawText(std::to_string(whiteStones.size()).c_str(), 100, BOARD_HEIGHT + CELL_SPACE, 16, BLACK);
    DrawText(std::to_string(blackStones.size()).c_str(), BOARD_WIDTH - 100, BOARD_HEIGHT + CELL_SPACE, 16, BLACK);
}


void Board::drawBoard() const {
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
