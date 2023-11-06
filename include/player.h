#ifndef PLAYER_H
#define PLAYER_H

#include "inputReader.h"
#include "raylib.h"
#include "animation.h"
#include <string>
#include <unordered_map>

class Game;
class Animation;
class Spritesheet;
class MoveState;
class State;

struct CharacterStats {
  float walk_speed;
  int max_health;
};

class Player {
  public:
    Vector2 pos = {0,0};
    Vector2 vel = {0,0};
    Vector2 accel = {0,0};
    Vector2 size;
    Game* game;
    bool inverse = false;
    CharacterStats stats = {5, 20};
    std::unordered_map<std::string, Animation*> anim;
    std::unordered_map<std::string, MoveState*> move;
    Animation* currentAnimation = nullptr;
    State* currentState = nullptr;
    InputReader* inputReader;
    
    Player(Game* game, InputReader* inputReader);
    ~Player();
    void update();
    void draw();
    void fireball();
    void thrust();
    void setAnimation(std::string anim_key);
    void handleStateChange(State* state);

    class Box {
    public:
      Rectangle relativeBounds;

      Box();
      Box(Rectangle rec);
      Box(float x, float y, float w, float h);

      Rectangle getTranslated(Player* p);
    };
};

class Celsius : public Player { 
public:
  Celsius(Game* game, InputReader* inputReader);
};

class Naruto : public Player { 
public:
  Naruto(Game* game, InputReader* inputReader);
};

#endif
