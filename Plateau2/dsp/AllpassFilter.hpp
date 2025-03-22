/**
 * @file AllpassFilter.hpp
 * @author Dale Johnson
 * @date ...uhhh
 */

#pragma once
#include "InterpDelay.hpp"
#include <cassert>

template<class T>
class AllpassFilter {
public:
    AllpassFilter() {
        clear();
        gain = 0;
    }

    AllpassFilter(long maxDelay, long initDelay = 0, T gain = 0) {
        clear();
        delay = InterpDelay<T>(maxDelay, initDelay);
        this->gain = gain;
    }

    T inline process() {
        //Note that negative gain does something

        //Feedback into delay buffer based on gain
        _inSum = input + delay.output * gain;

        //output is the delay output subtract the feedback input
        output = delay.output - _inSum * gain;

        //feed the next sample into the delay
        delay.input = _inSum;

        //proccess the delay sample
        delay.process();

        return output;
    }

    void clear() {
        input = 0;
        output = 0;
        _inSum = 0;
        _outSum = 0;
        delay.clear();
    }

    void setGain(const T newGain) {
        assert(newGain >= -1.0);
        assert(newGain <= 1.0);

        gain = newGain;
    }


    //init signal IO
    T input;
    T output;

    //Create an interpolating delay called delay
    InterpDelay<T> delay;

private:
    T gain;
    T _inSum;
    T _outSum;
};

template<class T>
class NestedAllPassType1 {
public:
    NestedAllPassType1() {
        gain1 = 0;
        gain2 = 0;
        decay1 = 0;
        decay2 = 0;
        clear();
    }

    NestedAllPassType1(long maxDelay, long delayTime1, long delayTime2) {
        delay1 = InterpDelay<T>(maxDelay, delayTime1);
        delay2 = InterpDelay<T>(maxDelay, delayTime2);
        gain1 = 0;
        gain2 = 0;
        decay1 = 0;
        decay2 = 0;
        clear();
    }

    T inline process() {
        _inSum1 = input + delay1.output * gain1;
        _inSum2 = _inSum1 + delay2.output * gain2;
        delay2.input = _inSum2;
        delay1.input = delay2.output * decay2 - _inSum2 * gain2;
        output = delay1.output * decay1 - _inSum1 * gain1;
        delay1.process();
        delay2.process();
        return output;
    }

    void clear() {
        input = 0;
        output = 0;

        _inSum1 = 0;
        _inSum2 = 0;

        delay1.clear();
        delay2.clear();
    }

    //IO
    T input;
    T output;

    //2 gains
    T gain1, gain2;

    //2 decays
    T decay1, decay2;

    //2 delays
    InterpDelay<T> delay1, delay2;
private:
    T _inSum1, _inSum2;
};
