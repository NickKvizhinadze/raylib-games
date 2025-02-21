#pragma once
#include "raylib.h"

class Nebula
{
private:
    int m_spriteCounts{8};
    int m_currentSprite{0};

    // pixels per second
    int m_velocity{0};
    float updateTime{1.0 / 12.0};
    float runningTime{0};

    Rectangle m_rec;
    Vector2 m_pos;

public:
    Nebula();
    Nebula(const int width, const int height, const int windowWidth, const int windowHeight, int velocity);
    ~Nebula();

    float GetPosX();
    void Draw(Texture2D texture);
    void PreDrawUpdate(float deltaTime);
    bool CheckCollision(Rectangle other);
private:
    void UpdatePosition(float deltaTime);
    void UpdateSprite(float deltaTime);
};
