#pragma once

#include <cstdint>
#include <SDL.h>
#include <SDL_opengl.h>

struct DMEditor;

struct GUI
{
	// Up-reference
	DMEditor *Editor;

	// SDL / gl contexts
	SDL_Window *Window;
	SDL_GLContext Context;
	const char* glsl_version;

	GUI();
	~GUI();
	
	bool Render();
};
