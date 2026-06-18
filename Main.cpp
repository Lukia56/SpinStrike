#include <DxLib.h>
#include "Application.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application app;

	// アプリを初期化
	if (app.Initialize())
	{
		// 初期化に成功したら、ゲームループ開始
		app.GameLoop();
	}

	// アプリを終了
	app.Finalize();

	return 0;
}
