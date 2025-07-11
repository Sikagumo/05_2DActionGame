/* --------------
　敵スライム処理
 ---------------- */
#include "EnemySlime.h"

/*　パラメータ割り当て(上書き)　*/
void EnemySlime::SetParam(void)
{
	imgFileName = "Enemy0.png"; // 画像ファイル
	size_	    = SIZE;			// 画像サイズ

	power_		= POWER;		// 攻撃力
	attackTime_ = ATTACK_TIME;	// 攻撃頻度
	speed_	    = SPEED;		// 移動速度
	speedAnim_  = SPEED_ANIM;	// 移動アニメーション速度
}
