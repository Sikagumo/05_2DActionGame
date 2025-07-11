#include "Vector2.h"
#include "Vector2F.h"
#include "GameScene.h"
#include "Enemy.h"
#include <math.h>
#include <DxLib.h>

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

void Enemy::Init(GameScene* scene)
{

	// ゲームシーンの機能を使えるように
	gameScene_ = scene;

	// 画像の分割読み込み
	LoadDivGraph(
		"Image/Enemy/Enemy4.png",
		16, 4, 4,
		SIZE_X, SIZE_Y,
		&imgs_[0][0]
	);

	// 初期位置
	pos_.x = 250;
	pos_.y = 250;

	// 初期の移動速度
	speed_ = SPEED_DEFAULT;

	// 向き
	dir_ = Utility::DIR::DOWN;

	// アニメーション速度
	speedAnim_ = ANIM_SPEED_DEFAULT;

	// アニメーションカウンタ
	cntAnim_ = 0;

}

void Enemy::Update(void)
{	
	Move(); // 移動処理

	// アニメーションカウンタの進行
	cntAnim_++;
}

void Enemy::Draw(void)
{

	// アニメーションのチップ番号を作る(0～3)
	int animNum = static_cast<int>(
		(static_cast<float>(cntAnim_) * speedAnim_)) % NUM_ANIM;

	Vector2 cameraPos = gameScene_->GetCameraPos();

	// 敵の表示
	DrawGraph(pos_.x - SIZE_X / 2 - cameraPos.x,
			  pos_.y - SIZE_Y / 2 - cameraPos.y,
			  imgs_[static_cast<int>(dir_)][animNum], true);
}

void Enemy::Release(void)
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
void Enemy::Move(void)
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
	Vector2 moveVec;
	moveVec.x = static_cast<int>(unitVec.x * SPEED_DEFAULT);
	moveVec.y = static_cast<int>(unitVec.y * SPEED_DEFAULT);


	// プレイヤー位置と同一時 処理終了
	if (size < SPEED_DEFAULT)
	{
		return;
	}

	/*　向き変更処理(移動量が変動した時だけ遷移)　*/


	/*　下向き処理　*/
	if (moveVec.x < moveVec.y &&
		moveVec.y > 0)
	{
		dir_ = Utility::DIR::DOWN;
	}

	/*　上向き処理　*/
	if (moveVec.x > moveVec.y &&
		moveVec.y < 0)
	{
		dir_ = Utility::DIR::UP;
	}
	
	/*　右向き処理　*/
	if (moveVec.x > moveVec.y &&
		moveVec.x > 0)
	{
		dir_ = Utility::DIR::RIGHT;
	}

	/*　左向き処理　*/
	if (moveVec.x < moveVec.y &&
		moveVec.x < 0)
	{
		dir_ = Utility::DIR::LEFT;
	}

	/*　移動処理　*/
	pos_.x += moveVec.x;
	pos_.y += moveVec.y;
}

/* --- <<< セッター処理 >>> --- */

void Enemy::SetPos(Vector2 pos)
{
	pos_ = pos;
}

/* --- <<< ゲッター処理 >>> --- */

/*　座標 取得　*/
Vector2 Enemy::GetPos(void)
{
	return pos_;
}