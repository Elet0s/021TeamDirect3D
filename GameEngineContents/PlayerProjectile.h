#pragma once
class PlayerProjectile
{
public:
	PlayerProjectile();
	~PlayerProjectile();


	PlayerProjectile(const PlayerProjectile& _Other) = delete;
	PlayerProjectile(PlayerProjectile&& _Other) noexcept = delete;
	PlayerProjectile& operator=(const PlayerProjectile& _Other) = delete;
	PlayerProjectile& operator=(PlayerProjectile&& _Other) noexcept = delete;
protected:

private:

};