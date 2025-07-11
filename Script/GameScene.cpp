/* ----------------
　ゲームシーン処理
 ------------------ */

#include "GameScene.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Player.h"
#include "Fader.h"

#include "Enemy.h"
#include "EnemyBase.h"
#include "EnemySlime.h"
#include "EnemyFire.h"
#include "EnemyLizard.h"
#include "EnemyBat.h"
#include "EnemyDragon.h"
#include "EnemyBoss.h"

#include "Vector2.h"
#include "Application.h"
#include "Collision.h"
#include "Sounds.h"

#include <DxLib.h>
#include <vector>


GameScene::GameScene(void)
{
	isState_ = false;

	eSpawnCounter_ = ENEMY_SPAWN_INTERVAL; // 出現カウンタ
}

GameScene::~GameScene(void)
{
}


void GameScene::Init(void)
{
	/*　オブジェクト動的確保　*/
	stage_ = new Stage;
	player_ = new Player;
	boss_ = new EnemyBoss;
	fader_ = new Fader;

	stage_->Init(this);	 // ステージ初期化
	player_->Init(this); // プレイヤー初期化
	boss_->Init(this);	 // ボス初期化
	fader_->Init();		 // フェード演出初期化

	enemys_.clear(); // 敵配列 初期化

	// フェード演出 有効化
	fader_->SetFade(Fader::STATE::FADE_IN, 0x000000);

	eSpawnCounter_ = 0; // カウンタ初期化

	/*　ヒットストップ初期化　*/
	hitStopCount_ = 0;
	isHitStop_ = false;

	isState_ = true;  // 遷移判定 有効化
	isFadeOut_ = false; // フェードアウト 無効化
}

void GameScene::Update(void)
{
	fader_->Update(); // フェード処理

	/*　ヒットストップ処理　*/

	if (isHitStop_ == true)
	{
		int temp = 0;
		/*　ヒットストップ演出　*/
		if (hitStopCount_ > 0)
		{
			if (isFadeOut_ == false)
			{
				isFadeOut_ = true;
				fader_->Init();
				fader_->SetFade(Fader::STATE::FADE_OUT, 0xFF0000);
			}

			hitStopCount_--;
			if ((hitStopCount_ % 2) != 0)
			{
				return;
			}
		}

		/*　画面遷移　*/
		else
		{
			SceneManager* scene = SceneManager::GetInstance();
			scene->ChangeScene(SCENE_TYPE::GAME_OVER);
		}
	}


	if (fader_->GetState() != Fader::STATE::NONE &&
		fader_->GetIsFeedEnd() == true)
	{
		stage_->Update();  // ステージ 更新
		player_->Update(); // プレイヤー 更新

		size_t size = enemys_.size(); // 動的配列 要素数確保
		for (int i = 0; i < size; i++)
		{
			enemys_[i]->Update(); // 敵更新処理

			/*　敵の攻撃処理　*/
			if (Collision::CheckBoxCollision(
				player_->GetPos(), Player::SIZE_X, Player::SIZE_Y,
				enemys_[i]->GetPos(), enemys_[i]->GetSize().x, enemys_[i]->GetSize().y) &&

				enemys_[i]->GetIsAttack() == true)
			{
				player_->SetDamage(enemys_[i]->GetPower());

				Sounds* sound = Sounds::GetInstance();
				sound->SetSoundActive(Sounds::TYPE::DAMAGE);
			}
		}

		boss_->Update(); // ボス更新処理

		if (Collision::CheckBoxCollision(
			player_->GetPos(), Player::SIZE_X, Player::SIZE_Y,
			boss_->GetPos(), boss_->GetSize().x, boss_->GetSize().y) &&
			boss_->GetIsAttack() == true)
		{
			player_->SetDamage(boss_->GetPower());

			Sounds* sound = Sounds::GetInstance();
			sound->SetSoundActive(Sounds::TYPE::DAMAGE);
		}

		/*　プレイヤー撃破判定　*/
		if (player_->GetIsKnockDown() == true)
		{
			/*　ヒットストップ 有効化　*/
			hitStopCount_ = HIT_COUNT_MAX;
			isHitStop_ = true;
		}

		MoveCamera(); // カメラ操作処理
		EnemySpawn(); // 敵生成処理
		BossSpawn();  // ボス生成処理
	}
}

/*　描画処理　*/
void GameScene::Draw(void)
{
	stage_->Draw();  // ステージ 描画

	if (boss_->GetIsActive() == true)
	{
		boss_->Draw(); // ボス描画
	}

	player_->Draw(); // プレイヤー 描画

	int size = static_cast<int>(enemys_.size()); // 敵配列要素数 取得
	for (int i = (size - 1); i >= 0; --i)
	{
		enemys_[i]->Draw(); // 敵 描画
	}

	fader_->Draw();	 // フェード演出 描画
}

/*　解放処理　*/
void GameScene::Release(void)
{
	if (isState_ == true)
	{
		stage_->Release();  // ステージ 画像解放
		boss_->Release();	// ボス 画像解放
		player_->Release(); // プレイヤー 画像解放
	}

	delete stage_;  // ステージ 解放
	delete boss_;	// ボス 解放
	delete player_; // プレイヤー 解放
	delete fader_;  // フェード演出 解放
}


/*　ワールド座標 → マップ座標 変換処理　*/
Vector2 GameScene::World2MapPos(Vector2 worldPos)
{
	Vector2 ret;

	int mapX = worldPos.x / Stage::CHIP_SIZE_X;
	int mapY = worldPos.y / Stage::CHIP_SIZE_Y;

	ret.x = mapX;
	ret.y = mapY;

	return ret;
}

/*　マップチップを使用した衝突判定　*/
bool GameScene::IsCollisionStage(Vector2 worldPos)
{
	// ワールド座標 → マップ座標 変換
	Vector2 mapPos = World2MapPos(worldPos);

	// プレイヤーがいる位置のマップチップ番号 取得処理
	int chipNo = stage_->GetChipNo(mapPos);

	for (int i = 0; i < MOVE_CHIP_COUNT; i++)
	{
		if (chipNo == collsionObjNo_[i])
		{
			return true;
		}
	}
	return false;
}

/*　カメラ移動処理　*/
void GameScene::MoveCamera(void)
{
	// プレイヤー座標取得
	Vector2 playerPos = player_->GetPos();

	/*　カメラ左移動制限処理　*/
	int cameraLeftLimit = cameraPos_.x + CAMERA_STATE_LENGTH;
	if (playerPos.x < cameraLeftLimit)
	{
		cameraPos_.x = (playerPos.x - CAMERA_STATE_LENGTH);
	}
	if (cameraPos_.x < 0)
	{
		cameraPos_.x = 0;
	}

	/*　カメラ右移動制限処理　*/
	int cameraRightLimit = (cameraPos_.x + Application::SCREEN_SIZE_X) - CAMERA_STATE_LENGTH;
	int mapRightLimit = (Stage::GROUND_SIZE_X * Stage::CHIP_SIZE_X) - Application::SCREEN_SIZE_X;

	if (playerPos.x > cameraRightLimit)
	{
		int moveCameraX = (playerPos.x - Application::SCREEN_SIZE_X);
		moveCameraX += CAMERA_STATE_LENGTH;

		cameraPos_.x = moveCameraX;
	}
	if (cameraPos_.x > mapRightLimit)
	{
		cameraPos_.x = mapRightLimit;
	}

	/*　カメラ上移動制限処理　*/
	int cameraUpLimit = cameraPos_.y + CAMERA_STATE_LENGTH;
	if (playerPos.y < cameraUpLimit)
	{
		cameraPos_.y = (playerPos.y - CAMERA_STATE_LENGTH);
	}
	if (cameraPos_.y < 0)
	{
		cameraPos_.y = 0;
	}

	/*　カメラ下移動制限処理　*/
	int cameraDownLimit = (cameraPos_.y + Application::SCREEN_SIZE_Y) - CAMERA_STATE_LENGTH;
	int mapDownLimit = (Stage::GROUND_SIZE_Y * Stage::CHIP_SIZE_Y) - Application::SCREEN_SIZE_Y;

	if (playerPos.y > cameraDownLimit)
	{
		int moveCameraY = (playerPos.y - Application::SCREEN_SIZE_Y);
		moveCameraY += CAMERA_STATE_LENGTH;

		cameraPos_.y = moveCameraY;
	}
	if (cameraPos_.y > mapDownLimit)
	{
		cameraPos_.y = mapDownLimit;
	}
}

/*　敵生成処理　*/
void GameScene::EnemySpawn(void)
{
	++eSpawnCounter_; // 敵出現カウンタ増加

	/*　カウンタ到達時 + 敵最大数以下の時　*/
	if (enemys_.size() < ENEMY_MAX &&
		eSpawnCounter_ > ENEMY_SPAWN_INTERVAL)
	{
		eSpawnCounter_ = 0; // カウンタ初期化

		/*　敵 動的生成　*/
		EnemyBase* newEnemy = nullptr;
		int enemyTypeMax = static_cast<int>(EnemyBase::TYPE::MAX) - 1;

		// 敵情報ランダム割り当て
		int newEnemyType = GetRand(enemyTypeMax);

		// TYPE型に変換
		EnemyBase::TYPE spawnType = static_cast<EnemyBase::TYPE>(newEnemyType);

		/*　敵情報 割り当て　*/
		switch (spawnType)
		{
			/*　スライム時　*/
		case EnemyBase::TYPE::SLIME:
			newEnemy = new EnemySlime();
			break;

			/*　火炎敵時　*/
		case EnemyBase::TYPE::FIRE:
			newEnemy = new EnemyFire();
			break;

			/*　リザード時　*/
		case EnemyBase::TYPE::LIZARD:
			newEnemy = new EnemyLizard();
			break;

			/*　蝙蝠時　*/
		case EnemyBase::TYPE::BAT:
			newEnemy = new EnemyBat();
			break;

			/*　ドラゴン時　*/
		case EnemyBase::TYPE::DRAGON:
			newEnemy = new EnemyDragon();
			break;

		}


		// 敵初期化
		newEnemy->Init(this);

		/*　出現位置 ランダム割り当て　*/
		int dirMax = static_cast<int>(Utility::DIR::MAX);
		int spawnDir = GetRand(dirMax - 1);

		// DIR型に変換
		Utility::DIR dir = static_cast<Utility::DIR>(spawnDir);

		Vector2 spawnPos; // 出現座標
		spawnPos.x = spawnPos.y = 0;

		/*　生成位置 割り当て　*/
		switch (dir)
		{
			/*　上側生成　*/
		case Utility::DIR::UP:
			spawnPos.x = cameraPos_.x + GetRand(Application::SCREEN_SIZE_X);
			spawnPos.y = cameraPos_.y;
			break;

			/*　右側生成　*/
		case Utility::DIR::RIGHT:
			spawnPos.x = cameraPos_.x + Application::SCREEN_SIZE_X;
			spawnPos.y = cameraPos_.y + GetRand(Application::SCREEN_SIZE_Y);
			break;

			/*　下側生成　*/
		case Utility::DIR::DOWN:
			spawnPos.x = cameraPos_.x + GetRand(Application::SCREEN_SIZE_X);
			spawnPos.y = cameraPos_.y + Application::SCREEN_SIZE_Y;
			break;

			/*　左側生成　*/
		case Utility::DIR::LEFT:
			spawnPos.x = cameraPos_.x;
			spawnPos.y = cameraPos_.y + GetRand(Application::SCREEN_SIZE_Y);
			break;

			/*　想定外状態時の生成位置　*/
		default:
			spawnPos.x = cameraPos_.x;
			spawnPos.y = cameraPos_.y;
			break;

			break;
		}

		// 座標 割り当て
		newEnemy->SetPos(spawnPos);
		// 動的配列に格納
		enemys_.push_back(newEnemy);
	}
}

/*　ボス生成処理　*/
void GameScene::BossSpawn(void)
{
	if (boss_->GetIsActive() == false)
	{
		Vector2 spawnPos; // 出現座標
		spawnPos.x = spawnPos.y = 0;

		boss_->Init(this); // ボス初期化

		/*　出現位置 ランダム割り当て　*/
		int dirMax = static_cast<int>(Utility::DIR::MAX);
		int spawnDir = GetRand(dirMax - 1);
		// DIR型に変換
		Utility::DIR dir = static_cast<Utility::DIR>(spawnDir);

		int maxX = (Stage::CHIP_SIZE_X * Stage::GROUND_SIZE_X);
		int maxY = (Stage::CHIP_SIZE_Y * Stage::GROUND_SIZE_Y);
		Vector2 size = boss_->GetSize();

		/*　生成位置 割り当て　*/
		switch (dir)
		{
			/*　上側生成　*/
		case Utility::DIR::UP:
			spawnPos.x = GetRand(maxX);
			spawnPos.y = -size.y;
			break;

			/*　右側生成　*/
		case Utility::DIR::RIGHT:
			spawnPos.x = maxX;
			spawnPos.y = GetRand(maxY);
			break;

			/*　下側生成　*/
		case Utility::DIR::DOWN:
			spawnPos.x = GetRand(maxX);
			spawnPos.y = maxY;
			break;

			/*　左側生成　*/
		case Utility::DIR::LEFT:
			spawnPos.x = -size.x;
			spawnPos.y = GetRand(maxY);
			break;
		}

		// 座標 割り当て
		boss_->SetPos(spawnPos);
	}
}


/* --- <<<  ゲッター処理 >>> --- */

/*　マップチップ番号 取得　*/
int GameScene::GetMapChipNo(Vector2 pos)
{
	return stage_->GetChipNo(pos);;
}

/*　カメラ位置 取得　*/
Vector2 GameScene::GetCameraPos(void)
{
	return cameraPos_;
}

/*　プレイヤー位置 取得　*/
Vector2 GameScene::GetPlayerPos(void)
{
	return player_->GetPos();
}