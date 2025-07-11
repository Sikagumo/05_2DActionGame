/* -------------
　ステージデータ
 --------------- */

class Vector2;
class GameScene;

class Stage
{
public:	
	/* --- <<< 列挙型定義 >>> --- */

	/* <<< マップチップ系 >>> */
	static constexpr int NUM_MAP_CHIPS_X = 16; // 横枚数
	static constexpr int NUM_MAP_CHIPS_Y = 28; // 縦枚数
	static constexpr int NUM_MAP_CHIPS = (NUM_MAP_CHIPS_X * NUM_MAP_CHIPS_Y); // 合計値

	static constexpr int CHIP_SIZE_X = 32; // 横サイズ
	static constexpr int CHIP_SIZE_Y = 32; // 縦サイズ

	/* <<< マップ系 >>> */
	static constexpr int GROUND_SIZE_X = 30; // マップ横サイズ
	static constexpr int GROUND_SIZE_Y = 30; // マップ縦サイズ


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// コンストラクタ
	Stage(void);

	// デストラクタ
	~Stage(void);

	void Init(GameScene* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

	// CSVファイルからステージデータ読み込み
	void LoadGroundCsvData(void);

	// マップチップ番号取得処理
	int GetChipNo(Vector2 mapPos);

private:

	GameScene* gameScene_;

	// マップ画像
	int imgMapChips_[NUM_MAP_CHIPS];

	// マップデータ
	int groundMap_[GROUND_SIZE_X][GROUND_SIZE_Y];
};

