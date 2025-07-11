/* -------------
　キー入力データ
 --------------- */

#include <map>

class InputManager
{
public:

	// インスタンスを明示的に生成
	static void CreateInstance(void);

	// インスタンスの取得
	static InputManager* GetInstance(void);

	// インスタンス削除処理
	static void DeleteInstance(void);


	void Init(void);   // 初期化処理
	void Update(void); // 更新処理

	void Add(int keyType); // キー追加処理
	void Delete(void);	   // リソースの破棄
	void Clear(void);	   // 一括削除処理

	/*　キー入力 連続押下判定 取得　*/
	bool IsNew(int key);

	/*　キー入力 押下判定 取得　*/
	bool IsTriggerDown(int key);

	/*　キー入力 解放判定 取得　*/
	bool IsTriggerUp(int key);


private:

	struct Info
	{
		int type_;	  // キー種類
		bool preKey_; //  前 キー入力状態
		bool curKey_; // 現在キー入力状態
		bool isDown_; // 押下判定
		bool isUp_;	  // 入力判定
	};

	// シングルトン用インスタンス
	static InputManager* instance_;

	std::map<int, InputManager::Info> keyInfo_;


	/* --- <<< コンストラクタ >>> --- */
	
	InputManager(void);
	InputManager(const InputManager& manager);

	~InputManager(void); // デストラクタ
};