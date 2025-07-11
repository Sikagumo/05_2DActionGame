/* ---------------
　シーン管理データ
 ----------------- */
#pragma once

#include "SceneData.h"
class TitleScene;
class GameScene;
class GameOver;

class SceneManager
{

public:

	/* --- <<< 定数定義 >>> --- */

	static constexpr int SCREEN_SIZE_X = 640;	// 画面の横サイズ
	static constexpr int SCREEN_SIZE_Y = 480;	// 画面の縦サイズ

	/* --- <<< 関数プロトタイプ宣言 >>> --- */
	// インスタンス 取得
	static SceneManager* GetInstance(void);

	static void DeleteInstance(void);


	// 初期処理(最初の１回のみ実行)
	void Init(void);

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);


	// シーン遷移
	void ChangeScene(SCENE_TYPE type);


private:

	SceneManager(void);	 // デフォルトコンストラクタ
	~SceneManager(void); // デストラクタ

	/* ↑コンストラクタ系をprivateにすることでシングルトンできる */

	// コピーコンストラクタ無効化
	SceneManager(const SceneManager& other);

	// インスタンス
	static SceneManager* instance_;

	TitleScene* titleScene_; // タイトルシーン
	GameScene* gameScene_;	 // ゲームシーン
	GameOver* gameOver_;	 // ゲームオーバー

	// 現在のシーン
	SCENE_TYPE sceneType_;
};