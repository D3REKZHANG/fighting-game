#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "animation.h"
#include <string>
#include <unordered_map>

class Game;
class Animation;
class Spritesheet;

class Player {
  public:
    Color colour;
    Vector2 pos;
    Vector2 vel = {0,0};
    Vector2 accel = {0,0};
    Vector2 size;
    Game* game;
    bool grounded;
    bool inverse;
    float speed = 5;
    std::unordered_map<std::string, Texture2D> tx;
    std::unordered_map<std::string, Spritesheet*> ss;
    std::unordered_map<std::string, Animation*> anim;
    Animation* currentAnimation = nullptr;
    
    Player(Color c, int x, int y, Vector2 size, Game* game, bool inverse);
    ~Player();
    void loadAssets();
    void update();
    void draw();
    void fireball();
    void thrust();
};

#endif
