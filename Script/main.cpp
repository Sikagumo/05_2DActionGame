/* ---------
　メイン処理
 ----------- */

#include <DxLib.h>
#include "Application.h"


// WinMain関数
//---------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// インスタンスの生成
	Application application;

	// 初期処理
	application.Init();

	// ゲームループ起動
	application.Run();

	// 解放処理
	application.Release();
	if (application.IsError())
	{
		return -1;
	}

	return 0;
}