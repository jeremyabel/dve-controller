#pragma once

enum BackgroundSources : unsigned char
{
	BackgroundSources_FlatColor			= 0x00,
	BackgroundSources_HueRot			= 0x01,
	BackgroundSources_SuperBlack		= 0x02,
	BackgroundSources_MixColor			= 0x03,
	BackgroundSources_ExtVideo			= 0x04
};