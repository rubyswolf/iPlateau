#include "Plateau.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

Plateau::Plateau(const InstanceInfo& info)
: iplug::Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
  GetParam(kDry)->InitPercentage("Dry", 100);
  GetParam(kFreeze1)->InitBool("Global Freeze", false);
  GetParam(kClear1)->InitBool("Global Clear", false);
  GetParam(kEnabled1)->InitBool("Tank 1 Enable", true);
  GetParam(kWet1)->InitPercentage("Wet 1", 50);
  GetParam(kPreDelay1)->InitSeconds("Pre Delay 1", 0., 0., 0.5, 0.01);
  GetParam(kInputLowDamp1)->InitDouble("Input Low Damp 1", 10., 0., 10., 0.01);
  GetParam(kInputHighDamp1)->InitDouble("Input High Damp 1", 10., 0., 10., 0.01);
  GetParam(kSize1)->InitDouble("Size 1", 0.5, 0., 1., 0.01);
  GetParam(kDiffusion1)->InitDouble("Diffusion 1", 10., 0., 10., 0.01);
  GetParam(kDecay1)->InitDouble("Decay 1", 0.7, 0.1, 0.9999, 0.01);
  GetParam(kReverbLowDamp1)->InitDouble("reverb1 Low Damp 1", 10., 0., 10., 0.01);
  GetParam(kReverbHighDamp1)->InitDouble("reverb1 High Damp 1", 10., 0., 10., 0.01);
  GetParam(kModSpeed1)->InitDouble("Modulation Speed 1", 0., 0., 1., 0.01);
  GetParam(kModDepth1)->InitDouble("Modulation Depth 1", 0.5, 0., 16., 0.01);
  GetParam(kModShape1)->InitDouble("Modulation Shape 1", 0.5, 0., 1., 0.01);
  GetParam(kFreeze1)->InitBool("Freeze 1", false);
  GetParam(kClear1)->InitBool("Clear 1", false);
  GetParam(kTunedMode1)->InitBool("Tuned Mode 1", false);
  GetParam(kDiffuseInput1)->InitBool("Diffuse Input 1", true);

  reverb1.setSampleRate(GetSampleRate());
  envelope1.setSampleRate(GetSampleRate());
  envelope1.setTime(0.004f);
  envelope1._value = 1.f;

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
    const IBitmap NeedleFG1PNG = pGraphics->LoadBitmap(NEEDLEFG1_FN);
    const IBitmap NeedleFG2PNG = pGraphics->LoadBitmap(NEEDLEFG2_FN);

    Knobs[0] = new NeedleKnob(IRECT::MakeXYWH(89 - 40, 141 + 50, 42, 42), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kDry);
    Knobs[1] = new NeedleKnob(IRECT::MakeXYWH(180+40, 141+50, 42, 42), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kWet1);
    //Knobs[0] = new NeedleKnob(IRECT::MakeXYWH(140, 87, 35, 35), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kPreDelay1));
    Knobs[2] = new NeedleKnob(IRECT::MakeXYWH(93, 230, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kInputLowDamp1);
    Knobs[3] = new NeedleKnob(IRECT::MakeXYWH(166, 230, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kInputHighDamp1);
    Knobs[4] = new NeedleKnob(IRECT::MakeXYWH(56, 310, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kSize1);
    Knobs[5] = new NeedleKnob(IRECT::MakeXYWH(130, 329, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kDiffusion1);
    Knobs[6] = new NeedleKnob(IRECT::MakeXYWH(203, 310, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kDecay1);
    Knobs[7] = new NeedleKnob(IRECT::MakeXYWH(93, 446, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kReverbLowDamp1);
    Knobs[8] = new NeedleKnob(IRECT::MakeXYWH(166, 446, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kReverbHighDamp1);
    Knobs[9] = new NeedleKnob(IRECT::MakeXYWH(56, 518, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kModSpeed1);
    Knobs[10] = new NeedleKnob(IRECT::MakeXYWH(203, 518, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kModDepth1);
    Knobs[11] = new NeedleKnob(IRECT::MakeXYWH(130, 543, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kModShape1);
    
	for (int i = 0; i < kNumKnobs; i++) {
		pGraphics->AttachControl(Knobs[i]);
	}

    float LEDScale = 0.2453054f;

    const ISVG LedOffSVG = pGraphics->LoadSVG(LEDOFF_FN);
    const ISVG LedOn1SVG = pGraphics->LoadSVG(LEDON1_FN);
    const ISVG LedOn2SVG = pGraphics->LoadSVG(LEDON2_FN);
    const ISVG LedOnBothSVG = pGraphics->LoadSVG(LEDONBOTH_FN);

    Switches[0] = new LEDSwitch(IRECT::MakeXYWH(-24+12.474, 470-65.198-45, 102, 102), LEDScale, LedOffSVG, LedOnBothSVG, LedOnBothSVG, kFreeze);
    Switches[1] = new LEDSwitch(IRECT::MakeXYWH(-24+12.474, 470-65.198+30, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kFreeze1);

	Switches[0]->SetChild(Switches[1]);

    Switches[2] = new LEDSwitch(IRECT::MakeXYWH(-14, 216, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kTunedMode1);
    Switches[3] = new LEDSwitch(IRECT::MakeXYWH(228, 216, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kDiffuseInput1);

    LEDButton* clearButton1 = new LEDButton(IRECT::MakeXYWH(238 - 12.474, 470 - 65.198 + 30, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, [this](IControl* clearControl) {SetParameterValue(kClear1, 1);});

    Buttons[0] = clearButton1;

    Buttons[1] = new LEDButton(IRECT::MakeXYWH(238 - 12.474, 470 - 65.198 - 45, 102, 102), LEDScale, LedOffSVG, LedOnBothSVG, LedOnBothSVG, [this, clearButton1](IControl* clearControl) {SetParameterValue(kClear, 1);clearButton1->SetValue(1.);clearButton1->SetDirty();}, clearButton1);

	for (int i = 0; i < kNumButtons; i++) {
		pGraphics->AttachControl(Buttons[i]);
	}

	//Tank Enable Button
    Switches[4] = new LEDSwitch(IRECT::MakeXYWH(106.5, 112, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG);
    Switches[4]->SetValue(1);

	for (int i = 0; i < kNumSwitches; i++) {
		pGraphics->AttachControl(Switches[i]);
	}


    LEDRadio* tank1Select = new LEDRadio(IRECT::MakeXYWH(106.5 - 20, 40, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, [this](IControl* radioControl) {SelectTank(false);});
    LEDRadio* tank2Select = new LEDRadio(IRECT::MakeXYWH(106.5 + 20, 40, 102, 102), LEDScale, LedOffSVG, LedOn2SVG, [this](IControl* radioControl) {SelectTank(true);});

	tank1Select->SetValue(1.);

    tank1Select->linkControls({ tank2Select });
    tank2Select->linkControls({ tank1Select });

    pGraphics->AttachControl(tank1Select);
    pGraphics->AttachControl(tank2Select);
  };
#endif
}

void Plateau::SelectTank(bool tank2) {
	tank2Selected = tank2;
    for (int i = 0; i < kNumKnobs; i++) {
        Knobs[i]->SelectTank(tank2);
    }
	for (int i = 0; i < kNumSwitches; i++) {
		Switches[i]->SelectTank(tank2);
	}
	for (int i = 0; i < kNumButtons; i++) {
		Buttons[i]->SelectTank(tank2);
	}
}

void Plateau::OnParamChange(int index)
{
    switch (index) {
    case kPreDelay1:
        reverb1.setPreDelay(GetParam(index)->Value());
        break;
    case kInputLowDamp1:
        reverb1.setInputFilterLowCutoffPitch(10.f - GetParam(index)->Value());
        break;
    case kInputHighDamp1:
        reverb1.setInputFilterHighCutoffPitch(GetParam(index)->Value());
        break;
    case kSize1:
    case kTunedMode1:
    {
        float size = GetParam(kSize1)->Value();
        bool tunedMode = GetParam(kTunedMode1)->Value();
        if (tunedMode) {
            reverb1.setTimeScale(0.0025f * powf(2.f, size * 5.f));
        }
        else {
            reverb1.setTimeScale(scale(size * size, 0.f, 1.f, 0.01f, 4.0f));
        }
        break;
    }
    case kDiffusion1:
        reverb1.setTankDiffusion(GetParam(index)->Value());
        break;
    case kDecay1:
    {
        float decay = GetParam(index)->Value();
        reverb1.setDecay(2.f * decay - decay * decay);
        break;
    }
    case kReverbLowDamp1:
        reverb1.setTankFilterLowCutFrequency(10.f - GetParam(index)->Value());
        break;
    case kReverbHighDamp1:
        reverb1.setTankFilterHighCutFrequency(GetParam(index)->Value());
        break;
    case kModSpeed1:
    {
        float modSpeed = GetParam(index)->Value();
        reverb1.setTankModSpeed(modSpeed * modSpeed * 99.f + 1.f);
        break;
    }
    case kModDepth1:
        reverb1.setTankModDepth(GetParam(index)->Value());
        break;
    case kModShape1:
        reverb1.setTankModShape(GetParam(index)->Value());
        break;
    case kDiffuseInput1:
        reverb1.enableInputDiffusion(GetParam(index)->Value());
        break;
    }
}


#if IPLUG_DSP
void Plateau::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const bool clearParam = GetParam(kClear1)->Value() || GetParam(kClear)->Value();
  const bool freezeParam = GetParam(kFreeze1)->Value();
  const double dryParam = GetParam(kDry)->Value()/100;
  const double wetParam = GetParam(kWet1)->Value()/100;
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
                envelope1.setStartEndPoints(1.f, 0.f);
                envelope1.trigger();
            }
            if (fadeOut && envelope1._justFinished) {
                reverb1.clear();
                fadeOut = false;
                fadeIn = true;
                envelope1.setStartEndPoints(0.f, 1.f);
                envelope1.trigger();
            }
            if (fadeIn && envelope1._justFinished) {
                fadeIn = false;
                cleared = true;
                envelope1._value = 1.f;
                SetParameterValue(kClear,0);
                SetParameterValue(kClear1,0);
            }
        }
        envelope1.process();

        if (freezeParam && !frozen) {
            frozen = true;
            reverb1.freeze(frozen);
        }
        else if (!freezeParam && frozen) {
            frozen = false;
            reverb1.freeze(frozen);
        }

        reverb1.process((double)(inputs[0][s] * envelope1._value), (double)(inputs[nChans>1?1:0][s] * envelope1._value));

        outputs[0][s] = inputs[0][s] * dryParam + reverb1.getLeftOutput() * wetParam;
        if (nChans > 1)
        {
            outputs[1][s] = inputs[1][s] * dryParam + reverb1.getRightOutput() * wetParam;
        }
  }
}
#endif
