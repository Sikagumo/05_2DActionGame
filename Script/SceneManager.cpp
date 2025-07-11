/* ----------
　シーン処理
 ------------ */

#include <DxLib.h>
#include "SceneManager.h"
#include "InputManager.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "GameOver.h"


SceneManager* SceneManager::instance_ = nullptr;

/*　インスタンス 取得処理　*/
SceneManager* SceneManager::GetInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager;
	}
	return instance_;
}

/*　インスタンス 削除処理　*/
void SceneManager::DeleteInstance(void)
{
	if (instance_ != nullptr)
	{
		delete instance_;
	}
}

/*　コンストラクタ　*/
SceneManager::SceneManager(void)
{
	titleScene_ = new TitleScene(); // タイトルシーン
	gameScene_ = new GameScene();	// ゲームシーン
	gameOver_ = new GameOver();	// ゲームオーバーシーン

	sceneType_ = SCENE_TYPE::NONE;
}

/*　デストラクタ　*/
SceneManager::~SceneManager(void)
{
}

/*　コピーコンストラクタ　*/
SceneManager::SceneManager(const SceneManager& other)
{

}


void SceneManager::Init(void)
{
	// 初期はタイトルシーン
	ChangeScene(SCENE_TYPE::TITLE);
}

void SceneManager::Update(void)
{
	SCENE_TYPE nextSceneType = sceneType_;

	switch (sceneType_)
	{
	case SCENE_TYPE::TITLE:
		// タイトルシーンの更新
		titleScene_->Update();
		break;

	case SCENE_TYPE::GAME:
		// ゲームシーンの更新
		gameScene_->Update();
		break;

	case SCENE_TYPE::GAME_OVER:
		// ゲームオーバーの更新
		gameOver_->Update();
		break;
	}
}

void SceneManager::Draw(void)
{
	// 描画先をバックバッファにする
	SetDrawScreen(DX_SCREEN_BACK);

	// 描画先をクリア
	ClsDrawScreen();

	switch (sceneType_)
	{
	case SCENE_TYPE::TITLE:
		// タイトルシーン 描画
		titleScene_->Draw();
		break;

	case SCENE_TYPE::GAME:
		// ゲームシーン 描画
		gameScene_->Draw();
		break;

	case SCENE_TYPE::GAME_OVER:
		// ゲームオーバーシーン 描画
		gameOver_->Draw();
		break;
	}
}

/*　解放処理　*/
void SceneManager::Release(void)
{
	/*　タイトルシーン 解放　*/
	titleScene_->Release();
	delete titleScene_;

	/*　ゲームシーン 解放　*/
	gameScene_->Release();
	delete gameScene_;

	/*　ゲームオーバーシーン 解放　*/
	gameOver_->Release();
	delete gameOver_;


	// インスタンス 削除処理
	DeleteInstance();

	// 終了処理
	DxLib_End();
}

/*　シーン遷移処理　*/
/// <summary>　シーン遷移処理　</summary>
/// <param name="type">遷移するシーン</param>
/// <returns>なし</returns>
void SceneManager::ChangeScene(SCENE_TYPE type)
{
	// シーンIDを変更
	sceneType_ = type;

	switch (sceneType_)
	{
	case SCENE_TYPE::TITLE:
		titleScene_->Init(); // タイトルシーン 初期化
		break;

	case SCENE_TYPE::GAME:
		gameScene_->Init(); // ゲームシーン 初期化
		break;

	case SCENE_TYPE::GAME_OVER:
		gameOver_->Init();	// ゲームオーバーシーン 初期化
		break;
	}

}
