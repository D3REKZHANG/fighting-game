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
  tx["adventurer_ss"] = LoadTexture("assets/adventurer_sprite.png");
  tx["celsius_ss"] = LoadTexture("assets/celsius_thrust.png");
  tx["cel_hurt"] = LoadTexture("assets/celsius_hurt.png");
  tx["naruto"] = LoadTexture("assets/naruto.png");
  ss["adventurer"] = new Spritesheet(tx["adventurer_ss"], {50, 37}, 3);
  ss["celsius"] = new Spritesheet(tx["celsius_ss"], {500, 250});
  ss["celsius_hurt"] = new Spritesheet(tx["cel_hurt"], {500, 250});
  ss["naruto"] = new Spritesheet(tx["naruto"], {100, 84}, 1.65);
}

AssetManager::~AssetManager() {
  for(auto s : ss){
    delete s.second;
  }
}

