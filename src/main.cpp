#include "board.h"

int main(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT + ADD_SCREEN_HEIGHT, "GoCPP");
    SetTargetFPS(FPS);

    Board mainBoard;

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        mainBoard.drawBoard();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
