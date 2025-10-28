#include "board.h"


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
            startPos = CELL_SIZE * CELLS_QUANT + NUMBERS_CELL_WIDTH;
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
            startPos = CELL_SIZE * CELLS_QUANT + LETTERS_CELL_HEIGHT - 20;
            first = false;
            x = 0;
        }
    }

    // Board itself
    for (int i = 0; i < CELLS_QUANT; i++) {
        for (int j = 0; j < CELLS_QUANT; j++) {
            // Horizontal lines
            const Vector2 startH = {
                NUMBERS_CELL_WIDTH,
                static_cast<float>(LETTERS_CELL_HEIGHT + i * CELL_SIZE + 10)
            }, endH = {
                NUMBERS_CELL_WIDTH + (CELLS_QUANT - 1) * CELL_SIZE,
                static_cast<float>(LETTERS_CELL_HEIGHT + i * CELL_SIZE + 10)
            };

            // Vertical lines
            const Vector2 startV = {
                static_cast<float>(NUMBERS_CELL_WIDTH + j * CELL_SIZE),
                LETTERS_CELL_HEIGHT + 10
            }, endV = {
                static_cast<float>(NUMBERS_CELL_WIDTH + j * CELL_SIZE),
                LETTERS_CELL_HEIGHT + (CELLS_QUANT - 1) * CELL_SIZE + 10
            };

            DrawLineEx(startH, endH, 1.5f, BLACK);
            DrawLineEx(startV, endV, 1.5f, BLACK);
        }
    }
}
