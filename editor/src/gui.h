#pragma once

struct Editor;

class GUI
{
public:

	GUI(Editor* editor);

	void Render();

private:

	Editor* EditorRef;
	
};
