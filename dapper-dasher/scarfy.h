#pragma once
#include "raylib.h"

class Scarfy
{
private:
    const char *m_texturePath = "./textures/scarfy.png";
    int m_spriteCounts{6};
    int m_currentSprite{0};

    float m_windowWidth;
    float m_windowHeight;

    // pixels per second
    int m_velocity{-600};
    float updateTime{1.0 / 12.0};
    float runningTime{0};
    const int m_jumpVelocity{-600};

    bool m_isInTheAir = false;

    Texture2D m_texture;
    Rectangle m_rec;
    Vector2 m_pos;

public:
    Scarfy(const int windowWidth, const int windowHeight);
    ~Scarfy();

    void Draw();
    void Jump(const float deltaTime);
    void UpdateVelocity(const float deltaTime, const int gravity);
    void PreDrawUpdate(float deltaTime);
    Rectangle GetRectangle();

private:
    void UpdatePosition(float deltaTime);
    void UpdateSprite(float deltaTime);
};
