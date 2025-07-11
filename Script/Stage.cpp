/* ------------
　ステージ処理
 -------------- */
#include "Stage.h"
#include "Vector2.h"
#include "GameScene.h"
#include <DxLib.h>
#include <string>
#include <fStream>
#include <sstream>


/*　デフォルトコンストラクタ　*/
Stage::Stage(void)
{
	for (int i = 0; i < NUM_MAP_CHIPS; i++)
	{
		imgMapChips_[i] = -1;
	}
}

/*　デストラクタ　*/
Stage::~Stage(void)
{
	
}


/*　初期化処理　*/
void Stage::Init(GameScene* scene)
{
	// ゲームシーン機能 割り当て
	gameScene_ = scene;

	/*　マップチップ読み込み　*/
	LoadDivGraph("Image/Stage/Map.png",
				 NUM_MAP_CHIPS,
				 NUM_MAP_CHIPS_X, NUM_MAP_CHIPS_Y,
				 CHIP_SIZE_X, CHIP_SIZE_Y,
				 imgMapChips_);

	LoadGroundCsvData(); // ステージデータ(CSV)読み込み
}

/*　更新処理　*/
void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	for (int y = 0; y < GROUND_SIZE_Y; y++)
	{
		for (int x = 0; x < GROUND_SIZE_X; x++)
		{
			// マップチップ番号 取得
			int mapChipNo = groundMap_[y][x];

			// マップチップ番号→画像ハンドルを取得
			int imgHandle = imgMapChips_[mapChipNo];

			/*　マップチップのワールド座標　*/
			int mapChipWorldPosX = x * CHIP_SIZE_X;
			int mapChipWorldPosY = y * CHIP_SIZE_Y;

			// カメラ座標 取得
			Vector2 cameraPos = gameScene_->GetCameraPos();

			/*　マップチップのスクリーン座標 
				[スクリーン座標 = ワールド座標 - カメラ座標]　*/
			int mapChipScreenPosX = mapChipWorldPosX - cameraPos.x;
			int mapChipScreenPosY = mapChipWorldPosY - cameraPos.y;

			// スクリーン座標 描画
			DrawGraph(mapChipScreenPosX,
					  mapChipScreenPosY,
					  imgHandle, true);
		}
	}
}

void Stage::Release(void)
{
	for (int i = 0; i < NUM_MAP_CHIPS; i++)
	{
		DeleteGraph(imgMapChips_[i]);
	}
}


/*　CSVファイルからステージデータ 読み込み処理　*/
void Stage::LoadGroundCsvData(void)
{
	/*　マップ初期化処理　*/
	for (int y = 0; y < GROUND_SIZE_Y; y++)
	{
		for (int x = 0; x < GROUND_SIZE_X; x++)
		{
			groundMap_[y][x] = -1;
		}
	}

	// ファイルの読み込み
	std::ifstream ifs = std::ifstream("Data/Ground.csv");
	if (!ifs)
	{
		return; // エラーチェック処理
	}

	std::string line; // 1行の文字情報
	std::string c;	  // 1文字情報
	int chipNo = 0;	  // int型マップチップ
	int x = 0;		  // マップX座標
	int y = 0;		  // マップY座標

	/*　1行単位読み込み処理　*/
	while (getline(ifs, line))
	{
		// string → ifstreamの仲間に変換
		std::istringstream stream(line);

		x = 0;

		/*　カンマ区切り１行読み込み　*/
		while (getline(stream, c, ','))
		{
			// string型 → int型に変換
			chipNo = stoi(c);

			// マップデータに値を格納
			groundMap_[y][x] = chipNo;

			x++;
		}
		y++;
	}
}


/*　マップチップ番号取得処理　*/
int Stage::GetChipNo(Vector2 mapPos)
{
	/*　配列外参照対策　*/
	if (mapPos.x < 0 || GROUND_SIZE_X <= mapPos.x ||
		mapPos.y < 0 || GROUND_SIZE_Y <= mapPos.y)
	{
		return -1;
	}
	return groundMap_[mapPos.y][mapPos.x];
}
