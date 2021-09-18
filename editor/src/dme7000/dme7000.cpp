#include <stdio.h>

#include "dme7000.h"
#include "imgui.h"

DME7000::DME7000()
{
}

DME7000::~DME7000()
{
}

void DME7000::DrawGUI()
{
	ImGui::Begin("Hello, world!");
	//if (ImGui::Checkbox(TestParameter.name, &TestParameter.value)) OnParameterChanged(TestParameter);
	ImGui::End();
}

void DME7000::OnParameterChanged(const Parameter changedParameter)
{
	printf("Parameter changed: %s\n", changedParameter.Name);
}

