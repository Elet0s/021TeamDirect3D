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
	SilphsBlade, //(��ȭ)

	Swordrang,

	MagicWisp,
	VoidWisp,//(��ȭ)

	DeathAura,

	ShamanStaff,
	ArcanistStaff,//(��ȭ)

	Katana,
	ArtificersKatana,//(��ȭ)

	Crossbow,
	FireRing,

	//�̹����� ���� �нú�
	SharpeningStone,
	Cardio,
	SharpEdge,
	Range,
	TenseString, // �̿ϼ�
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

	Overworked,   // �̿ϼ�
	Average,	  // �̿ϼ� 
	Overloaded,	  // �̿ϼ�
	MultiHanded,
	Recursion,
	Accumulation,
	Heavy,
	AbsoluteFocus,
	Perfection,
	Fractal,
	ThornFirework,
	Lunatic,

	//�̹����� ��� �нú�
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

	Thorn,  // ����
	Castle,
	Turtle,
	Flesh,
	Martyr,

	//�̹����� ���� �нú�
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
	AtkMutiple,								    // ���ع��   100%,
	AttackSpeed,								// ���� �ӵ�  100.0%
	AddProjectile,								// �߰� ����ü  0
	ThroughProjectile,                          // ����ü ���� (������� �浹�ϴ°�) 0 
	ProjectileSize,                             // ����ü ũ�� 100%
	ProjectileDuration,							// ����ü ���ӽð� 100%
	ProjectileSpeed,                            // ����ü �ӵ� (���󰡴� �̵��ӵ�) 100%
	RangeSize,                                  // ���� ũ��(����, �������� ũ��� ����) 100%
	KnockBack,									// �˹�(���Ͱ� �з����� �Ÿ�) 100%
	CriticalChance,                             // ġ��ŸȮ�� 10%
	CriticalDamege,                             // ġ��Ÿ ������ (ġ��Ÿ�� ������ ����)  150%
	GoldMultiple,                               // �����(��带 ���� ���� ȹ�� ����) 100%
	ExpMultiple,								// ����ġ���(����ġ�� ���� ���� ȹ�� ����) 100%
	Def,                                        // ���� 0 
	DashFullCharge,                             // �뽬�ִ����� (�뽬�� �����Ǵ� �ִ� ����) 0
	DashReChargeTime,                           // �뽬 ������ �ð�(�뽬�� ������ �Ǵµ� �ɸ��� �ð�) 3.0f
	DashReUseTime,                              // �뽬 ���� �ð�(�뽬�� ����ϰ� ���� �ٽ� ����� �� ���� �ɸ��� �ð�) 0.3f
	DashReChargeCount,                          // ������ �Ǵ� �뽬 �� (������ �ð��� ������ �뽬�� �����Ǵ� ��) 1
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