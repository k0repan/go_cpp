#include "board.h"

#include <vector>


// Convert coords to cell position
Vector2Int getPosXYFloatToInt(const float x, const float y) {
    return {(x - NUMBERS_CELL_WIDTH) / CELL_SPACE, (y - LETTERS_CELL_HEIGHT) / CELL_SPACE};
}


int Board::setStoneOnBoard(const int col, const int row) {
    if (whiteBowl.empty() || board[row][col]) return -1;

    auto stone = std::move(whiteBowl.top());
    whiteBowl.pop();

    stone->x = NUMBERS_CELL_WIDTH + col * CELL_SPACE - CELL_SPACE / 2;
    stone->y = LETTERS_CELL_HEIGHT + row * CELL_SPACE - 10;

    board[row][col] = std::move(stone);

    std::cout << "Stone placed at: " << col << ", " << row << std::endl;
    // Make check for liberties
    return 1;
}

void Board::drawBowls() const {
    constexpr float scaleFigureToCell = CELL_SPACE / coefCompression / static_cast<float>(textureWidth);
    // White bowl
    DrawTextureEx(bowlWStone,
        {whiteBowlPos.x - 7, whiteBowlPos.y - 9},
        0, scaleFigureToCell, WHITE);
    DrawText(std::to_string(whiteBowl.size()).c_str(),
        whiteBowlPos.x + 7, whiteBowlPos.y + 7, 16, BLACK);

    // Black bowl
    DrawTextureEx(bowlBStone,
        { blackBowlPos.x - 7, blackBowlPos.y - 9},
        0, scaleFigureToCell, WHITE);
    DrawText(std::to_string(blackBowl.size()).c_str(),
        blackBowlPos.x + 7, blackBowlPos.y + 7, 16, WHITE);
}

void Board::drawStones() const {
    for (int i = 0; i < CELLS_QUANT; ++i) {
        for (int j = 0; j < CELLS_QUANT; ++j) {
            if (board[i][j]) {
                board[i][j]->drawStone();
            }
        }
    }
}


void Board::initBowls() {
    for (int i = 0; i < WHITE_STONES_QUANT; ++i) {
        whiteBowl.push(std::make_unique<Stone>(Stone(false, whiteBowlPos.x, whiteBowlPos.y)));
    }
    for (int i = 0; i < BLACK_STONES_QUANT; ++i) {
        blackBowl.push(std::make_unique<Stone>(Stone(true, blackBowlPos.x, blackBowlPos.y)));
    }
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
