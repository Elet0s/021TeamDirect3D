#pragma once
class Projectile :public GameEngineActor
{
public:
	Projectile();
	~Projectile();

	Projectile(const Projectile& _Other) = delete;
	Projectile(Projectile&& _Other) noexcept = delete;
	Projectile& operator=(const Projectile& _Other) = delete;
	Projectile& operator=(Projectile&& _Other) noexcept = delete;

	CollisionReturn ProjectileToPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);
	void ProjectileSet(float _atk );
public:
	bool posSet_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void Shoothing(float _deltaTime);
	void TimeOff(float _deltaTime);
	void LevelEndEvent() override;
private:
	GameEngineTextureRenderer* projectileRen_;
	GameEngineCollision* projectileCol_;
	float timer_;
	float projectileatk_;
	float px_;
	float py_;
	float mpx_;
	float mpy_;
	float4 range_;
	float4 resultVector_;
	bool shoothing_;
};