#pragma once
#include "raylib.h"

class Background
{
    const char *m_backgroundTexturePath{"./textures/far-buildings.png"};
    const char *m_midgroundTexturePath{"./textures/back-buildings.png"};
    const char *m_foregroundTexturePath{"./textures/foreground.png"};
    Texture2D m_backgroundTexture;
    Texture2D m_midgroundTexture;
    Texture2D m_foregroundTexture;

    float m_scale{5.0};
    float m_backgroundPosX{};
    float m_midgroundPosX{};
    float m_foregroundPosX{};
    Vector2 m_position1;
    Vector2 m_position2;
    Vector2 m_midGroundPosition1;
    Vector2 m_midGroundPosition2;
    Vector2 m_foregroundPosition1;
    Vector2 m_foregroundPosition2;

public:
    Background();
    ~Background();
    void Draw(float deltaTime);

private:
    void DrawBackground(float deltaTime, Texture2D *texture, float *backgroundX, int velocity);
};
