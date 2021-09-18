#pragma once

#include <vector>

#include "gui.h"
#include "display.h"
#include "device.h"

struct Editor
{
	GUI gui;
	Display display;

	std::vector<Device*> devices;

	Editor();
	~Editor();
	
	void Run();
};
