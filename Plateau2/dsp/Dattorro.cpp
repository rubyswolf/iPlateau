#include "Dattorro.hpp"
#include <cassert>
#include <algorithm>

Dattorro1997Tank::Dattorro1997Tank()
{
    timePadding = 16;

    leftOutDCBlock.setCutoffFreq(20.0);
    rightOutDCBlock.setCutoffFreq(20.0);

    lfo1.setFrequency(lfo1Freq);
    lfo2.setFrequency(lfo2Freq);
    lfo3.setFrequency(lfo3Freq);
    lfo4.setFrequency(lfo4Freq);

    lfo1.setRevPoint(0.5);
    lfo2.setRevPoint(0.5);
    lfo3.setRevPoint(0.5);
    lfo4.setRevPoint(0.5);
}

void Dattorro1997Tank::process(const double leftIn, const double rightIn,
                               double* leftOut, double* rightOut) {
    tickApfModulation();

    decay = frozen ? 1.0 : decayParam;

    leftSum += leftIn;
    rightSum += rightIn;

    leftApf1.input = leftSum;
    leftDelay1.input = leftApf1.process();
    leftDelay1.process();
    leftHighCutFilter.input = leftDelay1.output;
    leftLowCutFilter.input = leftHighCutFilter.process();
    leftApf2.input = (leftDelay1.output * (1.0 - fade) + leftLowCutFilter.process() * fade) * decay;
    leftDelay2.input = leftApf2.process();
    leftDelay2.process();

    rightApf1.input = rightSum;
    rightDelay1.input = rightApf1.process();
    rightDelay1.process();
    rightHighCutFilter.input = rightDelay1.output;
    rightLowCutFilter.input =  rightHighCutFilter.process();
    rightApf2.input = (rightDelay1.output * (1.0 - fade) + rightLowCutFilter.process() * fade) * decay;
    rightDelay2.input = rightApf2.process();
    rightDelay2.process();

    rightSum = leftDelay2.output * decay;
    leftSum = rightDelay2.output * decay;

    leftOutDCBlock.input = leftApf1.output;
    leftOutDCBlock.input += leftDelay1.tap(scaledOutputTaps[L_DELAY_1_L_TAP_1]);
    leftOutDCBlock.input += leftDelay1.tap(scaledOutputTaps[L_DELAY_1_L_TAP_2]);
    leftOutDCBlock.input -= leftApf2.delay1.tap(scaledOutputTaps[L_APF_2_L_TAP]);
    leftOutDCBlock.input -= leftApf2.delay2.tap(scaledOutputTaps[L_APF_2_L_TAP]);
    leftOutDCBlock.input += leftDelay2.tap(scaledOutputTaps[L_DELAY_2_L_TAP]);
    leftOutDCBlock.input -= rightDelay1.tap(scaledOutputTaps[R_DELAY_1_L_TAP]);
    leftOutDCBlock.input -= rightApf2.delay1.tap(scaledOutputTaps[R_APF_2_L_TAP]);
    leftOutDCBlock.input -= rightApf2.delay2.tap(scaledOutputTaps[R_APF_2_L_TAP]);
    leftOutDCBlock.input -= rightDelay2.tap(scaledOutputTaps[R_DELAY_2_L_TAP]);

    rightOutDCBlock.input = rightApf1.output;
    rightOutDCBlock.input += rightDelay1.tap(scaledOutputTaps[R_DELAY_1_R_TAP_1]);
    rightOutDCBlock.input += rightDelay1.tap(scaledOutputTaps[R_DELAY_1_R_TAP_2]);
    rightOutDCBlock.input -= rightApf2.delay1.tap(scaledOutputTaps[R_APF_2_R_TAP]);
    rightOutDCBlock.input -= rightApf2.delay2.tap(scaledOutputTaps[R_APF_2_R_TAP]);
    rightOutDCBlock.input += rightDelay2.tap(scaledOutputTaps[R_DELAY_2_R_TAP]);
    rightOutDCBlock.input -= leftDelay1.tap(scaledOutputTaps[L_DELAY_1_R_TAP]);
    rightOutDCBlock.input -= leftApf2.delay1.tap(scaledOutputTaps[L_APF_2_R_TAP]);
    rightOutDCBlock.input -= leftApf2.delay2.tap(scaledOutputTaps[L_APF_2_R_TAP]);
    rightOutDCBlock.input -= leftDelay2.tap(scaledOutputTaps[L_DELAY_2_R_TAP]);

    *leftOut = leftOutDCBlock.process() * 0.5;
    *rightOut = rightOutDCBlock.process() * 0.5;

    fade += fadeStep * fadeDir;
    fade = (fade < 0.0) ? 0.0 : ((fade > 1.0) ? 1.0 : fade);

    assert(fade >= 0.0);
    assert(fade <= 1.0);
}

void Dattorro1997Tank::freeze(bool freezeFlag) {
    frozen = freezeFlag;
    if (frozen) {
        fadeDir = -1.0;
        decay = 1.0;
    }
    else {
        fadeDir = 1.0;
        decay = decayParam;
    }
}

void Dattorro1997Tank::setSampleRate(const double newSampleRate) {
    sampleRate = newSampleRate;
	assert(sampleRate >= 1.0f);

    sampleRateScale = sampleRate / dattorroSampleRate;

    fadeStep = 1.0 / sampleRate;

    leftOutDCBlock.setSampleRate(sampleRate);
    rightOutDCBlock.setSampleRate(sampleRate);

    rescaleTapTimes();
    initialiseDelaysAndApfs();
    setTimeScale(timeScale);
    clear();
}

void Dattorro1997Tank::setTimeScale(const double newTimeScale) {
    timeScale = newTimeScale;
    timeScale = timeScale < minTimeScale ? minTimeScale : timeScale;

    rescaleApfAndDelayTimes();
}

void Dattorro1997Tank::setVariance(const double newVariance) {
	variance = newVariance;

    rescaleApfAndDelayTimes();
}

void Dattorro1997Tank::setDecay(const double newDecay) {
    decayParam = newDecay;
}

void Dattorro1997Tank::setModSpeed(const double newModSpeed) {
	modSpeed = newModSpeed;
	updateLFOSpeeds();
}

void Dattorro1997Tank::setModVariance(const double newModVariance) {
	modVariance = newModVariance;
	lfo1.setPhase(0);
	lfo2.setPhase(0);
	lfo3.setPhase(0);
	lfo4.setPhase(0);
	updateLFOSpeeds();
}

void Dattorro1997Tank::updateLFOSpeeds() {
	double avg1 = (lfo1Freq + lfo3Freq) / 2;
	double avg2 = (lfo2Freq + lfo4Freq) / 2;
	lfo1.setFrequency(linterp<double>(avg1, lfo1Freq, modVariance) * modSpeed);
	lfo2.setFrequency(linterp<double>(avg2, lfo2Freq, modVariance) * modSpeed);
	lfo3.setFrequency(linterp<double>(avg1, lfo3Freq, modVariance) * modSpeed);
	lfo4.setFrequency(linterp<double>(avg2, lfo4Freq, modVariance) * modSpeed);
}

void Dattorro1997Tank::setModDepth(const double newModDepth) {
    modDepth = newModDepth;
    lfoExcursion = newModDepth * lfoMaxExcursion * sampleRateScale;
}

void Dattorro1997Tank::setModShape(const double shape) {
    lfo1.setRevPoint(shape);
    lfo2.setRevPoint(shape);
    lfo3.setRevPoint(shape);
    lfo4.setRevPoint(shape);
}

void Dattorro1997Tank::setHighCutFrequency(const double frequency) {
    leftHighCutFilter.setCutoffFreq(frequency);
    rightHighCutFilter.setCutoffFreq(frequency);
}

void Dattorro1997Tank::setLowCutFrequency(const double frequency) {
    leftLowCutFilter.setCutoffFreq(frequency);
    rightLowCutFilter.setCutoffFreq(frequency);
}

void Dattorro1997Tank::setDiffusion(const double diffusion) {
    assert(diffusion >= 0.0 && diffusion <= 10.0);

    double diffusion1 = scale(diffusion, 0.0, 10.0, 0.0, maxDiffusion1);
    double diffusion2 = scale(diffusion, 0.0, 10.0, 0.0, maxDiffusion2);

    leftApf1.setGain(-diffusion1, -diffusion1);
    leftApf2.setGain(diffusion2, diffusion2);
    rightApf1.setGain(-diffusion1, -diffusion1);
    rightApf2.setGain(diffusion2, diffusion2);
}

void Dattorro1997Tank::setDiffusionNesting(const bool nesting) {
	leftApf1.nested = nesting;
	leftApf2.nested = nesting;
	rightApf1.nested = nesting;
	rightApf2.nested = nesting;

	leftApf1.delay2.clear();
	leftApf2.delay2.clear();
	rightApf1.delay2.clear();
	rightApf2.delay2.clear();
}

void Dattorro1997Tank::setDiffusionDecay(const double diffusionDecay) {
	leftApf1.setDecay(diffusionDecay, diffusionDecay);
	leftApf2.setDecay(diffusionDecay, diffusionDecay);
	rightApf1.setDecay(diffusionDecay, diffusionDecay);
	rightApf2.setDecay(diffusionDecay, diffusionDecay);
}

void Dattorro1997Tank::clear() {
    leftApf1.clear();
    leftDelay1.clear();
    leftHighCutFilter.clear();
    leftLowCutFilter.clear();
    leftApf2.clear();
    leftDelay2.clear();

    rightApf1.clear();
    rightDelay1.clear();
    rightHighCutFilter.clear();;
    rightLowCutFilter.clear();
    rightApf2.clear();
    rightDelay2.clear();

    leftOutDCBlock.clear();
    rightOutDCBlock.clear();

    leftSum = 0.0;
    rightSum = 0.0;
}

void Dattorro1997Tank::initialiseDelaysAndApfs() {
    auto maxScaledOutputTap = *std::max_element(scaledOutputTaps.begin(),
                                                scaledOutputTaps.end());
    auto calcMaxTime = [&](double delayTime) -> long {
        return (long)(sampleRateScale * (delayTime * 4 + 
                                         maxScaledOutputTap + timePadding));
    };

    const long kLeftApf1MaxTime = calcMaxTime(std::max({ leftApf1Time, (leftApf1Time + rightApf1Time) / 2 }));
    const long kLeftDelay1MaxTime = calcMaxTime(std::max({ leftDelay1Time, (leftDelay1Time + rightDelay1Time) / 2 }));
    const long kLeftApf2MaxTime = calcMaxTime(std::max({ leftApf2Time, (leftApf2Time + rightApf2Time) / 2 }));
    const long kLeftDelay2MaxTime = calcMaxTime(std::max({ leftDelay2Time, (leftDelay2Time + rightDelay2Time) / 2 }));
    const long kRightApf1MaxTime = calcMaxTime(std::max({ rightApf1Time, (leftApf1Time + rightApf1Time) / 2 }));
    const long kRightDelay1MaxTime = calcMaxTime(std::max({ rightDelay1Time, (leftDelay1Time + rightDelay1Time) / 2 }));
    const long kRightApf2MaxTime = calcMaxTime(std::max({ rightApf2Time, (leftApf2Time + rightApf2Time) / 2 }));
    const long kRightDelay2MaxTime = calcMaxTime(std::max({ rightDelay2Time, (leftDelay2Time + rightDelay2Time) / 2 }));

    leftApf1 = AllpassFilter<double>(kLeftApf1MaxTime);
    leftDelay1 = InterpDelay<double>(kLeftDelay1MaxTime);
    leftApf2 = AllpassFilter<double>(kLeftApf2MaxTime);
    leftDelay2 = InterpDelay<double>(kLeftDelay2MaxTime);
    rightApf1 = AllpassFilter<double>(kRightApf1MaxTime);
    rightDelay1 = InterpDelay<double>(kRightDelay1MaxTime);
    rightApf2 = AllpassFilter<double>(kRightApf2MaxTime);
    rightDelay2 = InterpDelay<double>(kRightDelay2MaxTime);
}

void Dattorro1997Tank::tickApfModulation() {
    double scaleFactor = timeScale;
	double avg1 = (scaledLeftApf1Time + scaledRightApf1Time) / 2;
	double avg2 = (scaledLeftApf2Time + scaledRightApf2Time) / 2;
    leftApf1.delay1.setDelayTime(lfo1.process() * lfoExcursion * scaleFactor + linterp<double>(avg1, scaledLeftApf1Time, variance));
    leftApf2.delay1.setDelayTime(lfo2.process() * lfoExcursion * scaleFactor + linterp<double>(avg2, scaledLeftApf2Time, variance));
    rightApf1.delay1.setDelayTime(lfo3.process() * lfoExcursion * scaleFactor + linterp<double>(avg1, scaledRightApf1Time, variance));
    rightApf2.delay1.setDelayTime(lfo4.process() * lfoExcursion * scaleFactor + linterp<double>(avg2, scaledRightApf2Time, variance));

    leftApf1.delay2.setDelayTime(lfo1.process() * lfoExcursion * scaleFactor + linterp<double>(avg1, scaledLeftApf1Time, variance));
    leftApf2.delay2.setDelayTime(lfo2.process() * lfoExcursion * scaleFactor + linterp<double>(avg2, scaledLeftApf2Time, variance));
    rightApf1.delay2.setDelayTime(lfo3.process() * lfoExcursion * scaleFactor + linterp<double>(avg1, scaledRightApf1Time, variance));
    rightApf2.delay2.setDelayTime(lfo4.process() * lfoExcursion * scaleFactor + linterp<double>(avg2, scaledRightApf2Time, variance));
}

void Dattorro1997Tank::rescaleApfAndDelayTimes() {
    double scaleFactor = timeScale * sampleRateScale;

    scaledLeftApf1Time = leftApf1Time * scaleFactor;
    scaledLeftDelay1Time = leftDelay1Time * scaleFactor;
    scaledLeftApf2Time = leftApf2Time * scaleFactor;
    scaledLeftDelay2Time = leftDelay2Time * scaleFactor;

    scaledRightApf1Time = rightApf1Time * scaleFactor;
    scaledRightDelay1Time = rightDelay1Time * scaleFactor;
    scaledRightApf2Time = rightApf2Time * scaleFactor;
    scaledRightDelay2Time = rightDelay2Time * scaleFactor;

	double avg1 = (scaledLeftDelay1Time + scaledRightDelay1Time) / 2;
	double avg2 = (scaledLeftDelay2Time + scaledRightDelay2Time) / 2;

    leftDelay1.setDelayTime(linterp<double>(avg1, scaledLeftDelay1Time, variance));
    leftDelay2.setDelayTime(linterp<double>(avg2, scaledLeftDelay2Time, variance));
    rightDelay1.setDelayTime(linterp<double>(avg1, scaledRightDelay1Time, variance));
    rightDelay2.setDelayTime(linterp<double>(avg2, scaledRightDelay2Time, variance));
}

void Dattorro1997Tank::rescaleTapTimes() {
    for (size_t i = 0; i < scaledOutputTaps.size(); ++i) {
        scaledOutputTaps[i] = (long)((double)kOutputTaps[i] * sampleRateScale);
    }
}

Dattorro::Dattorro()
    : tank()
{
}

void Dattorro::process(double leftInput, double rightInput, double sent) {
    leftInputDCBlock.input = leftInput;
    rightInputDCBlock.input = rightInput;
    inputLpf.setCutoffFreq(inputHighCut);
    inputHpf.setCutoffFreq(inputLowCut);
    inputLpf.input = leftInputDCBlock.process() + rightInputDCBlock.process();
    inputHpf.input = inputLpf.process();
    inputHpf.process();
    preDelay.input = inputHpf.output;
    preDelay.process();
	preDelay.output += sent;
    inApf1.input = preDelay.output;
    inApf2.input = inApf1.process();
    inApf3.input = inApf2.process();
    inApf4.input = inApf3.process();
    tankFeed = preDelay.output * (1.0 - diffuseInput) + inApf4.process() * diffuseInput;

    tank.process(tankFeed, tankFeed, &leftOut, &rightOut);
}

void Dattorro::clear() {
    leftInputDCBlock.clear();
    rightInputDCBlock.clear();

    inputLpf.clear();
    inputHpf.clear();
    preDelay.clear();
    inApf1.clear();
    inApf2.clear();
    inApf3.clear();
    inApf4.clear();

    tank.clear();
}

void Dattorro::setTimeScale(double timeScale) {
    tank.setTimeScale(timeScale);
}

void Dattorro::setTankVariance(double variance) {
	tank.setVariance(variance);
}

void Dattorro::setPreDelay(double t) {
    preDelayTime = t;
    preDelay.setDelayTime(preDelayTime * sampleRate);
}

void Dattorro::setSampleRate(double newSampleRate) {
    assert(newSampleRate > 0.);

    sampleRate = newSampleRate;

    preDelay = InterpDelay<double>(std::ceil(sampleRate/2)+1, 0);

    inputLpf = OnePoleLPFilter(22000.0);
    inputHpf = OnePoleHPFilter(0.0);

    inApf1 = AllpassFilter<double>(dattorroScale(8 * kInApf1Time), dattorroScale(kInApf1Time), inputDiffusion1);
    inApf2 = AllpassFilter<double>(dattorroScale(8 * kInApf2Time), dattorroScale(kInApf2Time), inputDiffusion1);
    inApf3 = AllpassFilter<double>(dattorroScale(8 * kInApf3Time), dattorroScale(kInApf3Time), inputDiffusion2);
    inApf4 = AllpassFilter<double>(dattorroScale(8 * kInApf4Time), dattorroScale(kInApf4Time), inputDiffusion2);

    tank.setSampleRate(sampleRate);
    dattorroScaleFactor = sampleRate / dattorroSampleRate;
    setPreDelay(preDelayTime);
    inApf1.delay1.setDelayTime(dattorroScale(kInApf1Time));
    inApf2.delay1.setDelayTime(dattorroScale(kInApf2Time));
    inApf3.delay1.setDelayTime(dattorroScale(kInApf3Time));
    inApf4.delay1.setDelayTime(dattorroScale(kInApf4Time));

	inApf1.delay2.setDelayTime(dattorroScale(kInApf1Time));
	inApf2.delay2.setDelayTime(dattorroScale(kInApf2Time));
	inApf3.delay2.setDelayTime(dattorroScale(kInApf3Time));
	inApf4.delay2.setDelayTime(dattorroScale(kInApf4Time));

    leftInputDCBlock.setSampleRate(sampleRate);
    rightInputDCBlock.setSampleRate(sampleRate);
    inputLpf.setSampleRate(sampleRate);
    inputHpf.setSampleRate(sampleRate);

    clear();
}

void Dattorro::freeze(bool freezeFlag) {
    tank.freeze(freezeFlag);
}

void Dattorro::setInputFilterLowCutoffPitch(double pitch) {
    inputLowCut = pitch2freq(pitch);
}

void Dattorro::setInputFilterHighCutoffPitch(double pitch) {
    inputHighCut = pitch2freq(pitch);
}

void Dattorro::enableInputDiffusion(bool enable) {
    diffuseInput = enable ? 1.0 : 0.0;
}

void Dattorro::setDecay(double newDecay) {
    decay = newDecay;
    //assert(decay <= 1.0);
    tank.setDecay(decay);
}

void Dattorro::setTankDiffusion(const double diffusion) {
    tank.setDiffusion(diffusion);
}

void Dattorro::setTankDiffusionNesting(const bool nesting) {
	tank.setDiffusionNesting(nesting);
}
void Dattorro::setTankDiffusionDecay(const double diffusionDecay) {
	tank.setDiffusionDecay(diffusionDecay);
}

void Dattorro::setTankFilterHighCutFrequency(const double pitch) {
    tank.setHighCutFrequency(pitch2freq(pitch));
}

void Dattorro::setTankFilterLowCutFrequency(const double pitch) {
    tank.setLowCutFrequency(pitch2freq(pitch));
}

void Dattorro::setTankModSpeed(const double modSpeed) {
    tank.setModSpeed(modSpeed);
}

void Dattorro::setTankModDepth(const double modDepth) {
    tank.setModDepth(modDepth);
}

void Dattorro::setTankModShape(const double modShape) {
    tank.setModShape(modShape);
}

void Dattorro::setTankModVariance(const double variance) {
	tank.setModVariance(variance);
}

double Dattorro::getLeftOutput() const {
    return leftOut;
}

double Dattorro::getRightOutput() const {
    return rightOut;
}

double Dattorro::dattorroScale(double delayTime) {
    return delayTime * dattorroScaleFactor;
}

