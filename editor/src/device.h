#pragma once

struct Editor;

struct Device
{
	Device() {}
	Device(Editor* editor) : EditorRef(editor) {}

	~Device() {}
	
	virtual void DrawGUI() {}
	virtual void DrawMenu() {}

	Editor* EditorRef;
};

