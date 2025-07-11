/* -------------------
　アプリケーション処理
 --------------------- */

#include <DxLib.h>
#include "Application.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "FrameRate.h"
#include "Sounds.h"


Application::Application(void)
{
	frameRate_ = new FrameRate; // フレームレート
	isError_ = false;
}

Application::~Application(void)
{
}


/*　初期化処理　*/
void Application::Init(void)
{
	// アプリケーションの初期設定
	SetWindowText("ASO Quest");

	// ウィンドウサイズ
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	SetWaitVSyncFlag(0); // 垂直同期無効化

	if (DxLib_Init() == -1)
	{
		isError_ = true;
		return;
	}

	// 音声 初期化(シングルトン)
	Sounds* sound = Sounds::GetInstance();
	sound->Init();

	// シーン管理初期化(シングルトン)
	SceneManager* scene = SceneManager::GetInstance();
	scene->Init();

	/*　入力制御 初期化　*/
	InputManager::CreateInstance();
	InputManager::GetInstance()->Init();
}


/*　実行時処理　*/
void Application::Run(void)
{
	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		frameRate_->Update(); // フレームレート更新

		if (frameRate_->GetLimitFrameRate() == true)
		{
			frameRate_->SetFrameRate();

			/*　シーン　*/
			SceneManager* scene = SceneManager::GetInstance();
			scene->Update(); // シーン 更新処理
			scene->Draw();	 // シーン 描画処理

			InputManager* input = InputManager::GetInstance();
			input->Update(); // 入力管理

			Sounds* sound = Sounds::GetInstance();
			sound->Update(); // 音声処理

			frameRate_->Draw();
			ScreenFlip();
		}
	}
}


/*　解放処理　*/
void Application::Release(void)
{
	/*　シーン管理 解放処理　*/
	SceneManager* scene = SceneManager::GetInstance();
	scene->Release();

	/*　入力管理 解放処理　*/
	InputManager* input = InputManager::GetInstance();
	input->Delete();

	Sounds* sound = Sounds::GetInstance();
	sound->Release();

	// フレームレート制御 解放処理
	delete frameRate_;

	if (DxLib_End() == -1)
	{
		isError_ = true;
		return;
	}
}

bool Application::IsError(void)
{
	return isError_;
}