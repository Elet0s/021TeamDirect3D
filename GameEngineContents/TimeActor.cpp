#include "PreCompile.h"
#include "TimeActor.h"
#include <cmath>

TimeActor::TimeActor() 
	: TimeRenderer_(nullptr)
	, UIRenderer_(nullptr)
{
}

TimeActor::~TimeActor() 
{
}

void TimeActor::Start()
{
	GameEngineFont::Load("Free Pixel");

	{
		UIRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		UIRenderer_->SetMesh("Rect");
		UIRenderer_->GetPixelData().mulColor_ = float4::Black;
		UIRenderer_->GetPixelData().mulColor_.a = 0.3f;
		UIRenderer_->SetTexture("DefaultUi.png");
		UIRenderer_->ScaleToTexture();
		UIRenderer_->ChangeCamera(CameraOrder::UICamera);
		UIRenderer_->GetTransform().SetWorldMove(float4(0.f, 340.0f));
	}

	{
		TimeRenderer_ = CreateComponent<GameEngineFontRenderer>();
		TimeRenderer_->SetTextPosition(float4{ 545.f, 0.f});
		TimeRenderer_->SetSize(30.f);
		TimeRenderer_->SetColor(float4::White);
		TimeRenderer_->ChangeCamera(CameraOrder::UICamera);
	}


}

void TimeActor::Update(float _deltaTime)
{
	SetTimer(TimeString);

	TimeRenderer_->SetText(TimeString,"Free Pixel");
}


void TimeActor::SetTimer(std::string& _Text)
{
	size_t n_zero = 2;
	float Time_all;
	int Time_s;
	int Time_m;

	Time_all = GetLevel()->GetAccTime(); // ���� ���������� ���۵ǰ� ����� �ð��� ���Ѵ�

	Time_m = static_cast<int>(Time_all) / 3600;		// �� �ð��� �ʷ� �ٲ۵ڿ� 3600���� ������ ���� ���Ѵ�
	Time_s = static_cast<int>(Time_all) - (3600 * Time_m);	// �� �ð��� �ʷ� �ٲ۵ڿ� 3600 * ���� �Ͽ� �ʸ� ���Ѵ�.
	Time_all -= static_cast<float>(Time_s);			// �� �ð����� �ʸ� ���� �Ҽ��� �ڸ��� ���Ѵ�.

	std::string num_text = std::to_string(Time_all);
	num_text = num_text.substr(num_text.find(".") + 1, num_text.find(".") + 2); // �Ҽ��� ���ڸ��� ����ϴ� �Լ�

	std::string num_s = std::to_string(Time_s);
	num_s = std::string(n_zero - std::min<size_t>(n_zero, num_s.length()), '0') + num_s; // ���ڸ��� ����ϱ� ���� ���� �ڸ����� ������ ���� �ڸ��� 0���� ä���.

	std::string num_m = std::to_string(Time_m);
	num_m = std::string(n_zero - std::min<size_t>(n_zero, num_m.length()), '0') + num_m; 

	TimeString = num_m + " : " + num_s + " : " + num_text; // ��, ��, 1000/1 �ʸ� ���� ����Ѵ�. 
}