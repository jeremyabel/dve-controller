#pragma once

struct Editor;

struct Device
{
	Device() {}
	Device(Editor* editor) : EditorRef(editor) {}

	~Device() {}
	
	virtual void Init() {}
	virtual void DrawGUI() {}
	virtual void DrawMenu() {}
	virtual void Tick() {}

	Editor* EditorRef;
};

