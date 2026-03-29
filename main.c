#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
int main(void) {
    InitWindow(800, 800, "Platform Game");
    int x=400, y=400;
    int yV=0;
    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_D)) {
            x+=10;
        }
        if (IsKeyDown(KEY_A)) {
            x-=10;
        }
        if (IsKeyPressed(KEY_W)) {
            if (y>740) {
             yV=-15;
            }

        }
        if (y < 765) {
            yV += 1;
        }
        if (y>=765) {
            y=764;
        }

        y+=yV;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(x,y,20,BLACK);
        EndDrawing();
    }


    return 0;
}