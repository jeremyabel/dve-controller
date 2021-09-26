#include "editor.h"
#include "gui.h"
#include "imgui.h"

GUI::GUI(Editor* inEditor)
	: EditorRef(inEditor)
{

}

void GUI::Render() 
{
	ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Test"))
			{
				
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	for (Device* device : EditorRef->Devices)
	{
		device->DrawGUI();
	}

	ImGui::End(); // main window
}