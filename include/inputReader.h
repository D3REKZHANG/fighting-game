#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <deque>

class Game;
class Player;

enum Button { NONE, LIGHT, MEDIUM, HEAVY };

struct Input {
  int motion;
  Button button;
  double time;
  
  bool operator!=(Input right) {
    return motion != right.motion || button != right.button;
  }
};

enum ControllerType { KEYBOARD, CONTROLLER };

struct ControlSet {
  ControllerType type;
  int controller_id;
  int left, right, up, down;
  int l, m, h, s;
};

class InputReader {
  private:
    Game* game;
    Player* player;
    ControlSet controls;
    bool isDown(int key);
  public:
    std::deque<Input> inputQueue;

    InputReader(Game* game, Player* player, ControlSet keyMap);
    Input read();
    void drawQueue();
};

#endif
