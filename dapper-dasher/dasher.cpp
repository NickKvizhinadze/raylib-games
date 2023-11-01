#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0;

        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
            data.frame = 0;
    }
    return data;
}

int main()
{
    // window dimension
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;
    // initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    // acceleration due the gravity (pixels/frame)/ frame
    const int gravity{1'000};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // anim data for nebula
    int sizeOfNebulae{10};
    AnimData nebulae[sizeOfNebulae]{};
    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.x = windowDimensions[0] + (i * 300);
        nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].runningTime = 0;
    }

    float finishLine{nebulae[sizeOfNebulae - 1].pos.x};
    // nebula X velocity (pixels/second)
    int nebVel{-200};

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    int velocity{0};

    // is the rectangle in the air?
    bool isInAir{false};
    // jump velocity (pixels/seconds)
    const int jumpVel{-600};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{0};

    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float midGroundX{0};

    Texture2D foreground = LoadTexture("textures/foreground.png");
    float foregroundX{0};

    bool collision{};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time (time from last frame)
        float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // scroll background
        bgX -= 20 * dT;

        if (bgX <= -background.width * 2)
        {
            bgX = 0.0;
        }

        // scroll midground
        midGroundX -= 40 * dT;

        if (midGroundX <= -midground.width * 2)
        {
            midGroundX = 0.0;
        }

        // scroll foreground
        foregroundX -= 60 * dT;

        if (foregroundX <= -foreground.width * 2)
        {
            foregroundX = 0.0;
        }

        // draw the background
        Vector2 bg1Pos = {bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos = {bgX + background.width * 2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        Vector2 midground1Pos = {midGroundX, 0.0};
        DrawTextureEx(midground, midground1Pos, 0.0, 2.0, WHITE);
        Vector2 midground2Pos = {midGroundX + midground.width * 2, 0.0};
        DrawTextureEx(midground, midground2Pos, 0.0, 2.0, WHITE);

        Vector2 foreground1Pos = {foregroundX, 0.0};
        DrawTextureEx(foreground, foreground1Pos, 0.0, 2.0, WHITE);
        Vector2 foreground2Pos = {foregroundX + foreground.width * 2, 0.0};
        DrawTextureEx(foreground, foreground2Pos, 0.0, 2.0, WHITE);

        // perform ground check
        if (isOnGround(scarfyData, windowDimensions[1]))
        {
            // rectangle is on the ground
            velocity = 0;
            if (isInAir)
                isInAir = false;
        }
        else
        {
            // rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // update nebula position
            nebulae[i].pos.x += nebVel * dT;
        }

        finishLine += (nebVel + 20) * dT;

        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // update running time
        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        for (AnimData nebula : nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2 * pad,
                nebula.rec.height - 2 * pad};

            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height,
            };

            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }
        if (collision)
        {
            DrawText("Game Over!", windowDimensions[0] / 4, windowDimensions[1] / 2, 40, RED);
        }
        else if (scarfyData.pos.x > finishLine)
        {
            DrawText("You win!", windowDimensions[0] / 4, windowDimensions[1] / 2, 40, RED);
        }
        else
        {
            for (int i = 0; i < sizeOfNebulae; i++)
            {
                // draw nebula
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }

            // draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(midground);
    UnloadTexture(foreground);
    UnloadTexture(background);
    UnloadTexture(nebula);
    UnloadTexture(scarfy);
    CloseWindow();
}
