/* ---------
　敵基本処理
 ----------- */
#include "Vector2.h"
#include "Vector2F.h"
#include "GameScene.h"
#include "EnemyBase.h"
#include <math.h>
#include <DxLib.h>

EnemyBase::EnemyBase(void)
{
	cntAnim_ = 0;
	dir_	 = Utility::DIR::UP;
	gameScene_ = nullptr;

	int max = (static_cast<int>(Utility::DIR::MAX));
	for (int y = 0; y < max; y++)
	{
		for (int x = 0; x < NUM_ANIM; x++)
		{
			imgs_[y][x] = -1;
		}
	}
		
}

EnemyBase::~EnemyBase(void)
{
}

void EnemyBase::Init(GameScene* scene)
{
	// ゲームシーンの機能を使えるように
	gameScene_ = scene;

	// 画像分割 読み込み
	std::string path = "Image/Enemy/";

	// パラメータ 割り当て
	SetParam();

	path += imgFileName;

	// 画像の分割読み込み
	LoadDivGraph(path.c_str(),
				 (NUM_ANIM * NUM_ANIM),
				 NUM_ANIM, NUM_ANIM,
				 size_.x, size_.y,
				 &(imgs_[0][0]));

	// 初期位置
	pos_.x = pos_.y = 0;

	// 攻撃頻度
	curAttackTime_ = attackTime_;

	// 向き
	dir_ = Utility::DIR::DOWN;

	// アニメーションカウンタ
	cntAnim_ = 0;

}

void EnemyBase::SetParam(void)
{
	imgFileName  = "Enemy4.png";
	size_		 = { 64,64 };

	power_		 = 1;
	attackTime_  = 1;
	speed_		 = 1;
	speedAnim_	 = 0.1f;
}


/*　更新処理　*/
void EnemyBase::Update(void)
{
	Move(); // 移動処理

	// アニメーションカウンタの進行
	cntAnim_++;

	if (curAttackTime_ > 0)
	{
		curAttackTime_ -= 0.01f; // 攻撃頻度時間 減少
	}
}


/*　描画処理　*/
void EnemyBase::Draw(void)
{
	// アニメーションのチップ番号を作る(0～3)
	int animNum = static_cast<int>(
		(static_cast<float>(cntAnim_) * speedAnim_)) % NUM_ANIM;

	Vector2 cameraPos = gameScene_->GetCameraPos();

	// 敵の表示
	DrawGraph(pos_.x - (size_.x / 2) - cameraPos.x,
			  pos_.y - (size_.y / 2) - cameraPos.y,
			  imgs_[static_cast<int>(dir_)][animNum], true);
}


/*　解放処理　*/
void EnemyBase::Release(void)
{
	// 読み込んだ画像の解放
	int max = static_cast<int>(Utility::DIR::MAX);

	for (int y = 0; y < max; y++)
	{
		for (int x = 0; x < NUM_ANIM; x++)
		{
			DeleteGraph(imgs_[y][x]);
		}
	}
}


/*　移動処理　*/
void EnemyBase::Move(void)
{
	SetMoveVector();

	/*　移動処理　*/
	pos_.x += moveVec_.x;
	pos_.y += moveVec_.y;
}

/*　移動ベクトル割り当て処理　*/
void EnemyBase::SetMoveVector(void)
{
	// プレイヤー位置 取得
	Vector2 pPos = gameScene_->GetPlayerPos();

	/*　プレイヤー位置との距離を測る　*/
	Vector2F vector;
	vector.x = static_cast<float>(pPos.x - pos_.x);
	vector.y = static_cast<float>(pPos.y - pos_.y);

	// ベクトルの長さの二乗
	float squaredSize = (vector.x * vector.x) + (vector.y * vector.y);

	// ベクトルの長さ(累乗していない値)
	float size = sqrtf(squaredSize);

	// 移動量が0の時 除算バグ対策で処理終了
	if (size == 0)
	{
		return;
	}

	// 単位ベクトル(長さが１のベクトル)
	Vector2F unitVec;

	/*　単位ベクトルは長さで割る　*/
	unitVec.x = vector.x / size;
	unitVec.y = vector.y / size;

	// ベクトルをスピードの長さにして移動ベクトルにする
	moveVec_.x = static_cast<int>(unitVec.x * speed_);
	moveVec_.y = static_cast<int>(unitVec.y * speed_);


	// プレイヤー位置と同一時 処理終了
	if (size < speed_)
	{
		return;
	}

	/*　向き変更処理(移動量が変動した時だけ遷移)　*/


	/*　下向き処理　*/
	if (moveVec_.x < moveVec_.y &&
		moveVec_.y > 0)
	{
		dir_ = Utility::DIR::DOWN;
	}

	/*　上向き処理　*/
	if (moveVec_.x > moveVec_.y &&
		moveVec_.y < 0)
	{
		dir_ = Utility::DIR::UP;
	}

	/*　右向き処理　*/
	if (moveVec_.x > moveVec_.y &&
		moveVec_.x > 0)
	{
		dir_ = Utility::DIR::RIGHT;
	}

	/*　左向き処理　*/
	if (moveVec_.x < moveVec_.y &&
		moveVec_.x < 0)
	{
		dir_ = Utility::DIR::LEFT;
	}
}


/* --- <<< セッター処理 >>> --- */

/// <summary>
/// 位置 割り当て
/// </summary>
/// <param name="pos">指定位置</param>
void EnemyBase::SetPos(Vector2 pos)
{
	pos_ = pos;
}

void EnemyBase::SetHit(Vector2 playerPos, float invTime)
{

}


/* --- <<< ゲッター処理 >>> --- */

/// <summary>
/// 座標取得
/// </summary>
/// <param name="">なし</param>
/// <returns>敵座標位置</returns>
Vector2 EnemyBase::GetPos(void)
{
	return pos_;
}

/// <summary>
/// 画像サイズ 取得
/// </summary>
/// <param name="">なし</param>
/// <returns>画像サイズ</returns>
Vector2 EnemyBase::GetSize(void)
{
	return size_;
}


/// <summary>
/// 攻撃力 取得
/// </summary>
/// <param name="">なし</param>
/// <returns>敵攻撃力</returns>
int EnemyBase::GetPower(void)
{
	return power_;
}


/// <summary>
/// 敵からの攻撃処理
/// </summary>
/// <param name="">なし</param>
/// <returns>攻撃しているかどうか</returns>
bool EnemyBase::GetIsAttack(void)
{
	if (curAttackTime_ <= 0)
	{
		curAttackTime_ = attackTime_; // 攻撃頻度時間 初期化

		return true;
	}

	return false;
}
