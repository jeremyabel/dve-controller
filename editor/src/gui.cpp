#include "editor.h"
#include "gui.h"

GUI::GUI(Editor* inEditor)
	: editor(inEditor)
{

}

void GUI::Render() 
{
	for (Device* device : editor->devices)
	{
		device->DrawGUI();
	}
}