#pragma once
class CleaverProjectile
{
public:
	CleaverProjectile();
	~CleaverProjectile();


	CleaverProjectile(const CleaverProjectile& _Other) = delete;
	CleaverProjectile(CleaverProjectile&& _Other) noexcept = delete;
	CleaverProjectile& operator=(const CleaverProjectile& _Other) = delete;
	CleaverProjectile& operator=(CleaverProjectile&& _Other) noexcept = delete;
protected:

private:

};