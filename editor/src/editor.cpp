#include "editor.h"
#include "imgui_impl_sdl.h"
#include "dme7000/dme7000.h"

Editor::Editor()
	: EditorDisplay(this)
	, EditorGUI(this)
	, isInitialized(false)
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

		// Initialize all devices before the first tick
		if (!isInitialized)
		{
			isInitialized = true;
			for (Device* device : Devices)
			{
				device->Init();
			}
		}

		size_t bytesAvailable = SerialComms.GetAvailableBufferSize();
		if (bytesAvailable)
		{
			uint8_t* buffer = (uint8_t*)malloc(bytesAvailable);
			SerialComms.Read(buffer, bytesAvailable);
			for (size_t i = 0; i < bytesAvailable; i++)
			{
				if (buffer[i] == 0xFF && buffer[i + 1] == 0x01)
				{
					for (Device* device : Devices)
					{
						device->Tick();
					}

					break;
				}
			}

			printf("Recieved: ");
			for (size_t i = 0; i < bytesAvailable; i++)
				printf("%02hhX ", buffer[i]);
			printf("\n");
			
			free(buffer);

			SerialComms.FlushInput();
		}

		EditorDisplay.Render();

		// Force 60fps (16ms per frame)
		// @QUESTION: I copied this from the internet. I don't trust it, but it works for now??? Any other suggestions?
		//uint32_t deltaTime = SDL_GetTicks() - oldTime;
		//if (deltaTime > 0 && deltaTime < 16)
		//{
		//	SDL_Delay(16 - deltaTime);
		//}
	}
}