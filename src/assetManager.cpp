#include "assetManager.h"

AssetManager* AssetManager::instance = nullptr;

AssetManager* AssetManager::getInstance() {
  if(instance == nullptr) {
    instance = new AssetManager();
  }
  return AssetManager::instance;
}

AssetManager::AssetManager(){}

AssetManager::~AssetManager() {
  for(auto s : ss){
    delete s.second;
  }
}

