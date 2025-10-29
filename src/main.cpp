#include <algorithm>

#include "board.h"
#define filenameIcon "../textures/go_cpp_icon.png"

// Check if the move can be able on the whole board
bool isValidMoveOnBoard(const float x, const float y) {
    const Vector2Int currentXY = getPosXYFloatToInt(x, y);
    return currentXY.first >= 0 && currentXY.first < CELLS_QUANT &&
        currentXY.second >= 0 && currentXY.second < CELLS_QUANT;
}

// Convert stone position to screen coords
inline Vector2 getPosXYIntToFloat(const int x, const int y) {
    return {static_cast<float>(x * CELL_SPACE + NUMBERS_CELL_WIDTH), static_cast<float>(y * CELL_SPACE + LETTERS_CELL_HEIGHT)};
}

// Convert mouse pos to board point
Vector2Int getBoardPositionFromMouse(const Vector2& mousePos) {
    int col = static_cast<int>((mousePos.x - NUMBERS_CELL_WIDTH + CELL_SPACE / 2) / CELL_SPACE),
    row = static_cast<int>((mousePos.y - LETTERS_CELL_HEIGHT + CELL_SPACE / 2) / CELL_SPACE);

    return {col, row};
}

Vector2 dragStoneCurrentPos {};

// Captured stone from bowl
void startDragStones(Board& board, const Vector2& mousePos) {
    if (mousePos.x >= whiteBowlPos.x - CELL_SPACE / 2 && mousePos.x <= whiteBowlPos.x + CELL_SPACE
        && mousePos.y >= whiteBowlPos.y - CELL_SPACE / 2 && mousePos.y <= whiteBowlPos.y + CELL_SPACE) {
        board.isStoneDragging = true;
    }
}

// Dynamic drag figure on screen
void updateDragStones(Board& board, const Vector2& mousePos) {
    if (board.isStoneDragging && !board.whiteBowl.empty()) {
        dragStoneCurrentPos = mousePos;
        board.whiteBowl.top()->dragAtCursor(mousePos.x, mousePos.y);

        Vector2Int boardPos = getBoardPositionFromMouse(mousePos);
        // std::cout << "Dragging over board position: " << boardPos.first << ", " << boardPos.second << std::endl;
    }
}

// Stand stone on end mouse pos
void endDragStones(Board& board) {
    if (board.isStoneDragging) {
        const Vector2Int boardPos = getBoardPositionFromMouse(dragStoneCurrentPos);
        const int newCol = boardPos.first;
        const int newRow = boardPos.second;
        const Vector2 newStoneXY = getPosXYIntToFloat(newCol, newRow);

        if (isValidMoveOnBoard(newStoneXY.x, newStoneXY.y) &&
            !board.whiteBowl.empty()) {
            const int setStatus = board.setStoneOnBoard(newCol, newRow);
            if (setStatus == -1) {
                std::cout << "Error occurred!" << std::endl;
            }
        }
        board.turnBackStone();
    }
}

void DragStones(const Vector2& mousePos, Board& board) {
    if (!board.isStoneDragging) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            startDragStones(board, mousePos);
        }
    } else {
        updateDragStones(board, mousePos);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            endDragStones(board);
        } if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            board.turnBackStone();
        }
    }
}


int main(){
    Vector2 mousePosition { 0 };

    InitWindow(BOARD_WIDTH,
        BOARD_HEIGHT + 2 * LETTERS_CELL_HEIGHT + ADD_SCREEN_HEIGHT,
        "GoCPP");
    SetTargetFPS(FPS);
    SetWindowIcon(LoadImage(filenameIcon));

    Board mainBoard;
    mainBoard.initBowls();

    while(!WindowShouldClose()){
        mousePosition = GetMousePosition();
        BeginDrawing();

        mainBoard.drawBoard();
        mainBoard.drawBowls();
        mainBoard.drawStones();

        DragStones(mousePosition, mainBoard);

        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
