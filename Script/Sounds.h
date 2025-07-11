/* ---------
　音声データ
 ----------- */
#pragma once

class Sounds
{
public:

	// インスタンス 明示的生成
	static void CreateInstance(void);

	// インスタンス 取得
	static Sounds* GetInstance(void);

	// インスタンス 削除処理
	static void DeleteInstance(void);

	// 音声種類
	enum class TYPE
	{
		CLICK,	// 入力SE
		DAMAGE, // 被ダメージSE

		MAX // 最大要素数
	};

	void Init(void);	// 初期化処理
	void Update(void);  // 更新処理
	void Release(void); // 解放処理

	// 音声有効化処理
	void SetSoundActive(TYPE soundTyoe);


private:

	static Sounds* instance_; // シングルトンインスタンス

	int sounds_[static_cast<int>(TYPE::MAX)];	 // 音声ハンドル
	bool isActive_[static_cast<int>(TYPE::MAX)]; // 音声再生有効化フラグ

	Sounds(void);			   // コンストラクタ
	Sounds(const Sounds& sound); // コンストラクタ

	~Sounds(void); // デストラクタ

	void SoundEffect(void); // SE再生処理
};