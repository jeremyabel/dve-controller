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
				const uint8_t stopPacket[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0x00 };
				SerialComms.Write(stopPacket, sizeof(stopPacket));
				
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
	
		// The serial device sends status packets at 60hz. The packet format is [0xFF, State, Error]
		size_t bytesAvailable = SerialComms.GetAvailableBufferSize();
		if (bytesAvailable)
		{
			// @TODO: Remove this alloc
			uint8_t* buffer = (uint8_t*)malloc(bytesAvailable);
			SerialComms.Read(buffer, bytesAvailable);
			for (size_t i = 0; i < bytesAvailable; i++)
			{
				// A state of 0x01 means the device is active and ready to recieve packets, so tick each device to send their data.
				if (buffer[i] == 0xFF && buffer[i + 1] == 0x01)
				{
					for (Device* device : Devices)
					{
						device->Tick();
					}

					break;
				}
			}

			// @TODO: Display this in a status bar or something similar
			printf("Recieved: ");
			for (size_t i = 0; i < bytesAvailable; i++)
				printf("%02hhX ", buffer[i]);
			printf("\n");
			
			free(buffer);
		}

		EditorDisplay.Render();
	}
}