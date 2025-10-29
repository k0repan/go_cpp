#include "board.h"
#define filenameIcon "../textures/go_cpp_icon.png"

// Check if the move can be able on the whole board
bool isValidMoveOnBoard(const float x, const float y) {
    const Vector2Int currentXY = getPosXYFloatToInt(x, y);
    return currentXY.first >= 0 && currentXY.first < CELLS_QUANT &&
        currentXY.second >= 0 && currentXY.second < CELLS_QUANT;
}

// Convert figure position to screen coords
inline Vector2 getPosXYIntToFloat(const int x, const int y) {
    return {static_cast<float>(x * CELL_SPACE + NUMBERS_CELL_WIDTH), static_cast<float>(y * CELL_SPACE + LETTERS_CELL_HEIGHT)};
}

// Convert mouse pos to cell position
inline Vector2Int getMousePosOnBoardXY(const Vector2 &mousePos) {
    return {static_cast<int>(mousePos.x - NUMBERS_CELL_WIDTH) / CELL_SPACE, static_cast<int>(mousePos.y - LETTERS_CELL_HEIGHT) / CELL_SPACE};
}

Vector2Int dragStoneCurrentPos {};

// Captured figure
void startDragFigures(Board& board, const Vector2& mousePos) {
    const Vector2Int xy = getMousePosOnBoardXY(mousePos);

    if (board.board[xy.second][xy.first]) {
        board.isStoneDragging = true;
        board.dragStonePos = xy;
    }
}

// Dynamic drag figure on screen
void updateDragFigures(const Board& board, const Vector2& mousePos) {
    if (board.isStoneDragging) {
        dragStoneCurrentPos = getMousePosOnBoardXY(mousePos);

        const Stone* stonePtr = board.board[board.dragStonePos.second][board.dragStonePos.first].get();
        if (stonePtr) {
            stonePtr->dragAtCursor(mousePos.x, mousePos.y);
        }
    }
}

// Stand figure on end mouse pos
void endDragFigures(Board& board) {
    if (board.isStoneDragging) {
        const int newCol = dragStoneCurrentPos.first;
        const int newRow = dragStoneCurrentPos.second;
        const Vector2 newStoneXY = getPosXYIntToFloat(newCol, newRow);

        if (isValidMoveOnBoard(newStoneXY.x, newStoneXY.y) && dragStoneCurrentPos != board.dragStonePos) {
            Stone* figurePtr = board.board[board.dragStonePos.second][board.dragStonePos.first].get();

            if (figurePtr) {
                /*const int moveStatus = board.moveFigureOnBoard(*figurePtr, newCol, newRow);
                if (moveStatus == 0){
                    figurePtr->moveFigure(newFigXY.x, newFigXY.y);
                    std::cout << board.getBoardStatus() << std::endl;
                }*/
            }
        }
        // board.turnBackFigure();
    }
}

void DragFigures(const Vector2& mousePos, Board& board) {
    if (!board.isStoneDragging) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isValidMoveOnBoard(mousePos.x, mousePos.y)) {
            startDragFigures(board, mousePos);
        }
    } else {
        updateDragFigures(board, mousePos);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            endDragFigures(board);
        } if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            // board.turnBackFigure();
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

    while(!WindowShouldClose()){
        mousePosition = GetMousePosition();
        BeginDrawing();

        mainBoard.drawBoard();
        mainBoard.drawBowls();

        DragFigures(mousePosition, mainBoard);

        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
