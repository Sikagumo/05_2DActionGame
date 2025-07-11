/* -----------
　ボス敵データ
 ------------- */

#include "EnemyBase.h"
#include "Vector2.h"

class EnemyBoss : public EnemyBase
{
public:

	/* --- <<< 定数定義 >>> --- */

	// サイズ
	static constexpr Vector2 SIZE = { (384 / 4), (512 / 4) };

	// 攻撃力
	static constexpr int POWER = 5;

	// 攻撃頻度
	static constexpr float ATTACK_TIME = 1.5f;

	// 移動速度
	static constexpr int SPEED = 8;

	// 移動アニメーション速度
	static constexpr float SPEED_ANIM = 0.1f;


	/*　出現頻度　*/
	static constexpr float SPAWN_TIME_MIN = 0.01f;
	static constexpr float SPAWN_TIME_MAX = 0.05f;

	// パラメータ割り当て(オーバーライド)
	void SetParam(void)override;

	// 移動処理(オーバーライド)
	void Move(void)override;

	// 有効化フラグ 取得
	bool GetIsActive(void);


private:

	float spawnTime_; // 生成間隔時間

	bool isActive_;	  // 出現中判定フラグ
	bool isGetMove_;  // プレイヤー位置取得フラグ
};