/* -----------
　蝙蝠敵データ
 ------------- */

#include "EnemyBase.h"
class EnemyBat : public EnemyBase
{
public:

	/* --- <<< 定数定義 >>> --- */

	// サイズ
	static constexpr Vector2 SIZE = { (128 / 4), (128 / 4) };

	// 攻撃力
	static constexpr int POWER = 1;

	// 攻撃頻度
	static constexpr float ATTACK_TIME = 1.0f;

	// 移動速度
	static constexpr int SPEED = 2;

	// 移動アニメーション速度
	static constexpr float SPEED_ANIM = 0.2f;



	// パラメータ割り当て(上書き)
	void SetParam(void) override;
};