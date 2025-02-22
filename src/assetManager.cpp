#include "assetManager.h"

AssetManager* AssetManager::instance = nullptr;

AssetManager* AssetManager::getInstance() {
  if(instance == nullptr) {
    instance = new AssetManager();
  }
  return AssetManager::instance;
}

AssetManager::AssetManager() {
  tx["motions"] = LoadTexture("assets/motions.png");       
  /* tx["adventurer_ss"] = LoadTexture("assets/adventurer_sprite.png");
  tx["celsius_ss"] = LoadTexture("assets/celsius_thrust.png");
  tx["cel_hurt"] = LoadTexture("assets/celsius_hurt.png");
  tx["naruto"] = LoadTexture("assets/naruto.png");

  ss["adventurer"] = new Spritesheet(tx["adventurer_ss"], {50, 37}, 3);
  ss["celsius"] = new Spritesheet(tx["celsius_ss"], {500, 250});
  ss["celsius_hurt"] = new Spritesheet(tx["cel_hurt"], {500, 250});
  ss["naruto"] = new Spritesheet(tx["naruto"], {100, 84}, 1.65); */

  ss["xun_idle"] = new Spritesheet(LoadTexture("assets/martial-hero-3/Sprite/Idle.png"), {126, 126}, 2);
  ss["xun_run"] = new Spritesheet(LoadTexture("assets/martial-hero-3/Sprite/Run.png"), {126, 126}, 2);
  ss["xun_hurt"] = new Spritesheet(LoadTexture("assets/martial-hero-3/Sprite/Take Hit.png"), {126, 126}, 2);
  ss["xun_death"] = new Spritesheet(LoadTexture("assets/martial-hero-3/Sprite/Death.png"), {126, 126}, 2);
  ss["xun_attack"] = new Spritesheet(LoadTexture("assets/martial-hero-3/Sprite/Attack1.png"), {126, 126}, 2);

  ss["xero_idle"] = new Spritesheet(LoadTexture("assets/martial-hero-1/Sprites/Idle.png"), {200, 200}, 2);
  ss["xero_run"] = new Spritesheet(LoadTexture("assets/martial-hero-1/Sprites/Run.png"), {200, 200}, 2);
  ss["xero_hurt"] = new Spritesheet(LoadTexture("assets/martial-hero-1/Sprites/Take Hit.png"), {200, 200}, 2);
  ss["xero_death"] = new Spritesheet(LoadTexture("assets/martial-hero-1/Sprites/Death.png"), {200, 200}, 2);
  ss["xero_jump"] = new Spritesheet(LoadTexture("assets/martial-hero-1/Sprites/Jump.png"), {200, 200}, 2);
  ss["xero_attack1"] = new Spritesheet(LoadTexture("assets/martial-hero-1/Sprites/Attack1.png"), {200, 200}, 2);
  ss["xero_attack2"] = new Spritesheet(LoadTexture("assets/martial-hero-1/Sprites/Attack2.png"), {200, 200}, 2);
}

AssetManager::~AssetManager() {
  for(auto s : ss){
    delete s.second;
  }
}

