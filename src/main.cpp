#include "raylib.h"
#include "player.h"
#include "game.h"

void update();
void draw();

Camera camera = { 0 };
Game* game;

const int screenWidth = 800;
const int screenHeight = 450;

int main()
{
  
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

    game->draw();

    DrawFPS(10, screenHeight-35);

  EndDrawing();
}
