#include "SceneData.h"
#include "Vector2.h"
#include <vector>
class Stage;
class Player;
class Enemy;
class EnemyBase;
class EnemyBoss;
class Fader;

class GameScene
{
public:

	// 移動可能マップチップの種類数
	static constexpr int MOVE_CHIP_COUNT = 7;

	// カメラ移動位置範囲
	static constexpr int CAMERA_STATE_LENGTH = 100;

	// 敵最大数
	static constexpr int ENEMY_MAX = 50;

	// 敵出現間隔(値が増えるにつれて間隔が延びる)
	static constexpr int ENEMY_SPAWN_INTERVAL = 20;

	// 最大ヒットストップ数
	static constexpr int HIT_COUNT_MAX = 50;


	/* --- <<< メンバ関数プロトタイプ宣言 >>> --- */

	// デフォルトコンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	// 初期処理(最初の１回のみ実行)
	void Init(void);

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);

	// ワールド座標 → マップ座標 変換処理
	Vector2 World2MapPos(Vector2 worldPos);

	// マップチップを使用した衝突判定
	bool IsCollisionStage(Vector2 worldPos);


	/* --- <<< ゲッター処理 >>> --- */

	// マップチップ番号 取得
	int GetMapChipNo(Vector2 worldPos);

	// カメラ座標 取得
	Vector2 GetCameraPos(void);

	// プレイヤー座標 取得
	Vector2 GetPlayerPos(void);

private:

	Stage* stage_;	 // ステージオブジェクト
	Player* player_; // プレイヤーオブジェクト
	Fader* fader_;	 // フェード演出オブジェクト

	std::vector<EnemyBase*> enemys_; // 複数敵 動的配列
	int eSpawnCounter_;				 // 敵出現カウンタ
	EnemyBoss* boss_;				 // ボス敵敵

	Vector2 cameraPos_; // カメラ位置

	// 移動不可マップチップ番号
	int collsionObjNo_[MOVE_CHIP_COUNT] = { 8,  16,17,64,65,33,32 };

	int hitStopCount_; // ヒットストップ数
	bool isHitStop_;   // ヒットストップ有効判定

	bool isState_; // 遷移したかの判定
	bool isFadeOut_;  // フェードアウトが有効かの判定


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	void MoveCamera(void); // カメラ移動処理
	void EnemySpawn(void); // 敵生成処理
	void BossSpawn(void);  // ボス敵生成処理
};
