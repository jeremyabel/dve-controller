#pragma once

#define SDL_MAIN_HANDLED
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

	Editor* EditorRef;

	SDL_Window* Window;
	SDL_GLContext Context;

	const char* glsl_version;

};
