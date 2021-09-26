#pragma once

struct DME7000;

struct GraphicGUI 
{ 
	struct GraphicUserDefinedFlags
	{
		bool LocalAxis  = false;
		bool GlobalAxis = false;
		bool AxisName   = false;
		bool ChannelId  = false;
		bool WireFrame  = false;
		bool Grid       = false;

		void OnFlagChanged(DME7000* DME);
	};

	struct GraphicShadowFlags
	{
		bool Axis     = false;
		bool AxisName = false;

		void OnFlagChanged(DME7000* DME);
	};

	struct GraphicSubPictureFlags
	{
		bool Axis      = false;
		bool AxisName  = false;
		bool ChannelId = false;
		bool WireFrame = false;

		void OnFlagChanged(DME7000* DME);
	};

	struct GraphicModeFlags
	{
		bool Reduce    = false;
		bool AutoErase = false;

		void OnFlagChanged(DME7000* DME);
	};

	GraphicUserDefinedFlags userDefinedFlags;
	GraphicSubPictureFlags subPictureFlags;
	GraphicShadowFlags shadowFlags;
	GraphicModeFlags modeFlags;

	DME7000* DME = nullptr;

	GraphicGUI(DME7000* inDME);

	void Init();
	void DrawGUI();
};
