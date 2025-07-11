/* ----------
　共有データ
 ------------ */
#pragma once
#include "Vector2.h"
#include "Vector2F.h"

// 共通で使用する定義
class Utility
{

public:

	// 移動方向
	enum class DIR
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};

	/*　四捨五入(引数：少数, 戻り値：整数)　*/
	static int Round(float value);

	/*　四捨五入(引数：少数ベクトル, 戻り値：整数ベクトル)　*/
	static Vector2 Round(Vector2F value);

	/*　四捨五入(引数：少数２つ, 戻り値：整数ベクトル)　*/
	static Vector2 Round(float x, float y);
};

