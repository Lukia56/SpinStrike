#include <DxLib.h>
#include "Application.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application app;

	if (app.Initialize())
	{
		app.GameLoop();
	}

	app.Finalize();

	return 0;
}
