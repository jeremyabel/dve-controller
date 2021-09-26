#include "editor.h"
#include "imgui_impl_sdl.h"
#include "dme7000/dme7000.h"

Editor::Editor()
	: EditorDisplay(this)
	, EditorGUI(this)
{
	Devices.emplace_back(new DME7000());
}

Editor::~Editor()
{
	Devices.clear();
}

void Editor::Run()
{
	bool done = false;
	while (!done) 
	{	
		// SDL event loop
		SDL_Event Event;
		while (SDL_PollEvent(&Event))
		{
			ImGui_ImplSDL2_ProcessEvent(&Event);
			if (Event.type == SDL_QUIT || (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_CLOSE))
			{
				done = true;
			}
		}
		
		EditorDisplay.Render();
	}
}