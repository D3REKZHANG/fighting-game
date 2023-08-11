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

class Player {
  public:
    Color colour;
    Vector2 pos = {0,0};
    Vector2 vel = {0,0};
    Vector2 accel = {0,0};
    Vector2 size;
    Game* game;
    bool inverse;
    float speed = 5;
    std::unordered_map<std::string, Animation*> anim;
    std::unordered_map<std::string, MoveState*> move;
    Animation* currentAnimation = nullptr;
    State* currentState = nullptr;
    InputReader* inputReader;
    
    Player(Color c, Vector2 size, Game* game, InputReader* inputReader, bool inverse);
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

#endif
