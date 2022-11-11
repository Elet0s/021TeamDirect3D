#pragma once

class Tile
{
	friend class TileMapRenderer;

	int tileIndex_;
	int zValue_;
	std::shared_ptr<GameEngineTexture> tileImage_;
public:
	Tile() : tileIndex_(0), zValue_(0), tileImage_(nullptr)
	{
	}
};

class TileMapRenderer: public GameEngineDefaultRenderer
{
public:
	TileMapRenderer();
	~TileMapRenderer();

protected:
	TileMapRenderer(const TileMapRenderer& _other) = delete;
	TileMapRenderer(TileMapRenderer&& _other) noexcept = delete;

private:
	TileMapRenderer& operator=(const TileMapRenderer& _other) = delete;
	TileMapRenderer& operator=(const TileMapRenderer&& _other) = delete;


public:	
	void CreateIsometricTileMap(
		int _x,
		int _y,
		const float4& _tileScale,
		const std::string& _folderTexture,
		int _defaultIndex = 0);
	void SetTileIndex(const float4& _pos, size_t _index);
	void GetTileIndex(const float4& _pos, int& _x, int& _y);

protected:
	void Render(float _deltaTime) override;

private:
	void Start() override;
	void Update(float _deltaTime) override;

private:
	std::shared_ptr<GameEngineFolderTexture> tileTextures_;

	int tileX_;
	int tileY_;

	float4 tileScale_;
	float4 tileScaleHalf_;

	std::vector<std::vector<Tile>> allTiles_;

	float4 frameData_;
	PixelData pixelData_;

};

