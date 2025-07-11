/* --------
　音声処理
 ---------- */

#include "Sounds.h"
#include <DxLib.h>


Sounds* Sounds::instance_;

Sounds::Sounds(void)
{
}

Sounds::Sounds(const Sounds& sound)
{

}

Sounds::~Sounds(void)
{
}

/*　インスタンス 明示的生成　*/
void Sounds::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Sounds;
	}
}

/// <summary>
/// インスタンス取得処理
/// </summary>
/// <returns>音声クラスのインスタンス</returns>
Sounds* Sounds::GetInstance(void)
{
	if (instance_ == nullptr)
	{
		Sounds::CreateInstance();
	}
	return instance_;
}

/*　インスタンス 解放処理　*/
void Sounds::DeleteInstance(void)
{
	if (instance_ == nullptr)
	{
		delete instance_;
	}
}

/*　初期化処理　*/
void Sounds::Init(void)
{
	int max = static_cast<int>(TYPE::MAX);
	sounds_[static_cast<int>(TYPE::CLICK)]  = LoadSoundMem("Sound/sound.mp3");
	sounds_[static_cast<int>(TYPE::DAMAGE)] = LoadSoundMem("Sound/EnemyAttack.mp3");


	for (int i = 0; i < max; i++)
	{
		isActive_[i] = false; // 音声無効化
	}
}

/*　更新処理　*/
void Sounds::Update(void)
{
	SoundEffect(); // サウンドエフェクト
}

/*　SE再生処理　*/
void Sounds::SoundEffect(void)
{
	int max = static_cast<int>(TYPE::MAX);
	for (int i = 0; i < max; i++)
	{
		if (isActive_[i] == true)
		{
			isActive_[i] = false;

			PlaySoundMem(sounds_[i], DX_PLAYTYPE_BACK, true);
		}
	}
}


/*　解放処理　*/
void Sounds::Release(void)
{
	int max = static_cast<int>(TYPE::MAX);
	for (int i = 0; i < max; i++)
	{
		DeleteSoundMem(sounds_[i]);
	}
}


/// <summary>
/// 音声有効化処理
/// </summary>
/// <param name="soundType">音声種類</param>
void Sounds::SetSoundActive(TYPE soundType)
{
	int type = static_cast<int>(soundType);
	
	isActive_[type] = true; // 再生フラグ有効化
}
