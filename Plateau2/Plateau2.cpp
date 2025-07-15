#include "Plateau2.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

Plateau2::Plateau2(const InstanceInfo& info)
: iplug::Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
  GetParam(kDry)->InitPercentage("Dry", 100);
  GetParam(kFreeze)->InitBool("Global Freeze", false);
  GetParam(kClear)->InitBool("Global Clear", false);
  GetParam(kLink1to2)->InitBool("Link Tank 1 to 2", false);

  GetParam(kEnable1)->InitBool("Tank 1 Enable", true);
  GetParam(kWet1)->InitPercentage("Wet 1", 50);
  GetParam(kInputLowDamp1)->InitDouble("Input Low Damp 1", 10., 0., 10., 0.01);
  GetParam(kInputHighDamp1)->InitDouble("Input High Damp 1", 10., 0., 10., 0.01);
  GetParam(kSize1)->InitDouble("Size 1", 0.5, 0., 1., 0.01);
  GetParam(kDiffusion1)->InitDouble("Diffusion 1", 10., 0., 10., 0.01);
  GetParam(kDecay1)->InitDouble("Decay 1", 0.45, 0.1, 0.9999, 0.01);
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
  GetParam(kNesting1)->InitBool("Nested Diffusion 1", false);
  GetParam(kDiffusionDecay1)->InitPercentage("Diffusion Decay 1", 76.9230);
  GetParam(kVariance1)->InitDouble("Tank Variance 1", 1., 0., 1., 0.01);
  GetParam(kSoftClip1)->InitBool("Soft Clip 1", false);
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
  GetParam(kDecay2)->InitDouble("Decay 2", 0.45, 0.1, 0.9999, 0.01);
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
  GetParam(kNesting2)->InitBool("Nested Diffusion 2", false);
  GetParam(kDiffusionDecay2)->InitPercentage("Diffusion Decay 2", 76.9230);
  GetParam(kVariance2)->InitDouble("Tank Variance 2", 1., 0., 1., 0.01);
  GetParam(kSoftClip2)->InitBool("Soft Clip 2", false);
  GetParam(kInput2)->InitPercentage("Input 2", 100);
  GetParam(kStereoSource2)->InitPercentage("Stereo Source 2", 0, -100, 100);
  GetParam(kWidth2)->InitPercentage("Stereo Width 2", 100, 0, 200);
  GetParam(kPan2)->InitPercentage("Pan 2", 0, -100, 100);
  GetParam(k2to1)->InitBool("Send Tank 2 to 1", false);
  GetParam(k2to1Level)->InitPercentage("Tank 1 to 2 Level");
  GetParam(k2to1Delay)->InitSeconds("Tank 2 to 1 Delay", 0., 0., 0.5, 0.01);
  GetParam(k2to1LowDamp)->InitDouble("Tank 2 to 1 Low Damp", 10., 0., 10., 0.01);
  GetParam(k2to1HighDamp)->InitDouble("Tank 2 to 1 High Damp", 10., 0., 10., 0.01);


  GetParam(kDanger)->InitBool("DANGER! Allow Unsafe Feedback", false);

  MakePreset("Default", 100.000000, false, false, false, true, 50.000000, 10.000000, 10.000000, 0.500000, 10.000000, 0.450000, 10.000000, 10.000000, 0.000000, 0.500000, 0.500000, 1.000000, false, false, false, true, 0.000000, false, 76.923000, 1.000000, false, 100.000000, 0.000000, 100.000000, 0.000000, false, 0.000000, 0.000000, 10.000000, 10.000000, false, 50.000000, 10.000000, 10.000000, 0.500000, 10.000000, 0.450000, 10.000000, 10.000000, 0.000000, 0.500000, 0.500000, 1.000000, false, false, false, true, 0.000000, false, 76.923000, 1.000000, false, 100.000000, 0.000000, 100.000000, 0.000000, false, 0.000000, 0.000000, 10.000000, 10.000000, false);
  MakePreset("Bassment", 68.452381, false, false, false, true, 92.261905, 10.000000, 4.866071, 0.473214, 3.571429, 0.377201, 10.000000, 6.875000, 0.272321, 1.285714, 0.500000, 1.000000, false, false, false, false, 0.000000, false, 76.923070, 0.982143, true, 100.000000, 0.000000, 131.250000, 0.000000, false, 0.000000, 0.000000, 10.000000, 10.000000, true, 47.619048, 3.616071, 10.000000, 0.553572, 5.892857, 0.591530, 7.232143, 10.000000, 0.218750, 3.000000, 0.299107, 0.459821, false, false, false, true, 0.039286, true, 36.744499, 0.165179, false, 100.000000, 0.000000, 100.000000, 0.000000, false, 0.000000, 0.000000, 10.000000, 10.000000, false);
  MakePreset("Polish", 100.000000, false, false, false, true, 29.166666, 10.000000, 8.169643, 0.191964, 6.473214, 0.300870, 10.000000, 7.366071, 0.272321, 1.285714, 0.500000, 1.000000, false, false, false, true, 0.000000, false, 76.923070, 1.000000, false, 100.000000, 0.000000, 100.000000, 0.000000, false, 0.000000, 0.000000, 10.000000, 10.000000, false, 50.000000, 10.000000, 10.000000, 0.500000, 10.000000, 0.450000, 10.000000, 10.000000, 0.000000, 0.500000, 0.500000, 1.000000, false, true, false, true, 0.000000, false, 76.923000, 1.000000, false, 100.000000, 0.000000, 100.000000, 0.000000, false, 0.000000, 0.000000, 10.000000, 10.000000, false);
  MakePreset("Cave", 100.000000, false, false, false, true, 50.000000, 10.000000, 7.991071, 0.589286, 10.000000, 0.386642, 10.000000, 5.803571, 0.000000, 0.000000, 0.500000, 1.000000, false, false, false, true, 0.000000, false, 76.923000, 1.000000, false, 100.000000, 0.000000, 100.000000, 0.000000, true, 29.910714, 0.131696, 10.000000, 10.000000, true, 22.619048, 10.000000, 7.767857, 0.584821, 10.000000, 0.466990, 10.000000, 7.053571, 0.245536, 0.714286, 0.500000, 1.000000, false, false, false, true, 0.000000, true, 64.423000, 1.000000, false, 22.321429, 0.000000, 100.000000, 0.000000, false, 0.000000, 0.000000, 10.000000, 10.000000, false);
  MakePreset("Canyon", 0.000000, false, true, false, true, 100.000000, 10.000000, 8.035714, 0.803571, 10.000000, 0.248644, 10.000000, 10.000000, 0.133929, 0.642857, 0.500000, 0.120535, false, true, false, true, 0.000000, true, 60.851571, 0.000000, true, 100.000000, -100.000000, 100.000000, -66.666666, false, 0.000000, 0.000000, 10.000000, 10.000000, true, 100.000000, 10.000000, 8.035714, 0.803571, 10.000000, 0.248644, 10.000000, 10.000000, 0.133929, 0.642857, 0.500000, 0.120535, true, true, false, true, 0.000000, true, 60.851568, 0.000000, true, 100.000000, 100.000000, 100.000000, 66.666663, false, 0.000000, 0.000000, 10.000000, 10.000000, false);
  MakePreset("ChorusVerb", 51.190476, false, false, false, true, 100.000000, 10.000000, 8.080357, 0.803571, 0.000000, 0.284801, 10.000000, 10.000000, 0.138393, 1.857143, 0.500000, 0.116071, false, false, false, false, 0.000000, true, 25.583714, 0.000000, false, 100.000000, 0.000000, 100.000000, 0.000000, true, 100.000000, 0.082589, 7.366071, 10.000000, true, 11.309524, 10.000000, 10.000000, 0.500000, 10.000000, 0.495112, 10.000000, 10.000000, 0.000000, 0.500000, 0.500000, 1.000000, false, false, false, true, 0.000000, false, 76.923000, 1.000000, false, 23.660714, 0.000000, 100.000000, 0.000000, false, 0.000000, 0.000000, 10.000000, 10.000000, false);
  MakePreset("Washout", 100.000000, false, false, false, true, 32.142857, 10.000000, 10.000000, 0.379464, 10.000000, 0.730733, 8.169643, 7.901786, 0.272321, 1.285714, 0.500000, 1.000000, false, false, false, true, 0.000000, true, 72.905213, 1.000000, false, 100.000000, 0.000000, 100.000000, 0.000000, false, 0.000000, 0.000000, 10.000000, 10.000000, false, 50.000000, 10.000000, 10.000000, 0.500000, 10.000000, 0.450000, 10.000000, 10.000000, 0.000000, 0.500000, 0.500000, 1.000000, false, false, false, true, 0.000000, false, 76.923000, 1.000000, false, 100.000000, 0.000000, 100.000000, 0.000000, false, 0.000000, 0.000000, 10.000000, 10.000000, false);
  MakePreset("Totally Tubular", 61.904762, false, false, false, true, 51.785714, 10.000000, 6.026786, 0.191964, 6.473214, 0.497723, 10.000000, 8.348214, 0.272321, 1.285714, 0.500000, 1.000000, false, false, true, true, 0.000000, false, 76.923070, 1.000000, false, 100.000000, 0.000000, 100.000000, 0.000000, true, 32.589286, 0.049107, 10.000000, 4.285714, true, 32.142857, 6.517857, 8.080357, 0.294643, 10.000000, 0.591530, 7.232143, 10.000000, 0.232143, 1.071429, 0.723214, 1.000000, false, false, false, true, 0.000000, true, 47.458785, 1.000000, false, 100.000000, 0.000000, 58.928571, 0.000000, false, 0.000000, 0.000000, 10.000000, 10.000000, false);

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
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    if ((now->tm_mon == 3) && (now->tm_mday == 1)) {
        pGraphics->OpenURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    }

    //Reset the page to the main page when the UI is created
    currentPage = 0;

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
    Knobs[kPreDelayKnob] = new NeedleKnob(IRECT::MakeXYWH(140, 135, 35, 35), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kPreDelay1, kPreDelay2);

    Knobs[kDiffusionDecayKnob] = new NeedleKnob(IRECT::MakeXYWH(233, 310, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kDiffusionDecay1, kDiffusionDecay2);
    Knobs[kDiffusionDecayKnob]->Bound = 72.6923f;

	Knobs[kModVarianceKnob] = new NeedleKnob(IRECT::MakeXYWH(130, 200, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kModVariance1, kModVariance2);

	Knobs[kVarianceKnob] = new NeedleKnob(IRECT::MakeXYWH(26, 310, 56, 56), NeedleSVG, NeedleBGSVG, NeedleFG1PNG, NeedleFG2PNG, kVariance1, kVariance2);

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

    constexpr double LEDScale = 0.2453054f;

    const ISVG LedOffSVG = pGraphics->LoadSVG(LEDOFF_FN);
    const ISVG LedOn1SVG = pGraphics->LoadSVG(LEDON1_FN);
    const ISVG LedOn2SVG = pGraphics->LoadSVG(LEDON2_FN);
    const ISVG LedOnBothSVG = pGraphics->LoadSVG(LEDONBOTH_FN);

	const ISVG DangerOffSVG = pGraphics->LoadSVG(DANGEROFF_FN);
	const ISVG DangerOnSVG = pGraphics->LoadSVG(DANGERON_FN);

	const ISVG LinkOffSVG = pGraphics->LoadSVG(LINKOFF_FN);
	const ISVG LinkOnSVG = pGraphics->LoadSVG(LINKON_FN);

	const ISVG HelpButtonSVG = pGraphics->LoadSVG(HELPBUTTON_FN);

	const ISVG CopyOffSVG = pGraphics->LoadSVG(COPYOFF_FN);
	const ISVG CopyOnSVG = pGraphics->LoadSVG(COPYON_FN);

	const ISVG SwapOffSVG = pGraphics->LoadSVG(SWAPOFF_FN);
	const ISVG SwapOnSVG = pGraphics->LoadSVG(SWAPON_FN);
   

	//Main page Switches
    Switches[0] = new LEDSwitch(IRECT::MakeXYWH(-11.526f, 404.802f-45, 102, 102), LEDScale, LedOffSVG, LedOnBothSVG, LedOnBothSVG, kFreeze, kFreeze);
    Switches[1] = new LEDSwitch(IRECT::MakeXYWH(-11.526f, 404.802f+30, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kFreeze1, kFreeze2);
    Switches[2] = new LEDSwitch(IRECT::MakeXYWH(-14, 216, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kTunedMode1, kTunedMode2);
    Switches[3] = new LEDSwitch(IRECT::MakeXYWH(228, 216, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kDiffuseInput1, kDiffuseInput2);

    LEDButton* clearButton = new LEDButton(IRECT::MakeXYWH(225.526f, 404.802f + 30, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, [this](IControl* clearControl) {
        if (tank2Selected) {
			clear2 = true;
        }
        else {
			clear1 = true;
        }
        });

    Buttons[0] = clearButton;

	//Global Clear Button
    Buttons[1] = new LEDButton(IRECT::MakeXYWH(225.526f, 404.802f - 45, 102, 102), LEDScale, LedOffSVG, LedOnBothSVG, LedOnBothSVG, [this, clearButton](IControl* clearControl) {
		clear1 = true;
		clear2 = true;
    }, clearButton);

	//Help Button
    Buttons[2] = new LEDButton(IRECT::MakeXYWH(129.5f, 535, 56, 56), 1, HelpButtonSVG, HelpButtonSVG, HelpButtonSVG, [this](IControl* button) {this->GetUI()->OpenURL("https://github.com/rubyswolf/iPlateau/wiki");});

	//Tank Copy Button
    Buttons[3] = new LEDButton(IRECT::MakeXYWH(15, 460, 80, 80), 1, CopyOffSVG, CopyOnSVG, CopyOnSVG, [this](IControl* button) {
		for (int i = kEnable1; i <= k1to2HighDamp; i++) {
			GetParam(i + offset)->Set(GetParam(i)->Value());
		}
		for (int i = 0; i < kNumKnobs; i++) {
            Knobs[i]->SetValue(GetParam(tank2Selected ? Knobs[i]->Param2Idx : Knobs[i]->Param1Idx)->GetNormalized());
            Knobs[i]->SetDirty(true);
		}
        for (int i = 0; i < kNumSwitches; i++) {
			Switches[i]->SetValue(GetParam(tank2Selected ? Switches[i]->Param2Idx : Switches[i]->Param1Idx)->GetNormalized());
            Switches[i]->SetDirty(true);
        }
    });

	//Tank Swap Button
	Buttons[4] = new LEDButton(IRECT::MakeXYWH(220, 460, 80, 80), 1, SwapOffSVG, SwapOnSVG, SwapOnSVG, [this](IControl* button) {
        for (int i = kEnable1; i <= k1to2HighDamp; i++) {
            double temp = GetParam(i)->Value();
			GetParam(i)->Set(GetParam(i + offset)->Value());
			GetParam(i + offset)->Set(temp);
        }
        for (int i = 0; i < kNumKnobs; i++) {
            Knobs[i]->SetValue(GetParam(tank2Selected ? Knobs[i]->Param2Idx : Knobs[i]->Param1Idx)->GetNormalized());
            Knobs[i]->SetDirty(true);
        }
        for (int i = 0; i < kNumSwitches; i++) {
            Switches[i]->SetValue(GetParam(tank2Selected ? Switches[i]->Param2Idx : Switches[i]->Param1Idx)->GetNormalized());
            Switches[i]->SetDirty(true);
        }
    });

	for (int i = 0; i <= 1; i++) {
		pGraphics->AttachControl(Buttons[i]);
	}
    for (int i = 2; i <= 4; i++) {
		pGraphics->AttachControl(Buttons[i]);
		Buttons[i]->Hide(true);
    }


	//Dump Preset Button
    //pGraphics->AttachControl((new LEDButton(IRECT::MakeXYWH(0, 40, 102, 102), LEDScale, LedOffSVG, LedOnBothSVG, LedOnBothSVG, [this](IControl* button) {DumpMakePresetSrc("C:/dev/Plugins/Plateau/Plateau2/preset.txt");})));

    //Save Button
    pGraphics->AttachControl((new LEDButton(IRECT::MakeXYWH(-14, 20, 102, 102), LEDScale, LedOffSVG, LedOnBothSVG, LedOnBothSVG, [this, pGraphics](IControl* button) {
        WDL_String filename;
        WDL_String path;
        pGraphics->PromptForFile(filename, path, EFileAction::Save, "pl2", [this, button](const WDL_String& fileName, const WDL_String& path) {
            if (path.GetLength()) {
                IByteChunk chunk;
                if (SerializeState(chunk)) {
                    FILE* f = fopen(fileName.Get(), "wb");
                    if (f) {
                        fwrite(chunk.GetData(), 1, chunk.Size(), f);
                        fclose(f);
                        button->SetValue(0);
                        button->SetDirty(false);
                    }
                }
            }
        });
    })));

    //Load Button
    pGraphics->AttachControl((new LEDButton(IRECT::MakeXYWH(228, 20, 102, 102), LEDScale, LedOffSVG, LedOnBothSVG, LedOnBothSVG, [this, pGraphics](IControl* button) {
        WDL_String filename;
        WDL_String path;
        pGraphics->PromptForFile(filename, path, EFileAction::Open, "pl2", [this, button](const WDL_String& fileName, const WDL_String& path) {
            FILE* f = fopen(fileName.Get(), "rb");
            if (f) {
                fseek(f, 0, SEEK_END);
                int size = (int)ftell(f);
                fseek(f, 0, SEEK_SET);

                IByteChunk chunk;
                chunk.Resize(size);
                fread(chunk.GetData(), 1, size, f);
                fclose(f);

                UnserializeState(chunk, 0);

                if (GetUI()) GetUI()->SetAllControlsDirty();
                button->SetValue(0);
                button->SetDirty(false);
            }
        });
    })));

	//Tank Enable Switch
    Switches[4] = new LEDSwitch(IRECT::MakeXYWH(106.5f, 112, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kEnable1, kEnable2);
    Switches[4]->SetValue(1);


	for (int i = 0; i <= 4; i++) {
		pGraphics->AttachControl(Switches[i]);
	}

    Switches[5] = new LEDSwitch(IRECT::MakeXYWH(210, 170, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kNesting1, kNesting2);

    //DANGER switch
    Switches[6] = new LEDSwitch(IRECT::MakeXYWH(102, 291, 112, 112), 1, DangerOffSVG, DangerOnSVG, DangerOnSVG, kDanger, kDanger);

    Switches[7] = new LEDSwitch(IRECT::MakeXYWH(3, 170, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, kSoftClip1, kSoftClip2);

	Switches[8] = new LEDSwitch(IRECT::MakeXYWH(102, 418, 112, 112), 1, LinkOffSVG, LinkOnSVG, LinkOnSVG, kLink1to2, kLink1to2);

	//Routing page Switches
	Switches[9] = new LEDSwitch(IRECT::MakeXYWH(106.5, 374, 102, 102), LEDScale, LedOffSVG, LedOn1SVG, LedOn2SVG, k1to2, k2to1);

    for (int i = 5; i <= 9; i++) {
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

	//Update the tank selection incase link changed when the UI was closed
    SelectTank(tank2Selected);
  };
#endif
}

void Plateau2::SelectTank(bool tank2) {
	tank2Selected = tank2;
    bool linkedTank2 = link1to2 ? false : tank2;
    for (int i = kDryKnob; i <= kWetKnob; i++) {
        Knobs[i]->SelectTank(tank2);
    }
    for (int i = kInputLowDampKnob; i <= kVarianceKnob; i++) {
        Knobs[i]->SelectTank(linkedTank2);
    }
    for (int i = kInputKnob; i < kNumKnobs; i++) {
        Knobs[i]->SelectTank(tank2);
    }

    Switches[0]->SelectTank(tank2);
	Switches[1]->SelectTank(tank2);
    Switches[2]->SelectTank(linkedTank2);
    Switches[3]->SelectTank(linkedTank2);
	Switches[4]->SelectTank(tank2);
    Switches[5]->SelectTank(linkedTank2);
	Switches[6]->SelectTank(tank2);
    Switches[7]->SelectTank(linkedTank2);
    Switches[8]->SelectTank(tank2);
    Switches[9]->SelectTank(tank2);

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
    for (int i = kPreDelayKnob; i <= kVarianceKnob; i++) {
        Knobs[i]->Hide(currentPage != 1);
    }
    for (int i = 5; i <= 8; i++) {
        Switches[i]->Hide(currentPage != 1);
    }
    for (int i = 2; i <= 4; i++) {
        Buttons[i]->Hide(currentPage != 1);
    }

	//Routing page
    Switches[9]->Hide(currentPage != 2);

	for (int i = kInputKnob; i <= kPanKnob; i++) {
		Knobs[i]->Hide(currentPage != 2);
	}

    UpdateSendVisibility();
}

void Plateau2::UpdateSendVisibility() {
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

void Plateau2::OnParamChange(int index) {
    if (link1to2) {
        if (index >= kInputLowDamp1 && index <= kSoftClip1 && index != kFreeze1 && index != kClear1) //Tank 1 range
        {
			UpdateParameter(index, index);
			UpdateParameter(index, index + offset); //Copy to tank 2
		}
        else if (!(index >= kInputLowDamp2 && index <= kSoftClip2 && index != kFreeze2 && index != kClear2)) //Not tank 2 range
        {
            UpdateParameter(index, index);
        }
    }
    else {
        UpdateParameter(index, index);
    }
}

void Plateau2::UpdateParameter(int sourceIndex, int targetIndex)
{
        switch (targetIndex) {
        case kDry:
            dryParam = GetParam(kDry)->Value() / 100;
            break;
        case kClear:
            if (GetParam(kClear)->Value() >= 0.5 && lastGlobalClear < 0.5) {
                clear1 = true;
                clear2 = true;
            }
            lastGlobalClear = GetParam(kClear)->Value();
            break;
        case kFreeze:
            reverb1.freeze(GetParam(kFreeze1)->Value() >= 0.5 || GetParam(kFreeze)->Value() >= 0.5);
            reverb2.freeze(GetParam(kFreeze2)->Value() >= 0.5 || GetParam(kFreeze)->Value() >= 0.5);
            break;
        case kLink1to2:
        {
            link1to2 = GetParam(kLink1to2)->Value() >= 0.5;
            if (link1to2) {
                for (int i = kInputLowDamp1; i <= kModVariance1; i++) {
                    UpdateParameter(i, i + offset); //Copy to tank 2
                }
                //Skip Freeze and Clear
                for (int i = kTunedMode1; i <= kSoftClip1; i++) {
                    UpdateParameter(i, i + offset); //Copy to tank 2
                }
            }
            else
            {
                for (int i = kInputLowDamp2; i <= kModVariance1; i++) {
                    UpdateParameter(i, i); //Restore to tank 2
                }
				//Skip Freeze and Clear
				for (int i = kTunedMode2; i <= kSoftClip2; i++) {
					UpdateParameter(i, i); //Restore to tank 2
				}
            }
            if (WindowIsOpen())
            {
                SelectTank(tank2Selected);
            }
            break;
        }
        case kEnable1:
            tank1Enabled = GetParam(kEnable1)->Value() >= 0.5;
            break;
        case kClear1:
            if (GetParam(kClear1)->Value() >= 0.5 && lastClear1 < 0.5) {
                clear1 = true;
            }
            lastClear1 = GetParam(kClear1)->Value();
            break;
        case kFreeze1:
            reverb1.freeze(GetParam(kFreeze1)->Value() >= 0.5 || GetParam(kFreeze)->Value() >= 0.5);
            break;
        case kWet1:
            wet1Param = GetParam(kWet1)->Value() / 100;
            break;
        case kInput1:
            input1Param = GetParam(kInput1)->Value() / 100;
            break;
        case kSoftClip1:
            softClip1Param = GetParam(sourceIndex)->Value() >= 0.5;
            break;
        case kWidth1:
            width1Param = GetParam(kWidth1)->Value() / 100;
            break;
        case kPreDelay1:
            reverb1.setPreDelay(GetParam(sourceIndex)->Value());
            break;
        case kInputLowDamp1:
            reverb1.setInputFilterLowCutoffPitch(10.f - GetParam(sourceIndex)->Value());
            break;
        case kInputHighDamp1:
            reverb1.setInputFilterHighCutoffPitch(GetParam(sourceIndex)->Value());
            break;
        case kSize1:
        case kTunedMode1:
        {
            bool source2 = sourceIndex == kSize2 || sourceIndex == kTunedMode2;
            double size = GetParam(source2 ? kSize2 : kSize1)->Value();
            if (GetParam(source2 ? kTunedMode2 : kTunedMode1)->Value() >= 0.5) {
                reverb1.setTimeScale(0.0025f * powf(2.f, size * 5.f));
            }
            else {
                reverb1.setTimeScale(scale<double>(size * size, 0.f, 1.f, 0.01f, 4.0f));
            }
            break;
        }
        case kDiffusion1:
            reverb1.setTankDiffusion(GetParam(sourceIndex)->Value());
            break;
        case kDecay1:
        {
            double decay = GetParam(sourceIndex)->Value();
            reverb1.setDecay(2 * decay - decay * decay);
            break;
        }
        case kReverbLowDamp1:
            reverb1.setTankFilterLowCutFrequency(10.f - GetParam(sourceIndex)->Value());
            break;
        case kReverbHighDamp1:
            reverb1.setTankFilterHighCutFrequency(GetParam(sourceIndex)->Value());
            break;
        case kModSpeed1:
        {
            double modSpeed = GetParam(sourceIndex)->Value();
            reverb1.setTankModSpeed(modSpeed * modSpeed * 99.f + 1.f);
            break;
        }
        case kModDepth1:
            reverb1.setTankModDepth(GetParam(sourceIndex)->Value());
            break;
        case kModShape1:
            reverb1.setTankModShape(GetParam(sourceIndex)->Value());
            break;
        case kDiffuseInput1:
            reverb1.enableInputDiffusion(GetParam(sourceIndex)->Value() >= 0.5);
            break;
        case kNesting1:
            reverb1.setTankDiffusionNesting(GetParam(sourceIndex)->Value() >= 0.5);
            break;
        case kDiffusionDecay1:
        {
            double scaled = scale<double>(GetParam(sourceIndex)->Value(), 0, 100, 0, 1.3);
            if (!GetParam(kDanger)->Value()) {
                //Clip to safe values
                scaled = clip<double>(scaled, 0.3, 1);
            }
            reverb1.setTankDiffusionDecay(scaled);
            break;
        }
        case kVariance1:
            reverb1.setTankVariance(GetParam(sourceIndex)->Value());
            break;
        case kStereoSource1:
            sourceBalance1 = balanceFactors(GetParam(kStereoSource1)->Value() / 100);
            break;
        case kPan1:
            panBalance1 = balanceFactors(GetParam(kPan1)->Value() / 100);
            break;
        case k1to2:
            send1to2 = tank1Enabled && GetParam(k1to2)->Value() >= 0.5;
            break;
        case k1to2Level:
            level1to2Param = GetParam(k1to2Level)->Value() / 100;
            break;
        case k1to2Delay:
            send1To2Delay.setDelayTime(GetParam(k1to2Delay)->Value() * GetSampleRate());
            break;
        case k1to2LowDamp:
            send1To2HP.setCutoffFreq(pitch2freq(10.f - GetParam(sourceIndex)->Value()));
            break;
        case k1to2HighDamp:
            send1To2LP.setCutoffFreq(pitch2freq(GetParam(sourceIndex)->Value()));
            break;
        case kModVariance1:
            reverb1.setTankModVariance(GetParam(sourceIndex)->Value());
            break;

        case kEnable2:
            tank2Enabled = GetParam(kEnable2)->Value() >= 0.5;
            break;
        case kClear2:
            if (GetParam(kClear2)->Value() >= 0.5 && lastClear2 < 0.5) {
                clear2 = true;
            }
            break;
        case kFreeze2:
            reverb2.freeze(GetParam(kFreeze2)->Value() >= 0.5 || GetParam(kFreeze)->Value() >= 0.5);
            break;
        case kWet2:
            wet2Param = GetParam(kWet2)->Value() / 100;
            break;
        case kInput2:
            input2Param = GetParam(kInput2)->Value() / 100;
            break;
        case kSoftClip2:
            softClip2Param = GetParam(sourceIndex)->Value() >= 0.5;
            break;
        case kWidth2:
            width2Param = GetParam(kWidth2)->Value() / 100;
            break;
        case kPreDelay2:
            reverb2.setPreDelay(GetParam(sourceIndex)->Value());
            break;
        case kInputLowDamp2:
            reverb2.setInputFilterLowCutoffPitch(10.f - GetParam(sourceIndex)->Value());
            break;
        case kInputHighDamp2:
            reverb2.setInputFilterHighCutoffPitch(GetParam(sourceIndex)->Value());
            break;
        case kSize2:
        case kTunedMode2:
        {
            bool source2 = sourceIndex == kSize2 || sourceIndex == kTunedMode2;
            double size = GetParam(source2 ? kSize2 : kSize1)->Value();
            if (GetParam(source2 ? kTunedMode2 : kTunedMode1)->Value() >= 0.5) {
                reverb2.setTimeScale(0.0025f * powf(2.f, size * 5.f));
            }
            else {
                reverb2.setTimeScale(scale<double>(size * size, 0.f, 1.f, 0.01f, 4.0f));
            }
            break;
        }
        case kDiffusion2:
            reverb2.setTankDiffusion(GetParam(sourceIndex)->Value());
            break;
        case kDecay2:
        {
            double decay = GetParam(sourceIndex)->Value();
            reverb2.setDecay(2.f * decay - decay * decay);
            break;
        }
        case kReverbLowDamp2:
            reverb2.setTankFilterLowCutFrequency(10.f - GetParam(sourceIndex)->Value());
            break;
        case kReverbHighDamp2:
            reverb2.setTankFilterHighCutFrequency(GetParam(sourceIndex)->Value());
            break;
        case kModSpeed2:
        {
            double modSpeed = GetParam(sourceIndex)->Value();
            reverb2.setTankModSpeed(modSpeed * modSpeed * 99.f + 1.f);
            break;
        }
        case kModDepth2:
            reverb2.setTankModDepth(GetParam(sourceIndex)->Value());
            break;
        case kModShape2:
            reverb2.setTankModShape(GetParam(sourceIndex)->Value());
            break;
        case kDiffuseInput2:
            reverb2.enableInputDiffusion(GetParam(sourceIndex)->Value() >= 0.5);
            break;
        case kNesting2:
            reverb2.setTankDiffusionNesting(GetParam(sourceIndex)->Value());
            break;
        case kDiffusionDecay2:
        {
            double scaled = scale<double>(GetParam(sourceIndex)->Value(), 0, 100, 0, 1.3);
            if (!GetParam(kDanger)->Value()) {
                //Clip to safe values
                scaled = clip<double>(scaled, 0.3, 1);
            }
            reverb2.setTankDiffusionDecay(scaled);
            break;
        }
        case kVariance2:
            reverb2.setTankVariance(GetParam(sourceIndex)->Value());
            break;
        case kStereoSource2:
            sourceBalance2 = balanceFactors(GetParam(kStereoSource2)->Value() / 100);
            break;
        case kPan2:
            panBalance2 = balanceFactors(GetParam(kPan2)->Value() / 100);
            break;
        case k2to1:
            send2to1 = tank2Enabled && GetParam(k2to1)->Value() && GetParam(kDanger)->Value() >= 0.5;
            break;
        case k2to1Level:
            level2to1Param = GetParam(k2to1Level)->Value() / 100;
            break;
        case k2to1Delay:
            send2To1Delay.setDelayTime(GetParam(k2to1Delay)->Value() * GetSampleRate());
            break;
        case k2to1LowDamp:
            send2To1HP.setCutoffFreq(pitch2freq(10.f - GetParam(sourceIndex)->Value()));
            break;
        case k2to1HighDamp:
            send2To1LP.setCutoffFreq(pitch2freq(GetParam(sourceIndex)->Value()));
            break;
        case kModVariance2:
            reverb2.setTankModVariance(GetParam(sourceIndex)->Value());
            break;

        case kDanger:
            if (GetParam(kDanger)->Value() <= 0.5) {
                //Reset the plugin when danger is turned off for safety
                clear1 = true;
                clear2 = true;
            }
            if (WindowIsOpen()) {
                UpdateSendVisibility();
                Knobs[kDiffusionDecayKnob]->Bound = GetParam(kDanger)->Value() ? 135.f : 72.6923f;

                SetParameterValue(kDiffusionDecay1, clip<double>(GetParam(kDiffusionDecay1)->Value(), 23.0769, 76.92307) / 100);
                SetParameterValue(kDiffusionDecay2, clip<double>(GetParam(kDiffusionDecay2)->Value(), 23.0769, 76.92307) / 100);

                Knobs[kDiffusionDecayKnob]->SetValue(GetParam(tank2Selected ? kDiffusionDecay2 : kDiffusionDecay1)->Value() / 100);
                Knobs[kDiffusionDecayKnob]->SetDirty(false);
            }
            break;
        }
}

bool Plateau2::SerializeState(IByteChunk& chunk) const
{
    return SerializeParams(chunk);
}

int Plateau2::UnserializeState(const IByteChunk& chunk, int pos)
{
    pos = UnserializeParams(chunk, pos);
    if (GetUI()) GetUI()->SetAllControlsDirty();
    return pos;
}

#if IPLUG_DSP
void Plateau2::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const int nChans = NOutChansConnected();
  
  for (int s = 0; s < nFrames; s++) {
        outputs[0][s] = inputs[0][s] * dryParam;
        if (nChans > 1)
        {
            outputs[1][s] = inputs[1][s] * dryParam;
        }

        if (tank1Enabled) {
            if (clear1) {
                if (!fadeOut1 && !fadeIn1) {
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
                    envelope1._value = 1.f;
                    clear1 = false;
                }
            }
            envelope1.process();

            reverb1.process((double)(std::get<0>(sourceBalance1) * envelope1._value * inputs[0][s] * input1Param), (double)(std::get<1>(sourceBalance1) * envelope1._value * (inputs[nChans > 1 ? 1 : 0][s] * input1Param)), (send2to1 ? (envelope1._value * level2to1Param * reverbOut2) : 0));

            std::tuple<double,double> out = seperation(reverb1.getLeftOutput()*envelope1._value, reverb1.getRightOutput()*envelope1._value, width1Param);
            out = { std::get<0>(panBalance1) * std::get<0>(out), std::get<1>(panBalance1)* std::get<1>(out) };

            outputs[0][s] += std::get<0>(out) * wet1Param;

			if (softClip1Param) {
				outputs[0][s] = std::tanh(outputs[0][s]);
			}

            if (nChans > 1)
            {
                outputs[1][s] += std::get<1>(out) * wet1Param;
                if (softClip1Param) {
                    outputs[1][s] = std::tanh(outputs[1][s]);
                }
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
            if (clear2) {
                if (!fadeOut2 && !fadeIn2) {
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
                    envelope2._value = 1.f;
                    clear2 = false;
                }
            }
            envelope2.process();

            reverb2.process((double)(std::get<0>(sourceBalance2)* envelope2._value* inputs[0][s] * input2Param), (double)(std::get<1>(sourceBalance2)* envelope2._value* (inputs[nChans > 1 ? 1 : 0][s] * input2Param)), (send1to2 ? (envelope2._value * level1to2Param * reverbOut1) : 0));


            std::tuple<double, double> out = seperation(reverb2.getLeftOutput()*envelope2._value, reverb2.getRightOutput()*envelope2._value, width2Param);
            out = { std::get<0>(panBalance2) * std::get<0>(out), std::get<1>(panBalance2) * std::get<1>(out) };

            outputs[0][s] += std::get<0>(out) * wet2Param;

			if (softClip2Param) {
				outputs[0][s] = std::tanh(outputs[0][s]);
			}

            if (nChans > 1)
            {
                outputs[1][s] += std::get<1>(out) * wet2Param;
				if (softClip2Param) {
					outputs[1][s] = std::tanh(outputs[1][s]);
				}
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
