#include <stdio.h>
#include "include/raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    

    InitWindow(screenWidth, screenHeight, "Game");

    Texture2D backGroundImage = LoadTexture("bg.png");
    Texture2D playerImage = LoadTexture("WALK.png");    

    float frameWidth = (float)(playerImage.width / 8);
    int maxFrames = (int)(playerImage.width / (int)frameWidth);

    const int playerStartY = screenHeight - playerImage.height/1.15;
    int playerX = 0;
    int playerY = playerStartY;
    double playerVerticalVelocity = 0;
    double playerVerticalAcceleration = 0;

    float timer = 0.0f;
    int frame = 0;

    bool isRight = true;
    float current_frame_width = frameWidth;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        timer += GetFrameTime();

        if (!isRight && current_frame_width > 0){
            current_frame_width = -1 * frameWidth;
        }
        if (isRight && current_frame_width < 0){
            current_frame_width = frameWidth;
        }

        if (IsKeyDown(KEY_D))
        {
            isRight = true;
            playerX += 3;   
        }
        if (IsKeyDown(KEY_A))
        {
            isRight = false;
            playerX -= 3;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A))
        {
            if (timer >= 0.2f){
                timer = 0.0f;
                frame += 1;
            }
            frame = frame % maxFrames;
        }
        else{
            frame = 0;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            playerVerticalVelocity = -7.5;
            playerVerticalAcceleration = 0.25;
        }
        
        

        playerY += (int)playerVerticalVelocity;
        playerVerticalVelocity += playerVerticalAcceleration;

        if (playerY >= playerStartY){
            playerY = playerStartY;
            playerVerticalVelocity = 0;
            playerVerticalAcceleration = 0;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(backGroundImage, 0, 0, WHITE);

            DrawTextureRec(
                playerImage,
                (Rectangle){frameWidth * frame, 0, current_frame_width, (float)playerImage.height},
                (Vector2){playerX, playerY},
                RAYWHITE);

        EndDrawing();
        
    }

    
    CloseWindow();        // Close window and OpenGL context

    return 0;
}