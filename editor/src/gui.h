#pragma once

struct Editor;

class GUI
{
public:

	GUI(Editor* editor);

	void Render(const int windowWidth, const int windowHeight, const int windowPosX, const int windowPosY);

private:

	Editor* EditorRef;
	
};
