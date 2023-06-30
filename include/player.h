#ifndef PLAYER_H
#define PLAYER_H

#include "inputReader.h"
#include "raylib.h"
#include "animation.h"
#include "move.h"
#include "state.h"
#include <string>
#include <unordered_map>

class Game;
class Animation;
class Spritesheet;

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
    std::unordered_map<std::string, Texture2D> tx;
    std::unordered_map<std::string, Spritesheet*> ss;
    std::unordered_map<std::string, Animation*> anim;
    std::unordered_map<std::string, Move*> move;
    Animation* currentAnimation = nullptr;
    State* state = nullptr;
    InputReader* inputReader;
    
    Player(Color c, Vector2 size, Game* game, InputReader* inputReader, bool inverse);
    ~Player();
    void update();
    void draw();
    void fireball();
    void thrust();
    void setAnimation(std::string anim_key);
};

#endif
