#include "editor.h"
#include "imgui_impl_sdl.h"
#include "dme7000/dme7000.h"

Editor::Editor()
	: EditorDisplay(this)
	, EditorGUI(this)
{
	SerialComms = Serial();
	SerialComms.Open();
	SerialComms.Flush();

	Devices.emplace_back(new DME7000(this));
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
		int oldTime = SDL_GetTicks();

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

		for (Device* device : Devices)
		{
			device->Tick();
		}

		EditorDisplay.Render();

		// Force 60fps (16ms per frame)
		// @QUESTION: I copied this from the internet. I don't trust it, but it works for now??? Any other suggestions?
		uint32_t deltaTime = SDL_GetTicks() - oldTime;
		if (deltaTime > 0 && deltaTime < 16)
		{
			SDL_Delay(16 - deltaTime);
		}
	}
}