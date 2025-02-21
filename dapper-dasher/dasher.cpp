#include <iostream>
#include "raylib.h"

#include "scarfy.h"
#include "nebula.h"
#include "backgroud.h"


int main()
{
    const int gravity{1'200};
    const int windowWidth{1280};
    const int windowHeight{720};

    InitWindow(windowWidth, windowHeight, "Dasher dapper");

    Background background{};
    Scarfy scarfyObj{windowWidth, windowHeight};

    const int sizeOfNebulae = 6;
    int nebulaVelocity{-600};
    Texture2D nebulaTexture = LoadTexture("./textures/12_nebula_spritesheet.png");
    Nebula nebulae[sizeOfNebulae];


    for (int i = 0; i < sizeOfNebulae; i++)
    {
        int randomOffset = rand() % (700 - 900 + 1) + 700;
        nebulae[i] = {nebulaTexture.width, nebulaTexture.height, windowWidth + i * randomOffset, windowHeight, nebulaVelocity};
    }

    float finishLinePosX = nebulae[sizeOfNebulae - 1].GetPosX() + 500;
    bool isGameOver{false};
    bool isGameWin{false};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        const float dT{GetFrameTime()};

        background.Draw(dT);

        if (isGameOver)
        {
            DrawText("Game Over!", windowWidth / 2 - 20, windowHeight / 2 - 20, 40, RED);
        }
        else if (isGameWin)
        {
            DrawText("Victory", windowWidth / 2 - 20, windowHeight / 2 - 20, 40, GREEN);
        }
        else
        {

            scarfyObj.UpdateVelocity(dT, gravity);

            if (IsKeyPressed(KEY_SPACE))
            {
                scarfyObj.Jump(dT);
            }
            scarfyObj.PreDrawUpdate(dT);
            Rectangle scarfyRec = scarfyObj.GetRectangle();

            for (unsigned int i = 0; i < sizeOfNebulae; i++)
            {
                bool collistion = nebulae[i].CheckCollision(scarfyRec);
                if (collistion)
                {
                    isGameOver = true;
                    break;
                }
                nebulae[i].PreDrawUpdate(dT);
                nebulae[i].Draw(nebulaTexture);
            }

            finishLinePosX += dT * nebulaVelocity;

            scarfyObj.Draw();

            if (scarfyRec.x >= finishLinePosX)
            {
                isGameWin = true;
            }
        }

        ClearBackground(WHITE);

        EndDrawing();
    }

    background.~Background();
    scarfyObj.~Scarfy();
    UnloadTexture(nebulaTexture);

    CloseWindow();
}
