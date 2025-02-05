#pragma once

#include "IPlug_include_in_plug_hdr.h"

#include "./dsp/LinearEnvelope.cpp"
#include "./dsp/Dattorro.cpp"

const int kNumPresets = 1;

enum EParams
{
    kDry,
    kWet,
    kPreDelay,
    kInputLowDamp,
    kInputHighDamp,
    kSize,
    kDiffusion,
    kDecay,
    kReverbLowDamp,
    kReverbHighDamp,
    kModSpeed,
    kModDepth,
    kModShape,
    kFreeze,
    kClear,
    kTunedMode,
    kDiffuseInput,
  kNumParams
};

using namespace iplug;
using namespace igraphics;

class Plateau final : public Plugin
{
public:
  Plateau(const InstanceInfo& info);


#if IPLUG_DSP // http://bit.ly/2S64BDd
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void OnParamChange(int index) override;
#endif
    private:
        Dattorro reverb;
        LinearEnvelope envelope;

        bool clear = false;
        bool cleared = true;
        bool fadeOut = false;
        bool fadeIn = false;

        bool frozen = false;
};
