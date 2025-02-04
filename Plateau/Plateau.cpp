#include "Plateau.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

#include "./controls/SVGLayerKnob.cpp"

Plateau::Plateau(const InstanceInfo& info)
: iplug::Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
  GetParam(kDry)->InitPercentage("Dry", 100);
  GetParam(kWet)->InitPercentage("Wet", 50);
  GetParam(kPreDelay)->InitSeconds("Pre Delay", 0., 0., 0.5, 0.01);
  GetParam(kInputLowDamp)->InitDouble("Input Low Damp", 10., 0., 10., 0.01);
  GetParam(kInputHighDamp)->InitDouble("Input High Damp", 10., 0., 10., 0.01);
  GetParam(kSize)->InitDouble("Size", 0.5, 0., 1., 0.01);
  GetParam(kDiffusion)->InitDouble("Diffusion", 10., 0., 10., 0.01);
  GetParam(kDecay)->InitDouble("Decay", 0.7, 0.1, 0.9999, 0.01);
  GetParam(kReverbLowDamp)->InitDouble("Reverb Low Damp", 10., 0., 10., 0.01);
  GetParam(kReverbHighDamp)->InitDouble("Reverb High Damp", 10., 0., 10., 0.01);
  GetParam(kModSpeed)->InitDouble("Modulation Speed", 0., 0., 1., 0.01);
  GetParam(kModDepth)->InitDouble("Modulation Depth", 0.5, 0., 16., 0.01);
  GetParam(kModShape)->InitDouble("Modulation Shape", 0.5, 0., 1., 0.01);
  GetParam(kFreeze)->InitBool("Freeze", false);
  GetParam(kClear)->InitBool("Clear", false);
  GetParam(kTunedMode)->InitBool("Tuned Mode", false);
  GetParam(kDiffuseInput)->InitBool("Diffuse Input", false);



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
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(89, 109, 42, 42), RoganSVG, RoganBGSVG, RoganFGSVG, kDry));
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(180, 109, 42, 42), RoganSVG, RoganBGSVG, RoganFGSVG, kWet));
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(140, 45, 35, 35), RoganSVG, RoganBGSVG, RoganFGSVG, kPreDelay));
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(93, 198, 56, 56), RoganSVG, RoganBGSVG, RoganFGSVG, kInputLowDamp));
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(166, 198, 56, 56), RoganSVG, RoganBGSVG, RoganFGSVG, kInputHighDamp));
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(56, 298, 56, 56), RoganSVG, RoganBGSVG, RoganFGSVG, kSize));
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(130, 317, 56, 56), RoganSVG, RoganBGSVG, RoganFGSVG, kDiffusion));
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(203, 298, 56, 56), RoganSVG, RoganBGSVG, RoganFGSVG, kDecay));
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(93, 417, 56, 56), RoganSVG, RoganBGSVG, RoganFGSVG, kReverbLowDamp));
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(166, 417, 56, 56), RoganSVG, RoganBGSVG, RoganFGSVG, kReverbHighDamp));
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(56, 518, 56, 56), RoganSVG, RoganBGSVG, RoganFGSVG, kModSpeed));
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(203, 518, 56, 56), RoganSVG, RoganBGSVG, RoganFGSVG, kModDepth));
    pGraphics->AttachControl(new ISVGLayerKnobControl(IRECT::MakeXYWH(130, 543, 56, 56), RoganSVG, RoganBGSVG, RoganFGSVG, kModShape));
    const ISVG LedOffSVG = pGraphics->LoadSVG(LEDOFF_FN);
    const ISVG LedOnSVG = pGraphics->LoadSVG(LEDON_FN);
    const ISVG LedBackgroundSVG = pGraphics->LoadSVG(LEDBG_FN);
  /*  pGraphics->AttachControl(new ISVGButtonControl(IRECT::MakeXYWH(-24, 400, 102, 102),))*/
  };
#endif
}

#if IPLUG_DSP
void Plateau::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const double gain = GetParam(kDry)->Value() / 100.;
  const int nChans = NOutChansConnected();
  
  for (int s = 0; s < nFrames; s++) {
    for (int c = 0; c < nChans; c++) {
      outputs[c][s] = inputs[c][s] * gain;
    }
  }
}
#endif
