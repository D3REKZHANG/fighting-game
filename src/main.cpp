#include "raylib.h"
#include "player.h"
#include "game.h"

void update();
void draw();

Camera camera = { 0 };
Game* game;

int main()
{
  const int screenWidth = 800;
  const int screenHeight = 450;
  
  InitWindow(screenWidth, screenHeight, "Fighting Game");

  SetTargetFPS(80);

  bool slowed = false;

  game = new Game(screenWidth, screenHeight);
  game->reset();

  while (!WindowShouldClose())
  {
    if(IsKeyPressed(KEY_P)) {
      SetTargetFPS(slowed ? 80 : 10);
      slowed = !slowed;
    }

    game->update();
    draw();
  }

  CloseWindow();
  delete game;

  return 0;
}

void draw()
{
  BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Fighting Game", 10, 40, 20, DARKGRAY);

    DrawFPS(10, 10);

    game->draw();
  EndDrawing();
}
