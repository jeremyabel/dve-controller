#include "editor.h"
#include "gui.h"

#include "imgui.h"

GUI::GUI(Editor* editor)
	: editor(editor)
{

}

void GUI::Render() 
{
	for (Device* device : editor->devices)
	{
		device->DrawGUI();
	}
}