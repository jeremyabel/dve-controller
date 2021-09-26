#pragma once

#include <vector>

#include "gui.h"
#include "display.h"
#include "device.h"

struct Editor
{
	Display EditorDisplay;
	GUI EditorGUI;

	std::vector<Device*> Devices;

	Editor();
	~Editor();
	
	void Run();
};
