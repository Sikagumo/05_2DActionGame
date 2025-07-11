/* -------------------
　タイトルシーンデータ
 --------------------- */

#pragma once

#include "SceneData.h"
class SceneManager;
class Fader;


class TitleScene
{
public:

	/* --- <<< 定数定義 >>> --- */

	/*　タイトル画像サイズ　*/
	static constexpr int TITLE_SIZE_X = 600;
	static constexpr int TITLE_SIZE_Y = 250;

	/*　"スタート"画像サイズ　*/
	static constexpr int START_SIZE_X = 337;
	static constexpr int START_SIZE_Y = 53;

	// 画像位置 移動値
	static constexpr int IMAGE_STATE_Y = 100;


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// デフォルトコンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	// 初期処理(最初の１回のみ実行)
	void Init();

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);

private:

	/* --- <<< メンバ変数定義 >>> --- */

	int imgTitle_; // タイトル画像
	int imgStart_; // スタート画像

	Fader* fader_; // フェード処理

	bool isState_; // ゲーム開始フラグ(連続押下対策)
};