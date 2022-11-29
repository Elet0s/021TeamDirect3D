#pragma once
#include "Player.h"
#include "Monster.h"
#include "BlackEyes.h"
#include "Brown.h"
#include "Green.h"
#include "NormalGoblin.h"
#include "RedFlyingEyes.h"
#include "FlyingEyes.h"

enum class ObjectOrder
{
	TileMap,
	Player,
	Monster,
	Mouse,
	Camera,
	MapObject,
	Sector,
	UI = 1000
};

enum class MonterOrder
{
	BlackEyes,
	Brown,
	FlyingEyes,
	Green,
	NormalGoblin,
	RedFlyingEyes
};

enum class SoulCard
{
	Cleaver,
	MagicWand,
	Shuriken,
	Spear,
	Bow,
	ThunderStaff,
	Pike,
	Kunai,
	
	WindsBlade,
	SilphsBlade, //(진화)
	
	Swordrang,
	
	MagicWisp,
	VoidWisp,//(진화)
	
	DeathAura,

	ShamanStaff,
	ArcanistStaff,//(진화)
	
	Katana,
	ArtificersKatana,//(진화)

	Crossbow,
	FireRing,
	
	//이밑으로 공격 패시브
	SharpeningStone,
	Cardio,
	ForgedIron,
	BloodPressure,
	Accuracy,
	lens,
	SharpEdge,
	Range,
	TenseString,
	Momentum,
	Muscle,
	Compromise,
	Practice,
	DamascusSteel,
	WeakPoint,
	Aiming,
	Area,
	Quick,
	Clumsy,
	TradeOff,
	Analysis,
	Celerity,
	GodsWrath,
	Penetration,
	Patience,
	SingleHanded,
	LightHand,
	Hypersonic,
	StoneHanded,
	Overworked,
	Average,
	Overloaded,
	MultiHanded,
	Recursion,
	Accumulation,
	Heavy,
	AbsoluteFocus,
	Perfection,
	Fractal,
	ThornFirework,
	Lunatic,
	//이밑으로 방어 패시브
	Healthy,
	Durability,
	StoneSkin,
	IronWill,
	HealingFactor,
	BlackBlood,
	LightArmor,
	IronSkin,
	SlipperySkin,
	Impenetrable,
	Tower,
	SteelSkin,
	Thorn,
	Castle,
	Turtle,
	Flesh,
	Martyr,
	//이밑으로 보조 패시브
	LowPressure,
	Agility,
	Void,
	Student,
	Dash,
	IceSpirit,
	DashCooldown,
	FireSpirit,
	Evasion,
	Oil,
	Bookworm,
	VoidSpirit
};
enum class CardValue
{
	Weapon,
	AtkBuff,
	DefBuff,
	SubBuff
};
enum class Artifact
{
	HandOfTheCheater,
	ChampionsBracer,
	SacredSword,
	ChickenSstatue,
	MartyrsCloak,
	WindsLing,
	CarvedDice,
	GlassSword,
	CursedBelt,
	SwordOfMidas,
	ShopKeepersPlate,
	GilgameshsRing,
	HolyCross,
	BhikkhuPearl,
	SaintsShinbone,
	CollectionBook,
	PorkStatue,
	HermessHood,
	BeefStatue,
	TrainingWeight,
	TrollBlood,
	GilgameshsCrown,
	SagesLeaf,
	OldCoin,
	AdventurersLicense,
	VoidStatue,
	LightningBoots,
	GilgameshsSeal,
	PhoenixTotem,
	AdamantiteRod,
	MythrilCompass,
	FightersRuby,
	CowardsSaphir,
	CorruptedCore
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

