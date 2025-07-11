/* -----------------
　タイトルシーン処理
 ------------------- */

#include <DxLib.h>
#include "TitleScene.h"
#include "Application.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Fader.h"
#include "Sounds.h"


TitleScene::TitleScene(void)
{
	imgTitle_ = -1;
	imgStart_ = -1;

	fader_ = new Fader;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init()
{
	imgTitle_ = LoadGraph("Image/UI/Title.png");
	imgStart_ = LoadGraph("Image/UI/HitStartKey.png");

	isState_ = false;
	fader_->Init();
}

void TitleScene::Update(void)
{
	fader_->Update(); // フェード演出 更新処理

	/*　遷移有効化　*/
	if (InputManager::GetInstance()->IsTriggerDown(KEY_INPUT_SPACE) &&
		isState_ == false)
	{
		fader_->SetFade(Fader::STATE::FADE_OUT, 0x000000);
		isState_ = true;

		// SE再生(シングルトン)
		Sounds* sound = Sounds::GetInstance();
		sound->SetSoundActive(Sounds::TYPE::CLICK);
	}

	/*　画面遷移処理　*/
	if (fader_->GetState() != Fader::STATE::NONE &&
		fader_->GetIsFeedEnd() == true)
	{
		// ゲームシーンに遷移(シングルトン)
		SceneManager* scene = SceneManager::GetInstance();
		scene->ChangeScene(SCENE_TYPE::GAME);
	}
}


void TitleScene::Draw(void)
{
	int screenX = Application::SCREEN_SIZE_X;
	int screenY = Application::SCREEN_SIZE_Y;

	// タイトル画像描画
	DrawGraph((screenX / 2) - (TITLE_SIZE_X / 2),
		(screenY / 2) - (TITLE_SIZE_Y / 2) - IMAGE_STATE_Y,
		imgTitle_, true);

	// スタートキー画像描画
	DrawGraph((screenX / 2) - (START_SIZE_X / 2),
		(screenY / 2) - (START_SIZE_Y / 2) + IMAGE_STATE_Y,
		imgStart_, true);

	fader_->Draw();
}


/*　解放処理　*/
void TitleScene::Release(void)
{
	delete fader_;

	DeleteGraph(imgTitle_);
	DeleteGraph(imgStart_);
}

