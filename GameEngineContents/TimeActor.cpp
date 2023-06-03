#include "PreCompile.h"
#include "TimeActor.h"
#include <cmath>

TimeActor::TimeActor() 
	: TimeRenderer_(nullptr)
	, UIRenderer_(nullptr)
	, time_(0)
{
}

TimeActor::~TimeActor() 
{
}

void TimeActor::Start()
{



	{
		UIRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		UIRenderer_->SetTexture("DarkGradient_Reverse.png");
		UIRenderer_->GetTransform().SetWorldScale(float4{ 256.f, 32.f, 1.f });
		UIRenderer_->ChangeCamera(CameraOrder::UICamera);
		UIRenderer_->GetTransform().SetWorldMove(float4(0.f, 340.0f));
	}

	{
		TimeRenderer_ = CreateComponent<GameEngineFontRenderer>();
		TimeRenderer_->SetTextPosition(float4{ 525.f, 0.f});
		TimeRenderer_->SetSize(50.f);
		TimeRenderer_->SetColor(float4::White);
		TimeRenderer_->ChangeCamera(CameraOrder::UICamera);
	}


}

void TimeActor::Update(float _deltaTime)
{
	time_ += _deltaTime;
	SetTimer(TimeString);

	TimeRenderer_->SetText(TimeString,"Free Pixel");
}


void TimeActor::SetTimer(std::string& _Text)
{
	size_t n_zero = 2;
	float Time_all;
	int Time_s;
	int Time_m;

	Time_all = time_; // 현재 스테이지가 시작되고 경과한 시간을 구한다

	Time_m = static_cast<int>(Time_all) / 60;		// 총 시간을 초로 바꾼뒤에 3600으로 나눠서 분을 구한다
	Time_s = static_cast<int>(Time_all) - (60 * Time_m);	// 총 시간을 초로 바꾼뒤에 3600 * 분을 하여 초를 구한다.
	Time_all -= static_cast<float>(Time_s) +  60.f * static_cast<float>(Time_m);			// 총 시간에서 초를 빼서 소수점 자리만 구한다.

	std::string num_text = std::to_string(Time_all);
	num_text = num_text.substr(num_text.find(".") + 1, num_text.find(".") + 2); // 소수점 세자리만 출력하는 함수

	size_t s = num_text.find(".") + 2 - num_text.find(".") + 1;

	std::string num_s = std::to_string(Time_s);
	num_s = std::string(n_zero - std::min<size_t>(n_zero, num_s.length()), '0') + num_s; // 세자리를 출력하기 위해 초의 자릿수를 구한후 남은 자리를 0으로 채운다.

	std::string num_m = std::to_string(Time_m);
	num_m = std::string(n_zero - std::min<size_t>(n_zero, num_m.length()), '0') + num_m; 

	TimeString = num_m + ":" + num_s + ":" + num_text; // 분, 초, 1000/1 초를 전부 출력한다. 
}