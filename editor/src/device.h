#pragma once

struct Device
{
	Device() {}
	~Device() {}
	
	// @TODO / @QUESTION: Can these be made pure virtual?
	virtual void DrawGUI() {}
	virtual void DrawMenu() {}
};

