#include "backgroud.h"

Background::Background()
{
    m_backgroundTexture = LoadTexture(m_backgroundTexturePath);
    m_midgroundTexture = LoadTexture(m_midgroundTexturePath);
    m_foregroundTexture = LoadTexture(m_foregroundTexturePath);
};

Background::~Background()
{
    UnloadTexture(m_backgroundTexture);
    UnloadTexture(m_midgroundTexture);
    UnloadTexture(m_foregroundTexture);
};

void Background::Draw(float deltaTime)
{
    DrawBackground(deltaTime, &m_backgroundTexture, &m_backgroundPosX, 20);
    DrawBackground(deltaTime, &m_midgroundTexture, &m_midgroundPosX, 40);
    DrawBackground(deltaTime, &m_foregroundTexture, &m_foregroundPosX, 20);
}

// Private Methods

void Background::DrawBackground(float deltaTime, Texture2D* texture, float* backgroundX, int velocity)
{
    if (m_backgroundPosX < -(texture->width * m_scale))
    {
        m_backgroundPosX = 0;
    }

    m_backgroundPosX -= 20 * deltaTime;

    Vector2 position1{m_backgroundPosX, 0.0};
    DrawTextureEx(*texture, position1, 0, m_scale, WHITE);

    Vector2 position2{m_backgroundPosX + texture->width * m_scale, 0.0};
    DrawTextureEx(*texture, position2, 0, m_scale, WHITE);
};

// void Background::Drawmidground(float deltaTime) {
//     if (m_midgroundPosX < -(m_backgroundTexture.width * m_scale))
//     {
//         m_backgroundPosX = 0;
//     }

//     m_backgroundPosX -= 20 * deltaTime;

//     Vector2 background1Position{m_backgroundPosX, 0.0};
//     DrawTextureEx(m_backgroundTexture, background1Position, 0, m_scale, WHITE);

//     Vector2 background2Position{m_backgroundPosX + m_backgroundTexture.width * m_scale, 0.0};
//     DrawTextureEx(m_backgroundTexture, background2Position, 0, m_scale, WHITE);

// };
