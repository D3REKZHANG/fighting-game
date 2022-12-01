#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include <string>
#include <unordered_map>

class Player;
class InputHandler;
struct Spritesheet;

class Game{
  const int screenWidth;
  const int screenHeight;
  int player1Score;
  int player2Score;
  Player* p1;
  Player* p2;
  InputHandler* h1;
  InputHandler* h2;
  Vector2 playerSize = {50, 250};
  int groundPosition;

  public:
    std::unordered_map<std::string, Texture2D> tx;
    std::unordered_map<std::string, Spritesheet> ss;

    Game(int width, int height);
    ~Game();
    void loadAssets();
    void draw();
    void handleInput();
    void update();
    void reset();
    int getWidth();
    int getHeight();
    int getGroundPos();
};

#endif
