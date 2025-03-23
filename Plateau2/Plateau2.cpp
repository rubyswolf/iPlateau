#include "Plateau2.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

Plateau2::Plateau2(const InstanceInfo& info)
: iplug::Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
  GetParam(kDry)->InitPercentage("Dry", 100);
  GetParam(kFreeze)->InitBool("Global Freeze", false);
  GetParam(kClear)->InitBool("Global Clear", false);

  GetParam(kEnable1)->InitBool("Tank 1 Enable", true);
  GetParam(kWet1)->InitPercentage("Wet 1", 50);
  GetParam(kPreDelay1)->InitSeconds("Pre Delay 1", 0., 0., 0.5, 0.01);
  GetParam(kInputLowDamp1)->InitDouble("Input Low Damp 1", 10., 0., 10., 0.01);
  GetParam(kInputHighDamp1)->InitDouble("Input High Damp 1", 10., 0., 10., 0.01);
  GetParam(kSize1)->InitDouble("Size 1", 0.5, 0., 1., 0.01);
  GetParam(kDiffusion1)->InitDouble("Diffusion 1", 10., 0., 10., 0.01);
  GetParam(kDecay1)->InitDouble("Decay 1", 0.7, 0.1, 0.9999, 0.01);
  GetParam(kReverbLowDamp1)->InitDouble("Reverb Low Damp 1", 10., 0., 10., 0.01);
  GetParam(kReverbHighDamp1)->InitDouble("Reverb High Damp 1", 10., 0., 10., 0.01);
  GetParam(kModSpeed1)->InitDouble("Modulation Speed 1", 0., 0., 1., 0.01);
  GetParam(kModDepth1)->InitDouble("Modulation Depth 1", 0.5, 0., 16., 0.01);
  GetParam(kModShape1)->InitDouble("Modulation Shape 1", 0.5, 0., 1., 0.01);
  GetParam(kFreeze1)->InitBool("Freeze 1", false);
  GetParam(kClear1)->InitBool("Clear 1", false);
  GetParam(kTunedMode1)->InitBool("Tuned Mode 1", false);
  GetParam(kDiffuseInput1)->InitBool("Diffuse Input 1", true);

  GetParam(kEnable2)->InitBool("Tank 2 Enable", false);
  GetParam(kWet2)->InitPercentage("Wet 2", 50);
  GetParam(kPreDelay2)->InitSeconds("Pre Delay 2", 0., 0., 0.5, 0.01);
  GetParam(kInputLowDamp2)->InitDouble("Input Low Damp 2", 10., 0., 10., 0.01);
  GetParam(kInputHighDamp2)->InitDouble("Input High Damp 2", 10., 0., 10., 0.01);
  GetParam(kSize2)->InitDouble("Size 2", 0.5, 0., 1., 0.01);
  GetParam(kDiffusion2)->InitDouble("Diffusion 2", 10., 0., 10., 0.01);
  GetParam(kDecay2)->InitDouble("Decay 2", 0.7, 0.1, 0.9999, 0.01);
  GetParam(kReverbLowDamp2)->InitDouble("Reverb Low Damp 2", 10., 0., 10., 0.01);
  GetParam(kReverbHighDamp2)->InitDouble("Reverb High Damp 2", 10., 0., 10., 0.01);
  GetParam(kModSpeed2)->InitDouble("Modulation Speed 2", 0., 0., 1., 0.01);
  GetParam(kModDepth2)->InitDouble("Modulation Depth 2", 0.5, 0., 16., 0.01);
  GetParam(kModShape2)->InitDouble("Modulation Shape 2", 0.5, 0., 1., 0.01);
  GetParam(kFreeze2)->InitBool("Freeze 2", false);
  GetParam(kClear2)->InitBool("Clear 2", false);
  GetParam(kTunedMode2)->InitBool("Tuned Mode 2", false);
  GetParam(kDiffuseInput2)->InitBool("Diffuse Input 2", true);


  reverb1.setSampleRate(GetSampleRate());
  envelope1.setSampleRate(GetSampleRate());
  envelope1.setTime(0.004f);
  envelope1._value = 1.f;
  
  reverb2.setSampleRate(GetSampleRate());
  envelope2.setSampleRate(GetSampleRate());
  envelope2.setTime(0.004f);
  envelope2._value = 1.f;

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {

    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachSVGBackground(BACKGROUND_FN);

    ISVG PageBackgrounds[kNumPages] = { pGraphics->LoadSVG(PAGEMAIN_FN), pGraphics->LoadSVG(PAGEEXTRAS_FN) };
	ISVG NextButtons[kNumPages] = { pGraphics->LoadSVG(NEXTEXTRAS_FN), pGraphics->LoadSVG(NEXTMAIN_FN) };
	ISVG PrevButtons[kNumPages] = { pGraphics->LoadSVG(PREVEXTRAS_FN), pGraphics->LoadSVG(PREVMAIN_FN) };

    PageBackgroundControl = new ISVGControl(pGraphics->GetBounds(), PageBackgrounds[0]);
    pGraphics->AttachControl(PageBackgroundControl);

    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    const ISVG NeedleSVG = pGraphics->LoadSVG(NEEDLE_FN);
    const ISVG NeedleBGSVG = pGraphics->LoadSVG(NEEDLEBG_FN);
    const IBitmap NeedleFG1PNG = pGraphics->LoadBitmap(NEEDLEFG1_FN);
    const IBitmap NeedleFG2PNG = pGraphics->LoadBitmap(NEEDLEFG2_FN);

    Knobs[0] = new NeedleKnob(IRECT::MakeXYWH(89 - 40, 141 + 50, 42, 42), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kDry, kDry);
    Knobs[1] = new NeedleKnob(IRECT::MakeXYWH(180+40, 141+50, 42, 42), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kWet1, kWet2);
    Knobs[2] = new NeedleKnob(IRECT::MakeXYWH(93, 230, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kInputLowDamp1, kInputLowDamp2);
    Knobs[3] = new NeedleKnob(IRECT::MakeXYWH(166, 230, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kInputHighDamp1, kInputHighDamp2);
    Knobs[4] = new NeedleKnob(IRECT::MakeXYWH(56, 310, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kSize1, kSize2);
    Knobs[5] = new NeedleKnob(IRECT::MakeXYWH(130, 329, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kDiffusion1, kDiffusion2);
    Knobs[6] = new NeedleKnob(IRECT::MakeXYWH(203, 310, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kDecay1, kDecay2);
    Knobs[7] = new NeedleKnob(IRECT::MakeXYWH(93, 446, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kReverbLowDamp1, kReverbLowDamp2);
    Knobs[8] = new NeedleKnob(IRECT::MakeXYWH(166, 446, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kReverbHighDamp1, kReverbHighDamp2);
    Knobs[9] = new NeedleKnob(IRECT::MakeXYWH(56, 518, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kModSpeed1, kModSpeed2);
    Knobs[10] = new NeedleKnob(IRECT::MakeXYWH(203, 518, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kModDepth1, kModDepth2);
    Knobs[11] = new NeedleKnob(IRECT::MakeXYWH(130, 543, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kModShape1, kModShape2);

    Knobs[12] = new NeedleKnob(IRECT::MakeXYWH(140, 140, 35, 35), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kPreDelay1, kPreDelay2);
    
	for (int i = 0; i <= 11; i++) {
		pGraphics->AttachControl(Knobs[i]);
	}
    
    for (int i = 12; i <= 12; i++) {
		pGraphics->AttachControl(Knobs[i]);
		Knobs[i]->Hide(true);
	}
    NextButtonControl = new NavigatorButton(IRECT::MakeXYWH(220.572f, 125.695f, 82.306f, 30.f), [this, PageBackgrounds, NextButtons, PrevButtons](IControl* pCaller) {
        ChangePage(1, PageBackgrounds, NextButtons, PrevButtons);
        }, pGraphics->LoadSVG(NEXTEXTRAS_FN));
    pGraphics->AttachControl(NextButtonControl);

    double LEDScale = 0.2453054f;

    const ISVG LedOffSVG = pGraphics->LoadSVG(LEDOFF_FN);
    const ISVG LedOn1SVG = pGraphics->LoadSVG(LEDON1_FN);
    const ISVG LedOn2SVG = pGraphics->LoadSVG(LEDON2_FN);
    const ISVG LedOnBothSVG = pGraphics->LoadSVG(LEDONBOTH_FN);

    Switches[0] = new LEDSwitch(IRECT::MakeXYWH(-11.526f, 404.802f-45, 102, 102), LEDScale, LedOffSVG, LedOnBothSVG, LedOnBothSVG, kFreeze, kFreeze);
    Switches[1] = new LEDSwitch(IRECT::MakeXYWH(-11.526f, 404.802f+30, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kFreeze1, kFreeze2);
    Switches[2] = new LEDSwitch(IRECT::MakeXYWH(-14, 216, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kTunedMode1, kTunedMode2);
    Switches[3] = new LEDSwitch(IRECT::MakeXYWH(228, 216, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kDiffuseInput1, kDiffuseInput2);

    LEDButton* clearButton = new LEDButton(IRECT::MakeXYWH(225.526f, 404.802f + 30, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, [this](IControl* clearControl) {SetParameterValue(kClear1, 1);});

    Buttons[0] = clearButton;

    Buttons[1] = new LEDButton(IRECT::MakeXYWH(225.526f, 404.802f - 45, 102, 102), LEDScale, LedOffSVG, LedOnBothSVG, LedOnBothSVG, [this, clearButton](IControl* clearControl) {SetParameterValue(kClear, 1);clearButton->SetValue(1.);clearButton->SetDirty();}, clearButton);

	for (int i = 0; i < kNumButtons; i++) {
		pGraphics->AttachControl(Buttons[i]);
	}

	//Tank Enable Button
    Switches[4] = new LEDSwitch(IRECT::MakeXYWH(106.5f, 112, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kEnable1, kEnable2);
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

    initalizedInterface = true;
  };
#endif
}

void Plateau2::SelectTank(bool tank2) {
	tank2Selected = tank2;
    for (int i = 0; i < kNumKnobs; i++) {
        Knobs[i]->SelectTank(tank2);
        //Knobs[i]->SetValue(GetParam(Knobs[i]->GetParamIdx())->Value());
		IEditorDelegate::SendParameterValueFromDelegate(Knobs[i]->GetParamIdx(), GetParam(Knobs[i]->GetParamIdx())->GetNormalized(), true);
    }
	for (int i = 0; i < kNumSwitches; i++) {
		Switches[i]->SelectTank(tank2);
	}
	for (int i = 0; i < kNumButtons; i++) {
		Buttons[i]->SelectTank(tank2);
	}
    IEditorDelegate::SendCurrentParamValuesFromDelegate();
}

void Plateau2::ChangePage(int direction, const ISVG PageBackgrounds[kNumPages], const ISVG NextButtons[kNumPages], const ISVG PreviousButtons[kNumPages])
{
    currentPage += direction;
    if (currentPage < 0) currentPage = kNumPages-1; // Wrap around
    if (currentPage > kNumPages - 1) currentPage = 0;

	PageBackgroundControl->SetSVG(PageBackgrounds[currentPage]);
	PageBackgroundControl->SetDirty(false);

	NextButtonControl->SetSVG(NextButtons[currentPage]);

	//PrevButtonControl->SetSVG(PreviousButtons[currentPage]);

    UpdatePageVisibility();
}

void Plateau2::UpdatePageVisibility()
{
    //Main page
    for (int i = 0; i <= 11; i++) {
        Knobs[i]->Hide(currentPage!=0);
    }
    for (int i = 0; i <= 4; i++) {
        Switches[i]->Hide(currentPage != 0);
    }
    for (int i = 0; i <= 1; i++) {
        Buttons[i]->Hide(currentPage != 0);
    }

	//Extras page
    for (int i = 12; i <= 12; i++) {
        Knobs[i]->Hide(currentPage != 1);
    }
}


void Plateau2::OnParamChange(int index)
{
    switch (index) {
        case kClear:
            if (initalizedInterface) {
			    if (GetParam(kClear)->Value() >= 1) {
                        SetParameterValue(kClear1, GetParam(kClear)->Value());
                        SetParameterValue(kClear2, GetParam(kClear)->Value());
                }
            }
            break;
        case kFreeze:
            if (initalizedInterface)
            {
                if (GetParam(kFreeze)->Value() >= 1) {
                    SetParameterValue(tank2Selected ? kFreeze1 : kFreeze2, 1.);
				    Switches[1]->SetValue(1.);
                }
                else {
                    SetParameterValue(tank2Selected ? kFreeze1 : kFreeze2, Switches[1]->GetPrefered());
                    Switches[1]->Update();
                }
			    Switches[1]->SetDirty();
            }
		    break;

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
            double size = GetParam(kSize1)->Value();
            bool tunedMode = GetParam(kTunedMode1)->Value();
            if (tunedMode) {
                reverb1.setTimeScale(0.0025f * powf(2.f, size * 5.f));
            }
            else {
                reverb1.setTimeScale(scale<double>(size * size, 0.f, 1.f, 0.01f, 4.0f));
            }
            break;
        }
        case kDiffusion1:
            reverb1.setTankDiffusion(GetParam(index)->Value());
            break;
        case kDecay1:
        {
            double decay = GetParam(index)->Value();
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
            double modSpeed = GetParam(index)->Value();
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

        case kPreDelay2:
            reverb2.setPreDelay(GetParam(index)->Value());
            break;
        case kInputLowDamp2:
            reverb2.setInputFilterLowCutoffPitch(10.f - GetParam(index)->Value());
            break;
        case kInputHighDamp2:
            reverb2.setInputFilterHighCutoffPitch(GetParam(index)->Value());
            break;
        case kSize2:
        case kTunedMode2:
        {
            double size = GetParam(kSize2)->Value();
            bool tunedMode = GetParam(kTunedMode2)->Value();
            if (tunedMode) {
                reverb2.setTimeScale(0.0025f * powf(2.f, size * 5.f));
            }
            else {
                reverb2.setTimeScale(scale<double>(size * size, 0.f, 1.f, 0.01f, 4.0f));
            }
            break;
        }
        case kDiffusion2:
            reverb2.setTankDiffusion(GetParam(index)->Value());
            break;
        case kDecay2:
        {
            double decay = GetParam(index)->Value();
            reverb2.setDecay(2.f * decay - decay * decay);
            break;
        }
        case kReverbLowDamp2:
            reverb2.setTankFilterLowCutFrequency(10.f - GetParam(index)->Value());
            break;
        case kReverbHighDamp2:
            reverb2.setTankFilterHighCutFrequency(GetParam(index)->Value());
            break;
        case kModSpeed2:
        {
            double modSpeed = GetParam(index)->Value();
            reverb2.setTankModSpeed(modSpeed * modSpeed * 99.f + 1.f);
            break;
        }
        case kModDepth2:
            reverb2.setTankModDepth(GetParam(index)->Value());
            break;
        case kModShape2:
            reverb2.setTankModShape(GetParam(index)->Value());
            break;
        case kDiffuseInput2:
            reverb2.enableInputDiffusion(GetParam(index)->Value());
            break;
    }
}


#if IPLUG_DSP
void Plateau2::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const int nChans = NOutChansConnected();
  
  for (int s = 0; s < nFrames; s++) {
        const double dryParam = GetParam(kDry)->Value() / 100;

        const bool tank1Enabled = GetParam(kEnable1)->Value();
        const bool tank2Enabled = GetParam(kEnable2)->Value();

        outputs[0][s] = inputs[0][s] * dryParam;
        if (nChans > 1)
        {
            outputs[1][s] = inputs[1][s] * dryParam;
        }

        if (tank1Enabled) {
            const bool clear1Param = GetParam(kClear1)->Value() || GetParam(kClear)->Value();
            const bool freeze1Param = GetParam(kFreeze1)->Value();
            const double wet1Param = GetParam(kWet1)->Value() / 100;

            if (clear1Param && !clear1 && cleared1) {
                cleared1 = false;
                clear1 = true;
            }
            else if (!clear1Param && cleared1) {
                clear1 = false;
            }

            if (clear1) {
                if (!cleared1 && !fadeOut1 && !fadeIn1) {
                    fadeOut1 = true;
                    envelope1.setStartEndPoints(1.f, 0.f);
                    envelope1.trigger();
                }
                if (fadeOut1 && envelope1._justFinished) {
                    reverb1.clear();
                    fadeOut1 = false;
                    fadeIn1 = true;
                    envelope1.setStartEndPoints(0.f, 1.f);
                    envelope1.trigger();
                }
                if (fadeIn1 && envelope1._justFinished) {
                    fadeIn1 = false;
                    cleared1 = true;
                    envelope1._value = 1.f;
                    SetParameterValue(kClear, 0);
                    SetParameterValue(kClear1, 0);
                }
            }
            envelope1.process();

            if (freeze1Param && !frozen1) {
                frozen1 = true;
                reverb1.freeze(frozen1);
            }
            else if (!freeze1Param && frozen1) {
                frozen1 = false;
                reverb1.freeze(frozen1);
            }

            reverb1.process((double)(inputs[0][s] * envelope1._value), (double)(inputs[nChans > 1 ? 1 : 0][s] * envelope1._value));

            outputs[0][s] += reverb1.getLeftOutput() * wet1Param;

            if (nChans > 1)
            {
                outputs[1][s] += reverb1.getRightOutput() * wet1Param;
            }
        }

        //I can't find a way to make tank 2 work without just copying and pasting everything
        if (tank2Enabled) {
            const bool clear2Param = GetParam(kClear2)->Value() || GetParam(kClear)->Value();
            const bool freeze2Param = GetParam(kFreeze2)->Value();
            const double wet2Param = GetParam(kWet2)->Value() / 100;

            if (clear2Param && !clear2 && cleared2) {
                cleared2 = false;
                clear2 = true;
            }
            else if (!clear2Param && cleared2) {
                clear2 = false;
            }

            if (clear2) {
                if (!cleared2 && !fadeOut2 && !fadeIn2) {
                    fadeOut2 = true;
                    envelope2.setStartEndPoints(1.f, 0.f);
                    envelope2.trigger();
                }
                if (fadeOut2 && envelope2._justFinished) {
                    reverb2.clear();
                    fadeOut2 = false;
                    fadeIn2 = true;
                    envelope2.setStartEndPoints(0.f, 1.f);
                    envelope2.trigger();
                }
                if (fadeIn2 && envelope2._justFinished) {
                    fadeIn2 = false;
                    cleared2 = true;
                    envelope2._value = 1.f;
                    SetParameterValue(kClear, 0);
                    SetParameterValue(kClear2, 0);
                }
            }
            envelope2.process();

            if (freeze2Param && !frozen2) {
                frozen2 = true;
                reverb2.freeze(frozen2);
            }
            else if (!freeze2Param && frozen2) {
                frozen2 = false;
                reverb2.freeze(frozen2);
            }

            reverb2.process((double)(inputs[0][s] * envelope2._value), (double)(inputs[nChans > 1 ? 1 : 0][s] * envelope2._value));

            outputs[0][s] += reverb2.getLeftOutput() * wet2Param;

            if (nChans > 1)
            {
                outputs[1][s] += reverb2.getRightOutput() * wet2Param;
            }
        }
  }
}
#endif
