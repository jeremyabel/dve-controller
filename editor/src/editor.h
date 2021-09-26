#pragma once

#include <vector>

#include "gui.h"
#include "display.h"
#include "device.h"
#include "serial.h"

struct Editor
{
	Display EditorDisplay;
	Serial SerialComms;
	GUI EditorGUI;

	std::vector<Device*> Devices;

	Editor();
	~Editor();
	
	void Run();
};
