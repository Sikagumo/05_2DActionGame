/* -------------
　プレイヤー処理
 --------------- */

#include <DxLib.h>
#include "Player.h"
#include "InputManager.h"
#include "GameScene.h"
#include "Vector2.h"
#include "Utility.h"
#include "Application.h"

Player::Player(void)
{
	int max = static_cast<int>(Utility::DIR::MAX);
	for (int y = 0; y < max; y++)
	{
		for (int x = 0; x < NUM_ANIM; x++)
		{
			imgs_[y][x] = -1; // プレイヤー画像
		}
	}
}

Player::~Player(void)
{
	int max = static_cast<int>(Utility::DIR::MAX);
	for (int y = 0; y < max; y++)
	{
		for (int x = 0; x < NUM_ANIM; x++)
		{
			DeleteGraph(imgs_[y][x]);
		}
	}
}


void Player::Init(GameScene* scene)
{
	// 画像の分割読み込み
	LoadDivGraph(
		"Image/Player/Player.png",
		16, 4, 4,
		SIZE_X, SIZE_Y,
		&imgs_[0][0]
	);

	// 初期位置
	pos_.x = START_POS_X;
	pos_.y = START_POS_Y;


	hp_ = MAX_HP; // HP
	damageTime_ = 0;	  // 被ダメージ演出時間

	// 初期の移動速度
	speed_ = SPEED_DEFAULT;

	// 向き
	dir_ = Utility::DIR::DOWN;

	speedAnim_ = ANIM_SPEED_DEFAULT; // アニメーション速度
	cntAnim_ = 0;					 // アニメーションカウンタ

	// ゲームシーン機能 割り当て
	gameScene_ = scene;
}


/*　更新処理　*/
void Player::Update(void)
{
	Move(); // 移動処理
}

/*　描画処理　*/
void Player::Draw(void)
{

	// アニメーションのチップ番号を作る(0～3)
	//int animNum = cntAnim_ * speedAnim_ % NUM_ANIM;
	int animNum =
		static_cast<int>((static_cast<float>(cntAnim_) * speedAnim_)) % NUM_ANIM;

	int worldPosX = pos_.x - (SIZE_X / 2);
	int worldPosY = pos_.y - ((SIZE_Y / 2) + (SIZE_Y / 4));

	// カメラ座標 取得
	Vector2 cameraPos = gameScene_->GetCameraPos();

	int screenPosX = worldPosX - cameraPos.x;
	int screenPosY = worldPosY - cameraPos.y;


	DrawFormatString(16, 0, 0xFF0000, "プレイヤーHP： %d", hp_);

	if (damageTime_ > 0)
	{
		damageTime_ -= 0.01f; // 演出時間減少

		/*　被ダメージ演出[色反転]　*/
		SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
		DrawGraph(screenPosX, screenPosY, imgs_[static_cast<int>(dir_)][animNum], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		DrawGraph(screenPosX, screenPosY, imgs_[static_cast<int>(dir_)][animNum], true);
	}
}

/*　解放処理　*/
void Player::Release(void)
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
void Player::Move(void)
{
	// 移動予定位置 保持
	Vector2 movePos = pos_;

	/*　縦移動処理　*/
	if (CheckHitKey(KEY_INPUT_UP))
	{
		dir_ = Utility::DIR::UP;
		movePos.y -= speed_;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		dir_ = Utility::DIR::DOWN;
		movePos.y += speed_;
	}

	/*　当たり判定のあるブロックに衝突時 移動無効　*/
	if (gameScene_->IsCollisionStage(movePos))
	{
		movePos = pos_;
	}

	// 移動可能時 移動反映/
	else
	{
		pos_ = movePos;
		// アニメーションカウンタの進行
		cntAnim_++;
	}

	/*　横移動処理　*/
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		dir_ = Utility::DIR::LEFT;
		movePos.x -= speed_;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		dir_ = Utility::DIR::RIGHT;
		movePos.x += speed_;
	}

	// 当たり判定のあるブロックに衝突時 移動無効
	if (gameScene_->IsCollisionStage(movePos))
	{
		movePos = pos_; // 移動位置 初期化	
	}

	// 移動可能時 移動反映
	else
	{
		pos_ = movePos;
		// アニメーションカウンタの進行
		cntAnim_++;
	}

}


/* --- <<< セッター処理 >>> --- */

/// <summary>
/// プレイヤー被ダメージ処理
/// </summary>
/// <param name="damage">被ダメージ値</param>
void Player::SetDamage(int damage)
{
	hp_ -= damage;
	if (hp_ < 0)
	{
		hp_ = 0;
	}

	damageTime_ = DAMAGE_TIME; // ダメージ演出時間有効化
}


/* --- <<< ゲッター処理 >>> --- */

/// <summary>
/// プレイヤー位置 取得
/// </summary>
/// <param name="">なし</param>
/// <returns>プレイヤー位置</returns>
Vector2 Player::GetPos(void)
{
	return pos_;
}

/// <summary>
/// プレイヤーが撃破されたかの判定
/// </summary>
/// <param name="">なし</param>
/// <returns>プレイヤー撃破</returns>
bool Player::GetIsKnockDown(void)
{
	if (hp_ <= 0)
	{
		return true;
	}
	return false;
}