#include "Plateau.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

//Custom Controls
#include "./controls/NeedleKnob.cpp"
#include "./controls/LEDButton.cpp"
#include "./controls/LEDSwitch.cpp"

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
    const ISVG NeedleSVG = pGraphics->LoadSVG(NEEDLE_FN);
    const ISVG NeedleBGSVG = pGraphics->LoadSVG(NEEDLEBG_FN);
    const IBitmap NeedleFGPNG = pGraphics->LoadBitmap(NEEDLEFG_FN);
    pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(89-40, 141+50, 42, 42), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kDry));
    pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(180+40, 141+50, 42, 42), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kWet));
    //pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(140, 87, 35, 35), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kPreDelay));
    pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(93, 230, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kInputLowDamp));
    pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(166, 230, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kInputHighDamp));
    pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(56, 310, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kSize));
    pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(130, 329, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kDiffusion));
    pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(203, 310, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kDecay));
    pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(93, 446, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kReverbLowDamp));
    pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(166, 446, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kReverbHighDamp));
    pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(56, 518, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kModSpeed));
    pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(203, 518, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kModDepth));
    pGraphics->AttachControl(new NeedleKnob(IRECT::MakeXYWH(130, 543, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFGPNG, kModShape));

    float LEDScale = 0.2453054f;

    const std::initializer_list<ISVG> LedSVGs = { pGraphics->LoadSVG(LEDOFF_FN), pGraphics->LoadSVG(LEDON_FN) };

    pGraphics->AttachControl(new LEDSwitch(IRECT::MakeXYWH(-24+12.474f, 470-65.198f, 102, 102), LEDScale, LedSVGs, kFreeze));
    pGraphics->AttachControl(new LEDSwitch(IRECT::MakeXYWH(-14, 216, 102, 102), LEDScale, LedSVGs, kTunedMode));
    pGraphics->AttachControl(new LEDSwitch(IRECT::MakeXYWH(228, 216, 102, 102), LEDScale, LedSVGs, kDiffuseInput));

    pGraphics->AttachControl(new LEDButton(IRECT::MakeXYWH(238-12.474f, 470-65.198f, 102, 102), LEDScale, LedSVGs, [this](IControl* clearControl) {SetParameterValue(kClear, 1);}));

    IControl* cButton = new LEDSwitch(IRECT::MakeXYWH(106.5, 112, 102, 102), LEDScale, LedSVGs);

    cButton->SetValue(1);

    pGraphics->AttachControl(cButton);
    pGraphics->AttachControl(new LEDSwitch(IRECT::MakeXYWH(106.5-20, 40, 102, 102), LEDScale, LedSVGs));
    pGraphics->AttachControl(new LEDSwitch(IRECT::MakeXYWH(106.5+20, 40, 102, 102), LEDScale, LedSVGs));
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
