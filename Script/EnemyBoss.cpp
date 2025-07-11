/* ----------
　敵ボス処理
 ------------ */

#include "EnemyBoss.h"
#include "Vector2F.h"
#include "GameScene.h"
#include "Stage.h"
#include <DxLib.h>

/*　パラメータ割り当て(オーバーライド)　*/
void EnemyBoss::SetParam(void)
{
	imgFileName = "Enemy5.png"; // 画像ファイル
	size_		= SIZE;			// 画像サイズ

	power_		= POWER;		// 攻撃力
	attackTime_ = ATTACK_TIME;	// 攻撃頻度
	speed_		= SPEED;		// 移動速度
	speedAnim_	= SPEED_ANIM;	// 移動アニメーション速度

	pos_.x = pos_.y = 0;
	isActive_  = false;

	SetMoveVector();  // 移動ベクトル 割り当て
}

/*　移動処理(オーバーライド)　*/
void EnemyBoss::Move(void)
{
	if (isActive_ == true)
	{
		/*　移動処理　*/
		pos_.x += moveVec_.x;
		pos_.y += moveVec_.y;

		int maxX = (Stage::CHIP_SIZE_X * Stage::GROUND_SIZE_X);
		int maxY = (Stage::CHIP_SIZE_Y * Stage::GROUND_SIZE_Y);

		if ((pos_.x + size_.x) < 0 ||
			(pos_.y + size_.y) < 0 ||
			pos_.x > maxX ||
			pos_.y > maxY)
		{
			isActive_ = false; //無効化
		}
	}
	else
	{
		SetMoveVector();  // 移動ベクトル 割り当て

		isActive_ = true; // 有効化
	}
}

/*　生存フラグ 取得　*/
bool EnemyBoss::GetIsActive(void)
{
	if (spawnTime_ <= 0)
	{
		return isActive_;
	}

	return false;
}