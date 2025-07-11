/* -----------
　敵基礎データ
 ------------- */

#pragma once

#include "Vector2.h"
#include "Utility.h"
#include <string>
class GameScene;


class EnemyBase
{
public:

	/* --- <<< 列挙型定義 >>> --- */
	enum class TYPE
	{
		SLIME  = 0, // スライム
		FIRE   = 1, // 火炎
		LIZARD = 2, // リザード
		BAT	   = 3, // 蝙蝠
		DRAGON = 4, // ドラゴン
		MAX	   = 5, // 最大要素数
	};


	/* --- <<< 定数定義 >>> --- */

	// 方向ごとのアニメーション数
	static constexpr int NUM_ANIM = 4;


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	EnemyBase(void);  // コンストラクタ
	~EnemyBase(void); // デストラクタ

	// 初期処理(最初の１回のみ実行)
	void Init(GameScene* scene);

	// パラメータ 割り当て
	virtual void SetParam(void);

	void Update(void);	// 更新処理(毎フレーム実行)
	void Draw(void);	// 描画処理(毎フレーム実行)
	void Release(void); // 解放処理(最後の１回のみ実行)


	virtual void Move(void); // 移動処理

	// 移動ベクトル 割り当て
	void SetMoveVector(void);


	/* --- <<< セッター処理 >>> --- */

	/// <summary>
	/// 位置 割り当て
	/// </summary>
	/// <param name="pos">指定位置</param>
	void SetPos(Vector2 pos);

	
	void SetHit(Vector2 playerPos,float invTime);


	/* --- <<< ゲッター処理 >>> --- */

	/// <summary>
	/// 座標取得
	/// </summary>
	/// <param name="">なし</param>
	/// <returns>敵座標位置</returns>
	Vector2 GetPos(void);

	/// <summary>
	/// 画像サイズ 取得
	/// </summary>
	/// <param name="">なし</param>
	/// <returns>画像サイズ</returns>
	Vector2 GetSize(void);

	/// <summary>
	/// 攻撃力 取得
	/// </summary>
	/// <param name="">なし</param>
	/// <returns>敵攻撃力</returns>
	int GetPower(void);

	/// <summary>
	/// 敵からの攻撃処理
	/// </summary>
	/// <param name="">なし</param>
	/// <returns>攻撃しているかどうか</returns>
	bool GetIsAttack(void);


protected:

	// ゲームシーンのポインタ変数
	GameScene* gameScene_;


	/* --- <<< メンバ変数定義 >>> --- */

	// 画像
	int imgs_[static_cast<int>(Utility::DIR::MAX)][NUM_ANIM];

	Vector2 pos_;	   // 表示座標
	int power_;		   // 攻撃力
	int speed_;		   // 移動速度
	Utility::DIR dir_; // 移動方向
	Vector2 moveVec_;  // 移動ベクトル
	float attackTime_; // 攻撃頻度

	float curAttackTime_; // 現在攻撃頻度[0でない時 プレイヤーに攻撃]

	int cntAnim_;	  // アニメーション
	float speedAnim_; // アニメーション速度

	std::string imgFileName; // 読み込む画像のファイル名
	Vector2 size_;			 // 画像のサイズ
};
