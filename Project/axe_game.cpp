#include "raylib.h"
#include <iostream>

int main()
{
  int width{800};
  int height{600};
  InitWindow(width, height, "Axe Game");

  int circleX{25};
  int circleY{275};
  int circleRadius{25};

  // circle coordinats
  int lCircleX;
  int rCircleX;
  int tCircleY;
  int bCircleY;

  int axeX{400};
  int axeY{300};
  int axeSize{50};

  // axes
  int lAxeX;
  int rAxeX;
  int tAxeY;
  int bAxeY;

  int axeDirection{1};

  bool collisionWithAxe{false};

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    if (collisionWithAxe)
    {
      if (IsKeyPressed(KEY_R))
      {
        axeX = 200;
        axeY = 0;
        collisionWithAxe = false;
      }
      DrawText("Game Over", 400 - 20, 300 - 20, 20, RED);
    }
    else
    {
      // circle coordinats
      int lCircleX = circleX - circleRadius;
      int rCircleX = circleX + circleRadius;
      int tCircleY = circleY - circleRadius;
      int bCircleY = circleY + circleRadius;

      // axe coordinats
      int lAxeX = axeX;
      int rAxeX = axeX + axeSize;
      int tAxeY = axeY;
      int bAxeY = axeY + axeSize;

      if (bAxeY >= tCircleY &&
          tAxeY <= bCircleY &&
          lAxeX <= rCircleX &&
          rAxeX >= lCircleX)
      {
        collisionWithAxe = true;
      }

      DrawCircle(circleX, circleY, circleRadius, BLUE);
      DrawRectangle(axeX, axeY, axeSize, axeSize, RED);

      if (bAxeY > height || tAxeY < 0)
      {
        axeDirection = -axeDirection;
      }

      axeY += (axeDirection * 10);

      if (IsKeyDown(KEY_D) && rCircleX < width)
      {
        circleX += 10;
      }

      if (IsKeyDown(KEY_A) && lCircleX > 0)
      {
        circleX -= 10;
      }

      if (IsKeyDown(KEY_W) && tCircleY > 0)
      {
        circleY -= 10;
      }

      if (IsKeyDown(KEY_S) && bCircleY < height)
      {
        circleY += 10;
      }
    }
    EndDrawing();
  }
}
