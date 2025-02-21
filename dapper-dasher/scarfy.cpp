#include "scarfy.h"
// #include <iostream>

Scarfy::Scarfy(const int windowWidth, const int windowHeight)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight)
{
    m_texture = LoadTexture(m_texturePath);

    m_rec.width = m_texture.width / m_spriteCounts;
    m_rec.height = m_texture.height;
    m_rec.x = 0;
    m_rec.y = 0;

    m_pos.x = windowWidth / 2 - m_rec.width / 2;
    m_pos.y = windowHeight - m_rec.height;
};

Scarfy::~Scarfy()
{
    UnloadTexture(m_texture);
}

void Scarfy::Draw()
{
    DrawTextureRec(m_texture, m_rec, m_pos, WHITE);
}

void Scarfy::Jump(const float deltaTime)
{
    if (!m_isInTheAir)
    {
        m_velocity += m_jumpVelocity;
    }
}

void Scarfy::UpdateVelocity(const float deltaTime, const int gravity)
{
    if (m_pos.y >= m_windowHeight - m_rec.height)
    {
        m_velocity = 0;
        m_isInTheAir = false;
    }
    else
    {
        m_velocity += (gravity * deltaTime);
        m_isInTheAir = true;
    }
}

void Scarfy::PreDrawUpdate(float deltaTime)
{
    UpdatePosition(deltaTime);
    UpdateSprite(deltaTime);
}

Rectangle Scarfy::GetRectangle()
{
    return {
        m_pos.x,
        m_pos.y,
        m_rec.width,
        m_rec.height};
}

// private methods
void Scarfy::UpdatePosition(float deltaTime)
{
    m_pos.y += m_velocity * deltaTime;
}

void Scarfy::UpdateSprite(float deltaTime)
{
    if (m_isInTheAir)
    {
        return;
    }

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        m_rec.x = m_currentSprite * m_rec.width;
        m_currentSprite++;
        if (m_currentSprite > m_spriteCounts - 1)
        {
            m_currentSprite = 0;
        }

        runningTime = 0;
    }
}
