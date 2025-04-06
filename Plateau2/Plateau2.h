#pragma once

#include "IPlug_include_in_plug_hdr.h"

#include "./dsp/LinearEnvelope.cpp"
#include "./dsp/Dattorro.cpp"

//Custom Controls
#include "./controls/NeedleKnob.cpp"
#include "./controls/LEDButton.cpp"
#include "./controls/LEDSwitch.cpp"
#include "./controls/LEDRadio.cpp"
#include "./controls/NavigatorButton.cpp"

const int kNumPresets = 3;

enum EParams
{
    kDry,
    kFreeze,
    kClear,
    kEnable1,
    kWet1,
    kInputLowDamp1,
    kInputHighDamp1,
    kSize1,
    kDiffusion1,
    kDecay1,
    kReverbLowDamp1,
    kReverbHighDamp1,
    kModSpeed1,
    kModDepth1,
    kModShape1,
    kModVariance1,
    kFreeze1,
    kClear1,
    kTunedMode1,
    kDiffuseInput1,
    kPreDelay1,
    kNesting1,
    kInputNesting1,
	kDiffusionDecay1,
	kVariance1,
	kSoftClip1,
    kInput1,
    kStereoSource1,
    kWidth1,
    kPan1,
    k1to2,
    k1to2Level,
    k1to2Delay,
	k1to2LowDamp,
	k1to2HighDamp,

    kEnable2,
    kWet2,
    kInputLowDamp2,
    kInputHighDamp2,
    kSize2,
    kDiffusion2,
    kDecay2,
    kReverbLowDamp2,
    kReverbHighDamp2,
    kModSpeed2,
    kModDepth2,
    kModShape2,
	kModVariance2,
    kFreeze2,
    kClear2,
    kTunedMode2,
    kDiffuseInput2,
    kPreDelay2,
    kNesting2,
    kInputNesting2,
    kDiffusionDecay2,
	kVariance2,
	kSoftClip2,
	kInput2,
	kStereoSource2,
	kWidth2,
	kPan2,
    k2to1,
    k2to1Level,
    k2to1Delay,
	k2to1LowDamp,
	k2to1HighDamp,

    kDanger,

    kNumParams
};

enum EKnobs {
	kDryKnob,
    kWetKnob,
	kInputLowDampKnob,
	kInputHighDampKnob,
	kSizeKnob,
	kDiffusionKnob,
	kDecayKnob,
	kReverbLowDampKnob,
	kReverbHighDampKnob,
	kModSpeedKnob,
	kModDepthKnob,
	kModShapeKnob,
	kPreDelayKnob,
	kDiffusionDecayKnob,
	kModVarianceKnob,
    kVarianceKnob,
	kInputKnob,
	kStereoSourceKnob,
	kWidthKnob,
	kPanKnob,
	kSendLevel,
	kSendDelay,
	kSendLowDamp,
	kSendHighDamp,
	kNumKnobs
};

const int kNumSwitches = 9;
const int kNumButtons = 2;
const int kNumPages = 3;
const int kNumSVGs = 5;

using namespace iplug;
using namespace igraphics;

class Plateau2 final : public Plugin
{
public:
  Plateau2(const InstanceInfo& info);
#if IPLUG_DSP // http://bit.ly/2S64BDd
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void ChangePage(int direction, const ISVG PageBackgrounds[kNumPages], const ISVG NextButtons[kNumPages], const ISVG PreviousButtons[kNumPages]);
  void UpdatePageVisibility();
  void UpdateSendVisibility();
  void OnParamChange(int index) override;
  bool WindowIsOpen();
  void SelectTank(bool tank2);
#endif
    private:
        Dattorro reverb1;
        double reverbOut1;
        std::tuple<double, double> sourceBalance1 = { 0, 0 };
        std::tuple<double, double> panBalance1 = { 0, 0 };
        LinearEnvelope envelope1;
        InterpDelay<double> send1To2Delay;
		OnePoleLPFilter send1To2LP = OnePoleLPFilter(22000.0);
		OnePoleHPFilter send1To2HP = OnePoleHPFilter(0.0);
        bool clear1 = false;
        bool cleared1 = true;
        bool fadeOut1 = false;
        bool fadeIn1 = false;
        bool frozen1 = false;
        
        Dattorro reverb2;
        double reverbOut2;
        std::tuple<double, double> sourceBalance2 = { 0, 0 };
        std::tuple<double, double> panBalance2 = { 0, 0 };
        LinearEnvelope envelope2;
        InterpDelay<double> send2To1Delay;
		OnePoleLPFilter send2To1LP = OnePoleLPFilter(22000.0);
		OnePoleHPFilter send2To1HP = OnePoleHPFilter(0.0);
        bool clear2 = false;
        bool cleared2 = true;
        bool fadeOut2 = false;
        bool fadeIn2 = false;
        bool frozen2 = false;

		bool tank2Selected = false;
		ISVGControl* PageBackgroundControl;
        NavigatorButton* NextButtonControl;
        NavigatorButton* PrevButtonControl;


        NeedleKnob* Knobs[kNumKnobs];
        LEDSwitch* Switches[kNumSwitches];
        LEDButton* Buttons[kNumButtons];
		ISVGControl* SVGs[kNumSVGs];


        int currentPage = 0;
};
