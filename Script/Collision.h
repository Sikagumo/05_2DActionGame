/* -----------
　衝突判定管理
 ------------- */
#pragma once
#include "Vector2.h"

class Collision
{
public:

	/*　衝突判定　*/

	/// <summary> 短形当たり判定 </summary>
	/// <param name="target1Pos">対象１位置</param>
	/// <param name="target1Size">対象１サイズ</param>
	/// <param name="target2Pos">対象２位置</param>
	/// <param name="target2Size">対象２サイズ</param>
	/// <returns>対象同士が衝突したかどうか(bool型)</returns>
	static bool CheckBoxCollision(Vector2 target1Pos, Vector2 target1Size, Vector2 target2Pos, Vector2 target2Size);


	/// <summary> 短形当たり判定 </summary>
	/// <param name="target1Pos">対象１位置</param>
	/// <param name="target1SizeX">対象１横サイズ</param>
	/// <param name="target1SizeY">対象１縦サイズ</param>
	/// <param name="target2Pos">対象２位置</param>
	/// <param name="target2SizeX">対象２横サイズ</param>
	/// <param name="target2SizeY">対象２縦サイズ</param>
	/// <returns>対象同士が衝突したかどうか(bool型)</returns>
	static bool CheckBoxCollision(Vector2 target1Pos, int target1SizeX, int target1SizeY, Vector2 target2Pos, int target2SizeX, int target2SizeY);
};