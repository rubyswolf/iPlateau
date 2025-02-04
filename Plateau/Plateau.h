#pragma once

#include "IPlug_include_in_plug_hdr.h"

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
#endif
};
