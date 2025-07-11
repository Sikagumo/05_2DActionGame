/* ---------------
　敵スライムデータ
 ----------------- */

#include "EnemyBase.h"

class EnemySlime : public EnemyBase
{
public:

	/* --- <<< 定数定義 >>> --- */

	// サイズ
	static constexpr Vector2 SIZE = { (96 / 4), (128 / 4) };

	// 攻撃力
	static constexpr int POWER = 1;

	// 攻撃頻度
	static constexpr float ATTACK_TIME = 0.9f;

	// 移動速度
	static constexpr int SPEED = 3;

	// 移動アニメーション速度
	static constexpr float SPEED_ANIM = 0.1f;


	// パラメータ割り当て(上書き)
	void SetParam(void) override;
};