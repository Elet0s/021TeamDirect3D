#pragma once
#include "Player.h"
#include "Monster.h"

enum class ObjectOrder
{
	TileMap,
	Player,
	Monster,
	UI = 1000
};


class GlobalContentsValue
{

public:
	class Actors
	{
	public:
		static Monster* testMonster_;

	private:
		Actors() {}
		~Actors() {}
	};

private:
	GlobalContentsValue() {}
	~GlobalContentsValue() {}
};

