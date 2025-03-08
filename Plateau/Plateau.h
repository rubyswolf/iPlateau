#pragma once

#include "IPlug_include_in_plug_hdr.h"

#include "./dsp/LinearEnvelope.cpp"
#include "./dsp/Dattorro.cpp"

//Custom Controls
#include "./controls/NeedleKnob.cpp"
#include "./controls/LEDButton.cpp"
#include "./controls/LEDSwitch.cpp"
#include "./controls/LEDRadio.cpp"

const int kNumPresets = 1;

enum EParams
{
    kDry,
    kFreeze,
    kClear,
    kEnabled1,
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
    kNumParams
};

const int kNumKnobs = 12;
const int kNumSwitches = 5;
const int kNumButtons = 2;

using namespace iplug;
using namespace igraphics;

class Plateau final : public Plugin
{
public:
  Plateau(const InstanceInfo& info);


#if IPLUG_DSP // http://bit.ly/2S64BDd
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void OnParamChange(int index) override;
  void SelectTank(bool tank2);
#endif
    private:
        Dattorro reverb1;
        LinearEnvelope envelope1;

        bool clear = false;
        bool cleared = true;
        bool fadeOut = false;
        bool fadeIn = false;

        bool frozen = false;

		bool tank2Selected = false;
		NeedleKnob* Knobs[kNumKnobs];
		LEDSwitch* Switches[kNumSwitches];
		LEDButton* Buttons[kNumButtons];
};