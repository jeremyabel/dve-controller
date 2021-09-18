#pragma once

#include "../device.h"
#include "types.h"

#define PARAM(MODULE, ID, TYPE, NAME) Parameter_ ## TYPE NAME = Parameter_ ## TYPE(MODULE, ID, #NAME);
#define PARAM_F(MODULE, ID, FLAGS, TYPE, NAME)  Parameter_ ## TYPE NAME = Parameter_ ## TYPE(MODULE, ID, #NAME, FLAGS);
#define PARAM_LIGHT(MODULE, LIGHT, ID, TYPE, NAME)  Parameter_ ## TYPE ## _Light NAME = Parameter_ ## TYPE ## _Light(MODULE, LIGHT, ID, #NAME); 
#define PARAM_VIDEO(MODULE, ID, SOURCE, TYPE, NAME) Parameter_ ## TYPE ## _Video NAME = Parameter_ ## TYPE ## _Video(MODULE, SOURCE, ID, #NAME);

struct DME7000 : public Device
{
	DME7000();
	~DME7000();

	void DrawGUI();
	void OnParameterChanged(Parameter changedParameter);

	// TODO
	//  - 38.1 Duality 3D Control

	// 11 BACKGROUND
	PARAM(0x90, 0x10, Bool, Background_Enable);
	PARAM(0x92, 0x10, Enum, Background_Source);
	PARAM(0xAD, 0x04, S16,  Background_Color_Lum);
	PARAM(0xAD, 0x05, S16,  Background_Color_Sat);
	PARAM(0xAD, 0x06, S16,  Background_Color_Hue);
	PARAM(0xAD, 0x07, S16,  Background_Color_Speed);
	PARAM_F(0xAB, 0x25, ParameterFlags_Global, S16, Background_SuperBlack_Level);

	// 12 BORDER
	PARAM(0x90, 0x12, Bool, Border_Enable);
	PARAM(0xA5, 0x01, S16,  Border_Width_Left);
	PARAM(0xA5, 0x02, S16,  Border_Width_Right);
	PARAM(0xA5, 0x03, S16,  Border_Width_Top);
	PARAM(0xA5, 0x04, S16,  Border_Width_Bottom);
	PARAM(0xA5, 0x14, S16,  Border_Density);
	PARAM(0x92, 0x13, Enum, Border_Source);
	PARAM(0xAD, 0x00, S16,  Border_Color_Lum);
	PARAM(0xAD, 0x01, S16,  Border_Color_Sat);
	PARAM(0xAD, 0x02, S16,  Border_Color_Hue);
	PARAM(0xAD, 0x03, S16,  Border_Color_Speed);
	PARAM(0x90, 0x14, Bool, Border_Soft_Enable);
	PARAM(0xA5, 0x0F, S16,  Border_Soft_Inner);
	PARAM(0xA5, 0x0A, S16,  Border_Soft_Outer); 

	// 13 CROP
	PARAM(0x90, 0x16, Bool, Crop_Enable);
	PARAM(0x92, 0x16, Bool, Crop_Invert);
	PARAM(0xA5, 0x1A, S16,  Crop_Left);
	PARAM(0xA5, 0x1B, S16,  Crop_Right);
	PARAM(0xA5, 0x1C, S16,  Crop_Top);
	PARAM(0xA5, 0x1D, S16,  Crop_Bottom);

	// 14 DROP SHADOW
	PARAM(0x90, 0x20, Bool, DropShadow_Enable);
	PARAM(0x92, 0x20, Enum, DropShadow_Source);
	PARAM(0x92, 0x25, Enum, DropShadow_Mode);
	PARAM(0xA5, 0x20, S16,  DropShadow_2D_Position_X);
	PARAM(0xA5, 0x21, S16,  DropShadow_2D_Position_Y);
	PARAM(0xA5, 0x22, S16,  DropShadow_2D_Density);
	PARAM(0xAD, 0x08, S16,  DropShadow_Color_Lum);
	PARAM(0xAD, 0x09, S16,  DropShadow_Color_Sat);
	PARAM(0xAD, 0x0A, S16,  DropShadow_Color_Hue);
	PARAM(0xAD, 0x0B, S16,  DropShadow_Color_Speed);
	PARAM(0x92, 0x28, Enum, DropShadow_3D_Light_Source);
	PARAM(0x92, 0x26, Enum, DropShadow_3D_Density_Type);
	PARAM(0xA5, 0x24, S16,  DropShadow_3D_Density_Flat);
	PARAM(0xA5, 0x26, S16,  DropShadow_3D_Density_Depth_Offset);
	PARAM(0xA5, 0x25, S16,  DropShadow_3D_Density_Depth_Gain);
	PARAM(0x92, 0x27, Enum, DropShadow_3D_Softness_Type);
	PARAM(0xA5, 0x27, S16,  DropShadow_3D_Softness_Flat);
	PARAM(0xA5, 0x29, S16,  DropShadow_3D_Density_Softness_Offset);
	PARAM(0xA5, 0x28, S16,  DropShadow_3D_Density_Softness_Gain);
	PARAM_LIGHT(0xB9, 0x02, 0x08, F32, DropShadow_3D_Light_Position_X);
	PARAM_LIGHT(0xB9, 0x02, 0x09, F32, DropShadow_3D_Light_Position_Y);
	PARAM_LIGHT(0xB9, 0x02, 0x0A, F32, DropShadow_3D_Light_Position_Z);
	PARAM_LIGHT(0xB9, 0x01, 0x08, F32, DropShadow_3D_Shadow_Position_X);
	PARAM_LIGHT(0xB9, 0x01, 0x09, F32, DropShadow_3D_Shadow_Position_Y);
	PARAM_LIGHT(0xB9, 0x01, 0x0A, F32, DropShadow_3D_Shadow_Position_Z);
	PARAM_LIGHT(0xB9, 0x01, 0x10, F32, DropShadow_3D_Shadow_Rotation_X);
	PARAM_LIGHT(0xB9, 0x01, 0x11, F32, DropShadow_3D_Shadow_Rotation_Y);
	PARAM_LIGHT(0xB9, 0x01, 0x12, F32, DropShadow_3D_Shadow_Rotation_Z);

	// 15 KEY BORDER
	PARAM(0x90, 0x17, Bool, KeyBorder_Enable);
	PARAM(0x92, 0x1A, Enum, KeyBorder_Outline);
	PARAM(0xA9, 0xBC, S16,  KeyBorder_Filter);
	PARAM(0xA9, 0xB8, S16,  KeyBorder_Width);
	PARAM(0xA9, 0xB9, S16,  KeyBorder_Soft);
	PARAM(0xA9, 0xBB, S16,  KeyBorder_Density);
	PARAM(0x92, 0x1B, Enum, KeyBorder_Source);
	PARAM(0xAD, 0x68, S16,  KeyBorder_Color_Lum);
	PARAM(0xAD, 0x69, S16,  KeyBorder_Color_Sat);
	PARAM(0xAD, 0x6A, S16,  KeyBorder_Color_Hue);
	PARAM(0xAD, 0x6B, S16,  KeyBorder_Color_Speed);

	// 16 WIPE CROP
	PARAM(0x90, 0x80, Bool, WipeCrop_Enable);
	PARAM(0x90, 0x82, Bool, WipeCrop_Edge_Enable);
	PARAM(0xA9, 0x10, S16,  WipeCrop_Edge_Width);
	PARAM(0x92, 0x81, Enum, WipeCrop_Edge_Source);
	PARAM(0xAD, 0x14, S16,  WipeCrop_Edge_Color_Lum);
	PARAM(0xAD, 0x15, S16,  WipeCrop_Edge_Color_Sat);
	PARAM(0xAD, 0x16, S16,  WipeCrop_Edge_Color_Hue);
	PARAM(0xAD, 0x17, S16,  WipeCrop_Edge_Color_Speed);
	PARAM(0xA9, 0x11, S16,  WipeCrop_Edge_Soft_Inner);
	PARAM(0xA9, 0x12, S16,  WipeCrop_Edge_Soft_Outer);

	// 17 COLOR MIX
	PARAM(0xAD, 0x18, S16,  ColorMix_Color1_Lum);
	PARAM(0xAD, 0x19, S16,  ColorMix_Color1_Sat);
	PARAM(0xAD, 0x1A, S16,  ColorMix_Color1_Hue);
	PARAM(0xAD, 0x1B, S16,  ColorMix_Color1_Speed);
	PARAM(0xAD, 0x1C, S16,  ColorMix_Color2_Lum);
	PARAM(0xAD, 0x1D, S16,  ColorMix_Color2_Sat);
	PARAM(0xAD, 0x1E, S16,  ColorMix_Color2_Hue);
	PARAM(0xAD, 0x1F, S16,  ColorMix_Color2_Speed);
	PARAM(0x90, 0xB6, Bool, ColorMix_Color1_Hue_Rot);
	PARAM(0x90, 0xB7, Bool, ColorMix_Color2_Hue_Rot);
	PARAM(0xA9, 0x30, S16,  ColorMix_Position_X);
	PARAM(0xA9, 0x31, S16,  ColorMix_Position_Y);
	PARAM(0xA9, 0x32, S16,  ColorMix_Size);
	PARAM(0xA9, 0x33, S16,  ColorMix_Soft);
	PARAM(0xA9, 0x34, S16,  ColorMix_Aspect);
	PARAM(0xA9, 0x35, S16,  ColorMix_Angle);
	PARAM(0xA9, 0x36, S16,  ColorMix_Speed);
	PARAM(0x92, 0xB2, Bool, ColorMix_Rotation);
	PARAM(0x90, 0xB2, Bool, ColorMix_Modify_Multi_Pattern);
	PARAM(0xA9, 0x40, S16,  ColorMix_Modify_Number_H);
	PARAM(0xA9, 0x41, S16,  ColorMix_Modify_Number_V);
	PARAM(0xA9, 0x42, Enum, ColorMix_Modify_Number_Shift);
	PARAM(0x90, 0xB5, Bool, ColorMix_Modify_Emboss);
	PARAM(0xA9, 0x3D, S16,  ColorMix_Modify_Shape_Strength);
	PARAM(0xA9, 0x3F, S16,  ColorMix_Modify_Shape_Width);
	PARAM(0x92, 0xB4, Enum, ColorMix_Modify_Type);
	PARAM(0x91, 0x10, S16,  ColorMix_Pattern_Number);
	PARAM(0x92, 0x3B, Enum, ColorMix_Pattern_Source);

	// 18 BEVELED EDGE
	PARAM(0x90, 0x18, Bool, BeveledEdge_Enable);
	PARAM(0x92, 0x17, Enum, BeveledEdge_Pattern);
	PARAM(0x92, 0x18, Enum, BeveledEdge_Mode);
	PARAM(0xA9, 0xB3, S16,  BeveledEdge_Width_H);
	PARAM(0xA9, 0xB4, S16,  BeveledEdge_Width_V);
	PARAM(0x90, 0x1A, Bool, BeveledEdge_Softness_Enable);
	PARAM(0xA9, 0xA3, S16,  BeveledEdge_Softness_Inner);
	PARAM(0xA9, 0xA5, S16,  BeveledEdge_Softness_Bound);
	PARAM(0xA9, 0xAA, S16,  BeveledEdge_Intensity_Left);
	PARAM(0xA9, 0xAB, S16,  BeveledEdge_Intensity_Right);
	PARAM(0xA9, 0xAC, S16,  BeveledEdge_Intensity_Top);
	PARAM(0xA9, 0xAD, S16,  BeveledEdge_Intensity_Bottom);
	PARAM(0xA9, 0xB5, S16,  BeveledEdge_Mix_Gain);
	PARAM(0x92, 0x19, Enum, BeveledEdge_Source);
	PARAM(0xAD, 0x50, S16,  BeveledEdge_Left_Color_Lum);
	PARAM(0xAD, 0x51, S16,  BeveledEdge_Left_Color_Sat);
	PARAM(0xAD, 0x52, S16,  BeveledEdge_Left_Color_Hue);
	PARAM(0xAD, 0x53, S16,  BeveledEdge_Left_Color_Speed);
	PARAM(0xAD, 0x54, S16,  BeveledEdge_Right_Color_Lum);
	PARAM(0xAD, 0x55, S16,  BeveledEdge_Right_Color_Sat);
	PARAM(0xAD, 0x56, S16,  BeveledEdge_Right_Color_Hue);
	PARAM(0xAD, 0x57, S16,  BeveledEdge_Right_Color_Speed);
	PARAM(0xAD, 0x58, S16,  BeveledEdge_Top_Color_Lum);
	PARAM(0xAD, 0x59, S16,  BeveledEdge_Top_Color_Sat);
	PARAM(0xAD, 0x5A, S16,  BeveledEdge_Top_Color_Hue);
	PARAM(0xAD, 0x5B, S16,  BeveledEdge_Top_Color_Speed);
	PARAM(0xAD, 0x5C, S16,  BeveledEdge_Bottom_Color_Lum);
	PARAM(0xAD, 0x5D, S16,  BeveledEdge_Bottom_Color_Sat);
	PARAM(0xAD, 0x5E, S16,  BeveledEdge_Bottom_Color_Hue);
	PARAM(0xAD, 0x5F, S16,  BeveledEdge_Bottom_Color_Speed);

	// 21 INPUT FREEZE
	PARAM(0x90, 0x30, Bool, InputFreeze_Enable_A);
	PARAM(0x90, 0x33, Bool, InputFreeze_Enable_B);
	PARAM(0x92, 0x31, Enum, InputFreeze_Mode_A);
	PARAM(0x92, 0x34, Enum, InputFreeze_Mode_B);
	PARAM(0xA3, 0x31, S16,  InputFreeze_TimeStrobe_Duration);
	PARAM(0xA3, 0x32, S16,  InputFreeze_TimeStrobe_Live);
	PARAM(0xA3, 0x33, S16,  InputFreeze_Film_Amount);
	PARAM(0x92, 0x30, Enum, InputFreeze_Delegation);
	PARAM(0x92, 0x32, Enum, InputFreeze_Video_Timing);
	PARAM(0x92, 0x33, Enum, InputFreeze_Key_Timing);

	// 22 MOTION DECAY
	PARAM(0x92, 0x4B, Enum, MotionDecay_Mix_Mode);

	// 23 TRAIL
	PARAM(0xA5, 0x43, S16, Trail_Duration);
	PARAM(0xA5, 0x45, S16, Trail_Live);

	// 24 WIND
	PARAM(0x92, 0x4D, Enum, Wind_Mode);
	PARAM(0xA5, 0x4A, S16,  Wind_Shift_H);
	PARAM(0xA5, 0x4B, S16,  Wind_Shift_V);
	PARAM(0x90, 0x4E, Bool, Wind_ModulationH_Enable);
	PARAM(0xA9, 0x90, S16,  Wind_ModulationH_Amplitude);
	PARAM(0xA9, 0x91, S16,  Wind_ModulationH_Frequency);
	PARAM(0x90, 0x4F, Bool, Wind_ModulationV_Enable);
	PARAM(0xA9, 0x94, S16,  Wind_ModulationV_Amplitude);
	PARAM(0xA9, 0x95, S16,  Wind_ModulationV_Frequency);

	// 25 KEYFRAME STROBE
	PARAM(0x90, 0x44, Bool, KeyframeStrobe_Strobe_Disable);

	// 26 MULTI FREEZE
	PARAM(0x92, 0x44, Enum, MultiFreeze_Number);

	// 27 UTILITY FREEZE
	PARAM(0x90, 0x38, Bool, UtilityFreeze_Input_Freeze);
	PARAM(0x90, 0x39, Bool, UtilityFreeze_Last_Freeze);
	PARAM(0x90, 0x3A, Bool, UtilityFreeze_Output_Freeze);
	PARAM(0x92, 0x38, Enum, UtilityFreeze_Input_Freeze_Source);
	PARAM(0x82, 0x14, Bool, UtilityFreeze_Output_Freeze_Preview);
	PARAM(0x92, 0x39, Enum, UtilityFreeze_Video_Timing);

	// 31 MULTI MOVE
	PARAM(0x90, 0x52, Bool, MultiMove_Enable);
	PARAM(0xA5, 0x69, S16,  MultiMove_Position_X);
	PARAM(0xA5, 0x6A, S16,  MultiMove_Position_Y);
	PARAM(0xA5, 0x6B, S16,  MultiMove_Size);
	PARAM(0xA5, 0x6C, S16,  MultiMove_Aspect);
	PARAM(0x92, 0x52, Bool, MultiMove_Invert_H);
	PARAM(0x92, 0x53, Bool, MultiMove_Invert_V);
	PARAM(0x92, 0x57, Bool, MultiMove_Shift_H);

	// 32 DEFOCUS
	PARAM(0x90, 0x57, Bool, Defocus_Enable);
	PARAM(0xA5, 0x6E, S16,  Defocus_Video_H);
	PARAM(0xA5, 0x70, S16,  Defocus_Video_V);
	PARAM(0xA5, 0x6F, S16,  Defocus_Key_H);
	PARAM(0xA5, 0x71, S16,  Defocus_Key_V);
	PARAM(0xA5, 0x6E, Bool, Defocus_Clean);

	// 33 BLUR
	PARAM(0x90, 0x56, Bool, Blur_Enable);
	PARAM(0xA5, 0x73, S16,  Blur_Video_Y_H);
	PARAM(0xA5, 0x75, S16,  Blur_Video_Y_V);
	PARAM(0xA5, 0x77, S16,  Blur_Video_C_H);
	PARAM(0xA5, 0x78, S16,  Blur_Video_C_V);
	PARAM(0xA5, 0x74, S16,  Blur_Key_H);
	PARAM(0xA5, 0x76, S16,  Blur_Key_V);

	// 34 DIM & FADE
	PARAM(0x90, 0x55, Bool, DimFade_Dim_Enable);
	PARAM(0xA5, 0x79, S16,  DimFade_Dim_Level_Start);
	PARAM(0xA5, 0x7A, S16,  DimFade_Dim_Level_Gain);
	PARAM(0x90, 0x59, Bool, DimFade_Dim_Color_Enable);
	PARAM(0x92, 0x58, Enum, DimFade_Dim_Source);
	PARAM(0xAD, 0x28, S16,  DimFade_Dim_Color_Lum);
	PARAM(0xAD, 0x29, S16,  DimFade_Dim_Color_Sat);
	PARAM(0xAD, 0x2A, S16,  DimFade_Dim_Color_Hue);
	PARAM(0xAD, 0x2B, S16,  DimFade_Dim_Color_Speed);
	PARAM(0x90, 0x54, S16,  DimFade_Fade_Enable);
	PARAM(0xA5, 0x7C, S16,  DimFade_Fade_Level_Start);
	PARAM(0xA5, 0x7D, S16,  DimFade_Fade_Level_Gain);

	// 35 GLOW
	PARAM(0x91, 0x30, Bool, Glow_Enable);
	PARAM(0xA5, 0xE0, S16,  Glow_Key_Process_Clip);
	PARAM(0xA5, 0xE1, S16,  Glow_Key_Process_Gain);
	PARAM(0xA5, 0xE2, S16,  Glow_Key_Process_Soft);
	PARAM(0x92, 0x5A, Enum, Glow_Source);
	PARAM(0xAD, 0x6C, S16,  Glow_Color_Lum);
	PARAM(0xAD, 0x6D, S16,  Glow_Color_Sat);
	PARAM(0xAD, 0x6E, S16,  Glow_Color_Hue);
	PARAM(0xAD, 0x6F, S16,  Glow_Color_Speed);
	PARAM(0x90, 0x31, Bool, Glow_Invert);

	// 36 BRICK
	PARAM(0x91, 0x00, Bool, Brick_Enable);
	PARAM(0x92, 0xD2, Enum, Brick_Mode);
	PARAM(0xA5, 0xD0, S16,  Brick_Height);
	PARAM(0x91, 0x02, Bool, Brick_Side_A_Enable);
	PARAM(0x91, 0x03, Bool, Brick_Side_B_Enable);
	PARAM(0xA5, 0xD1, S16,  Brick_Crop_H_Left);
	PARAM(0xA5, 0xD2, S16,  Brick_Crop_H_Right);
	PARAM(0xA5, 0xD3, S16,  Brick_Crop_V_Top);
	PARAM(0xA5, 0xD4, S16,  Brick_Crop_V_Bottom);
	PARAM(0x92, 0xD0, Enum, Brick_Side_A_Source);
	PARAM(0x92, 0xD1, Enum, Brick_Side_B_Source);
	PARAM(0xAD, 0x60, S16,  Brick_Side_A_Color_Lum);
	PARAM(0xAD, 0x61, S16,  Brick_Side_A_Color_Sat);
	PARAM(0xAD, 0x62, S16,  Brick_Side_A_Color_Hue);
	PARAM(0xAD, 0x63, S16,  Brick_Side_A_Color_Speed);
	PARAM(0xAD, 0x64, S16,  Brick_Side_B_Color_Lum);
	PARAM(0xAD, 0x65, S16,  Brick_Side_B_Color_Sat);
	PARAM(0xAD, 0x66, S16,  Brick_Side_B_Color_Hue);
	PARAM(0xAD, 0x67, S16,  Brick_Side_B_Color_Speed);
	PARAM(0x91, 0x04, Bool, Brick_Side_A_Front_Invert_H);
	PARAM(0x91, 0x05, Bool, Brick_Side_A_Front_Invert_V);
	PARAM(0x91, 0x06, Bool, Brick_Side_A_Back_Invert_H);
	PARAM(0x91, 0x07, Bool, Brick_Side_A_Back_Invert_V);
	PARAM(0x91, 0x08, Bool, Brick_Side_B_Front_Invert_H);
	PARAM(0x91, 0x09, Bool, Brick_Side_B_Front_Invert_V);
	PARAM(0x91, 0x0A, Bool, Brick_Side_B_Back_Invert_H);
	PARAM(0x91, 0x0B, Bool, Brick_Side_B_Back_Invert_V);
	PARAM(0xA9, 0x58, S16,  Brick_Side_A_Adjust_H);
	PARAM(0xA9, 0x59, S16,  Brick_Side_A_Adjust_V);
	PARAM(0xA9, 0x5A, S16,  Brick_Side_B_Adjust_H);
	PARAM(0xA9, 0x5B, S16,  Brick_Side_B_Adjust_V);

	// 38 DUALITY
	PARAM(0x91, 0xF0, Bool, Duality_Enable);
	PARAM(0x92, 0xF1, Enum, Duality_Priority);

	// 39.1 SUB PICTURE BORDER
	PARAM_F(0x91, 0xF1, ParameterFlags_SubPicture, Bool, SubPicture_Border_Enable);
	PARAM_F(0xA9, 0xE1, ParameterFlags_SubPicture, S16,  SubPicture_Border_Width_Left);
	PARAM_F(0xA9, 0xE2, ParameterFlags_SubPicture, S16,  SubPicture_Border_Width_Right);
	PARAM_F(0xA9, 0xE3, ParameterFlags_SubPicture, S16,  SubPicture_Border_Width_Top);
	PARAM_F(0xA9, 0xE4, ParameterFlags_SubPicture, S16,  SubPicture_Border_Width_Bottom);
	PARAM_F(0x92, 0xF0, ParameterFlags_SubPicture, Enum, SubPicture_Border_Source);
	PARAM_F(0xAD, 0x90, ParameterFlags_SubPicture, S16,  SubPicture_Border_Color_Lum);
	PARAM_F(0xAD, 0x91, ParameterFlags_SubPicture, S16,  SubPicture_Border_Color_Sat);
	PARAM_F(0xAD, 0x92, ParameterFlags_SubPicture, S16,  SubPicture_Border_Color_Hue);
	PARAM_F(0xAD, 0x93, ParameterFlags_SubPicture, S16,  SubPicture_Border_Color_Speed);

	// 39.2 SUB PICTURE CROP
	PARAM_F(0x91, 0xF2, ParameterFlags_SubPicture, Bool, SubPicture_Crop_Enable);
	PARAM_F(0xA9, 0xE6, ParameterFlags_SubPicture, S16,  SubPicture_Crop_Left);
	PARAM_F(0xA9, 0xE7, ParameterFlags_SubPicture, S16,  SubPicture_Crop_Right);
	PARAM_F(0xA9, 0xE8, ParameterFlags_SubPicture, S16,  SubPicture_Crop_Top);
	PARAM_F(0xA9, 0xE9, ParameterFlags_SubPicture, S16,  SubPicture_Crop_Bottom);

	// 39.3 SUB PICTURE BEVELED EDGE
	PARAM_F(0x91, 0xE8, ParameterFlags_SubPicture, Bool, SubPicture_BeveledEdge_Enable);
	PARAM_F(0x92, 0xF4, ParameterFlags_SubPicture, Enum, SubPicture_BeveledEdge_Pattern);
	PARAM_F(0x92, 0xF5, ParameterFlags_SubPicture, Enum, SubPicture_BeveledEdge_Mode);
	PARAM_F(0xA9, 0xF0, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Width_H);
	PARAM_F(0xA9, 0xF1, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Width_V);
	PARAM_F(0x91, 0xE9, ParameterFlags_SubPicture, Bool, SubPicture_BeveledEdge_Softness_Enable);
	PARAM_F(0xA9, 0xF2, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Softness_Inner);
	PARAM_F(0xA9, 0xF3, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Softness_Bound);
	PARAM_F(0xA9, 0xF4, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Intensity_Left);
	PARAM_F(0xA9, 0xF5, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Intensity_Right);
	PARAM_F(0xA9, 0xF6, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Intensity_Top);
	PARAM_F(0xA9, 0xF7, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Intensity_Bottom);
	PARAM_F(0xA9, 0xF8, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Mix_Gain);
	PARAM_F(0x92, 0xF6, ParameterFlags_SubPicture, Enum, SubPicture_BeveledEdge_Source);
	PARAM_F(0xAD, 0x98, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Left_Color_Lum);
	PARAM_F(0xAD, 0x99, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Left_Color_Sat);
	PARAM_F(0xAD, 0x9A, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Left_Color_Hue);
	PARAM_F(0xAD, 0x9B, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Left_Color_Speed);
	PARAM_F(0xAD, 0x9C, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Right_Color_Lum);
	PARAM_F(0xAD, 0x9D, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Right_Color_Sat);
	PARAM_F(0xAD, 0x9E, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Right_Color_Hue);
	PARAM_F(0xAD, 0x9F, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Right_Color_Speed);
	PARAM_F(0xAD, 0xA0, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Top_Color_Lum);
	PARAM_F(0xAD, 0xA1, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Top_Color_Sat);
	PARAM_F(0xAD, 0xA2, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Top_Color_Hue);
	PARAM_F(0xAD, 0xA3, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Top_Color_Speed);
	PARAM_F(0xAD, 0xA4, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Bottom_Color_Lum);
	PARAM_F(0xAD, 0xA5, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Bottom_Color_Sat);
	PARAM_F(0xAD, 0xA6, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Bottom_Color_Hue);
	PARAM_F(0xAD, 0xA7, ParameterFlags_SubPicture, S16,  SubPicture_BeveledEdge_Bottom_Color_Speed);

	// 39.5 SUB PICTURE POSTER & NEGATIVE
	PARAM_F(0x91, 0xE0, ParameterFlags_SubPicture, Bool, SubPicture_PosterNegative_Posterization_Enable);
	PARAM_F(0xA9, 0xDC, ParameterFlags_SubPicture, S16,  SubPicture_PosterNegative_Posterization_Value);
	PARAM_F(0x91, 0xE1, ParameterFlags_SubPicture, Bool, SubPicture_PosterNegative_Solarization_Enable);
	PARAM_F(0xA9, 0xDD, ParameterFlags_SubPicture, S16,  SubPicture_PosterNegative_Solarization_Value);
	PARAM_F(0x91, 0xE2, ParameterFlags_SubPicture, Bool, SubPicture_PosterNegative_Negative_Y_Enable);
	PARAM_F(0x91, 0xE3, ParameterFlags_SubPicture, Bool, SubPicture_PosterNegative_Negative_C_Enable);

	// 39.6 SUB PICTURE SEPIA & MONO
	PARAM_F(0x91, 0xE4, ParameterFlags_SubPicture, Bool, SubPicture_SepiaMono_Sepia_Enable);
	PARAM_F(0xA9, 0xDE, ParameterFlags_SubPicture, S16,  SubPicture_SepiaMono_Sepia_Y);
	PARAM_F(0xA9, 0xDF, ParameterFlags_SubPicture, S16,  SubPicture_SepiaMono_Sepia_C);
	PARAM_F(0x92, 0xF3, ParameterFlags_SubPicture, Enum, SubPicture_SepiaMono_Source);
	PARAM_F(0xAD, 0x94, ParameterFlags_SubPicture, S16,  SubPicture_SepiaMono_Color_Lum);
	PARAM_F(0xAD, 0x95, ParameterFlags_SubPicture, S16,  SubPicture_SepiaMono_Color_Sat);
	PARAM_F(0xAD, 0x96, ParameterFlags_SubPicture, S16,  SubPicture_SepiaMono_Color_Hue);
	PARAM_F(0xAD, 0x97, ParameterFlags_SubPicture, S16,  SubPicture_SepiaMono_Color_Speed);
	PARAM_F(0x91, 0xE5, ParameterFlags_SubPicture, Bool, SubPicture_SepiaMono_Mono_Enable);

	// 39.7 SUB PICTURE CONTRAST
	PARAM_F(0x91, 0xE6, ParameterFlags_SubPicture, Bool, SubPicture_Contrast_Y_Enable);
	PARAM_F(0xA9, 0xF9, ParameterFlags_SubPicture, S16,  SubPicture_Contrast_Y_Clip);
	PARAM_F(0xA9, 0xFA, ParameterFlags_SubPicture, S16,  SubPicture_Contrast_Y_Gain);
	PARAM_F(0xA9, 0xFB, ParameterFlags_SubPicture, S16,  SubPicture_Contrast_Y_Offset);
	PARAM_F(0x91, 0xE7, ParameterFlags_SubPicture, Bool, SubPicture_Contrast_C_Enable);
	PARAM_F(0xA9, 0xFC, ParameterFlags_SubPicture, S16,  SubPicture_Contrast_C_Gain);
	PARAM_F(0xA9, 0xFD, ParameterFlags_SubPicture, S16,  SubPicture_Contrast_C_Offset);

	// 41 POSTER & NEGATIVE
	PARAM(0x90, 0x65, Bool, PosterNegative_Posterization_Enable);
	PARAM(0xA5, 0x90, S16,  PosterNegative_Posterization_Value);
	PARAM(0x90, 0x64, Bool, PosterNegative_Solarization_Enable);
	PARAM(0xA5, 0x91, S16,  PosterNegative_Solarization_Value);
	PARAM(0x90, 0x66, Bool, PosterNegative_Negative_Y_Enable);
	PARAM(0x90, 0x67, Bool, PosterNegative_Negative_C_Enable);

	// 42 SEPIA & MONO
	PARAM(0x90, 0x60, Bool, SepiaMono_Sepia_Enable);
	PARAM(0xA5, 0x96, S16,  SepiaMono_Sepia_Y);
	PARAM(0xA5, 0x97, S16,  SepiaMono_Sepia_C);
	PARAM(0x92, 0x61, Enum, SepiaMono_Source);
	PARAM(0xAD, 0x24, S16,  SepiaMono_Color_Lum);
	PARAM(0xAD, 0x25, S16,  SepiaMono_Color_Sat);
	PARAM(0xAD, 0x26, S16,  SepiaMono_Color_Hue);
	PARAM(0xAD, 0x27, S16,  SepiaMono_Color_Speed);
	PARAM(0x92, 0x70, Bool, SepiaMono_Mono_Enable);

	// 43 CONTRAST
	PARAM(0x90, 0x62, Bool, Contrast_Y_Enable);
	PARAM(0xA5, 0xA0, S16,  Contrast_Y_Clip);
	PARAM(0xA5, 0x93, S16,  Contrast_Y_Gain);
	PARAM(0xA5, 0x92, S16,  Contrast_Y_Offset);
	PARAM(0x90, 0x63, Bool, Contrast_C_Enable);
	PARAM(0xA5, 0x95, S16,  Contrast_C_Gain);
	PARAM(0xA5, 0x94, S16,  Contrast_C_Offset);

	// 44 MOSAIC & NOISE
	PARAM(0x90, 0x68, Bool, MosaicNoise_Enable);
	PARAM(0x92, 0x62, Enum, MosaicNoise_Mode);
	PARAM(0xA5, 0x9A, S16,  MosaicNoise_Size);
	PARAM(0xA5, 0x9B, S16,  MosaicNoise_Aspect);
	PARAM(0x92, 0x60, Bool, MosaicNoise_Random_Enable);
	PARAM(0xA5, 0xA2, S16,  MosaicNoise_Random_Speed);
	PARAM(0xA5, 0xA1, S16,  MosaicNoise_Random_Pattern);
	PARAM(0xA5, 0x9E, S16,  MosaicNoise_Random_Amount);
	PARAM(0x92, 0x63, Bool, MosaicNoise_Random_Lock);
	PARAM(0x90, 0x6E, Bool, MosaicNoise_Noise_Enable);
	PARAM(0xA5, 0xA3, S16,  MosaicNoise_Noise_Clip);
	PARAM(0xA5, 0xA4, S16,  MosaicNoise_Noise_Gain);
	PARAM(0x90, 0x6F, Bool, MosaicNoise_Noise_Lock);

	// 45 MASK
	PARAM(0x90, 0x81, Bool, Mask_Modify_Enable);
	PARAM(0x92, 0x8F, Enum, Mask_Destination);

	// 46 SKETCH
	PARAM(0x90, 0x69, Bool, Sketch_Enable);
	PARAM(0x92, 0x65, Enum, Sketch_Mode);
	PARAM(0xA5, 0x84, S16,  Sketch_Contour_Mix);
	PARAM(0xA5, 0x85, S16,  Sketch_Contour_Clip);
	PARAM(0xA5, 0x86, S16,  Sketch_Contour_Gain);
	PARAM(0x92, 0x67, Enum, Sketch_Relief_Pattern);
	PARAM(0xA5, 0x8F, S16,  Sketch_Relief_Angle);
	PARAM(0x92, 0x68, Enum, Sketch_Chroma_Type);
	PARAM(0xA5, 0x87, S16,  Sketch_Chroma_Gain);
	PARAM(0xAD, 0x75, S16,  Sketch_Chroma_Sat);
	PARAM(0xAD, 0x76, S16,  Sketch_Chroma_Hue);
	PARAM(0xAD, 0x77, S16,  Sketch_Chroma_Speed);
	PARAM(0x90, 0x6A, Bool, Sketch_Negative);
	PARAM(0x92, 0x64, Enum, Sketch_Edge_Mode);
	PARAM(0xAD, 0x4C, S16,  Sketch_Edge_Lum);
	PARAM(0xAD, 0x4D, S16,  Sketch_Edge_Sat);
	PARAM(0xAD, 0x4E, S16,  Sketch_Edge_Hue);
	PARAM(0xAD, 0x4F, S16,  Sketch_Edge_Speed);
	PARAM(0x92, 0x66, Enum, Sketch_Canvas_Mode);
	PARAM(0xAD, 0x74, S16,  Sketch_Canvas_Lum);
	PARAM(0xAD, 0x75, S16,  Sketch_Canvas_Sat);
	PARAM(0xAD, 0x76, S16,  Sketch_Canvas_Hue);
	PARAM(0xAD, 0x77, S16,  Sketch_Canvas_Speed);

	// 47 METAL EFFECT
	PARAM(0x91, 0x86, Bool, MetalEffect_Enable);
	PARAM(0x92, 0xE6, Enum, MetalEffect_Input);
	PARAM(0x92, 0xE7, Enum, MetalEffect_Mode);
	PARAM(0xB5, 0x20, S16,  MetalEffect_Mix);
	PARAM(0xB5, 0x23, S16,  MetalEffect_Modify_Clip);
	PARAM(0xB5, 0x24, S16,  MetalEffect_Modify_Gain);
	PARAM(0xB5, 0x25, S16,  MetalEffect_Modify_Offset);
	PARAM(0x91, 0x87, Bool, MetalEffect_PhaseRotation_Enable);
	PARAM(0xB5, 0x21, S16,  MetalEffect_PhaseRotation_Phase);
	PARAM(0xB5, 0x22, S16,  MetalEffect_PhaseRotation_Speed);
	PARAM(0x91, 0x88, Bool, MetalEffect_V_Modulation);

	// 48 COLOR CORRECTION
	PARAM(0x91, 0x80, Bool, ColorCorrection_Enable);
	PARAM(0x92, 0xE0, Enum, ColorCorrection_Input);
	PARAM(0x91, 0x81, Bool, ColorCorrection_InputAdjust_Enable);
	PARAM(0xAD, 0xC0, S16,  ColorCorrection_InputAdjust_Gain_Y);
	PARAM(0xAD, 0xC1, S16,  ColorCorrection_InputAdjust_Gain_C);
	PARAM(0xAD, 0xC2, S16,  ColorCorrection_InputAdjust_Hue);
	PARAM(0xAD, 0xC3, S16,  ColorCorrection_InputAdjust_Black);
	PARAM(0x91, 0x82, Bool, ColorCorrection_Primary_Enable);
	PARAM(0xB5, 0x50, S16,  ColorCorrection_Primary_Curve_R_1_X);
	PARAM(0xB5, 0x51, S16,  ColorCorrection_Primary_Curve_R_1_Y);
	PARAM(0xB5, 0x52, S16,  ColorCorrection_Primary_Curve_R_2_X);
	PARAM(0xB5, 0x53, S16,  ColorCorrection_Primary_Curve_R_2_Y);
	PARAM(0xB5, 0x54, S16,  ColorCorrection_Primary_Curve_R_3_X);
	PARAM(0xB5, 0x55, S16,  ColorCorrection_Primary_Curve_R_3_Y);
	PARAM(0xB5, 0x56, S16,  ColorCorrection_Primary_Curve_R_4_X);
	PARAM(0xB5, 0x57, S16,  ColorCorrection_Primary_Curve_R_4_Y);
	PARAM(0xB5, 0x58, S16,  ColorCorrection_Primary_Curve_R_5_X);
	PARAM(0xB5, 0x59, S16,  ColorCorrection_Primary_Curve_R_5_Y);
	PARAM(0xB5, 0x60, S16,  ColorCorrection_Primary_Curve_G_1_X);
	PARAM(0xB5, 0x61, S16,  ColorCorrection_Primary_Curve_G_1_Y);
	PARAM(0xB5, 0x62, S16,  ColorCorrection_Primary_Curve_G_2_X);
	PARAM(0xB5, 0x63, S16,  ColorCorrection_Primary_Curve_G_2_Y);
	PARAM(0xB5, 0x64, S16,  ColorCorrection_Primary_Curve_G_3_X);
	PARAM(0xB5, 0x65, S16,  ColorCorrection_Primary_Curve_G_3_Y);
	PARAM(0xB5, 0x66, S16,  ColorCorrection_Primary_Curve_G_4_X);
	PARAM(0xB5, 0x67, S16,  ColorCorrection_Primary_Curve_G_4_Y);
	PARAM(0xB5, 0x68, S16,  ColorCorrection_Primary_Curve_G_5_X);
	PARAM(0xB5, 0x69, S16,  ColorCorrection_Primary_Curve_G_5_Y);
	PARAM(0xB5, 0x70, S16,  ColorCorrection_Primary_Curve_B_1_X);
	PARAM(0xB5, 0x71, S16,  ColorCorrection_Primary_Curve_B_1_Y);
	PARAM(0xB5, 0x72, S16,  ColorCorrection_Primary_Curve_B_2_X);
	PARAM(0xB5, 0x73, S16,  ColorCorrection_Primary_Curve_B_2_Y);
	PARAM(0xB5, 0x74, S16,  ColorCorrection_Primary_Curve_B_3_X);
	PARAM(0xB5, 0x75, S16,  ColorCorrection_Primary_Curve_B_3_Y);
	PARAM(0xB5, 0x76, S16,  ColorCorrection_Primary_Curve_B_4_X);
	PARAM(0xB5, 0x77, S16,  ColorCorrection_Primary_Curve_B_4_Y);
	PARAM(0xB5, 0x78, S16,  ColorCorrection_Primary_Curve_B_5_X);
	PARAM(0xB5, 0x79, S16,  ColorCorrection_Primary_Curve_B_5_Y);
	PARAM(0xB5, 0x00, S16,  ColorCorrection_Primary_White_R);
	PARAM(0xB5, 0x01, S16,  ColorCorrection_Primary_White_G);
	PARAM(0xB5, 0x02, S16,  ColorCorrection_Primary_White_B);
	PARAM(0xB5, 0x03, S16,  ColorCorrection_Primary_Gamma_R);
	PARAM(0xB5, 0x04, S16,  ColorCorrection_Primary_Gamma_G);
	PARAM(0xB5, 0x05, S16,  ColorCorrection_Primary_Gamma_B);
	PARAM(0xB5, 0x06, S16,  ColorCorrection_Primary_Black_R);
	PARAM(0xB5, 0x07, S16,  ColorCorrection_Primary_Black_G);
	PARAM(0xB5, 0x08, S16,  ColorCorrection_Primary_Black_B);
	PARAM(0xB5, 0x09, S16,  ColorCorrection_Primary_Knee_R);
	PARAM(0xB5, 0x0A, S16,  ColorCorrection_Primary_Knee_G);
	PARAM(0xB5, 0x0B, S16,  ColorCorrection_Primary_Knee_B);
	PARAM(0x91, 0x83, Bool, ColorCorrection_Secondary_Enable);
	PARAM(0xAD, 0xD8, S16,  ColorCorrection_Secondary_Blue_Lum);
	PARAM(0xAD, 0xD9, S16,  ColorCorrection_Secondary_Blue_Sat);
	PARAM(0xAD, 0xDA, S16,  ColorCorrection_Secondary_Blue_Hue);
	PARAM(0xAD, 0xD4, S16,  ColorCorrection_Secondary_Cyan_Lum);
	PARAM(0xAD, 0xD5, S16,  ColorCorrection_Secondary_Cyan_Sat);
	PARAM(0xAD, 0xD6, S16,  ColorCorrection_Secondary_Cyan_Hue);
	PARAM(0xAD, 0xD0, S16,  ColorCorrection_Secondary_Green_Lum);
	PARAM(0xAD, 0xD1, S16,  ColorCorrection_Secondary_Green_Sat);
	PARAM(0xAD, 0xD2, S16,  ColorCorrection_Secondary_Green_Hue);
	PARAM(0xAD, 0xCC, S16,  ColorCorrection_Secondary_Yellow_Lum);
	PARAM(0xAD, 0xCD, S16,  ColorCorrection_Secondary_Yellow_Sat);
	PARAM(0xAD, 0xCE, S16,  ColorCorrection_Secondary_Yellow_Hue);
	PARAM(0xAD, 0xC8, S16,  ColorCorrection_Secondary_Red_Lum);
	PARAM(0xAD, 0xC9, S16,  ColorCorrection_Secondary_Red_Sat);
	PARAM(0xAD, 0xCA, S16,  ColorCorrection_Secondary_Red_Hue);
	PARAM(0xAD, 0xC4, S16,  ColorCorrection_Secondary_Magenta_Lum);
	PARAM(0xAD, 0xC5, S16,  ColorCorrection_Secondary_Magenta_Sat);
	PARAM(0xAD, 0xC6, S16,  ColorCorrection_Secondary_Magenta_Hue);
	PARAM(0x91, 0x84, Bool, ColorCorrection_LumaProcess_Enable);
	PARAM(0x92, 0xE2, Enum, ColorCorrection_LumaProcess_Mode);
	PARAM(0xAD, 0xDC, S16,  ColorCorrection_LumaProcess_Tint_Bright_Lum);
	PARAM(0xAD, 0xDD, S16,  ColorCorrection_LumaProcess_Tint_Bright_Sat);
	PARAM(0xAD, 0xDE, S16,  ColorCorrection_LumaProcess_Tint_Bright_Hue);
	PARAM(0xAD, 0xDF, S16,  ColorCorrection_LumaProcess_Mod_Bright_Hue);
	PARAM(0xAD, 0xE0, S16,  ColorCorrection_LumaProcess_Tint_Middle_Lum);
	PARAM(0xAD, 0xE1, S16,  ColorCorrection_LumaProcess_Tint_Middle_Sat);
	PARAM(0xAD, 0xE2, S16,  ColorCorrection_LumaProcess_Tint_Middle_Hue);
	PARAM(0xAD, 0xE3, S16,  ColorCorrection_LumaProcess_Mod_Middle_Hue);
	PARAM(0xAD, 0xE4, S16,  ColorCorrection_LumaProcess_Tint_Dark_Lum);
	PARAM(0xAD, 0xE5, S16,  ColorCorrection_LumaProcess_Tint_Dark_Sat);
	PARAM(0xAD, 0xE6, S16,  ColorCorrection_LumaProcess_Tint_Dark_Hue);
	PARAM(0xAD, 0xE7, S16,  ColorCorrection_LumaProcess_Mod_Dark_Hue);
	PARAM(0xAD, 0xE8, S16,  ColorCorrection_LumaProcess_Mix_Bright_Lum);
	PARAM(0xAD, 0xE9, S16,  ColorCorrection_LumaProcess_Mix_Bright_Sat);
	PARAM(0xAD, 0xEA, S16,  ColorCorrection_LumaProcess_Mix_Bright_Hue);
	PARAM(0xAD, 0xEB, S16,  ColorCorrection_LumaProcess_Hue_Dark);
	PARAM(0xAD, 0xEC, S16,  ColorCorrection_LumaProcess_Mix_Dark_Lum);
	PARAM(0xAD, 0xED, S16,  ColorCorrection_LumaProcess_Mix_Dark_Sat);
	PARAM(0xAD, 0xEE, S16,  ColorCorrection_LumaProcess_Mix_Dark_Hue);
	PARAM(0xAD, 0xEF, S16,  ColorCorrection_LumaProcess_Hue_Bright);
	PARAM(0xB5, 0x14, S16,  ColorCorrection_LumaProcess_Mix_Boundary_Level);
	PARAM(0xB5, 0x15, S16,  ColorCorrection_LumaProcess_Mix_Boundary_Soft);
	PARAM(0xB5, 0x16, S16,  ColorCorrection_LumaProcess_Hue_Sat);
	PARAM(0x92, 0xE3, Enum, ColorCorrection_LumaProcess_Hue_Direction);

	// 51 FRONT VIDEO
	PARAM(0x81, 0x00, Enum, FrontVideo_Input);

	// 52 FRONT KEY
	PARAM(0x92, 0x74, Enum, FrontKey_Source);
	PARAM(0x81, 0x02, Enum, FrontKey_Input);
	PARAM(0xA5, 0xB0, S16,  FrontKey_Clip);
	PARAM(0xA5, 0xB1, S16,  FrontKey_Gain);
	PARAM(0x90, 0x73, Bool, FrontKey_Invert);

	// 53 BACK VIDEO
	PARAM(0x81, 0x01, Enum, BackVideo_Input);

	// 54 BACK KEY
	PARAM(0x92, 0x75, Enum, BackKey_Source);
	PARAM(0x81, 0x03, Enum, BackKey_Input);
	PARAM(0x90, 0x74, Bool, BackKey_Invert);

	// 55 INPUT INVERT
	PARAM(0x90, 0x7A, Bool, InputInvert_Main_FrontInvert_H_1);
	PARAM(0x90, 0x7B, Bool, InputInvert_Main_FrontInvert_V_1);
	PARAM(0x90, 0x7C, Bool, InputInvert_Main_FrontInvert_H_2);
	PARAM(0x90, 0x7D, Bool, InputInvert_Main_FrontInvert_V_2);
	PARAM(0x90, 0x71, Bool, InputInvert_Main_BackInvert_H_1);
	PARAM(0x90, 0x72, Bool, InputInvert_Main_BackInvert_V_1);
	PARAM(0x90, 0x75, Bool, InputInvert_Main_BackInvert_H_2);
	PARAM(0x90, 0x76, Bool, InputInvert_Main_BackInvert_V_2);
	PARAM(0x91, 0xF6, Bool, InputInvert_Sub_FrontInvert_H);
	PARAM(0x91, 0xF7, Bool, InputInvert_Sub_FrontInvert_V);
	PARAM(0x91, 0xF8, Bool, InputInvert_Sub_BackInvert_H);
	PARAM(0x91, 0xF9, Bool, InputInvert_Sub_BackInvert_V);

	// 56 INTERPOLATION
	PARAM(0x92, 0x72, Enum, Interpolation_Front_Video);
	PARAM(0x92, 0x73, Enum, Interpolation_Back_Video);
	PARAM(0x92, 0x76, Enum, Interpolation_Front_Key);
	PARAM(0x92, 0x77, Enum, Interpolation_Back_Key);
	PARAM(0x92, 0xF8, Enum, Interpolation_ExtFront_Video);
	PARAM(0x92, 0xF9, Enum, Interpolation_ExtBack_Video);

	// 57 EXT VIDEO
	PARAM_VIDEO(0xA0, 0x01, 0x3F, Enum, ExtVideo_TBC_Center);
	PARAM_VIDEO(0xA3, 0x01, 0x3F, S16,  ExtVideo_Input_Phase);
	PARAM_F(0xA8, 0x0B, ParameterFlags_Global, Enum, ExtVideo_Output_Source);
	PARAM_F(0xAB, 0x26, ParameterFlags_Global, S16,  ExtVideo_Output_Phase);
	PARAM(0x91, 0xFA, Bool, ExtVideo_Separate_Side);

	// 101 WAVE
	PARAM(0x90, 0xE2, Bool, NonLinear_Wave_Mode_1);
	PARAM(0x92, 0xC4, Bool, NonLinear_Wave_Mode_2);
	PARAM(0x92, 0xC5, Bool, NonLinear_Wave_Mode_3);
	PARAM(0xB1, 0x00, S16,  NonLinear_Wave_ModulationH_Amplitude);
	PARAM(0xB1, 0x01, S16,  NonLinear_Wave_ModulationH_Frequency);
	PARAM(0xB1, 0x02, S16,  NonLinear_Wave_ModulationH_Offset);
	PARAM(0xB1, 0x03, S16,  NonLinear_Wave_ModulationH_Speed);
	PARAM(0xB1, 0x04, S16,  NonLinear_Wave_ModulationV_Amplitude);
	PARAM(0xB1, 0x05, S16,  NonLinear_Wave_ModulationV_Frequency);
	PARAM(0xB1, 0x06, S16,  NonLinear_Wave_ModulationV_Offset);
	PARAM(0xB1, 0x07, S16,  NonLinear_Wave_ModulationV_Speed);
	PARAM(0xB1, 0x29, S16,  NonLinear_Wave_Slant_Angle);
	PARAM(0x90, 0xC4, Bool, NonLinear_Wave_Lock_1);
	PARAM(0x90, 0xC9, Bool, NonLinear_Wave_Lock_2);
	PARAM(0x92, 0xC1, Enum, NonLinear_Wave_Form);
	PARAM(0xB1, 0x22, S16,  NonLinear_Wave_Randomness);
	PARAM(0x90, 0xC8, Bool, NonLinear_Wave_Range_Enable_1);
	PARAM(0x90, 0xC9, Bool, NonLinear_Wave_Range_Enable_2);
	PARAM(0xB1, 0x14, S16,  NonLinear_Wave_Range_Size);
	PARAM(0xB1, 0x15, S16,  NonLinear_Wave_Range_Offset);
	PARAM(0xB1, 0x16, S16,  NonLinear_Wave_Range_Envelope);
	PARAM(0x90, 0xCD, Bool, NonLinear_Wave_Reverse_Range);
	PARAM(0x90, 0xE4, Bool, NonLinear_Wave_Envelope_Enable);

	// 102 MOSAIC GLASS
	PARAM(0x90, 0xE2, Enum, NonLinear_MosaicGlass_Mode);
	PARAM(0xB1, 0x00, S16,  NonLinear_MosaicGlass_ModulationH_Amplitude);
	PARAM(0xB1, 0x01, S16,  NonLinear_MosaicGlass_ModulationH_Frequency);
	PARAM(0xB1, 0x02, S16,  NonLinear_MosaicGlass_ModulationH_Offset);
	PARAM(0xB1, 0x03, S16,  NonLinear_MosaicGlass_ModulationH_Speed);
	PARAM(0xB1, 0x04, S16,  NonLinear_MosaicGlass_ModulationV_Amplitude);
	PARAM(0xB1, 0x05, S16,  NonLinear_MosaicGlass_ModulationV_Frequency);
	PARAM(0xB1, 0x06, S16,  NonLinear_MosaicGlass_ModulationV_Offset);
	PARAM(0xB1, 0x07, S16,  NonLinear_MosaicGlass_ModulationV_Speed);
	PARAM(0xB1, 0x29, S16,  NonLinear_MosaicGlass_Slant_Angle);
	PARAM(0x90, 0xC4, Bool, NonLinear_MosaicGlass_Lock_1);
	PARAM(0x90, 0xC5, Bool, NonLinear_MosaicGlass_Lock_2);
	PARAM(0x92, 0xC0, Enum, NonLinear_MosaicGlass_Form_H);
	PARAM(0x92, 0xC1, Enum, NonLinear_MosaicGlass_Form_V);
	PARAM(0xB1, 0x20, S16,  NonLinear_MosaicGlass_Randomness_H);
	PARAM(0xB1, 0x22, S16,  NonLinear_MosaicGlass_Randomness_V);
	PARAM(0x90, 0xC8, Bool, NonLinear_MosaicGlass_Range_Enable_1);
	PARAM(0x90, 0xC9, Bool, NonLinear_MosaicGlass_Range_Enable_2);
	PARAM(0xB1, 0x10, S16,  NonLinear_MosaicGlass_RangeH_Size);
	PARAM(0xB1, 0x11, S16,  NonLinear_MosaicGlass_RangeH_Offset);
	PARAM(0xB1, 0x12, S16,  NonLinear_MosaicGlass_RangeH_Envelope);
	PARAM(0xB1, 0x14, S16,  NonLinear_MosaicGlass_RangeV_Size);
	PARAM(0xB1, 0x15, S16,  NonLinear_MosaicGlass_RangeV_Offset);
	PARAM(0xB1, 0x16, S16,  NonLinear_MosaicGlass_RangeV_Envelope);
	PARAM(0x90, 0xCC, Bool, NonLinear_MosaicGlass_Reverse_H);
	PARAM(0x90, 0xCD, Bool, NonLinear_MosaicGlass_Reverse_V);

	// 103 FLAG
	PARAM(0xB1, 0x00, S16,  NonLinear_Flag_Modulation_Amplitude);
	PARAM(0xB1, 0x01, S16,  NonLinear_Flag_Modulation_Frequency);
	PARAM(0xB1, 0x02, S16,  NonLinear_Flag_Modulation_Offset);
	PARAM(0xB1, 0x03, S16,  NonLinear_Flag_Modulation_Speed);
	PARAM(0xB1, 0x29, S16,  NonLinear_Flag_Slant_Angle);
	PARAM(0x90, 0xC4, Bool, NonLinear_Flag_Lock_1);
	PARAM(0x90, 0xC5, Bool, NonLinear_Flag_Lock_2);
	PARAM(0x92, 0xC0, Enum, NonLinear_Flag_Form);
	PARAM(0xB1, 0x20, S16,  NonLinear_Flag_Randomness);
	PARAM(0x90, 0xC8, Bool, NonLinear_Flag_Range_Enable_1);
	PARAM(0x90, 0xC9, Bool, NonLinear_Flag_Range_Enable_2);
	PARAM(0xB1, 0x10, S16,  NonLinear_Flag_Range_Size);
	PARAM(0xB1, 0x11, S16,  NonLinear_Flag_Range_Offset);
	PARAM(0xB1, 0x12, S16,  NonLinear_Flag_Range_Envelope);
	PARAM(0x90, 0xCD, Bool, NonLinear_Flag_Reverse_Range);
	PARAM(0x90, 0xE4, Bool, NonLinear_Flag_Envelope_Enable);

	// 104 RIPPLE
	PARAM(0x92, 0xC6, Enum, NonLinear_Ripple_Mode);
	PARAM(0xB1, 0x08, S16,  NonLinear_Ripple_ModulationRadial_Amplitude);
	PARAM(0xB1, 0x09, S16,  NonLinear_Ripple_ModulationRadial_Frequency);
	PARAM(0xB1, 0x0A, S16,  NonLinear_Ripple_ModulationRadial_Offset);
	PARAM(0xB1, 0x0B, S16,  NonLinear_Ripple_ModulationRadial_Speed);
	PARAM(0xB1, 0x0C, S16,  NonLinear_Ripple_ModulationAngular_Amplitude);
	PARAM(0xB1, 0x0D, S16,  NonLinear_Ripple_ModulationAngular_Frequency);
	PARAM(0xB1, 0x0E, S16,  NonLinear_Ripple_ModulationAngular_Offset);
	PARAM(0xB1, 0x0F, S16,  NonLinear_Ripple_ModulationAngular_Speed);
	PARAM(0xB1, 0x2B, S16,  NonLinear_Ripple_Position_X);
	PARAM(0xB1, 0x2C, S16,  NonLinear_Ripple_Position_Y);
	PARAM(0x90, 0xC6, Bool, NonLinear_Ripple_Lock);
	PARAM(0x90, 0xD1, Bool, NonLinear_Ripple_Form_PositiveOnly);
	PARAM(0x92, 0xC2, Enum, NonLinear_Ripple_Form_Radial);
	PARAM(0x92, 0xC3, Enum, NonLinear_Ripple_Form_Angular);
	PARAM(0xB1, 0x24, S16,  NonLinear_Ripple_Randomness_Radial);
	PARAM(0xB1, 0x26, S16,  NonLinear_Ripple_Randomness_Angular);
	PARAM(0x90, 0xCA, Bool, NonLinear_Ripple_Range_Enable_1);
	PARAM(0x90, 0xCB, Bool, NonLinear_Ripple_Range_Enable_2);
	PARAM(0xB1, 0x18, S16,  NonLinear_Ripple_Range_Size);
	PARAM(0xB1, 0x19, S16,  NonLinear_Ripple_Range_Offset);
	PARAM(0xB1, 0x1A, S16,  NonLinear_Ripple_Range_Envelope);
	PARAM(0x90, 0xE4, Bool, NonLinear_Ripple_Envelope_Enable);

	// 105 RINGS
	PARAM(0xB1, 0x50, S16,  NonLinear_Rings_Transition_Progress);
	PARAM(0xB1, 0x52, S16,  NonLinear_Rings_Transition_Random);
	PARAM(0xB1, 0x75, S16,  NonLinear_Rings_Transition_Spiral);
	PARAM(0xB1, 0x38, S16,  NonLinear_Rings_Partition_Width);
	PARAM(0xB1, 0x39, S16,  NonLinear_Rings_Partition_Random);
	PARAM(0xB1, 0x2B, S16,  NonLinear_Rings_Position_X);
	PARAM(0xB1, 0x2C, S16,  NonLinear_Rings_Position_Y);
	PARAM(0xB1, 0x71, S16,  NonLinear_Rings_Start_Angle);
	PARAM(0x90, 0xD5, Bool, NonLinear_Rings_Pixel_Enable);
	PARAM(0xB1, 0x80, S16,  NonLinear_Rings_Pixel_Density);
	PARAM(0xB1, 0x3A, S16,  NonLinear_Rings_Pixel_Random);

	// 106 BROKEN GLASS
	PARAM(0xB1, 0x50, S16,  NonLinear_BrokenGlass_Transition_Progress);
	PARAM(0xB1, 0x52, S16,  NonLinear_BrokenGlass_Transition_Random);
	PARAM(0xB1, 0x75, S16,  NonLinear_BrokenGlass_Transition_Spiral);
	PARAM(0xB1, 0x3C, S16,  NonLinear_BrokenGlass_Partition_Width);
	PARAM(0xB1, 0x3D, S16,  NonLinear_BrokenGlass_Partition_Random);
	PARAM(0xB1, 0x2B, S16,  NonLinear_BrokenGlass_Position_X);
	PARAM(0xB1, 0x2C, S16,  NonLinear_BrokenGlass_Position_Y);
	PARAM(0xB1, 0x71, S16,  NonLinear_BrokenGlass_Start_Angle);
	PARAM(0x90, 0xD6, Bool, NonLinear_BrokenGlass_Direction);
	PARAM(0x90, 0xD5, Bool, NonLinear_BrokenGlass_Pixel_Enable);
	PARAM(0xB1, 0x80, S16,  NonLinear_BrokenGlass_Pixel_Density);
	PARAM(0xB1, 0x3E, S16,  NonLinear_BrokenGlass_Pixel_Random);

	// 107 FLYING BARS
	PARAM(0xB1, 0x50, S16,  NonLinear_FlyingBars_Transition_Progress);
	PARAM(0xB1, 0x20, S16,  NonLinear_FlyingBars_Transition_Random);
	PARAM(0xB1, 0x54, S16,  NonLinear_FlyingBars_Transition_Angle);
	PARAM(0xB1, 0x30, S16,  NonLinear_FlyingBars_Partition_Width);
	PARAM(0xB1, 0x31, S16,  NonLinear_FlyingBars_Partition_Random);
	PARAM(0xB1, 0x29, S16,  NonLinear_FlyingBars_Partition_Angle);

	// 108 SPLIT
	PARAM(0x90, 0x51, Bool, NonLinear_Split_Enable);
	PARAM(0xA5, 0x63, S16,  NonLinear_Split_Transition_H_1);
	PARAM(0xA5, 0x64, S16,  NonLinear_Split_Transition_H_2);
	PARAM(0xA5, 0x65, S16,  NonLinear_Split_Transition_V_1);
	PARAM(0xA5, 0x66, S16,  NonLinear_Split_Transition_V_2);
	PARAM(0xA5, 0x67, S16,  NonLinear_Split_Partition_H);
	PARAM(0xA5, 0x68, S16,  NonLinear_Split_Partition_V);
	PARAM(0x92, 0x51, Bool, NonLinear_Split_Double);

	// 109 SPLIT SLIDE
	PARAM(0x92, 0xCA, Enum, NonLinear_SplitSlide_Mode);
	PARAM(0xB1, 0x50, S16,  NonLinear_SplitSlide_TransitionH_Progress);
	PARAM(0xB1, 0x20, S16,  NonLinear_SplitSlide_TransitionH_Random);
	PARAM(0xB1, 0x00, S16,  NonLinear_SplitSlide_TransitionH_Skew);
	PARAM(0xB1, 0x30, S16,  NonLinear_SplitSlide_PartitionH_Width);
	PARAM(0xB1, 0x33, S16,  NonLinear_SplitSlide_PartitionH_Position);
	PARAM(0xB1, 0x51, S16,  NonLinear_SplitSlide_TransitionV_Progress);
	PARAM(0xB1, 0x22, S16,  NonLinear_SplitSlide_TransitionV_Random);
	PARAM(0xB1, 0x04, S16,  NonLinear_SplitSlide_TransitionV_Skew);
	PARAM(0xB1, 0x34, S16,  NonLinear_SplitSlide_PartitionV_Width);
	PARAM(0xB1, 0x37, S16,  NonLinear_SplitSlide_PartitionV_Position);

	// 110 CHARACTER TRAIL
	PARAM(0xB1, 0x2B, S16,  NonLinear_CharacterTrail_Transition_Progress);
	PARAM(0xB1, 0x00, S16,  NonLinear_CharacterTrail_Transition_Expand);
	PARAM(0xB1, 0x29, S16,  NonLinear_CharacterTrail_Transition_Angle);
	PARAM(0xB1, 0x2A, S16,  NonLinear_CharacterTrail_Angle);
	PARAM(0x90, 0xD5, Bool, NonLinear_CharacterTrail_Pixel_Enable);
	PARAM(0xB1, 0x80, S16,  NonLinear_CharacterTrail_Pixel_Density);
	PARAM(0xB1, 0x81, S16,  NonLinear_CharacterTrail_Pixel_Random);

	// 111 MIRROR
	PARAM(0x90, 0x50, Bool, NonLinear_Mirror_Enable);
	PARAM(0x92, 0x50, S16,  NonLinear_Mirror_Configuration);

	// 112 LENS
	PARAM(0x92, 0xC7, Enum, NonLinear_Lens_Mode_1);
	PARAM(0x92, 0xE2, Enum, NonLinear_Lens_Mode_2);
	PARAM(0x92, 0xC9, Enum, NonLinear_Lens_Mode_3);
	PARAM(0xB1, 0x60, S16,  NonLinear_Lens_MagnifySizeH_Mag);
	PARAM(0xB1, 0x61, S16,  NonLinear_Lens_MagnifySizeH_Curve);
	PARAM(0xB1, 0x62, S16,  NonLinear_Lens_MagnifySizeH_Size);
	PARAM(0xB1, 0x64, S16,  NonLinear_Lens_MagnifySizeV_Mag);
	PARAM(0xB1, 0x65, S16,  NonLinear_Lens_MagnifySizeV_Curve);
	PARAM(0xB1, 0x66, S16,  NonLinear_Lens_MagnifySizeV_Size);
	PARAM(0xB1, 0x2B, S16,  NonLinear_Lens_Position_X);
	PARAM(0xB1, 0x2C, S16,  NonLinear_Lens_Position_Y);
	PARAM(0xB1, 0x28, S16,  NonLinear_Lens_Aspect);
	PARAM(0xB1, 0x58, S16,  NonLinear_Lens_Angle);
	PARAM(0xB1, 0x29, S16,  NonLinear_Lens_Slant_Angle);
	PARAM(0x90, 0xD2, Bool, NonLinear_Lens_Lens_Only);

	// 113 CIRCLE
	PARAM(0xB1, 0x08, S16, NonLinear_Circle_Radius);

	// 114 PANORAMA
	PARAM(0xB1, 0x00, S16, NonLinear_Panorama_Curve_H);
	PARAM(0xB1, 0x04, S16, NonLinear_Panorama_Curve_V);
	PARAM(0xB1, 0x2B, S16, NonLinear_Panorama_Position_X);
	PARAM(0xB1, 0x2C, S16, NonLinear_Panorama_Position_Y);

	// 120 PAGE TURN
	PARAM(0xA9, 0x80, S16, NonLinear_PageTurn_Shape_Radius);
	PARAM(0xA9, 0x81, S16, NonLinear_PageTurn_Shape_Angle);
	PARAM(0xA9, 0x82, S16, NonLinear_PageTurn_Shape_Offset);

	// 121 ROLL
	PARAM(0xA9, 0x80, S16, NonLinear_Roll_Shape_Radius);
	PARAM(0xA9, 0x81, S16, NonLinear_Roll_Shape_Angle);
	PARAM(0xA9, 0x82, S16, NonLinear_Roll_Shape_Offset);

	// 122 CYLINDER
	PARAM(0xA9, 0x83, S16, NonLinear_Cylinder_Shape_Radius);
	PARAM(0xA9, 0x84, S16, NonLinear_Cylinder_Shape_MinR);
	PARAM(0xA9, 0x85, S16, NonLinear_Cylinder_Shape_Offset);

	// 123 SPHERE
	PARAM(0xA9, 0x83, S16, NonLinear_Sphere_Shape_Radius);
	PARAM(0xA9, 0x84, S16, NonLinear_Sphere_Shape_MinR);
	PARAM(0xA9, 0x85, S16, NonLinear_Sphere_Shape_Offset);

	// 131 TWIST
	PARAM(0x92, 0xC0, Enum, NonLinear_Twist_Form_H);
	PARAM(0x92, 0xC1, Enum, NonLinear_Twist_Form_V);
	PARAM(0xB1, 0x00, S16,  NonLinear_Twist_ModulationH_Amplitude);
	PARAM(0xB1, 0x01, S16,  NonLinear_Twist_ModulationH_Frequency);
	PARAM(0xB1, 0x02, S16,  NonLinear_Twist_ModulationH_Offset);
	PARAM(0xB1, 0x03, S16,  NonLinear_Twist_ModulationH_Speed);
	PARAM(0xB1, 0x04, S16,  NonLinear_Twist_ModulationV_Amplitude);
	PARAM(0xB1, 0x05, S16,  NonLinear_Twist_ModulationV_Frequency);
	PARAM(0xB1, 0x06, S16,  NonLinear_Twist_ModulationV_Offset);
	PARAM(0xB1, 0x07, S16,  NonLinear_Twist_ModulationV_Speed);
	PARAM(0x90, 0xC4, Bool, NonLiner_Twist_Lock_1);
	PARAM(0x90, 0xC5, Bool, NonLiner_Twist_Lock_2);
	PARAM(0x90, 0xE2, Bool, NonLinear_Twist_Slant90);

	// 132 EXPLOSION
	PARAM(0x92, 0xC7, Enum, NonLinear_Explosion_Mask_Pattern);
	PARAM(0xB1, 0x50, S16,  NonLinear_Explosion_Transition_Progress);
	PARAM(0xB1, 0x5C, S16,  NonLinear_Explosion_Transition_Curve);
	PARAM(0xB1, 0x5B, S16,  NonLinear_Explosion_Transition_Spiral);
	PARAM(0xB1, 0x2B, S16,  NonLinear_Explosion_Position_X);
	PARAM(0xB1, 0x2C, S16,  NonLinear_Explosion_Position_Y);
	PARAM(0x90, 0xD5, Bool, NonLinear_Explosion_Pixel_Enable);
	PARAM(0xB1, 0x80, S16,  NonLinear_Explosion_Pixel_Density);
	PARAM(0xB1, 0x81, S16,  NonLinear_Explosion_Pixel_Random);

	// 133 SWIRL
	PARAM(0xB1, 0x74, S16,  NonLinear_Swirl_Transition);
	PARAM(0xB1, 0x71, S16,  NonLinear_Swirl_Angle_Center);
	PARAM(0xB1, 0x73, S16,  NonLinear_Swirl_Angle_Outer);
	PARAM(0xB1, 0x70, S16,  NonLinear_Swirl_Area);
	PARAM(0xB1, 0x2B, S16,  NonLinear_Swirl_Position_X);
	PARAM(0xB1, 0x2C, S16,  NonLinear_Swirl_Position_Y);
	PARAM(0x90, 0xE0, Bool, NonLinear_Swirl_Pixel_Enable_1);
	PARAM(0x90, 0xD5, Bool, NonLinear_Swirl_Pixel_Enable_2);
	PARAM(0xB1, 0x80, S16,  NonLinear_Swirl_Pixel_Density);
	PARAM(0xB1, 0x81, S16,  NonLinear_Swirl_Pixel_Random);

	// 134 BLIND
	PARAM(0x92, 0xCB, Enum, NonLinear_Blind_Mode);
	PARAM(0xB1, 0x7E, S16,  NonLinear_Blind_Transition_Rotate);
	PARAM(0xB1, 0x7F, S16,  NonLinear_Blind_Transition_Perspective);
	PARAM(0xB1, 0x30, S16,  NonLinear_Blind_Partition_Width);
	PARAM(0xB1, 0x33, S16,  NonLinear_Blind_Partition_Position);
	PARAM(0xB1, 0x29, S16,  NonLinear_Blind_Partition_Angle);
	PARAM(0xB1, 0x2B, S16,  NonLinear_Blind_Position_X);
	PARAM(0xB1, 0x2C, S16,  NonLinear_Blind_Position_Y);

	// 135 KALEIDOSCOPE
	PARAM(0xB1, 0x40, S16,  NonLinear_Kaleidoscope_Number);
	PARAM(0xB1, 0x3F, S16,  NonLinear_Kaleidoscope_Phase);
	PARAM(0xB1, 0x2B, S16,  NonLinear_Kaleidoscope_Offset_H);
	PARAM(0xB1, 0x2C, S16,  NonLinear_Kaleidoscope_Offset_V);
	PARAM(0x90, 0xD8, Bool, NonLinear_Kaleidoscope_Mirror_H);
	PARAM(0x90, 0xD8, Bool, NonLinear_Kaleidoscope_Mirror_V);
	PARAM(0xB1, 0x78, S16,  NonLinear_Kaleidoscope_Position_X);
	PARAM(0xB1, 0x79, S16,  NonLinear_Kaleidoscope_Position_Y);
	PARAM(0x90, 0xDF, Bool, NonLinear_Kaleidoscope_Cyclic);

	// 136 MULTI MIRROR
	PARAM(0xB1, 0x30, S16, NonLinear_MultiMirror_MirrorH_Spacing);
	PARAM(0xB1, 0x2B, S16, NonLinear_MultiMirror_MirrorH_Position);
	PARAM(0xB1, 0x7A, S16, NonLinear_MultiMirror_MirrorH_Offset);
	PARAM(0xB1, 0x34, S16, NonLinear_MultiMirror_MirrorV_Spacing);
	PARAM(0xB1, 0x2C, S16, NonLinear_MultiMirror_MirrorV_Position);
	PARAM(0xB1, 0x7B, S16, NonLinear_MultiMirror_MirrorV_Offset);
	PARAM(0xB1, 0x29, S16, NonLinear_MultiMirror_Slant_Angle);

	// 137 MELT
	PARAM(0x92, 0xC0, Enum, NonLinear_Melt_Pattern);
	PARAM(0xB1, 0x50, S16,  NonLinear_Melt_Transition_Progress);
	PARAM(0xB1, 0x04, S16,  NonLinear_Melt_Transition_Curve);
	PARAM(0xB1, 0x22, S16,  NonLinear_Melt_Transition_Random);
	PARAM(0xB1, 0x00, S16,  NonLinear_Melt_Border_Amplitude);
	PARAM(0xB1, 0x01, S16,  NonLinear_Melt_Border_Frequency);
	PARAM(0xB1, 0x02, S16,  NonLinear_Melt_Border_Offset);
	PARAM(0xB1, 0x2A, S16,  NonLinear_Melt_Slant_Angle);
	PARAM(0x90, 0xC4, Bool, NonLinear_Melt_Lock_1);
	PARAM(0x90, 0xC5, Bool, NonLinear_Melt_Lock_2);
	PARAM(0x90, 0xE2, Enum, NonLinear_Melt_Direction);
	PARAM(0x90, 0xE0, Bool, NonLinear_Melt_Pixel_Enable_1);
	PARAM(0x90, 0xD5, Bool, NonLinear_Melt_Pixel_Enable_2);
	PARAM(0xB1, 0x80, S16,  NonLinear_Melt_Pixel_Density);
	PARAM(0xB1, 0x81, S16,  NonLinear_Melt_Pixel_Random);

	// 201 GRAPHIC SETUP
	PARAM(0xE0, 0x00, Bool, GraphicSetup_Enable);
	PARAM(0xE0, 0x01, Enum, GraphicSetup_User_Defined_Mode_1);
	PARAM(0xE0, 0x02, Enum, GraphicSetup_User_Defined_Mode_2);
	PARAM(0xE0, 0x03, Enum, GraphicSetup_Shadow_Elements);
	PARAM(0xE0, 0x04, Enum, GraphicSetup_Sub_Picture_Elements);
	PARAM(0xE0, 0x10, Enum, GraphicSetup_Mode);
	PARAM(0xE0, 0x13, Enum, GraphicSetup_Recovery_Time);
	PARAM(0xE0, 0x30, S16,  GraphicSetup_Size);

	// 301 LIGHTING
	PARAM(0x90, 0x90, Bool, Lighting_Enable);
	PARAM(0x92, 0x90, Enum, Lighting_Pattern);
	PARAM(0xA9, 0x70, S16,  Lighting_Shape_Size);
	PARAM(0xA9, 0x71, S16,  Lighting_Shape_Soft);
	PARAM(0xA9, 0x65, S16,  Lighting_Shape_Offset);
	PARAM(0xA9, 0x6A, S16,  Lighting_Position_X);
	PARAM(0xA9, 0x6B, S16,  Lighting_Position_Y);
	PARAM(0xA9, 0x66, S16,  Lighting_Position_Angle);
	PARAM(0x92, 0x92, Enum, Lighting_Light_Area);
	PARAM(0xA9, 0x72, S16,  Lighting_Intensity_Light);
	PARAM(0xA9, 0x73, S16,  Lighting_Intensity_Ambient);
	PARAM(0x92, 0x91, Bool, Lighting_Hue_Rot);
	PARAM(0xAD, 0x10, S16,  Lighting_LightColor_Lum);
	PARAM(0xAD, 0x11, S16,  Lighting_LightColor_Sat);
	PARAM(0xAD, 0x12, S16,  Lighting_LightColor_Hue);
	PARAM(0xAD, 0x1C, S16,  Lighting_LightColor_Speed);

	// 302 SPOTLIGHT
	PARAM(0x90, 0x8E, Bool, Spotlight_Enable);
	PARAM(0xA9, 0x50, S16,  Spotlight_Intensity);
	PARAM(0x92, 0x85, Enum, Spotlight_Mix_Mode);
	PARAM(0x92, 0x84, Enum, Spotlight_Source);
	PARAM(0xAD, 0x30, S16,  Spotlight_Color_Lum);
	PARAM(0xAD, 0x31, S16,  Spotlight_Color_Sat);
	PARAM(0xAD, 0x32, S16,  Spotlight_Color_Hue);
	PARAM(0xAD, 0x33, S16,  Spotlight_Color_Speed);

	// 303 TARGET LIGHT
	PARAM(0x91, 0x10, Bool, TargetLight_Enable);
	PARAM(0x91, 0x11, Bool, TargetLight_Light_Invert);
	PARAM(0x92, 0x98, Enum, TargetLight_Pattern);
	PARAM(0xA9, 0xC0, S16,  TargetLight_Position_X);
	PARAM(0xA9, 0xC1, S16,  TargetLight_Position_Y);
	PARAM(0xA9, 0xC2, S16,  TargetLight_Position_Size);
	PARAM(0xA9, 0xC6, S16,  TargetLight_Intensity);
	PARAM(0xA9, 0xC7, S16,  TargetLight_Soft);
	PARAM(0x92, 0x99, Enum, TargetLight_Mix_Mode);
	PARAM(0x92, 0x9D, Enum, TargetLight_Area);
	PARAM(0x91, 0x13, Bool, TargetLight_PatternModify_Rotation);
	PARAM(0xA9, 0xC3, S16,  TargetLight_PatternModify_Aspect);
	PARAM(0xA9, 0xC4, S16,  TargetLight_PatternModify_Angle);
	PARAM(0xA9, 0xC5, S16,  TargetLight_PatternModify_Rotation_Speed);
	PARAM(0x91, 0x16, Bool, TargetLight_PatternModify_Lock_H);
	PARAM(0x91, 0x17, Bool, TargetLight_PatternModify_Lock_V);
	PARAM(0xB1, 0x00, S16,  TargetLight_PatternModify_ModulationH_Amplitude);
	PARAM(0xB1, 0x01, S16,  TargetLight_PatternModify_ModulationH_Frequency);
	PARAM(0xB1, 0x02, S16,  TargetLight_PatternModify_ModulationH_Offset);
	PARAM(0xB1, 0x03, S16,  TargetLight_PatternModify_ModulationH_Speed);
	PARAM(0xB1, 0x04, S16,  TargetLight_PatternModify_ModulationV_Amplitude);
	PARAM(0xB1, 0x05, S16,  TargetLight_PatternModify_ModulationV_Frequency);
	PARAM(0xB1, 0x06, S16,  TargetLight_PatternModify_ModulationV_Offset);
	PARAM(0xB1, 0x07, S16,  TargetLight_PatternModify_ModulationV_Speed);
	PARAM(0x92, 0x9A, Enum, TargetLight_Source);
	PARAM(0xAD, 0x80, S16,  TargetLight_Color_Lum);
	PARAM(0xAD, 0x81, S16,  TargetLight_Color_Sat);
	PARAM(0xAD, 0x82, S16,  TargetLight_Color_Hue);
	PARAM(0xAD, 0x83, S16,  TargetLight_Color_Speed);
	
	// 304 TARGET SPOTLIGHT
	PARAM(0x90, 0x8F, Bool, TargetSpotlight_Enable);
	PARAM(0x92, 0x86, Enum, TargetSpotlight_Reflect_Mode);
	PARAM(0xA9, 0x61, S16,  TargetSpotlight_Position_Longitude);
	PARAM(0xA9, 0x60, S16,  TargetSpotlight_Position_Latitude);
	PARAM(0xA9, 0x63, S16,  TargetSpotlight_Position_X);
	PARAM(0xA9, 0x64, S16,  TargetSpotlight_Position_Y);
	PARAM(0x90, 0x94, Bool, TargetSpotlight_Angle_Enable);
	PARAM(0xA9, 0x15, S16,  TargetSpotlight_Angle_Speed);
	PARAM(0x90, 0x93, Bool, TargetSpotlight_Revolution_Enable);
	PARAM(0xA9, 0x62, S16,  TargetSpotlight_Revolution_Radius);
	PARAM(0xA9, 0x68, S16,  TargetSpotlight_Revolution_Speed);
	PARAM(0xA9, 0x11, S16,  TargetSpotlight_Offset);

	// 715 OUTPUT CONTROL
	PARAM_F(0xA8, 0x40, ParameterFlags_Global, Enum, OutputControl_Analog_Signal);
	PARAM_F(0xA8, 0x42, ParameterFlags_Global, Enum, OutputControl_Rounding_Video);
	PARAM_F(0xA8, 0x43, ParameterFlags_Global, Enum, OutputControl_Rounding_Key);
	PARAM_F(0xA8, 0x44, ParameterFlags_Global, Enum, OutputControl_V_Phase);
	PARAM_F(0xAB, 0x21, ParameterFlags_Global, S16,  OutputControl_H_Phase_Video);
	PARAM_F(0xAB, 0x22, ParameterFlags_Global, S16,  OutputControl_H_Phase_Key);
	PARAM_F(0xA8, 0x49, ParameterFlags_Global, Enum, OutputControl_Blanking);

	// 716 PROCESS CONTROL
	PARAM_F(0xA8, 0x18, ParameterFlags_Global, Enum, ProcessControl_Filter_Mode);
	PARAM_F(0xA8, 0x60, ParameterFlags_Global, Enum, ProcessControl_Filter_Type);
	PARAM_F(0xA8, 0x41, ParameterFlags_Global, Bool, ProcessControl_Limiter_Video);
	PARAM_F(0xA8, 0x16, ParameterFlags_Global, Bool, ProcessControl_Limiter_Matte);
	PARAM_F(0xAB, 0x02, ParameterFlags_Global, S16,  ProcessControl_Matte_Lum_Max);
	PARAM_F(0xAB, 0x20, ParameterFlags_Global, S16,  ProcessControl_White_Clip);
	PARAM_F(0xAB, 0x24, ParameterFlags_Global, S16,  ProcessControl_Dark_Clip);
	PARAM_F(0xA8, 0x45, ParameterFlags_Global, Enum, ProcessControl_External_Key);
	PARAM_F(0xA8, 0x46, ParameterFlags_Global, Enum, ProcessControl_Key_Filter);
	PARAM_F(0xA8, 0x47, ParameterFlags_Global, Enum, ProcessControl_Analog_External_Key);
	PARAM_F(0xA8, 0x4A, ParameterFlags_Global, Enum, ProcessControl_Adaptive_Mode);
	PARAM( 0x90, 0x53,                         Bool, ProcessControl_Wrap_Around);

	// TRANSFORM
	PARAM(0xA1, 0x08, F32, Transform_Location_X);
	PARAM(0xA1, 0x09, F32, Transform_Location_Y);
	PARAM(0xA1, 0x10, F32, Transform_Location_Z);
	PARAM(0xA1, 0x04, F32, Transform_TargetLocSize_X);
	PARAM(0xA1, 0x05, F32, Transform_TargetLocSize_Y);
	PARAM(0xA1, 0x06, F32, Transform_TargetLocSize_Z);
	PARAM(0xA1, 0x18, F32, Transform_Perspective_X);
	PARAM(0xA1, 0x19, F32, Transform_Perspective_Y);
	PARAM(0xA1, 0x1A, F32, Transform_Perspective_Z);
	PARAM(0xA1, 0x10, F32, Transform_Rotation_X);
	PARAM(0xA1, 0x11, F32, Transform_Rotation_Y);
	PARAM(0xA1, 0x12, F32, Transform_Rotation_Z);
	PARAM(0xA1, 0x86, F32, Transform_Size);
	PARAM(0xA1, 0x94, F32, Transform_SkewAspect_X);
	PARAM(0xA1, 0x95, F32, Transform_SkewAspect_Y);
	PARAM(0xA1, 0x96, F32, Transform_SkewAspect_Z);
	PARAM(0xA1, 0x24, F32, Transform_TargetSpin_X);
	PARAM(0xA1, 0x25, F32, Transform_TargetSpin_Y);
	PARAM(0xA1, 0x26, F32, Transform_TargetSpin_Z);
	PARAM(0xA1, 0xA4, F32, Transform_SourceSpin_X);
	PARAM(0xA1, 0xA5, F32, Transform_SourceSpin_Y);
	PARAM(0xA1, 0xA6, F32, Transform_SourceSpin_Z);

	// RECURSIVE TRAILS
	PARAM(0x90, 0x40, Bool, RecursiveTrails_Enable);
	PARAM(0x90, 0x45, Bool, RecursiveTrails_Wind);
	PARAM(0x92, 0x41, Enum, RecursiveTrails_Mode);
	PARAM(0x90, 0x41, Bool, RecursiveTrails_Resume_Recur);
	PARAM(0xA5, 0x40, S16,  RecursiveTrails_Decay_Video);
	PARAM(0xA5, 0x41, S16,  RecursiveTrails_Decay_Key);
	PARAM(0xA5, 0x42, S16,  RecursiveTrails_Decay_Dust);
	PARAM(0x90, 0x4A, Bool, RecursiveTrails_Defocus_Enable);
	PARAM(0xA5, 0x4C, S16,  RecursiveTrails_Defocus_Video);
	PARAM(0xA5, 0x4D, S16,  RecursiveTrails_Defocus_Key);
	PARAM(0x92, 0x43, Enum, RecursiveTrails_Priority);
	PARAM(0xA5, 0x54, S16,  RecursiveTrails_Mix);
	PARAM(0x90, 0x43, Bool, RecursiveTrails_Source_Enable);
	PARAM(0x92, 0x49, Enum, RecursiveTrails_Source_Trail_Type);
	PARAM(0x92, 0x46, Enum, RecursiveTrails_Source);
	PARAM(0xAD, 0x20, S16,  RecursiveTrails_Color_Lum);
	PARAM(0xAD, 0x21, S16,  RecursiveTrails_Color_Sat);
	PARAM(0xAD, 0x22, S16,  RecursiveTrails_Color_Hue);
	PARAM(0xAD, 0x23, S16,  RecursiveTrails_Color_Speed);
	PARAM(0x90, 0x4C, Bool, RecursiveTrails_HueRange_Enable);
	PARAM(0xAD, 0x48, S16,  RecursiveTrails_HueRange_Center);
	PARAM(0xAD, 0x49, S16,  RecursiveTrails_HueRange_Range);
	PARAM(0xAD, 0x4C, S16,  RecursiveTrails_HueRange_Step);
	PARAM(0x92, 0x4A, Enum, RecursiveTrails_Hue_Path);
	PARAM(0x91, 0x20, Bool, RecursiveTrails_Dust_Enable);
	PARAM(0xA5, 0x50, S16,  RecursiveTrails_Dust_Level);
	PARAM(0xA5, 0x51, S16,  RecursiveTrails_Dust_Soft);
	PARAM(0xA5, 0x4E, S16,  RecursiveTrails_Dust_Size_H);
	PARAM(0xA5, 0x4F, S16,  RecursiveTrails_Dust_Size_V);
	PARAM(0x92, 0x4C, Enum, RecursiveTrails_Dust_Pattern);
	PARAM(0x91, 0x21, Bool, RecursiveTrails_Dust_Invert);

	// VIDEO SOURCES
	PARAM_VIDEO(0xA0, 0x01, 0x00, Enum, VideoSources_SourceA_TBC_Center);
	PARAM_VIDEO(0xA3, 0x01, 0x00, S16,  VideoSources_SourceA_Phase);
	PARAM_VIDEO(0xA0, 0x04, 0x00, Enum, VideoSources_SourceA_H_Shift);
	PARAM_VIDEO(0xA0, 0x01, 0x01, Enum, VideoSources_SourceB_TBC_Center);
	PARAM_VIDEO(0xA3, 0x01, 0x01, S16,  VideoSources_SourceB_Phase);
	PARAM_VIDEO(0xA0, 0x04, 0x01, Enum, VideoSources_SourceB_H_Shift);

	// KEY SOURCES
	PARAM_VIDEO(0xA0, 0x01, 0x04, Enum, KeySources_SourceA_TBC_Center);
	PARAM_VIDEO(0xA3, 0x01, 0x04, S16,  KeySources_SourceA_Phase);
	PARAM_VIDEO(0xA0, 0x01, 0x05, Enum, KeySources_SourceB_TBC_Center);
	PARAM_VIDEO(0xA3, 0x01, 0x05, S16,  KeySources_SourceB_Phase);
	PARAM_VIDEO(0xA0, 0x04, 0x02, Enum, KeySources_H_Shift);

	// SOURCE SETTINGS
	PARAM(0x90, 0x70, Bool, SourceSettings_Separate_Side);
	PARAM(0x90, 0x7F, Bool, SourceSettings_KF_XPoint_Hold);

	// RANDOM COLOR
	PARAM(0x91, 0x22, Bool, RandomColor_Enable);
	PARAM(0xAD, 0x40, S16,  RandomColor_Gain_Lum);
	PARAM(0xAD, 0x41, S16,  RandomColor_Gain_Chroma);
	PARAM(0xA5, 0x55, S16,  RandomColor_TileSize_H);
	PARAM(0xA5, 0x56, S16,  RandomColor_TileSize_V);

	// NON-LINEAR SETUP
	PARAM(0x92, 0xA0, Enum, NonLinear_Setup_1);
	PARAM(0x92, 0xC8, Enum, NonLinear_Setup_2);

	// NON-LINEAR CURVE SOURCE
	PARAM(0x92, 0xA2, Enum, NonLinear_CurveSource_Mode);
	PARAM(0x90, 0xA2, Bool, NonLinear_CurveSource_Back_Color);
	PARAM(0x90, 0xA3, Bool, NonLinear_CurveSource_Transformed_Back_Color);
	PARAM(0x92, 0x78, Enum, NonLinear_CurveSource_Source);
	PARAM(0xAD, 0x34, S16,  NonLinear_CurveSource_Color_Lum);
	PARAM(0xAD, 0x34, S16,  NonLinear_CurveSource_Color_Sat);
	PARAM(0xAD, 0x34, S16,  NonLinear_CurveSource_Color_Hue);
	PARAM(0xAD, 0x34, S16,  NonLinear_CurveSource_Color_Speed);

	// PATTERN GENERATOR
	PARAM(0x98, 0x00, S16,  PatternGenerator_Main_Pattern_Number);
	PARAM(0x98, 0x01, S16,  PatternGenerator_Sub_Pattern_Number);
	PARAM(0x92, 0x80, Enum, PatternGenerator_Pattern_Mix_Mode);
	PARAM(0xA9, 0x07, S16,  PatternGenerator_Mix_Ratio);
	PARAM(0xA9, 0x03, S16,  PatternGenerator_Shape_Poly);
	PARAM(0xA9, 0x03, S16,  PatternGenerator_Shape_Star);
	PARAM(0xA9, 0x04, S16,  PatternGenerator_Shape_Pattern);
	PARAM(0xA9, 0x00, S16,  PatternGenerator_Position_X);
	PARAM(0xA9, 0x01, S16,  PatternGenerator_Position_Y);
	PARAM(0xA9, 0x02, S16,  PatternGenerator_Size);
	PARAM(0xA9, 0x13, S16,  PatternGenerator_Soft);
	PARAM(0xA9, 0x14, S16,  PatternGenerator_Aspect);
	PARAM(0xA9, 0x15, S16,  PatternGenerator_Angle);
	PARAM(0xA9, 0x16, S16,  PatternGenerator_Speed);
	PARAM(0x92, 0x82, Enum, PatternGenerator_Rotation);
	PARAM(0x92, 0x83, Bool, PatternGenerator_Invert);

	// PATTERN MODIFY
	PARAM(0x90, 0x8A, Bool, PatternModify_Multi_Pattern);
	PARAM(0xA9, 0x20, S16,  PatternModify_Number_H);
	PARAM(0xA9, 0x21, S16,  PatternModify_Number_V);
	PARAM(0xA9, 0x22, S16,  PatternModify_Number_Shift);
	PARAM(0x90, 0x8B, Bool, PatternModify_ModulationH_Enable);
	PARAM(0xA9, 0x17, S16,  PatternModify_ModulationH_Amplitude);
	PARAM(0xA9, 0x18, S16,  PatternModify_ModulationH_Frequency);
	PARAM(0xA9, 0x19, S16,  PatternModify_ModulationH_Speed);
	PARAM(0x90, 0x8C, Bool, PatternModify_ModulationV_Enable);
	PARAM(0xA9, 0x1A, S16,  PatternModify_ModulationV_Amplitude);
	PARAM(0xA9, 0x1B, S16,  PatternModify_ModulationV_Frequency);
	PARAM(0xA9, 0x1C, S16,  PatternModify_ModulationV_Speed);
	PARAM(0x90, 0x8D, Bool, PatternModify_ModulationFringe_Enable);
	PARAM(0xA9, 0x1D, S16,  PatternModify_ModulationFringe_Amplitude);
	PARAM(0xA9, 0x1E, S16,  PatternModify_ModulationFringe_Frequency);
	PARAM(0xA9, 0x1F, S16,  PatternModify_ModulationFringe_Speed);
	PARAM(0x90, 0xF0, Bool, PatternModify_Lock);
	PARAM(0x90, 0x8B, Bool, PatternModify_Spring_Enable);
	PARAM(0xA9, 0x23, S16,  PatternModify_Spring_Amount);
	PARAM(0x90, 0x87, Bool, PatternModify_Spiral_Enable);
	PARAM(0xA9, 0x24, S16,  PatternModify_Spiral_Amount);

	/* SPECIAL PARAMETERS:
     * 
	 *  17 COLOR MIX - Pattern Number
	 *  21 INPUT FREEZE - Enable & Mode
	 *  101 WAVE - Mode - 3 Bool packets w/ custom logic
	 *  101 WAVE - Lock - 2 Bool packets ""
	 *  111 MIRROR - Mirror - S16, 1 packet w/ custom logic
	 *  112 LENS - Mode - 2 packets w/ custom logic
	 *  201 GRAPHIC SETUP - User Defined Mode - S16, 1 packet w/ custom logic
	 *  202 GRAPHIC CONTROL - All - ""
	 *  203 GRAPHIC 3D SHADOW - All - ""
	 *  204 GRAPHIC SUB PICTURE - All - ""
	 * 
	*/
};
