#include "editor.h"
#include "gui.h"
#include "imgui.h"

GUI::GUI(Editor* inEditor)
	: EditorRef(inEditor)
{

}

void GUI::Render(const int windowWidth, const int windowHeight, const int windowPosX, const int windowPosY)
{
	ImGui::SetNextWindowSize(ImVec2((float)windowWidth, (float)windowHeight), ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2((float)windowPosX, (float)windowPosY), ImGuiCond_Always);

	ImGui::Begin("Main Window", nullptr,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_MenuBar
	);

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

	ImGui::End(); // Main Window
}