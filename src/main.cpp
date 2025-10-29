#include "board.h"


int main(){
    InitWindow(BOARD_WIDTH,
        BOARD_HEIGHT + 2 * LETTERS_CELL_HEIGHT + ADD_SCREEN_HEIGHT,
        "GoCPP");
    SetTargetFPS(FPS);

    Board mainBoard;

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        mainBoard.drawBoard();
        mainBoard.drawTiles();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
