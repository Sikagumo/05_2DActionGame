/* ---------------
　プレイヤーデータ
 ----------------- */
#pragma once

#include "Vector2.h"
#include "Utility.h"
class InputManager;
class GameScene;


class Player
{

public:

	/* --- <<< 定数定義 >>> --- */

	static constexpr int SIZE_X = 64;	// 横サイズ
	static constexpr int SIZE_Y = 64;	// 縦サイズ

	static constexpr int START_POS_X = 500;
	static constexpr int START_POS_Y = 250;

	// 方向ごとのアニメーション数
	static constexpr int NUM_ANIM = 4;

	// 移動速度
	static constexpr int SPEED_DEFAULT = 5;

	// アニメーション速度
	static constexpr float ANIM_SPEED_DEFAULT = 0.1f;

	// 最大HP
	static constexpr int MAX_HP = 50;

	// 被ダメージ演出時間
	static constexpr float DAMAGE_TIME = 0.1f;


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// コンストラクタ
	Player(void);

	// デストラクタ
	~Player(void);


	/// <summary>
	/// 初期処理(最初の１回のみ実行)
	/// </summary>
	/// <param name="scene">ゲームシーンの要素</param>
	void Init(GameScene* scene);

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);


	/* --- <<< セッター処理 >>> --- */

	/// <summary>
	/// プレイヤーの被ダメージ処理
	/// </summary>
	/// <param name="damage">被ダメージの値</param>
	void SetDamage(int damage);


	/* --- <<< ゲッター処理 >>> --- */

	/// <summary>
	/// プレイヤー位置 取得
	/// </summary>
	/// <param name="">なし</param>
	/// <returns>プレイヤー位置</returns>
	Vector2 GetPos(void);

	/// <summary>
	/// プレイヤーが撃破されたかの判定
	/// </summary>
	/// <param name="">なし</param>
	/// <returns>プレイヤー撃破</returns>
	bool GetIsKnockDown(void);

private:

	/* --- <<< 列挙型定義 >>> --- */

	enum class KEY_TYPE
	{
		UP = 0,
		W = 1,
		DOWN = 2,
		S = 3,
		LEFT = 4,
		A = 5,
		RIGHT = 6,
		D = 7,
		MAX = 8,
	};


	/* --- <<< 変数定義 >>> --- */
	// 画像
	int imgs_[static_cast<int>(Utility::DIR::MAX)][NUM_ANIM];

	Vector2 pos_;		// 表示座標
	Vector2 cameraPos_; // カメラ座標

	int hp_; // 現在HP

	float damageTime_; // 被ダメージ演出時間

	int speed_;		   // 移動速度
	Utility::DIR dir_; // 移動方向

	int cntAnim_;	  // 現在アニメーション
	float speedAnim_; // アニメーション速度

	// ゲームシーン
	GameScene* gameScene_;


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// 移動処理
	void Move(void);
};
