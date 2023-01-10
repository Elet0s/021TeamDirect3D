#pragma once

enum class ObjectOrder
{
	Skill,
	Mouse,
	Camera,
	TreeObject,
	MapObject,
	Sector,
	Item,
	SkillSerchBoad,
	Range,
	Projectile,
	TileMap,
	Road,
	Monster,
	Player,
	UI = 1000
};

enum class MonsterOrder
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
	None,
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
	SharpEdge,
	Range,
	TenseString, // 미완성
	Momentum,
	Muscle,
	Compromise,
	Practice,
	DamascusSteel,
	Aiming,
	Area,
	Quick,
	Clumsy,
	TradeOff,
	Celerity,
	GodsWrath,
	Penetration,
	Patience,
	SingleHanded,
	LightHand,
	Hypersonic,
	StoneHanded,

	Overworked,   // 미완성
	Average,	  // 미완성 
	Overloaded,	  // 미완성
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

	Thorn,  // 보류
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
	DashCooldown,
	Oil,
	Bookworm,
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


enum class PlayerStatue
{
	AtkMutiple,								    // 피해배수   100%,
	AttackSpeed,								// 공격 속도  100.0%
	AddProjectile,								// 추가 투사체  0
	ThroughProjectile,                          // 투사체 관통 (몇번까지 충돌하는가) 0 
	ProjectileSize,                             // 투사체 크기 100%
	ProjectileDuration,							// 투사체 지속시간 100%
	ProjectileSpeed,                            // 투사체 속도 (날라가는 이동속도) 100%
	RangeSize,                                  // 범위 크기(오라, 마법진의 크기와 관련) 100%
	KnockBack,									// 넉백(몬스터가 밀려나는 거리) 100%
	CriticalChance,                             // 치명타확률 10%
	CriticalDamege,                             // 치명타 데미지 (치명타시 데미지 비율)  150%
	GoldMultiple,                               // 골드배수(골드를 얻을 때의 획득 비율) 100%
	ExpMultiple,								// 경험치배수(경험치를 얻을 때의 획득 비율) 100%
	Def,                                        // 방어력 0 
	DashFullCharge,                             // 대쉬최대충전 (대쉬가 충전되는 최대 개수) 0
	DashReChargeTime,                           // 대쉬 재충전 시간(대쉬가 재충전 되는데 걸리는 시간) 3.0f
	DashReUseTime,                              // 대쉬 재사용 시간(대쉬를 사용하고 나서 다시 사용할 때 까지 걸리는 시간) 0.3f
	DashReChargeCount,                          // 재충전 되는 대쉬 수 (재충전 시간이 지나고 대쉬가 충전되는 수) 1
};

enum class Rank
{
	Spotted,
	Normal,
	UnCommon,
	Rare,
	Epic,
};

enum class ItemObjectOrder
{
	None,
	GreenExp,
	YellowExp,
	RedExp,
	Meet,
	Voidbead,
	Gold,
	Box
};

enum class StageType
{
	ComBat,
	Elite,
	Chest,
	Event,
	Boss,
	Empty,
	Max
};

enum class ComBatType
{
	TimeAttack,
	Kill,
	EilteKill,
	BossKill,
	Max
};