#include "nebula.h"
#include <iostream>

Nebula::Nebula()
{
};

Nebula::Nebula(const int width, const int height, const int positionX, const int positionY, int velocity)
:m_velocity(velocity)
{
    m_rec.x = 0;
    m_rec.y = 0;
    m_rec.width = width / m_spriteCounts;
    m_rec.height = height / m_spriteCounts;

    m_pos.x = positionX,
    m_pos.y = positionY - m_rec.height;
};

Nebula::~Nebula()
{
}

float Nebula::GetPosX()
{
    return m_pos.x;
}

bool Nebula::CheckCollision(Rectangle other)
{
    const int padding{20};
    const Rectangle rec {
        m_pos.x + padding,
        m_pos.y + padding,
        m_rec.width - 2 * padding,
        m_rec.height - 2 * padding
    };

    return CheckCollisionRecs(rec, other);
}

void Nebula::Draw(Texture2D texture)
{
    DrawTextureRec(texture, m_rec, m_pos, WHITE);
}

void Nebula::PreDrawUpdate(const float deltaTime)
{
    UpdatePosition(deltaTime);
    UpdateSprite(deltaTime);
}

// private methods
void Nebula::UpdatePosition(const float deltaTime)
{
    m_pos.x += (m_velocity * deltaTime);
}

void Nebula::UpdateSprite(float deltaTime)
{
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
