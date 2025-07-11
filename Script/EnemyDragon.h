/* ---------------
　敵ドラゴンデータ
 ----------------- */

#include "EnemyBase.h"

class EnemyDragon : public EnemyBase
{
public:

	/* --- <<< 定数定義 >>> --- */

	// サイズ
	static constexpr Vector2 SIZE = { (256 / 4), (256 / 4) };

	// 攻撃力
	static constexpr int POWER = 3;

	// 攻撃頻度
	static constexpr float ATTACK_TIME = 1.0f;

	// 移動速度
	static constexpr int SPEED = 3;

	// 移動アニメーション速度
	static constexpr float SPEED_ANIM = 0.1f;


	// パラメータ割り当て(上書き)
	void SetParam(void)override;

};