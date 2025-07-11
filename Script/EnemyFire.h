/* -----------
　火炎敵データ
 ------------- */
#include "EnemyBase.h"

class EnemyFire : public EnemyBase
{
public:
	/* --- <<< 定数定義 >>> --- */

	// サイズ
	static constexpr Vector2 SIZE = { (96 / 4), (128 / 4) };

	// 攻撃力
	static constexpr int POWER = 2;

	// 攻撃頻度
	static constexpr float ATTACK_TIME = 1.25f;

	// 移動速度
	static constexpr int SPEED = 2;

	// 移動アニメーション速度
	static constexpr float SPEED_ANIM = 0.1f;


	// パラメータ割り当て(上書き)
	void SetParam(void) override;
};