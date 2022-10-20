#pragma once

class MetaSpriteWindow;
class MetaLevel: public GameEngineLevel
{
public:
	MetaLevel();
	~MetaLevel();

protected:
	MetaLevel(const MetaLevel& _other) = delete;
	MetaLevel(MetaLevel&& _other) noexcept = delete;

private:
	MetaLevel& operator=(const MetaLevel& _other) = delete;
	MetaLevel& operator=(const MetaLevel&& _other) = delete;


public:	

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void LevelStartEvent() override;
	void LevelEndEvent() override;


private:
	MetaSpriteWindow* metaAnimationGUI_;
};

