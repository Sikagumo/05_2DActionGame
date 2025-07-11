#include <DxLib.h>
#include "Application.h"
#include "Fader.h"

Fader::Fader(void)
{
	state_ = STATE::NONE;
	alpha_ = 0.0f;
	isPreEnd_ = true;
	isFadeEnd_ = true;
}

Fader::~Fader(void)
{
}

void Fader::Init(void)
{
	state_ = STATE::NONE;
	alpha_ = 0.0f;
	isPreEnd_ = true;
	isFadeEnd_ = true;
}

void Fader::Update(void)
{

	if (isFadeEnd_)
	{
		// フェード処理が終了していたら何もしない
		return;
	}

	if (isPreEnd_)
	{
		// 1フレーム後(Draw後)に終了とする
		isFadeEnd_ = true;
		return;
	}

	switch (state_)
	{

	case STATE::NONE:
		return;

	case STATE::FADE_OUT:
		alpha_ += SPEED_ALPHA;

		if (alpha_ > 255)
		{
			// フェード終了
			alpha_ = 255;
			isPreEnd_ = true;
		}
		break;

	case STATE::FADE_IN:
		alpha_ -= SPEED_ALPHA;

		if (alpha_ < 0)
		{
			// フェード終了
			alpha_ = 0;
			isPreEnd_ = true;
		}
		break;

	default:
		return;

	}

}

void Fader::Draw(void)
{

	switch (state_)
	{
	case STATE::NONE:
		return;

	case STATE::FADE_OUT:
	case STATE::FADE_IN:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha_));
		DrawBox(0, 0,
			Application::SCREEN_SIZE_X,
			Application::SCREEN_SIZE_Y,
			color_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	}
}


void Fader::SetFade(STATE state, unsigned int color)
{
	state_ = state;
	color_ = color;

	if (state_ != STATE::NONE)
	{
		isPreEnd_ = false;
		isFadeEnd_ = false;

		if (state == STATE::FADE_OUT)
		{
			alpha_ = 0;
		}
		if (state == STATE::FADE_IN)
		{
			alpha_ = 255;
		}
	}
}


Fader::STATE Fader::GetState(void)
{
	return state_;
}

bool Fader::GetIsFeedEnd(void)
{
	return isFadeEnd_;
}
