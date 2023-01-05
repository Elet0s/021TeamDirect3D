#include"PreCompile.h"
#include"GameItemObjectManager.h"

GameItemObjectManager::GameItemObjectManager()
{

}
GameItemObjectManager::~GameItemObjectManager()
{

}

void GameItemObjectManager::Start()
{
	expContainer_.reserve(300);
	meetContainer_.reserve(10);
	voidbeadContainer_.reserve(10);
	goldContainer_.reserve(10);
}