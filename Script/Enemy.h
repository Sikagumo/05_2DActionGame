/* --------
　敵データ
 ---------- */

#pragma once

#include "Vector2.h"
#include "Utility.h"
class HPBer;
class GameScene;

class Enemy
{

public:

	static const int SIZE_X = 64;	// 横サイズ
	static const int SIZE_Y = 64;	// 縦サイズ

	// 方向ごとのアニメーション数
	static constexpr int NUM_ANIM = 4;

	// 移動速度
	static constexpr int SPEED_DEFAULT = 2;

	// アニメーション速度
	static constexpr float ANIM_SPEED_DEFAULT = 0.1f;

	// コンストラクタ
	Enemy(void);

	// デストラクタ
	~Enemy(void);

	// 初期処理(最初の１回のみ実行)
	void Init(GameScene* scene);

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);

	/* --- <<< セッター処理 >>> --- */

	// 座標 割り当て
	void SetPos(Vector2 pos);


	/* --- <<< ゲッター処理 >>> --- */

	// 座標 取得
	Vector2 GetPos(void);


private:

	// ゲームシーンのポインタ変数
	GameScene* gameScene_;


	/* --- <<< メンバ変数定義 >>> --- */

	// 画像
	int imgs_[static_cast<int>(Utility::DIR::MAX)][NUM_ANIM];

	Vector2 pos_;	   // 表示座標
	int speed_;		   // 移動速度
	Utility::DIR dir_; // 移動方向

	int cntAnim_;	  // アニメーション
	float speedAnim_; // アニメーション速度

	HPBer* hpBer_;


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	void Move(void); // 移動処理
};
