/* ---------------
　敵リザードデータ
 ----------------- */
#include "EnemyBase.h"

class EnemyLizard : public EnemyBase
{
public:

	/* --- <<< 定数定義 >>> --- */

	// サイズ
	static constexpr Vector2 SIZE = { (192 / 4), (256 / 4) };

	// 攻撃力
	static constexpr int POWER = 3;

	// 攻撃頻度
	static constexpr float ATTACK_TIME = 2.5f;

	// 移動速度
	static constexpr int SPEED = 3;

	// 移動アニメーション速度
	static constexpr float SPEED_ANIM = 0.1f;


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// パラメータ割り当て(上書き)
	void SetParam(void) override;
};