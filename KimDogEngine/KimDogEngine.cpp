#include "stdafx.h"
#include "KimDogEngine.h"
#include "System.h"

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, INT)
{
	System sys;

	sys.Init();

	sys.Run();

	return 0;
}