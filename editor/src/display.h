#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

struct Editor;

class Display
{
public:
	
	Display(Editor* editor);
	~Display();

	void Render();

private:

	Editor* editor;

	SDL_Window* window;
	SDL_GLContext context;

	const char* glsl_version;

};
