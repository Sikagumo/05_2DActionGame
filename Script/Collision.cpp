/* ----------
　当たり判定
 ------------ */

#include "Collision.h"

/* --- <<< 短形当たり判定 >>> --- */

/// <summary> 短形当たり判定 </summary>
/// <param name="target1Pos">対象１位置</param>
/// <param name="target1Size">対象１サイズ</param>
/// <param name="target2Pos">対象２位置</param>
/// <param name="target2Size">対象２サイズ</param>
/// <returns>対象同士が衝突したかどうか(bool型)</returns>
bool Collision::CheckBoxCollision(Vector2 target1Pos, Vector2 target1Size, Vector2 target2Pos, Vector2 target2Size)
{
	if (target1Pos.x > (target2Pos.x + target2Size.x) &&
		target1Pos.y > (target2Pos.y + target2Size.y) &&
		(target1Pos.x + target1Size.x) < target2Pos.x &&
		(target1Pos.y + target1Size.y) < target2Pos.y)
	{
		return true;
	}
	return false;
}

/// <summary> 短形当たり判定 </summary>
/// <param name="target1Pos">対象１位置</param>
/// <param name="target1SizeX">対象１横サイズ</param>
/// <param name="target1SizeY">対象１縦サイズ</param>
/// <param name="target2Pos">対象２位置</param>
/// <param name="target2SizeX">対象２横サイズ</param>
/// <param name="target2SizeY">対象２縦サイズ</param>
/// <returns>対象同士が衝突したかどうか(bool型)</returns>
bool Collision::CheckBoxCollision(Vector2 target1Pos, int target1SizeX, int target1SizeY, Vector2 target2Pos, int target2SizeX, int target2SizeY)
{
	if (target1Pos.x < (target2Pos.x + target2SizeX) &&
		target1Pos.y < (target2Pos.y + target2SizeY) &&
		(target1Pos.x + target1SizeX) > target2Pos.x &&
		(target1Pos.y + target1SizeY) > target2Pos.y)
	{
		return true;
	}
	return false;
}