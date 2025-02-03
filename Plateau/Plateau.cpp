#include "Plateau.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

#include "./controls/SVGLayerKnob.cpp"

Plateau::Plateau(const InstanceInfo& info)
: iplug::Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
  GetParam(kGain)->InitDouble("Gain", 0., 0., 100.0, 0.01, "%");



#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {

    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachSVGBackground(BACKGROUND_FN);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    const IRECT b = pGraphics->GetBounds();
    const ISVG RoganSVG = pGraphics->LoadSVG(ROGAN_FN);
    const ISVG RoganBGSVG = pGraphics->LoadSVG(ROGANBG_FN);
    const ISVG RoganFGSVG = pGraphics->LoadSVG(ROGANFG_FN);
    pGraphics->AttachControl(new ISVGLayerKnobControl(b.GetCentredInside(100).GetVShifted(-100), RoganSVG, RoganBGSVG, RoganFGSVG, kGain));

  };
#endif
}

#if IPLUG_DSP
void Plateau::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const double gain = GetParam(kGain)->Value() / 100.;
  const int nChans = NOutChansConnected();
  
  for (int s = 0; s < nFrames; s++) {
    for (int c = 0; c < nChans; c++) {
      outputs[c][s] = inputs[c][s] * gain;
    }
  }
}
#endif
