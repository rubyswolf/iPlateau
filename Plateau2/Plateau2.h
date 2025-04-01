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

const int kNumPresets = 1;

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
    kFreeze1,
    kClear1,
    kTunedMode1,
    kDiffuseInput1,
    kPreDelay1,
    kNesting1,
    kInputNesting1,
	kDiffusionDecay1,
    kInput1,
    kStereoSource1,
    kWidth1,
    kPan1,
    k1to2,
    k1to2Level,
    k1to2Delay,

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
    kFreeze2,
    kClear2,
    kTunedMode2,
    kDiffuseInput2,
    kPreDelay2,
    kNesting2,
    kInputNesting2,
    kDiffusionDecay2,
	kInput2,
	kStereoSource2,
	kWidth2,
	kPan2,
    k2to1,
    k2to1Level,
    k2to1Delay,

    kDanger,

    kNumParams
};

const int kNumKnobs = 20;
const int kNumSwitches = 8;
const int kNumButtons = 2;
const int kNumPages = 3;
const int kNumSVGs = 4;

using namespace iplug;
using namespace igraphics;

class Plateau2 final : public Plugin
{
public:
  Plateau2(const InstanceInfo& info);

  bool initalizedInterface = false;


#if IPLUG_DSP // http://bit.ly/2S64BDd
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void ChangePage(int direction, const ISVG PageBackgrounds[kNumPages], const ISVG NextButtons[kNumPages], const ISVG PreviousButtons[kNumPages]);
  void UpdatePageVisibility();
  void UpdateSendVisibility();
  void OnParamChange(int index) override;
  void SelectTank(bool tank2);
#endif
    private:
        Dattorro reverb1;
        double reverbOut1;
        std::tuple<double, double> sourceBalance1 = { 0, 0 };
        std::tuple<double, double> panBalance1 = { 0, 0 };
        LinearEnvelope envelope1;
        InterpDelay<double> send1To2Delay;
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