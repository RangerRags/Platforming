#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"


#define MAX_LEVELS 3

int main(void) {
    InitWindow(800, 800, "Platform Game");
    int x = 200, y = 400;
    int ground = 765;
    bool onGround = false;
    int currentLevel = 0;
    int yV = 0;
    SetTargetFPS(60);
    int radius = 20;
    int teleportCooldown = 0;

    Vector2 leftRect = {-100, -100};
    Vector2 rightRect = {-100, -100};
    int levels[MAX_LEVELS][10][10] = {
        // Level 0
        {
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,0,1,1},
            {0,0,0,0,0,0,0,1,1,1},
            {0,0,0,0,0,0,1,1,1,1},
            {0,0,0,0,0,1,1,1,1,1},
            {0,0,0,0,1,1,1,1,1,1},
        },
        // Level 1
        {
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,1,0,0,0,0},
            {0,0,0,1,2,1,2,1,0,0},
        },
        //Level 2
        {
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,1,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0},
            {0,0,0,1,0,0,0,0,0,0},
        },
    };

    while (!WindowShouldClose()) {
        onGround = false;
        ground = 765;

        int (*activeMaze)[10] = levels[currentLevel];

        // --- Input ---
        if (IsKeyDown(KEY_D)) x += 10;
        if (IsKeyDown(KEY_A)) x -= 10;

        //portals
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            leftRect = GetMousePosition();
        }
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            rightRect = GetMousePosition();
        }

        if (teleportCooldown > 0) {
            teleportCooldown--;
        }

        // --- Collision ---
        Rectangle left  = {leftRect.x,  leftRect.y,  20, 100};
        Rectangle right = {rightRect.x, rightRect.y, 20, 100};

        if (teleportCooldown == 0) {
            if (CheckCollisionCircleRec((Vector2){x, y}, radius, left)) {
                x = rightRect.x + (x < leftRect.x ? -30 : 30);
                y = rightRect.y + 50;
                teleportCooldown = 30;
            } else if (CheckCollisionCircleRec((Vector2){x, y}, radius, right)) {
                x = leftRect.x + (x < rightRect.x ? -30 : 30);
                y = leftRect.y + 50;
                teleportCooldown = 30;
            }
        }
        // --- Gravity ---
        if (!onGround) yV += 1;
        y += yV;

        // --- Platform collision ---
        for (int row = 0; row < 10; row++) {
            for (int col = 0; col < 10; col++) {
                int wallX = col * 80;
                int wallY = row * 80;

                if (activeMaze[row][col] == 1) {
                    if (x + 20 > wallX && x - 20 < wallX + 80 &&
                        y + 20 > wallY && y - 20 < wallY + 80) {

                        int overlapLeft   = (x + 20) - wallX;
                        int overlapRight  = (wallX + 80) - (x - 20);
                        int overlapTop    = (y + 20) - wallY;
                        int overlapBottom = (wallY + 80) - (y - 20);

                        int minOverlap = overlapLeft;
                        if (overlapRight  < minOverlap) minOverlap = overlapRight;
                        if (overlapTop    < minOverlap) minOverlap = overlapTop;
                        if (overlapBottom < minOverlap) minOverlap = overlapBottom;

                        if (minOverlap == overlapLeft)       x = wallX - 20;
                        else if (minOverlap == overlapRight) x = wallX + 80 + 20;
                        else if (minOverlap == overlapTop) { y = wallY - 20; yV = 0; onGround = true; }
                        else                               { y = wallY + 80 + 20; yV = 0; }
                    }
                }

                if (activeMaze[row][col] == 2) {
                    if (x + 20 > wallX && x - 20 < wallX + 80 &&
                        y + 20 > wallY && y - 20 < wallY + 80) {
                        x = 21;
                        y = 400;
                    }
                }
            }
        }

        // --- Floor ---
        if (y >= ground) {
            y = ground - 1;
            yV = 0;
            onGround = true;
        }

        // --- Boundaries + level transition ---
        if (x >= 780) {
            if (currentLevel < MAX_LEVELS - 1) {
                currentLevel++;
                x = 21;
                y = 400;
                yV = 0;
            } else {
                x = 779; // clamp at last level
            }
        }
        if (x <= 20) x = 21;

        // --- Jump ---
        if (IsKeyPressed(KEY_W) && onGround) {
            yV = -15;
        }

        // --- Draw ---
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(x, y, 20, BLACK);
        DrawRectangle(leftRect.x,  leftRect.y,  20, 100, BLUE);
        DrawRectangle(rightRect.x, rightRect.y, 20, 100, RED);
        DrawText(TextFormat("Level: %d  x:%d y:%d", currentLevel + 1, x, y), 10, 10, 20, GREEN);

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (activeMaze[i][j] == 1) {
                    DrawRectangle(j*80, i*80, 80, 80, BLACK);
                }
                if (activeMaze[i][j] == 2) {
                    int tx = j*80 + 40;
                    int ty = i*80 + 40;
                    DrawTriangle(
                        (Vector2){tx,      ty - 20},
                        (Vector2){tx - 20, ty + 40},
                        (Vector2){tx + 20, ty + 40},
                        BLACK
                    );
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}