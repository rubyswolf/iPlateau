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
    kNumParams
};

const int kNumKnobs = 13;
const int kNumSwitches = 5;
const int kNumButtons = 2;
const int kNumPages = 2;

using namespace iplug;
using namespace igraphics;

class Plateau final : public Plugin
{
public:
  Plateau(const InstanceInfo& info);

  bool initalizedInterface = false;


#if IPLUG_DSP // http://bit.ly/2S64BDd
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void ChangePage(int direction, const ISVG PageBackgrounds[kNumPages], const ISVG NextButtons[kNumPages], const ISVG PreviousButtons[kNumPages]);
  void UpdatePageVisibility();
  void OnParamChange(int index) override;
  void SelectTank(bool tank2);
  void ProcessReverb(sample** inputs, sample** outputs, int nFrames, int nChans, Dattorro& reverb, LinearEnvelope& envelope, bool& clear, bool& cleared, bool& fadeOut, bool& fadeIn, bool& frozen, int kClear, int kFreeze, int kWet);
#endif
    private:
        Dattorro reverb1;
        LinearEnvelope envelope1;
        bool clear1 = false;
        bool cleared1 = true;
        bool fadeOut1 = false;
        bool fadeIn1 = false;
        bool frozen1 = false;
        
        Dattorro reverb2;
        LinearEnvelope envelope2;
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


        int currentPage = 0;
};