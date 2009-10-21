// YGEGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "YGEEngineCore.h"
#include "GameStates.h"
#include <iostream>

using namespace std;
using namespace YGECore;

int _tmain(int argc, _TCHAR* argv[])
{
	YGEEngineCore core;

	core.init();
	core.run();
	core.shutdown();

	return 0;
}

