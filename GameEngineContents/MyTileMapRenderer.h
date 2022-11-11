#pragma once

// Ό³Έν :
class Tile
{
	friend class MyTileMapRenderer;

	int tileIndex_;
	int zValue_;
	std::shared_ptr<GameEngineTexture> tileImage_;
public:
	Tile() : tileIndex_(0), zValue_(0), tileImage_(nullptr)
	{
	}
};


class MyTileMapRenderer : public GameEngineDefaultRenderer
{
public:
	// constrcuter destructer
	MyTileMapRenderer();
	~MyTileMapRenderer();

	// delete Function
	MyTileMapRenderer(const MyTileMapRenderer& _Other) = delete;
	MyTileMapRenderer(MyTileMapRenderer&& _Other) noexcept = delete;
	MyTileMapRenderer& operator=(const MyTileMapRenderer& _Other) = delete;
	MyTileMapRenderer& operator=(MyTileMapRenderer&& _Other) noexcept = delete;



public:
	void CreateTileMap(
		int _x,
		int _y,
		const float4& _tileScale,
		const std::string& _Texture);
	void SetTileIndex(const float4& _pos, size_t _index);
	void GetTileIndex(const float4& _pos, int& _x, int& _y);

	void SetPivot(PivotMode _pivot);
	

protected:
	void Render(float _deltaTime) override;

private:
	void Start() override;
	void Update(float _deltaTime) override;

	void MoveWorld(int _Dir);

private:
	bool KeyFree;
	int tileX_;
	int tileY_;

	std::shared_ptr<GameEngineTexture> tileTextures_;

	float4 tilescale_;
	float4 tilescalehalf_;
	float4 tilerotate_;
	PivotMode pivotmode_;

	std::vector<std::vector<Tile>> alltiles_;

	AtlasData atlasdatainst_;
	PixelData pixeldata_;


};

