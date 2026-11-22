#pragma once
#include <cstdint>
#include <string>
#include <cmath>

#define _TAU 6.283185307179586

//Linearly interpolates from a to b for parameter f from 0 to 1
template<typename T>
T linterp(T a, T b, T f) {
    return a + f * (b - a);
}

template<typename T>
T clip(T a, T min, T max) {
    return a < min ? min : (a > max ? max : a);
}

template<typename T>
class SoftClipProcessor {
public:
    SoftClipProcessor() { setSampleRate(44100.0); }

    void setSampleRate(double sampleRate) {
        constexpr double dcCutoff = 5.0;
        if (sampleRate <= 0.0)
            sampleRate = 44100.0;
        mDCPole = static_cast<T>(std::exp(-_TAU * dcCutoff / sampleRate));
        mDCGain = static_cast<T>(0.5) * (static_cast<T>(1) + mDCPole);
        clear();
    }

    void clear() {
        mPreviousEvenResidual = static_cast<T>(0);
        mPreviousDCOutput = static_cast<T>(0);
    }

    T process(T input, bool enabled = true) {
        // This bounded series generates H2 at -75 dB and each following even
        // harmonic at 0.1 times the previous amplitude (-20 dB per order).
        constexpr T evenHarmonicRatio = static_cast<T>(0.1);
        constexpr T secondHarmonicAmplitude = static_cast<T>(0.00017779323093966893);
        constexpr T zeroInputSeries = static_cast<T>(1) / (static_cast<T>(1) - evenHarmonicRatio);
        const T cos2 = static_cast<T>(1) - static_cast<T>(2) * input * input;
        const T series = (cos2 - evenHarmonicRatio)
            / (static_cast<T>(1) - static_cast<T>(2) * evenHarmonicRatio * cos2
                + evenHarmonicRatio * evenHarmonicRatio);
        const T evenResidual = secondHarmonicAmplitude * (series - zeroInputSeries);

        // Asymmetric distortion creates DC. Remove it from the residual only,
        // preserving the clean and odd-harmonic paths exactly.
        const T dcBlockedResidual = mDCGain * (evenResidual - mPreviousEvenResidual)
            + mDCPole * mPreviousDCOutput;
        mPreviousEvenResidual = evenResidual;
        mPreviousDCOutput = dcBlockedResidual;

        if (!enabled)
            return input;

        // Keep the calibrated tanh residual for the existing odd harmonics.
        constexpr T oddHarmonicMix = static_cast<T>(0.0010364515875936784);
        const T oddOutput = input + oddHarmonicMix * (std::tanh(input) - input);
        return oddOutput + dcBlockedResidual;
    }

private:
    T mDCPole = static_cast<T>(0);
    T mDCGain = static_cast<T>(1);
    T mPreviousEvenResidual = static_cast<T>(0);
    T mPreviousDCOutput = static_cast<T>(0);
};

template<typename T>
T scale(T a, T inMin, T inMax, T outMin, T outMax) {
    return (a - inMin)/(inMax - inMin) * (outMax - outMin) + outMin;
}

template<typename T>
T semitone(T x) {
    return ((int)(x * 12)) * 0.0833333f;
}

std::tuple<double, double> balanceFactors(double pan) {
    //Circular Equal Power Panning from pan -1 to 1
    return {
        std::cos((pan + 1) * _TAU / 8),
        std::sin((pan + 1) * _TAU / 8)
    };
}


std::tuple<double, double> seperation(double left, double right, double width) {
    double mid = (left + right) * 0.5;  // Mid (Mono)
    double side = (left - right) * 0.5;  // Side (Stereo Width)

    side *= width; // Adjust stereo width (1.0 = original, 0.0 = mono, >1.0 = widened)

    double newLeft = mid + side;
    double newRight = mid - side;

    return { newLeft, newRight };
}

float pitch2freq(const double pitch) {
    return 440.0 * std::pow(2.0, pitch - 5.0);
}

uint32_t mwcRand(uint32_t& w, uint32_t& z);

std::string extractDirectoryFromFilePath(const std::string& filepath); 
