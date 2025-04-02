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
