#pragma once

#include <vector>

#include "gui.h"
#include "display.h"
#include "device.h"

struct Editor
{
	Display display;
	GUI gui;

	std::vector<Device*> devices;

	Editor();
	~Editor();
	
	void Run();
};
