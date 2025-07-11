/* -------------------------
　ゲームオーバーシーンデータ
 --------------------------- */

#pragma once

class SceneManager; // シーン管理
class Fader;		// フェード演出

class GameOver
{
public:

	/* --- <<< 定数定義 >>> --- */

	/*　画像サイズ　*/
	static constexpr int SIZE_X = 457;
	static constexpr int SIZE_Y = 81;

	static constexpr float FEED_WAIT_TIME  = 1.25f; // フェード待機時間
	static constexpr float STATE_TIME	   = 0.5f; // 遷移待機時間


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	GameOver(void);	 // コンストラクタ
	~GameOver(void); // デストラクタ

	void Init(void);	// 初期化処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void Release(void); // 解放処理


private:

	/* --- <<< メンバ変数定義 >>> --- */

	int image_; // ゲームオーバー画像

	Fader* fader_; // フェード演出

	bool isState_; // 入力判定フラグ

	float feedTime_;  // フェードアウト待機時間
	float stateTime_; // 遷移待機時間
};