/* --------------
　敵ドラゴン処理
 ---------------- */
#include "EnemyDragon.h"

/*　パラメータ割り当て(上書き)　*/
void EnemyDragon::SetParam(void)
{
	imgFileName = "Enemy4.png"; // 画像ファイル
	size_		= SIZE;			// 画像サイズ

	power_		= POWER;		// 攻撃力
	attackTime_ = ATTACK_TIME;	// 攻撃頻度
	speed_		= SPEED;		// 移動速度
	speedAnim_	= SPEED_ANIM;	// 移動アニメーション速度
}
