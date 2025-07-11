/* -------
　共有処理
 --------- */

#include "Utility.h"
#include "Vector2.h"
#include "Vector2F.h"


/* <<< 四捨五入 >>> */
/// <summary>
/// 四捨五入
/// </summary>
/// <param name="引数：">少数</param>
/// <param name="戻り値：">整数</param>
/// <returns></returns>
int Utility::Round(float value)
{
	return static_cast<int>(Round(value));
}
/// <summary>
/// 四捨五入
/// </summary>
/// <param name="引数：">少数ベクトル</param>
/// <param name="戻り値：">整数ベクトル</param>
/// <returns></returns>
Vector2 Utility::Round(Vector2F value)
{
	Vector2 ret;
	ret.x = static_cast<int>(Round(value.x));
	ret.y = static_cast<int>(Round(value.y));
	return ret;
}
/// <summary>
/// 四捨五入
/// </summary>
/// <param name="引数：">少数ベクトル２つ</param>
/// <param name="戻り値：">整数ベクトル</param>
/// <returns></returns>
Vector2 Utility::Round(float x, float y)
{
	Vector2 ret;
	ret.x = static_cast<int>(Round(x));
	ret.y = static_cast<int>(Round(y));

	return ret;
}