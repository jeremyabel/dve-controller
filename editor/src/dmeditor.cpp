#include <cstdlib>
#include "dmeditor.h"

DMEditor::DMEditor()
{
	gui.Editor = this;
}

void DMEditor::Run()
{
	bool done = false;
	while (!done) 
	{
		if (!gui.Render())
		{
			done = true;
		}
	}
}