#pragma once

// GENERAL - SOURCES

enum FillSource
{
	FillSource_FlatColor   = 0x00,
	FillSource_HueRot      = 0x01,
	FillSource_SuperBlack  = 0x02,
	FillSource_MixColor    = 0x03,
	FillSource_ExtVideo    = 0x04,
	FillSource_RandomColor = 0x05,
	FillSource_FreezeVideo = 0x07,
	FillSource_InputVideo  = 0x08
};

// GENERAL - VIDEO

enum VideoTiming
{
	VideoTiming_Frame  = 0x00,
	VideoTiming_Field1 = 0x01,
	VideoTiming_Field2 = 0x02
};

enum VideoDelegation
{
	VideoDelegation_VideoKey = 0x00,
	VideoDelegation_Video    = 0x01,
	VideoDelegation_Key      = 0x02
};

enum VideoInterpolation
{
	VideoInterpolation_AdaptiveYC = 0x04,
	VideoInterpolation_Adaptive   = 0x00,
	VideoInterpolation_Frame      = 0x02,
	VideoInterpolation_Field      = 0x01
};

enum VideoKeySource
{
	VideoKeySource_Internal  = 0x01,
	VideoKeySource_External  = 0x02,
	VideoKeySource_Luminance = 0x03,
	VideoKeySource_Off       = 0x04
};

enum VideoTBCCenter
{
	VideoTBCCenter_00H = 0x00,
	VideoTBCCenter_05H = 0x01,
	VideoTBCCenter_10H = 0x02,
	VideoTBCCenter_15H = 0x03
};

enum VideoHShift
{
	VideoHShift_Off   = 0x00,
	VideoHShift_Left  = 0x03,
	VideoHShift_Right = 0x07
};

enum VideoInput
{
	VideoInput_A = 0x00,
	VideoInput_B = 0x01
};

enum KeyInput
{
	KeyInput_A = 0x04,
	KeyInput_B = 0x05
};

// GENERAL - NON-LINEAR

enum NonLinearWaveForm
{
	NonLinearWaveForm_Triangle  = 0x02,
	NonLinearWaveForm_Rectangle = 0x03,
	NonLinearWaveForm_Sine      = 0x04,
	NonLinearWaveForm_Parabola  = 0x05,
	NonLinearWaveForm_Cubic     = 0x06,
	NonLinearWaveForm_Circle    = 0x07
};

// 14 DROP SHADOW

enum DropShadowMode
{
	DropShadowMode_Auto   = 0x00,
	DropShadowMode_Target = 0x02,
	DropShadowMode_3D     = 0x03
};

enum DropShadowLightSource
{
	DropShadowLightSource_Spot  = 0x00,
	DropShadowLightSource_Plane = 0x01
};

enum DropShadowDensityType
{
	DropShadowDensityType_Flat  = 0x00,
	DropShadowDensityType_Depth = 0x01
};

enum DropShadowSoftnessType
{
	DropShadowSoftnessType_Flat  = 0x00,
	DropShadowSoftnessType_Depth = 0x01
};

// 17 COLOR MIX

enum ColorMixPatternSource
{
	ColorMixPatternSource_Wipe          = 0x00,
	ColorMixPatternSource_UtilityFreeze = 0x01
};

// 18 BEVELED EDGE

enum BeveledEdgePattern
{
	BeveledEdgePattern_Center     = 0x21,
	BeveledEdgePattern_UpperLeft  = 0x05,
	BeveledEdgePattern_UpperRight = 0x06,
	BeveledEdgePattern_LowerLeft  = 0x07,
	BeveledEdgePattern_LowerRight = 0x08
};

enum BeveledEdgeMode
{
	BeveledEdgeMode_Light = 0x00,
	BeveledEdgeMode_Matte = 0x01
};

// 21 INPUT FREEZE

enum InputFreezeMode
{
	InputFreezeMode_Frame      = 0x01,
	InputFreezeMode_TimeStrobe = 0x02,
	InputFreezeMode_KF_Strobe  = 0x03,
	InputFreezeMode_Film       = 0x04
};

// 22 MOTION DECAY

enum MotionDecayMixMode
{
	MotionDecayMixMode_Hard = 0x00,
	MotionDecayMixMode_Soft = 0x02
};

// 24 WIND

enum WindMode
{
	WindMode_Trail  = 0x00,
	WindMode_Motion = 0x01
};

// 26 MULTI FREEZE

enum MultiFreezeNumber
{
	MultiFreezeNumber_4  = 0x02,
	MultiFreezeNumber_9  = 0x03,
	MultiFreezeNumber_16 = 0x04,
	MultiFreezeNumber_25 = 0x05
};

// 27 UTILITY FREEZE 

enum UtilityFreezeInputSource
{
	UtilityFreezeInputSource_Input    = 0x00,
	UtilityFreezeInputSource_ExtVideo = 0x01
};

// 36 BRICK

enum BrickMode
{
	BrickMode_Crop        = 0x00,
	BrickMode_Compression = 0x01
};

// 38 DUALITY

enum DualityPriority
{
	DualityPriority_Over  = 0x00,
	DualityPriority_Under = 0x01
};

// 45 MASK

enum MaskDestination
{
	MaskDestination_Modify        = 0x01,
	MaskDestination_DefocusBlur   = 0x02,
	MaskDestination_Metal         = 0x03,
	MaskDestination_CCR_Primary   = 0x04,
	MaskDestination_CCR_Secondary = 0x05,
	MaskDestination_CCR_Luma      = 0x06
};

// 46 SKETCH

enum SketchMode
{
	SketchMode_Enhance = 0x00,
	SketchMode_Sketch  = 0x01,
	SketchMode_Draw1   = 0x02,
	SketchMode_Draw2   = 0x03,
	SketchMode_Relief  = 0x04
};

// 47 METAL EFFECT

enum MetalEffectInput
{
	MetalEffectInput_Main = 0x00,
	MetalEffectInput_Sub  = 0x01
};

enum MetalEffectMode
{
	MetalEffectMode_Gold    = 0x00,
	MetalEffectMode_Silver  = 0x01,
	MetalEffectMode_Rainbow = 0x02,
	MetalEffectMode_Psyche  = 0x03
};

// 48 COLOR CORRECTION

enum ColorCorrectionInput
{
	ColorCorrectionInput_Main = 0x00,
	ColorCorrectionInput_Sub  = 0x01
};

enum ColorCorrectionLumaProcessMode
{
	ColorCorrectionLumaProcessMode_TintAdd  = 0x00,
	ColorCorrectionLumaProcessMode_ColorMod = 0x01,
	ColorCorrectionLumaProcessMode_MixColor = 0x02,
	ColorCorrectionLumaProcessMode_HueMod   = 0x03
};

enum ColorCorrectionLumaProcessDirction
{
	ColorCorrectionLumaProcessDirction_CW  = 0x00,
	ColorCorrectionLumaProcessDirction_CCW = 0x01
};

// 57 EXT VIDEO
enum ExtVideoOutputSource
{
	ExtVideoOutputSource_ExtVideo = 0x00,
	ExtVideoOutputSource_KeyZ     = 0x02
};

// 101 WAVE

enum WaveMode
{
	WaveMode_HV    = 0x00,
	WaveMode_Slant = 0x01,
	WaveMode_Size  = 0x02
};

// 102 MOSAIC GLASS

enum MosaicGlassMode
{
	MosaicGlassMode_HV    = 0x00,
	MosaicGlassMode_Slant = 0x01
};

// 104 RIPPLE

enum RippleMode
{
	RippleMode_Radial  = 0x01,
	RippleMode_Angular = 0x02,
	RippleMode_Both    = 0x03
};

// 112 LENS

enum LensMode
{
	LensMode_Circle    = 0x00,
	LensMode_Rectangle = 0x01,
	LensMode_Star      = 0x02,
	LensMode_Heart     = 0x03,
	LensMode_Bar       = 0x04,
	LensMode_Cross     = 0x05
};

// 132 EXPLOSION

enum ExplosionMaskPattern
{
	ExplosionMaskPattern_Rectangle = 0x01,
	ExplosionMaskPattern_Circle    = 0x02,
	ExplosionMaskPattern_Star      = 0x03,
	ExplosionMaskPattern_Heart     = 0x04,
	ExplosionMaskPattern_Ellipse   = 0x05
};

// 134 BLIND

enum BlindMode
{
	BlindMode_Bar   = 0x01,
	BlindMode_Wedge = 0x02
};

// 137 MELT

enum MeltPattern
{
	MeltPattern_Triangle  = 0x02,
	MeltPattern_Rectangle = 0x03,
	MeltPattern_Sine      = 0x04,
	MeltPattern_Parabola  = 0x05,
	MeltPattern_Cubic     = 0x06,
	MeltPattern_Circle    = 0x07,
	MeltPattern_Melt1     = 0x41,
	MeltPattern_Melt2     = 0x42
};

enum MeltDirection
{
	MeltDirection_Down = 0x00,
	MeltDirection_Up   = 0x01
};

// 201 GRAPHIC SETUP

enum GraphicSetupMode
{
	GraphicSetupMode_Default     = 0x01,
	GraphicSetupMode_UserDefined = 0x02
};

enum GraphicSetupRecoveryTime
{
	GraphicSetupRecoveryTime_05 = 0x00,
	GraphicSetupRecoveryTime_30 = 0x01,
	GraphicSetupRecoveryTime_50 = 0x02
};

// 301 LIGHTING

enum LightingPattern
{
	LightingPattern_Plane  = 0x00,
	LightingPattern_Circle = 0x01,
	LightingPattern_Bar    = 0x03
};

enum LightingArea
{
	LightingArea_Normal = 0x00,
	LightingArea_Invert = 0x02
};

// 302 SPOTLIGHT

enum SpotlightMixMode
{
	SpotlightMixMode_Add = 0x00,
	SpotlightMixMode_Mix = 0x01
};

// 303 TARGET LIGHT

enum TargetLightPattern
{
	TargetLightPattern_Circle = 0x00,
	TargetLightPattern_Box    = 0x01,
	TargetLightPattern_Wipe   = 0x02
};

enum TargetLightMixMode
{
	TargetLightMixMode_Add = 0x00,
	TargetLightMixMode_Mix = 0x01
};

enum TargetLightArea
{
	TargetLightArea_VideoOnly      = 0x01,
	TargetLightArea_BackgroundOnly = 0x02,
	TargetLightArea_All            = 0x03
};

// 304 TARGET SPOTLIGHT

enum TargetSpotlightReflectMode
{
	TargetSpotlightReflectMode_Plane     = 0x00,
	TargetSpotlightReflectMode_GlossWipe = 0x08,
	TargetSpotlightReflectMode_MatteWipe = 0x09
};

// 715 OUTPUT CONTROL

enum OutputControlRounding
{
	OutputControlRounding_10Bit = 0x00,
	OutputControlRounding_8Bit  = 0x01
};

enum OutputControlAnalogSignal
{
	OutputControlAnalogSignal_BetaCam0  = 0x00,
	OutputControlAnalogSignal_RGB       = 0x04,
	OutputControlAnalogSignal_SMPTE     = 0x10,
	OutputControlAnalogSignal_BetaCam75 = 0x20
};

enum OutputControlVPhase
{
	OutputControlVPhase_0H = 0x00,
	OutputControlVPhase_1H = 0x01
};

enum OutputControlBlanking
{
	OutputControlBlanking_Narrow = 0x00,
	OutputControlBlanking_Wide   = 0x01
};

// 716 PROCESS CONTROL

enum ProcessControlFilterMode
{
	ProcessControlFilterMode_Mode1 = 0x00,
	ProcessControlFilterMode_Mode2 = 0x01
};

enum ProcessControlFilterType
{
	ProcessControlFilterType_Flat  = 0x00,
	ProcessControlFilterType_Depth = 0x01
};

enum ProcessControlExternalKey
{
	ProcessControlExternalKey_Process = 0x00,
	ProcessControlExternalKey_Through = 0x01
};

enum ProcessControlKeyFilter
{
	ProcessControlKeyFilter_Off     = 0x00,
	ProcessControlKeyFilter_LowPass = 0x01,
	ProcessControlKeyFilter_Trap    = 0x02
};

enum ProcessControlAnalogExtKey
{
	ProcessControlAnalogExtKey_WithSync = 0x00,
	ProcessControlAnalogExtKey_WithoutSync = 0x01
};

enum ProcessControlAdaptiveMode
{
	ProcessControlAdaptiveMode_1 = 0x01,
	ProcessControlAdaptiveMode_2 = 0x02,
	ProcessControlAdaptiveMode_3 = 0x03,
	ProcessControlAdaptiveMode_4 = 0x04
};

// RECURSIVE TRAILS

enum RecursiveTrailsMode
{
	RecursiveTrailsMode_KeyframeStrobe = 0x03,
	RecursiveTrailsMode_MotionDecay    = 0x05,
	RecursiveTrailsMode_Trail          = 0x06,
	RecursiveTrailsMode_MultiFreeze    = 0x09,
	RecursiveTrailsMode_Wind           = 0x0B
};

enum RecursiveTrailsPriority
{
	RecursiveTrailsPriority_Over  = 0x00,
	RecursiveTrailsPriority_Under = 0x01,
	RecursiveTrailsPriority_Mix   = 0x02
};

enum RecursiveTrailsTrailType
{
	RecursiveTrailsTrailType_Live   = 0x00,
	RecursiveTrailsTrailType_Freeze = 0x01
};

enum RecursiveTrailsHuePath
{
	RecursiveTrailsHuePath_Module = 0x00,
	RecursiveTrailsHuePath_Swing  = 0x01
};

enum RecursiveTrailsDustPattern
{
	RecursiveTrailsDustPattern_Form1 = 0x01,
	RecursiveTrailsDustPattern_Form2 = 0x02
};

// NON-LINEAR CURVE SOURCE

enum NonLinearCurveSourceMode
{
	NonLinearCurveSourceMode_FrontBack = 0x00,
	NonLinearCurveSourceMode_Front     = 0x01,
	NonLinearCurveSourceMode_Back      = 0x02
};

// PATTERN GENERATOR

enum PatternGeneratorMixMode
{
	PatternGeneratorMixMode_Off = 0x00,
	PatternGeneratorMixMode_Mix = 0x01,
	PatternGeneratorMixMode_NAM = 0x02
};