/* -----------------------
　ゲームオーバーシーン処理
 ------------------------- */

#include <DxLib.h>
#include "GameOver.h"
#include "Application.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Fader.h"
#include "Sounds.h"


GameOver::GameOver(void)
{
	image_ = -1; // ゲームオーバー

	fader_ = new Fader;
}

GameOver::~GameOver(void)
{
}

/*　初期化処理　*/
void GameOver::Init(void)
{
	image_ = LoadGraph("Image/UI/Gameover.png");

	isState_ = false;

	fader_->Init();
	fader_->SetFade(Fader::STATE::FADE_IN, 0xFF0000);

	feedTime_ = FEED_WAIT_TIME;
	stateTime_ = STATE_TIME;
}

/*　更新処理　*/
void GameOver::Update(void)
{
	fader_->Update(); // フェード処理

	/*　フェードイン処理　*/
	if (fader_->GetState() == Fader::STATE::FADE_IN &&
		fader_->GetIsFeedEnd() == true)
	{
		if (feedTime_ > 0)
		{
			feedTime_ -= 0.01f;
		}
	}

	/*　フェード演出状態 遷移処理　*/
	if (feedTime_ <= 0 && isState_ == false)
	{
		/*　フェードアウト化　*/
		fader_->Init();
		fader_->SetFade(Fader::STATE::FADE_OUT, 0x000000);
		isState_ = true;
	}

	/*　遷移待機処理　*/
	if (fader_->GetState() == Fader::STATE::FADE_OUT &&
		fader_->GetIsFeedEnd() == true)
	{
		if (stateTime_ > 0)
		{
			stateTime_ -= 0.01f;
		}
	}
	/*　画面遷移処理　*/
	if (stateTime_ <= 0)
	{
		// タイトルシーンに遷移(シングルトン)
		SceneManager* scene = SceneManager::GetInstance();
		scene->ChangeScene(SCENE_TYPE::TITLE);
	}
}

/*　描画処理　*/
void GameOver::Draw(void)
{
	int screenX = Application::SCREEN_SIZE_X;
	int screenY = Application::SCREEN_SIZE_Y;

	// ゲームオーバー画像 描画
	DrawGraph((screenX / 2) - (SIZE_X / 2),
			  (screenY / 2) - (SIZE_Y / 2),
			  image_, true);

	fader_->Draw(); // フェード描画
}

/*　解放処理　*/
void GameOver::Release(void)
{
	delete fader_; // フェード演出 解放

	DeleteGraph(image_); // ゲームオーバー画像 解放
}
