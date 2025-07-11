/* ------------
　キー入力処理
 -------------- */
#include "InputManager.h"
#include <DxLib.h>

InputManager* InputManager::instance_;


InputManager::InputManager(void)
{

}

InputManager::InputManager(const InputManager& manager) 
{

}

InputManager::~InputManager(void)
{

}

/*　インスタンスを明示的に生成　*/
void InputManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new InputManager;
	}
}

/*　インスタンス取得処理　*/
InputManager* InputManager::GetInstance(void)
{
	if (instance_ == nullptr)
	{
		InputManager::CreateInstance();
	}
	return instance_;
}

/*　インスタンス解放　*/
void InputManager::DeleteInstance(void)
{
	if (instance_ == nullptr)
	{
		delete instance_;
	}
}

/*　初期化処理　*/
void InputManager::Init(void)
{
	/*　キー登録　*/
	InputManager::GetInstance()->Add(KEY_INPUT_SPACE);
	InputManager::GetInstance()->Add(KEY_INPUT_N);
	InputManager::GetInstance()->Add(KEY_INPUT_Z);
}

/*　更新処理　*/
void InputManager::Update(void)
{
	for (int i = 0; i < keyInfo_.size(); ++i)
	{
		// キーフレーム更新
		keyInfo_[i].preKey_ = keyInfo_[i].curKey_;

		/*　押下判定　*/
		if (CheckHitKey(keyInfo_[i].type_))
		{
			keyInfo_[i].curKey_ = true;
		}
		else
		{
			keyInfo_[i].curKey_ = false;
		}


		/*　入力判定[前フレーム未入力 + 今フレーム入力時 有効化]　*/
		if (keyInfo_[i].preKey_ == false && keyInfo_[i].curKey_ == true)
		{
			keyInfo_[i].isDown_ = true;
		}
		else
		{
			keyInfo_[i].isDown_ = false;
		}

		/*　キーを離す判定[前フレーム入力 + 今フレーム未入力時 有効化]　*/
		if (keyInfo_[i].preKey_ == true && keyInfo_[i].curKey_ == false)
		{
			keyInfo_[i].isUp_ = true;
		}
		else
		{
			keyInfo_[i].isUp_ = false;
		}
	}
}


/// <summary>
/// 判定キー追加処理
/// </summary>
/// <param name="keyType">追加するキーの値</param>
void InputManager::Add(int keyType)
{
	InputManager::Info info;
	info.type_ = keyType;

	/*　キー判定初期化　*/
	info.preKey_ = false;
	info.curKey_ = false;
	info.isDown_ = false;
	info.isUp_	 = false;

	keyInfo_.emplace(keyType, info); // 判定キー登録
}

/*　キー情報インスタンス削除　*/
void InputManager::Delete(void)
{
	keyInfo_.clear(); // キー情報削除
	delete instance_; // インスタンス削除
}

/*　キー情報削除　*/
void InputManager::Clear(void)
{
	keyInfo_.clear();
}


/// <summary>
/// キー入力判定 取得
/// </summary>
/// <param name="key">登録番号</param>
/// <returns>キー入力しているかの判定</returns>
bool InputManager::IsNew(int key)
{
	InputManager::Info info = keyInfo_[key];
	return info.curKey_;
}

/// <summary>
/// キー押下判定 取得
/// </summary>
/// <param name="key">登録番号</param>
/// <returns>キー押下をしたかの判定</returns>
bool InputManager::IsTriggerDown(int key)
{
	InputManager::Info info = keyInfo_[key];
	return info.isDown_;
}

/// <summary>
/// キーを離す判定 取得
/// </summary>
/// <param name="key">登録番号</param>
/// <returns>キーを離したかの判定</returns>
bool InputManager::IsTriggerUp(int key)
{
	InputManager::Info info = keyInfo_[key];
	return info.isUp_;;
}