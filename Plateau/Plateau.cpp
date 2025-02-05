#include "Plateau.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

#include "./controls/SVGLayerKnob.cpp"

#include "./controls/IBButtonHold.cpp"

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
  GetParam(kDiffuseInput)->InitBool("Diffuse Input", true);

  reverb.setSampleRate(GetSampleRate());
  envelope.setSampleRate(GetSampleRate());
  envelope.setTime(0.004f);
  envelope._value = 1.f;

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {

    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachSVGBackground(BACKGROUND_FN);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
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

    const IBitmap LedPNG = pGraphics->LoadBitmap(LED_FN,2,true);
    pGraphics->AttachControl(new IBSwitchControl(IRECT::MakeXYWH(-24, 400, 102, 102), LedPNG, kFreeze));
    pGraphics->AttachControl(new IBSwitchControl(IRECT::MakeXYWH(-14, 184, 102, 102), LedPNG, kTunedMode));
    pGraphics->AttachControl(new IBSwitchControl(IRECT::MakeXYWH(228, 184, 102, 102), LedPNG, kDiffuseInput));

    pGraphics->AttachControl(new IBButtonHoldControl(IRECT::MakeXYWH(238, 400, 102, 102), LedPNG, [this](IControl* clearControl) {SetParameterValue(kClear, 1);}));
  };
#endif
}

void Plateau::OnParamChange(int index)
{
    switch (index) {
    case kPreDelay:
        reverb.setPreDelay(GetParam(index)->Value());
        break;
    case kInputLowDamp:
        reverb.setInputFilterLowCutoffPitch(10.f - GetParam(index)->Value());
        break;
    case kInputHighDamp:
        reverb.setInputFilterHighCutoffPitch(GetParam(index)->Value());
        break;
    case kSize:
    case kTunedMode:
    {
        float size = GetParam(kSize)->Value();
        bool tunedMode = GetParam(kTunedMode)->Value();
        if (tunedMode) {
            reverb.setTimeScale(0.0025f * powf(2.f, size * 5.f));
        }
        else {
            reverb.setTimeScale(scale(size * size, 0.f, 1.f, 0.01f, 4.0f));
        }
        break;
    }
    case kDiffusion:
        reverb.setTankDiffusion(GetParam(index)->Value());
        break;
    case kDecay:
    {
        float decay = GetParam(index)->Value();
        reverb.setDecay(2.f * decay - decay * decay);
        break;
    }
    case kReverbLowDamp:
        reverb.setTankFilterLowCutFrequency(10.f - GetParam(index)->Value());
        break;
    case kReverbHighDamp:
        reverb.setTankFilterHighCutFrequency(GetParam(index)->Value());
        break;
    case kModSpeed:
    {
        float modSpeed = GetParam(index)->Value();
        reverb.setTankModSpeed(modSpeed * modSpeed * 99.f + 1.f);
        break;
    }
    case kModDepth:
        reverb.setTankModDepth(GetParam(index)->Value());
        break;
    case kModShape:
        reverb.setTankModShape(GetParam(index)->Value());
        break;
    case kDiffuseInput:
        reverb.enableInputDiffusion(GetParam(index)->Value());
        break;
    }
}


#if IPLUG_DSP
void Plateau::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const bool clearParam = GetParam(kClear)->Value();
  const bool freezeParam = GetParam(kFreeze)->Value();
  const double dryParam = GetParam(kDry)->Value()/100;
  const double wetParam = GetParam(kWet)->Value()/100;
  const int nChans = NOutChansConnected();
  
  for (int s = 0; s < nFrames; s++) {
        if (clearParam && !clear && cleared) {
            cleared = false;
            clear = true;
        }
        else if (!clearParam && cleared) {
            clear = false;
        }

        if (clear) {
            if (!cleared && !fadeOut && !fadeIn) {
                fadeOut = true;
                envelope.setStartEndPoints(1.f, 0.f);
                envelope.trigger();
            }
            if (fadeOut && envelope._justFinished) {
                reverb.clear();
                fadeOut = false;
                fadeIn = true;
                envelope.setStartEndPoints(0.f, 1.f);
                envelope.trigger();
            }
            if (fadeIn && envelope._justFinished) {
                fadeIn = false;
                cleared = true;
                envelope._value = 1.f;
                SetParameterValue(kClear,0);
            }
        }
        envelope.process();

        if (freezeParam && !frozen) {
            frozen = true;
            reverb.freeze(frozen);
        }
        else if (!freezeParam && frozen) {
            frozen = false;
            reverb.freeze(frozen);
        }

        reverb.process((double)(inputs[0][s] * envelope._value), (double)(inputs[nChans>1?1:0][s] * envelope._value));

        outputs[0][s] = inputs[0][s] * dryParam + reverb.getLeftOutput() * wetParam;
        if (nChans > 1)
        {
            outputs[1][s] = inputs[1][s] * dryParam + reverb.getRightOutput() * wetParam;
        }
  }
}
#endif
