#include "editor.h"
#include "gui.h"

GUI::GUI(Editor* inEditor)
	: EditorRef(inEditor)
{

}

void GUI::Render() 
{
	for (Device* device : EditorRef->Devices)
	{
		device->DrawGUI();
	}
}