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
  GetParam(kModVariance1)->InitDouble("Modulation Variance 1", 1., 0., 1., 0.01);
  GetParam(kFreeze1)->InitBool("Freeze 1", false);
  GetParam(kClear1)->InitBool("Clear 1", false);
  GetParam(kTunedMode1)->InitBool("Tuned Mode 1", false);
  GetParam(kDiffuseInput1)->InitBool("Diffuse Input 1", true);
  GetParam(kPreDelay1)->InitSeconds("Pre Delay 1", 0., 0., 0.5, 0.01);
  GetParam(kNesting1)->InitBool("Nested Tank Diffusion 1", false);
  GetParam(kInputNesting1)->InitBool("Nested Input Diffusion 1", false);
  GetParam(kDiffusionDecay1)->InitPercentage("Tank Diffusion Decay 1", 76.9230);
  GetParam(kInput1)->InitPercentage("Input 1", 100);
  GetParam(kStereoSource1)->InitPercentage("Stereo Source 1", 0, -100, 100);
  GetParam(kWidth1)->InitPercentage("Stereo Width 1", 100, 0, 200);
  GetParam(kPan1)->InitPercentage("Pan 1", 0, -100, 100);
  GetParam(k1to2)->InitBool("Send Tank 1 to 2", false);
  GetParam(k1to2Level)->InitPercentage("Tank 1 to 2 Level");
  GetParam(k1to2Delay)->InitSeconds("Tank 1 to 2 Delay", 0., 0., 0.5, 0.01);
  GetParam(k1to2LowDamp)->InitDouble("Tank 1 to 2 Low Damp", 10., 0., 10., 0.01);
  GetParam(k1to2HighDamp)->InitDouble("Tank 1 to 2 High Damp", 10., 0., 10., 0.01);


  GetParam(kEnable2)->InitBool("Tank 2 Enable", false);
  GetParam(kWet2)->InitPercentage("Wet 2", 50);
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
  GetParam(kModVariance2)->InitDouble("Modulation Variance 2", 1., 0., 1., 0.01);
  GetParam(kFreeze2)->InitBool("Freeze 2", false);
  GetParam(kClear2)->InitBool("Clear 2", false);
  GetParam(kTunedMode2)->InitBool("Tuned Mode 2", false);
  GetParam(kDiffuseInput2)->InitBool("Diffuse Input 2", true);
  GetParam(kPreDelay2)->InitSeconds("Pre Delay 2", 0., 0., 0.5, 0.01);
  GetParam(kNesting2)->InitBool("Nested Tank Diffusion 2", false);
  GetParam(kInputNesting2)->InitBool("Nested Input Diffusion 2", false);
  GetParam(kDiffusionDecay2)->InitPercentage("Tank Diffusion Decay 2", 76.9230);
  GetParam(kInput2)->InitPercentage("Input 2", 100);
  GetParam(kStereoSource2)->InitPercentage("Stereo Source 2", 0, -100, 100);
  GetParam(kWidth2)->InitPercentage("Stereo Width 2", 100, 0, 200);
  GetParam(kPan2)->InitPercentage("Pan 2", 0, -100, 100);
  GetParam(k2to1)->InitBool("Send Tank 2 to 1", false);
  GetParam(k2to1Level)->InitPercentage("Tank 1 to 2 Level");
  GetParam(k2to1Delay)->InitSeconds("Tank 2 to 1 Delay", 0., 0., 0.5, 0.01);
  GetParam(k2to1LowDamp)->InitDouble("Tank 2 to 1 Low Damp", 10., 0., 10., 0.01);
  GetParam(k2to1HighDamp)->InitDouble("Tank 2 to 1 High Damp", 10., 0., 10., 0.01);


  GetParam(kDanger)->InitBool("DANGER! Allow Unsafe Feedback Settings", false);


  reverb1.setSampleRate(GetSampleRate());
  envelope1.setSampleRate(GetSampleRate());
  envelope1.setTime(0.004f);
  envelope1._value = 1.f;
  
  reverb2.setSampleRate(GetSampleRate());
  envelope2.setSampleRate(GetSampleRate());
  envelope2.setTime(0.004f);
  envelope2._value = 1.f;

  uint16_t MaxSendDelay = std::ceil(GetSampleRate()/2)+1;

  send1To2Delay = InterpDelay<double>(MaxSendDelay, 0);
  send2To1Delay = InterpDelay<double>(MaxSendDelay, 0);

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {

    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachSVGBackground(BACKGROUND_FN);

    ISVG PageBackgrounds[kNumPages] = { pGraphics->LoadSVG(PAGEMAIN_FN), pGraphics->LoadSVG(PAGEEXTRAS_FN), pGraphics->LoadSVG(PAGEROUTING_FN) };
	ISVG NextButtons[kNumPages] = { pGraphics->LoadSVG(NEXTEXTRAS_FN), pGraphics->LoadSVG(NEXTROUTING_FN),  pGraphics->LoadSVG(NEXTMAIN_FN) };
	ISVG PrevButtons[kNumPages] = { pGraphics->LoadSVG(PREVROUTING_FN), pGraphics->LoadSVG(PREVMAIN_FN),  pGraphics->LoadSVG(PREVEXTRAS_FN) };

    PageBackgroundControl = new ISVGControl(pGraphics->GetBounds(), PageBackgrounds[0]);
    pGraphics->AttachControl(PageBackgroundControl);

    SVGs[0] = new ISVGControl(IRECT::MakeXYWH(61.06f, 376.55f, 192.880f, 235), pGraphics->LoadSVG(DANGERPANEL_FN));
	pGraphics->AttachControl(SVGs[0]);
	SVGs[0]->Hide(true);

    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    const ISVG NeedleSVG = pGraphics->LoadSVG(NEEDLE_FN);
    const ISVG NeedleBGSVG = pGraphics->LoadSVG(NEEDLEBG_FN);
    const IBitmap NeedleFG1PNG = pGraphics->LoadBitmap(NEEDLEFG1_FN);
    const IBitmap NeedleFG2PNG = pGraphics->LoadBitmap(NEEDLEFG2_FN);

	//Main Page Knobs
    Knobs[kDryKnob] = new NeedleKnob(IRECT::MakeXYWH(89 - 40, 141 + 50, 42, 42), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kDry, kDry);
    Knobs[kWetKnob] = new NeedleKnob(IRECT::MakeXYWH(180+40, 141+50, 42, 42), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kWet1, kWet2);
    Knobs[kInputLowDampKnob] = new NeedleKnob(IRECT::MakeXYWH(93, 230, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kInputLowDamp1, kInputLowDamp2);
    Knobs[kInputHighDampKnob] = new NeedleKnob(IRECT::MakeXYWH(166, 230, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kInputHighDamp1, kInputHighDamp2);
    Knobs[kSizeKnob] = new NeedleKnob(IRECT::MakeXYWH(56, 310, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kSize1, kSize2);
    Knobs[kDiffusionKnob] = new NeedleKnob(IRECT::MakeXYWH(130, 329, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kDiffusion1, kDiffusion2);
    Knobs[kDecayKnob] = new NeedleKnob(IRECT::MakeXYWH(203, 310, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kDecay1, kDecay2);
    Knobs[kReverbLowDampKnob] = new NeedleKnob(IRECT::MakeXYWH(93, 446, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kReverbLowDamp1, kReverbLowDamp2);
    Knobs[kReverbHighDampKnob] = new NeedleKnob(IRECT::MakeXYWH(166, 446, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kReverbHighDamp1, kReverbHighDamp2);
    Knobs[kModSpeedKnob] = new NeedleKnob(IRECT::MakeXYWH(56, 518, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kModSpeed1, kModSpeed2);
    Knobs[kModDepthKnob] = new NeedleKnob(IRECT::MakeXYWH(203, 518, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kModDepth1, kModDepth2);
    Knobs[kModShapeKnob] = new NeedleKnob(IRECT::MakeXYWH(130, 543, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kModShape1, kModShape2);
    
	for (int i = 0; i <= 11; i++) {
		pGraphics->AttachControl(Knobs[i]);
	}

    SVGs[4] = new ISVGControl(IRECT::MakeXYWH(94.119f, 488.230, 126.762f, 116.922f), pGraphics->LoadSVG(SENDLABELS_FN));
	pGraphics->AttachControl(SVGs[4]);
	SVGs[4]->Hide(true);

	//Extras Page Knobs
    Knobs[kPreDelayKnob] = new NeedleKnob(IRECT::MakeXYWH(140, 140, 35, 35), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kPreDelay1, kPreDelay2);

    Knobs[kDiffusionDecayKnob] = new NeedleKnob(IRECT::MakeXYWH(233, 310, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kDiffusionDecay1, kDiffusionDecay2);
    Knobs[kDiffusionDecayKnob]->Bound = 72.6923f;

	Knobs[kModVarianceKnob] = new NeedleKnob(IRECT::MakeXYWH(233, 518, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kModVariance1, kModVariance2);

	//Routing Page Knobs
    Knobs[kInputKnob] = new NeedleKnob(IRECT::MakeXYWH(93, 170, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kInput1, kInput2);
    Knobs[kStereoSourceKnob] = new NeedleKnob(IRECT::MakeXYWH(166, 170, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kStereoSource1, kStereoSource2);

    Knobs[kWidthKnob] = new NeedleKnob(IRECT::MakeXYWH(93, 294, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kWidth1, kWidth2);
    Knobs[kPanKnob] = new NeedleKnob(IRECT::MakeXYWH(166, 294, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kPan1, kPan2);

    Knobs[kSendLevel] = new NeedleKnob(IRECT::MakeXYWH(93, 440, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, k1to2Level, k2to1Level);
    Knobs[kSendDelay] = new NeedleKnob(IRECT::MakeXYWH(166, 440, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, k1to2Delay, k2to1Delay);

	Knobs[kSendLowDamp] = new NeedleKnob(IRECT::MakeXYWH(93, 530, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, k1to2LowDamp, k2to1LowDamp);
	Knobs[kSendHighDamp] = new NeedleKnob(IRECT::MakeXYWH(166, 530, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, k1to2HighDamp, k2to1HighDamp);
    
    for (int i = kPreDelayKnob; i <= kSendHighDamp; i++) {
		pGraphics->AttachControl(Knobs[i]);
		Knobs[i]->Hide(true);
	}

    NextButtonControl = new NavigatorButton(IRECT::MakeXYWH(213, 125.695f, 90, 30), [this, PageBackgrounds, NextButtons, PrevButtons](IControl* pCaller) {
        ChangePage(1, PageBackgrounds, NextButtons, PrevButtons);
    }, NextButtons[0]);
    pGraphics->AttachControl(NextButtonControl);

    PrevButtonControl = new NavigatorButton(IRECT::MakeXYWH(12, 125.695f, 90, 30), [this, PageBackgrounds, NextButtons, PrevButtons](IControl* pCaller) {
    ChangePage(-1, PageBackgrounds, NextButtons, PrevButtons);
    }, PrevButtons[0]);
    pGraphics->AttachControl(PrevButtonControl);

    double LEDScale = 0.2453054f;

    const ISVG LedOffSVG = pGraphics->LoadSVG(LEDOFF_FN);
    const ISVG LedOn1SVG = pGraphics->LoadSVG(LEDON1_FN);
    const ISVG LedOn2SVG = pGraphics->LoadSVG(LEDON2_FN);
    const ISVG LedOnBothSVG = pGraphics->LoadSVG(LEDONBOTH_FN);

	const ISVG DangerOffSVG = pGraphics->LoadSVG(DANGEROFF_FN);
	const ISVG DangerOnSVG = pGraphics->LoadSVG(DANGERON_FN);

	//Main page Switches
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

	//Tank Enable Switch
    Switches[4] = new LEDSwitch(IRECT::MakeXYWH(106.5f, 112, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kEnable1, kEnable2);
    Switches[4]->SetValue(1);


	for (int i = 0; i <= 4; i++) {
		pGraphics->AttachControl(Switches[i]);
	}

    Switches[5] = new LEDSwitch(IRECT::MakeXYWH(210, 170, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kNesting1, kNesting2);

    //DANGER switch
    Switches[6] = new LEDSwitch(IRECT::MakeXYWH(102, 301, 112, 112), 1, DangerOffSVG, DangerOnSVG, DangerOnSVG, kDanger, kDanger);

	//Routing page Switches
	Switches[7] = new LEDSwitch(IRECT::MakeXYWH(106.5, 374, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, k1to2, k2to1);

    for (int i = 5; i <= 7; i++) {
        pGraphics->AttachControl(Switches[i]);
		Switches[i]->Hide(true);
    }

    SVGs[1] = new ISVGControl(IRECT::MakeMidXYWH(157.5f, 395, 86.109f, 14.207f), pGraphics->LoadSVG(SEND1TO2_FN));
    SVGs[2] = new ISVGControl(IRECT::MakeMidXYWH(157.5f, 395, 89.227f, 17.208f), pGraphics->LoadSVG(SEND2TO1_FN));
    SVGs[3] = new ISVGControl(IRECT::MakeMidXYWH(157.5f, 510, 162.106f, 45.576f), pGraphics->LoadSVG(REQUIRESDANGER_FN));

    for (int i = 1; i <= 3; i++) {
        pGraphics->AttachControl(SVGs[i]);
        SVGs[i]->Hide(true);
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

void Plateau2::SelectTank(bool tank2) {
	tank2Selected = tank2;
    for (int i = 0; i < kNumKnobs; i++) {
        Knobs[i]->SelectTank(tank2);
        //Knobs[i]->SetValue(GetParam(Knobs[i]->GetParamIdx())->Value());
		//IEditorDelegate::SendParameterValueFromDelegate(Knobs[i]->GetParamIdx(), GetParam(Knobs[i]->GetParamIdx())->GetNormalized(), true);
    }
	for (int i = 0; i < kNumSwitches; i++) {
		Switches[i]->SelectTank(tank2);
	}
	for (int i = 0; i < kNumButtons; i++) {
		Buttons[i]->SelectTank(tank2);
	}

    UpdateSendVisibility();

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
	PrevButtonControl->SetSVG(PreviousButtons[currentPage]);

    UpdatePageVisibility();
}

void Plateau2::UpdatePageVisibility()
{
    //Main page
    for (int i = kDryKnob; i <= kModShapeKnob; i++) {
        Knobs[i]->Hide(currentPage!=0);
    }
    for (int i = 0; i <= 4; i++) {
        Switches[i]->Hide(currentPage != 0);
    }
    for (int i = 0; i <= 1; i++) {
        Buttons[i]->Hide(currentPage != 0);
    }

	//Extras page
    for (int i = kPreDelayKnob; i <= kModVarianceKnob; i++) {
        Knobs[i]->Hide(currentPage != 1);
    }
    for (int i = 5; i <= 6; i++) {
        Switches[i]->Hide(currentPage != 1);
    }

	//Routing page
	for (int i = kInputKnob; i <= kPanKnob; i++) {
		Knobs[i]->Hide(currentPage != 2);
	}
    UpdateSendVisibility();
}

void Plateau2::UpdateSendVisibility() {
    for (int i = 7; i <= 7; i++) {
        Switches[i]->Hide(currentPage != 2);
    }
    bool dangerous = GetParam(kDanger)->Value();
    for (int i = kSendLevel; i <= kSendHighDamp; i++) {
        Knobs[i]->Hide(currentPage != 2 || (!dangerous && tank2Selected));
    }
    SVGs[0]->Hide(currentPage != 2 || !tank2Selected);
    SVGs[1]->Hide(currentPage != 2 || tank2Selected);
    SVGs[2]->Hide(currentPage != 2 || !tank2Selected);
    SVGs[3]->Hide(currentPage != 2 || !tank2Selected || dangerous);
    SVGs[4]->Hide(currentPage != 2 || (!dangerous && tank2Selected));
}

bool Plateau2::WindowIsOpen() {
	IGraphics* pGraphics = GetUI();
	return pGraphics && pGraphics->WindowIsOpen();
}

void Plateau2::OnParamChange(int index)
{
    switch (index) {
        case kClear:
            if (WindowIsOpen()) {
			    if (GetParam(kClear)->Value() >= 0.5) {
                    SetParameterValue(kClear1, GetParam(kClear)->Value());
                    SetParameterValue(kClear2, GetParam(kClear)->Value());
                }
            }
            break;
        case kFreeze:
            if (WindowIsOpen())
            {
                if (GetParam(kFreeze)->Value() >= 0.5) {
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
            if (GetParam(kTunedMode1)->Value()>=0.5) {
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
            reverb1.setDecay(2 * decay - decay * decay);
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
            reverb1.enableInputDiffusion(GetParam(index)->Value()>=0.5);
            break;
		case kNesting1:
			reverb1.setTankDiffusionNesting(GetParam(index)->Value()>=0.5);
            break;
        case kDiffusionDecay1:
        {
            double scaled = scale<double>(GetParam(index)->Value(), 0, 100, 0, 1.3);
            if (!GetParam(kDanger)->Value()) {
				//Clip to safe values
                scaled = clip<double>(scaled, 0.3, 1);
            }
			reverb1.setTankDiffusionDecay(scaled);
            break;
        }
        case kStereoSource1:
            sourceBalance1 = balanceFactors(GetParam(kStereoSource1)->Value()/100);
            break;
        case kPan1:
            panBalance1 = balanceFactors(GetParam(kPan1)->Value()/100);
            break;
        case k1to2Delay:
            send1To2Delay.setDelayTime(GetParam(k1to2Delay)->Value() * GetSampleRate());
            break;
		case k1to2LowDamp:
			send1To2HP.setCutoffFreq(pitch2freq(10.f - GetParam(index)->Value()));
			break;
		case k1to2HighDamp:
			send1To2LP.setCutoffFreq(pitch2freq(GetParam(index)->Value()));
			break;
		case kModVariance1:
			reverb1.setTankModVariance(GetParam(index)->Value());
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
            if (GetParam(kTunedMode2)->Value()>=0.5) {
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
            reverb2.enableInputDiffusion(GetParam(index)->Value()>=0.5);
            break;
        case kNesting2:
            reverb2.setTankDiffusionNesting(GetParam(index)->Value());
            break;
        case kDiffusionDecay2:
        {
            double scaled = scale<double>(GetParam(index)->Value(), 0, 100, 0, 1.3);
            if (!GetParam(kDanger)->Value()) {
                //Clip to safe values
                scaled = clip<double>(scaled, 0.3, 1);
            }
            reverb2.setTankDiffusionDecay(scaled);
            break;
        }
        case kStereoSource2:
            sourceBalance2 = balanceFactors(GetParam(kStereoSource2)->Value()/100);
            break;
        case kPan2:
            panBalance2 = balanceFactors(GetParam(kPan2)->Value()/100);
            break;
        case k2to1Delay:
            send2To1Delay.setDelayTime(GetParam(k2to1Delay)->Value() * GetSampleRate());
            break;
		case k2to1LowDamp:
			send2To1HP.setCutoffFreq(pitch2freq(10.f - GetParam(index)->Value()));
			break;
		case k2to1HighDamp:
			send2To1LP.setCutoffFreq(pitch2freq(GetParam(index)->Value()));
			break;
		case kModVariance2:
			reverb2.setTankModVariance(GetParam(index)->Value());
            break;

		case kDanger:
			if (GetParam(kDanger)->Value()<=0.5) {
				//Reset the plugin when danger is turned off for safety
                SetParameterValue(kClear, 1);
			}
			if (WindowIsOpen()) {
                UpdateSendVisibility();
                Knobs[kDiffusionDecayKnob]->Bound = GetParam(kDanger)->Value() ? 135.f : 72.6923f;

                SetParameterValue(kDiffusionDecay1, clip<double>(GetParam(kDiffusionDecay1)->Value(), 23.0769, 76.92307)/100);
                SetParameterValue(kDiffusionDecay2, clip<double>(GetParam(kDiffusionDecay2)->Value(), 23.0769, 76.92307)/100);

                Knobs[kDiffusionDecayKnob]->SetValue((tank2Selected ? GetParam(kDiffusionDecay2)->Value() : GetParam(kDiffusionDecay1)->Value()) / 100);
				Knobs[kDiffusionDecayKnob]->SetDirty(false);
			}
            break;
    }
}


#if IPLUG_DSP
void Plateau2::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const int nChans = NOutChansConnected();
  
  for (int s = 0; s < nFrames; s++) {
        const double dryParam = GetParam(kDry)->Value() / 100;

        const bool tank1Enabled = GetParam(kEnable1)->Value()>=0.5;
        const bool tank2Enabled = GetParam(kEnable2)->Value()>=0.5;

		const bool send2to1 = tank2Enabled && GetParam(k2to1)->Value() && GetParam(kDanger)->Value()>=0.5;
        const bool send1to2 = tank1Enabled && GetParam(k1to2)->Value()>=0.5;

        outputs[0][s] = inputs[0][s] * dryParam;
        if (nChans > 1)
        {
            outputs[1][s] = inputs[1][s] * dryParam;
        }

        if (tank1Enabled) {
            const bool clear1Param = GetParam(kClear1)->Value()>=0.5 || GetParam(kClear)->Value()>=0.5;
            const bool freeze1Param = GetParam(kFreeze1)->Value() >= 0.5;
            const double wet1Param = GetParam(kWet1)->Value() / 100;
            const double input1 = GetParam(kInput1)->Value() / 100;
			const double level2to1 = GetParam(k2to1Level)->Value() / 100;

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

            reverb1.process((double)(std::get<0>(sourceBalance1) * envelope1._value * inputs[0][s] * input1), (double)(std::get<1>(sourceBalance1) * envelope1._value * (inputs[nChans > 1 ? 1 : 0][s] * input1)), (send2to1 ? (envelope1._value * level2to1 * reverbOut2) : 0));

            std::tuple<double,double> out = seperation(reverb1.getLeftOutput(), reverb1.getRightOutput(), GetParam(kWidth1)->Value() / 100);
            out = { std::get<0>(panBalance1) * std::get<0>(out), std::get<1>(panBalance1)* std::get<1>(out) };

            outputs[0][s] += std::get<0>(out) * wet1Param;

            if (nChans > 1)
            {
                outputs[1][s] += std::get<1>(out) * wet1Param;
            }

            if (send1to2) {
				send1To2Delay.input = 0.707 * (reverb1.getLeftOutput() + reverb1.getRightOutput());
				send1To2Delay.process();
				send1To2LP.input = send1To2Delay.output;
				send1To2LP.process();
				send1To2HP.input = send1To2LP.output;
				send1To2HP.process();
				reverbOut1 = send1To2HP.output;
            }
        }

        //I can't find a way to make tank 2 work without just copying and pasting everything
        if (tank2Enabled) {
            const bool clear2Param = GetParam(kClear2)->Value() || GetParam(kClear)->Value();
            const bool freeze2Param = GetParam(kFreeze2)->Value();
            const double wet2Param = GetParam(kWet2)->Value() / 100;
			const double input2 = GetParam(kInput2)->Value() / 100;
			const double level1to2 = GetParam(k1to2Level)->Value() / 100;

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

            reverb2.process((double)(std::get<0>(sourceBalance2)* envelope2._value* inputs[0][s] * input2), (double)(std::get<1>(sourceBalance2)* envelope2._value* (inputs[nChans > 1 ? 1 : 0][s] * input2)), (send1to2 ? (envelope2._value * level1to2 * reverbOut1) : 0));


            std::tuple<double, double> out = seperation(reverb2.getLeftOutput(), reverb2.getRightOutput(), GetParam(kWidth2)->Value()/100);
            out = { std::get<0>(panBalance2) * std::get<0>(out), std::get<1>(panBalance2) * std::get<1>(out) };

            outputs[0][s] += std::get<0>(out) * wet2Param;

            if (nChans > 1)
            {
                outputs[1][s] += std::get<1>(out) * wet2Param;
            }

            if (send2to1) {
                send2To1Delay.input = 0.707 * (reverb2.getLeftOutput()+reverb2.getRightOutput());
                send2To1Delay.process();
				send2To1LP.input = send2To1Delay.output;
				send2To1LP.process();
				send2To1HP.input = send2To1LP.output;
				send2To1HP.process();
				reverbOut2 = send2To1HP.output;
            }
        }
  }
}
#endif
