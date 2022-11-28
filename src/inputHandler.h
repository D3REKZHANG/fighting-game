#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <string>
#include <deque>
#include <unordered_map>
#include "raylib.h"

class Game;
class Player;

struct MotionInput {
  int input;
  double time;
};

class InputHandler {
  Game* game;
  Player* player;
  std::unordered_map<std::string, int> keyMap;
  std::deque<MotionInput> inputQueue;
  public:
    InputHandler(Game* game, Player* player, std::unordered_map<std::string, int> keyMap);
    void readInput();
    void handle();
    void drawQueue();
};

#endif
