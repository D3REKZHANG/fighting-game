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
  private:
    Game* game;
    Player* player;
    std::unordered_map<std::string, int> keyMap;
    void readInput();
  public:
    std::deque<MotionInput> inputQueue;

    InputHandler(Game* game, Player* player, std::unordered_map<std::string, int> keyMap);
    void handle();
    void drawQueue();
};

#endif
